// $Id$
//*************************************************************************
//* --------------------
//* J4IR
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*     2005/07/16  A.Miyamoto  Modified to include GLD IR
//*************************************************************************

#include "J4IR.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "J4UnionSolid.hh"
#include <cmath>

#include "J4IRQMField.hh"

#include "J4ParameterList.hh"
#include "J4ParameterTable.hh"

#include "J4IRBPIP.hh"
#include "J4IRBPMiddle.hh"

#include "J4IRCH2Mask.hh"

#include "J4IRBCAL.hh"
#include "J4IRFCAL.hh"
#include "J4IRWMask3.hh"
#include "J4IRTubs.hh"
#include "J4IRCons.hh"
#include "J4IRSlantTubs.hh"

#include "J4OptDet.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IR::fName("IR");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IR::J4IR(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno ) :
            J4VIRAcceleratorComponent( fName, parent, nclones,
                                    nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IR::~J4IR()
{
    std::vector<J4VComponent*>::iterator iv;
    for( iv=fComponents.begin() ; iv!=fComponents.end(); iv++ ) {
      if( Deregister(*iv) ) { delete *iv; }
    }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IR::Assemble() 
{   
  if(!GetLV()){

    J4ParameterList   *pl = J4ParameterList::GetInstance();

    G4int nsolids = pl->GetIRNSolids();
    G4String bpname=GetName()+".Center";
    G4VSolid *lastsolid=new G4Tubs(bpname, 0, pl->GetIRREdges(0), pl->GetIRZEdges(0), 0, 2*M_PI);

    G4VSolid *tmpsolid=0;
    G4String blank;

    for(int i=1;i<nsolids;i++) {
      for(int j=0;j<2;j++) {
        G4double hzlen=(pl->GetIRZEdges(i) - pl->GetIRZEdges(i-1))*0.5;
        std::ostringstream sname; 
        sname << GetName() << ".SolidTemp" << i << "-" << j << std::ends;
        if( pl->GetIRShapes(i) == 0 ) {
          tmpsolid = new G4Tubs(sname.str(), 0, pl->GetIRREdges(i-1), hzlen, 0, 2*M_PI);
         }
        else {
          if( j == 0 ) {
  	    tmpsolid=new G4Cons(sname.str(), 0, pl->GetIRREdges(i-1),
			0, pl->GetIRREdges(i), hzlen, 0, 2*M_PI);
          }
	    else {
  	    tmpsolid=new G4Cons(sname.str(), 0, pl->GetIRREdges(i),
			0, pl->GetIRREdges(i-1), hzlen, 0, 2*M_PI);
	    }
        
      }
        G4double  zpos = pl->GetIRZEdges(i-1) + hzlen ;
	if ( j == 1 ) zpos *= -1 ;
        G4ThreeVector tmptrans(0, 0, zpos);
        std::ostringstream sname2;
        sname2 << GetName() ;
        if( !( i == nsolids-1 && j == 1 ) ) { 
          sname2 << ".SolidJoin" << i << "-" << j << std::ends;
          }
        G4VSolid *irjoin = new J4UnionSolid(sname2.str(), lastsolid, tmpsolid, 0, tmptrans);
        lastsolid = irjoin;
      }
    }

//    J4IRParameterList* list = OpenParameterList();
//    J4IRWMaskParameterList* wlist = J4IRWMaskParameterList::GetInstance();

    Register(lastsolid);
    SetSolid(lastsolid);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    G4String material = J4ParameterTable::GetValue("J4IR.Material","vacuum");
    G4double maxTime = J4ParameterTable::GetValue("J4IR.UserMaxTime",1000.0)*nanosecond;
    MakeLVWith(OpenMaterialStore()->Order(material), new G4UserLimits(DBL_MAX,DBL_MAX,maxTime));
    
    // SetVisAttribute ---------------
    G4bool visatt = J4ParameterTable::GetValue("J4IR.VisAtt",true);
    std::vector<double> col=J4ParameterTable::GetDValue("J4IR.Color","0.5 0.5 0.5 0.0",4);
    G4Color icolor(col[0], col[1], col[2], col[3]);  // cyan

    PaintLV(visatt, icolor);

    //
    // Install daughter PV -----------
    //
    
    fComponents.push_back(new J4IRBPIP(this,1,1,0,-1));
    
    Assemble_BeamPipeMiddle();

// QC1 geometry
    G4double rmin,rmax,zlen,zpos;

//     AssembleSmallAngle_QC1();
//    Q magnets
    G4int nq=J4ParameterTable::GetValue("J4IR.NumberOfQ",1);
    G4double ebeam=J4ParameterTable::GetValue("J4IR.Q.BeamEnergy",250.0)*GeV;
    for(int i=0;i<nq;i++) {
        std::vector<double> qpara;  // rmin, rmax, zlen, zpos, sign
   std::ostringstream sname3;
	sname3 << "J4IR.Q" << i << ".Geometry" << std::ends;
	qpara=J4ParameterTable::GetDValue((sname3.str()).c_str(),
			"3.0 8.0 300.0 450.0 1.0 -65.0", 6);
        for(G4int j=0;j<4;j++) { qpara[j] *= cm; }
        G4bool isDownStream=FALSE;
        if( qpara[4] < 0.0 ) isDownStream = TRUE;
   std::ostringstream sname4;
	sname4 << "J4IR_Q" << i << std::ends;
	G4double bgrad = -65.0*tesla/meter;
	Assemble_Qx((sname4.str()).c_str(), 
		qpara[0], qpara[1], qpara[2], qpara[3], isDownStream,
		ebeam, bgrad);
    }

//
    fComponents.push_back(new J4IRCH2Mask(this,1,2,0,-1, FALSE));
    fComponents.push_back(new J4IRCH2Mask(this,1,2,1,-1, TRUE));
    fComponents.push_back(new J4IRBCAL(this, 1, 2, 0, -1, FALSE));
    fComponents.push_back(new J4IRBCAL(this, 1, 2, 1, -1, TRUE));

    fComponents.push_back(new J4IRFCAL(this, 1, 4, 0, -1, FALSE));
    fComponents.push_back(new J4IRFCAL(this, 1, 4, 1, -1, FALSE));
    fComponents.push_back(new J4IRFCAL(this, 1, 4, 2, -1, TRUE));
    fComponents.push_back(new J4IRFCAL(this, 1, 4, 3, -1, TRUE));

// Mask before QC1
    rmin = J4ParameterTable::GetValue("J4IR.WMask3.InnerRadius",20.0)*cm;
    rmax = J4ParameterTable::GetValue("J4IR.WMask3.OuterRadius",35.0)*cm;
    zlen = J4ParameterTable::GetValue("J4IR.WMask3.Length",160.0)*cm;
    zpos = J4ParameterTable::GetValue("J4IR.WMask3.ZPosition",290.0)*cm;
    material= J4ParameterTable::GetValue("J4IR.WMask3.Material","Tungsten");
    visatt = J4ParameterTable::GetValue("J4IR.VisAtt.WMask3",true);
    col=J4ParameterTable::GetDValue("J4IR.Color.WMask3","1.0 0.0 1.0 1.0",4);
    G4Color icol(col[0], col[1], col[2], col[3]); 
    fComponents.push_back(new J4IRTubs("IRWMask3P", rmin, rmax, zlen*0.5,zpos+0.5*zlen, material, 
	 visatt, icol, this, 1, 2, 0, -1, FALSE));
    fComponents.push_back(new J4IRTubs("IRWMask3M", rmin, rmax, zlen*0.5,zpos+0.5*zlen, material, 
	 visatt, icol, this, 1, 2, 1, -1, TRUE));

// Mask around QC1
    rmin = J4ParameterTable::GetValue("J4IR.WMask4.InnerRadius",20.0)*cm;
    rmax = J4ParameterTable::GetValue("J4IR.WMask4.OuterRadius",35.0)*cm;
    zlen = J4ParameterTable::GetValue("J4IR.WMask4.Length",160.0)*cm;
    zpos = J4ParameterTable::GetValue("J4IR.WMask4.ZPosition",450.0)*cm;
    G4double zcnt=zpos+0.5*zlen;

    material= J4ParameterTable::GetValue("J4IR.WMask4.Material","Tungsten");
    visatt = J4ParameterTable::GetValue("J4IR.VisAtt.WMask4",true);
    col=J4ParameterTable::GetDValue("J4IR.Color.WMask4","0.5 0.0 0.5 1.0",4);
    G4Color icol2(col[0], col[1], col[2], col[3]); 
    fComponents.push_back(new J4IRTubs("IRWMask4P", rmin, rmax, zlen*0.5, 
	zcnt, material, 
	visatt, icol2, this, 1, 2, 0, -1, FALSE));
    fComponents.push_back(new J4IRTubs("IRWMask4M", rmin, rmax, zlen*0.5, 
	zcnt, material, 
	visatt, icol2, this, 1, 2, 1, -1, TRUE));

// --------------------------------------------------

    int ndet=J4ParameterTable::GetValue("J4IR.OptDet.N",0);
    for(G4int idet=0;idet<ndet;idet++){
      fComponents.push_back(new J4OptDet(this, G4String("J4IR.OptDet"), ndet, idet));
    }


// ----------------------------------------------------------------
// Register solids set mother/daughter relation.
    std::vector<J4VComponent*>::iterator iv;
    for( iv=fComponents.begin() ; iv!=fComponents.end(); iv++ ) {
      Register(*iv);
      (*iv)->InstallIn(this);
      SetDaughter(*iv);
    }


  }     
}


//=====================================================================
//* Assemble beam pipe midle.
//* Use of UnionSolids are abondoned because of too many error 
//* From BoolOperation Unimplemented case.
// ----------------------------------------------------------
void J4IR::Assemble_BeamPipeMiddle()
{

    G4int nsolids  = J4ParameterTable::GetValue("J4IR.BeamPipeMiddle.NumSolides", 4);
    std::vector<double> rmax;
    rmax = J4ParameterTable::GetDValue("J4IR.BeamPipeMiddle.REdges","1.525 8.0 8.0 15.0",nsolids);
    std::vector<double> zpos;
    zpos = J4ParameterTable::GetDValue("J4IR.BeamPipeMiddle.ZEdges","7.0 80.0 320.0 410.0", nsolids);
    std::vector<int> ishape;
    ishape=J4ParameterTable::GetIValue("J4IR.BeamPipeMiddle.Shapes","0 1 0 1",nsolids);
    G4double althick = J4ParameterTable::GetValue("J4IR.BeamPipeMiddle.Thickness",0.2)*cm;
    G4double bethick = J4ParameterTable::GetValue("J4IR.BeamPipeIP.Thickness",0.025)*cm;

    for(int i=0;i<nsolids;i++) {
	rmax[i] *= cm;        zpos[i] *= cm;
    }
    G4String material = J4ParameterTable::GetValue("J4IR.BeamPipeMiddle.Material","Aluminum");
    G4bool visatt = J4ParameterTable::GetValue("J4IR.VisAtt.BeamPipeMiddle",true);
    std::vector<double> col=J4ParameterTable::GetDValue("J4IR.Color.BeamPipeMiddle","0.0 0.5 0.5 1.0",4);
    G4Color icolor(col[0], col[1], col[2], col[3]);  // cyan

 
   std::string nstr0(GetName()+"/BPMiddle");
   std::string nstr1;
   for(int j=0;j<2;j++){
     std::ostringstream sname;
     sname << j << std::ends;
     nstr1=nstr0+sname.str();
     G4bool flag=false;
     if( j == 1 ) flag=true;
     G4double hzlen=(zpos[1]-zpos[0])*0.5;
     G4double zcnt =(zpos[1]+zpos[0])*0.5;
     J4IRCons *cons1 = new J4IRCons(nstr1, rmax[0]-bethick, rmax[0], 
			rmax[1]-althick, rmax[1], hzlen, zcnt, this, 1, 2, j, -1, flag);
     cons1->SetAttribute(material, visatt, icolor);
     fComponents.push_back(cons1);

     for(G4int i=2;i<nsolids;i++) {
        std::ostringstream sname;
        sname << GetName() << j << ".v" << i << std::ends;	
        nstr1=nstr0+sname.str();
        hzlen=(zpos[i]-zpos[i-1])*0.5;
        zcnt =(zpos[i]+zpos[i-1])*0.5;
        if( ishape[i] == 0 ) {
 	  J4IRTubs *tmps = new J4IRTubs(nstr1, rmax[i]-althick, rmax[i], hzlen, zcnt,
		material, visatt, icolor, this, 1, 2, j, -1, flag);
	  fComponents.push_back(tmps);
        }
        else {
          G4double thick=althick;
          if( i==2 ) thick=bethick;
          cons1 = new J4IRCons(nstr1, rmax[i-1]-thick, rmax[i-1], 
			rmax[i]-althick, rmax[i], hzlen, zcnt, this, 1, 2, j, -1, flag);
          cons1->SetAttribute(material, visatt, icolor);
          fComponents.push_back(cons1);
        }
      }           
   }
}


//=====================================================================
//* QC1/Wmask4(Arround QC1)
// ----------------------------------------------------------
void J4IR::Assemble_Qx(G4String name, G4double rmin, G4double rmax, 
	G4double zlen, G4double zpos, G4double isDownStream, 
	G4double ebeam, G4double bgrad) 
//  ebeam : beam energy in unit of GeV.
//  brad  : Magnetic field gradiant of QC ( For electron side Q magnet )
{
    G4double qcangle=J4ParameterTable::GetValue("J4IR.Q.Angle",0.00)*rad;
    G4String material= J4ParameterTable::GetValue("J4IR.Q.Material","Iron");
    G4bool visatt = J4ParameterTable::GetValue("J4IR.VisAtt.Q",true);
    std::vector<double> col=J4ParameterTable::GetDValue("J4IR.Color.Q",
	"1.0 0.5 0.5 1.0",4);
    G4Color icolqc(col[0], col[1], col[2], col[3]); 
    G4double zcnt = zpos + 0.5*zlen;
    J4IRQMField* qc1fielde = new J4IRQMField(ebeam, -bgrad,rmin, rmax, zlen ) ;
    J4IRQMField* qc1fieldp = new J4IRQMField(ebeam,  bgrad,rmin, rmax, zlen ) ;

// Small angle case.  QD axis is along Z-axis

    if( std::abs(qcangle) < 0.001 ) {
	 J4IRTubs *qc1p=new J4IRTubs("IRQC1P", rmin, rmax, zlen*0.5,
	    zcnt, material, visatt, icolqc, this, 1, 2, 0, -1, FALSE);
	 fComponents.push_back(qc1p);
	 qc1p->SetMField(qc1fielde);

         J4IRTubs *qc1m=new J4IRTubs("IRQC1M", rmin, rmax, zlen*0.5,
	    zcnt, material, visatt, icolqc, this, 1, 2, 1, -1, TRUE);
	 fComponents.push_back(qc1m);    
    	 qc1m->SetMField(qc1fieldp);
    }

// Large angle case.  QC axis is along beam line	
    else {
      if( isDownStream ) { qcangle *= -1.0 ; }
      G4String tname=name+".plus";
      J4IRSlantTubs *qcp=new J4IRSlantTubs(tname, rmin, rmax, 0.5*zlen,
  	  zcnt, qcangle, this, 1, 2, 0, -1, FALSE);
      qcp->SetAttribute(material, visatt, icolqc);
      fComponents.push_back(qcp);
      qcp->SetMField(qc1fielde);

      tname=name+".minus";
      J4IRSlantTubs *qcm=new J4IRSlantTubs(tname, rmin, rmax, 0.5*zlen,
	 zcnt, qcangle, this, 1, 2, 1, -1, TRUE);
      qcm->SetAttribute(material, visatt, icolqc);
      fComponents.push_back(qcm);
      qcm->SetMField(qc1fieldp);
   }


}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IR::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------
/*
void J4IR::InstallIn(J4VComponent *mother,
                             G4RotationMatrix     *prot, 
                             const G4ThreeVector  &tlate )
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}
*/
//* Draw  --------------------------------------------------------
void J4IR::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IR::Print() const
{
}

	
	

