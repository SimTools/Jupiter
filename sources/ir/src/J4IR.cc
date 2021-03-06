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

#include "G4Region.hh"

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
    G4String bpname=GetName()+"/Center";
    G4VSolid *lastsolid=new G4Tubs(bpname, 0, pl->GetIRREdges(0), pl->GetIRZEdges(0), 0, 2*M_PI);

    G4VSolid *tmpsolid=0;
    G4String blank;

    for(int i=1;i<nsolids;i++) {
      for(int j=0;j<2;j++) {
        G4double hzlen=(pl->GetIRZEdges(i) - pl->GetIRZEdges(i-1))*0.5;
        std::ostringstream sname; 
        sname << GetName() << "/SolidTemp" << i << "-" << j << std::ends;
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
          sname2 << "/SolidJoin" << i << "-" << j << std::ends;
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

    // Vacuum at IP
    G4double rvout = J4ParameterTable::GetValue("J4IR.BeamPipeIP.OuterRadius", 1.525)*cm;
    G4double rvin  = rvout-J4ParameterTable::GetValue("J4IR.BeamPipeIP.Thickness", 0.025)*cm; 
    G4double zvlen = J4ParameterTable::GetValue("J4IR.BeamPipeIP.HalfZLength",7.0)*cm;
    G4Color ivcolor(1.0, 1.0, 1.0, 0.0);

    J4IRTubs *bpvac = new J4IRTubs("IPVacuum", 0.0, rvin,
               zvlen, 0.0, "vacuum", false, ivcolor, this, 1, 1, 0, -1, false);
    fComponents.push_back(bpvac);
    
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

    Assemble_BeamPipeQC();


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

#if G4VERSION_NUMBER < 910
    G4Region *bpregion=new G4Region("BPandMask");
    for( iv=fComponents.begin() ; iv!=fComponents.end(); iv++ ) {
      G4int ind=(*iv)->GetName().index("BPMiddle");
      G4int ind2=(*iv)->GetName().index("IR/IRWMask");
      if ( ind > 0 || ind2 > 0 ) {
	//	std::cerr << " Region=" << (*iv)->GetName() << std::endl;
	bpregion->AddRootLogicalVolume((*iv)->GetLV());
      }
    }

    G4Region *irregion=new G4Region("IRRegion");
    for( iv=fComponents.begin() ; iv!=fComponents.end(); iv++ ) {
      G4int ind=(*iv)->GetName().index("BPVacuum");
      G4int ind2=(*iv)->GetName().index("IR/IRQC");
      if ( ind > 0 || ind2 > 0) {
	std::cerr << " Region=" << (*iv)->GetName() << std::endl;
	irregion->AddRootLogicalVolume((*iv)->GetLV());
      }
    }
#endif
    //    irregion->AddRootLogicalVolume(GetLV());

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
    G4Color icolvc(1.0, 1.0, 1.0, 0.0);  // cyan

    G4String matvac="vacuum";

    //  std::string nstr0(GetName()+"/BPMiddle");
   std::string nstr0("BPMiddle");
   std::string nstrv("BPVacuum");
   std::string nstra;
   std::string nstrb;
   G4double tolerance=1.0E-5*mm;
   for(int j=0;j<2;j++){
     std::ostringstream snamea;
     snamea << j << std::ends;
     nstra=nstr0+snamea.str();
     G4bool flag=false;
     if( j == 1 ) flag=true;
     G4double hzlen=(zpos[1]-zpos[0])*0.5;
     G4double zcnt =(zpos[1]+zpos[0])*0.5;
     J4IRCons *cons1 = new J4IRCons(nstra.c_str(), rmax[0]-bethick, rmax[0], 
		rmax[1]-althick, rmax[1], hzlen, zcnt, this, 1, 2, j, -1, flag);
     cons1->SetAttribute(material, visatt, icolor);
     fComponents.push_back(cons1);

     nstra=nstrv+snamea.str();
     J4IRCons *conv1 = new J4IRCons(nstra.c_str(),0.0, rmax[0]-bethick-tolerance,
		    0.0, rmax[1]-althick-tolerance, hzlen, zcnt, this, 1,2,j,-1,flag);
     conv1->SetAttribute(matvac, false, icolor);
     fComponents.push_back(conv1);

     for(G4int i=2;i<nsolids;i++) {
        std::ostringstream snameb;
        std::ostringstream snamec;
        snameb << nstr0 << j << "Loc" << i << std::ends;
        snamec << nstrv << j << "VLoc" << i <<std::ends;
        nstrb=snameb.str();
        hzlen=(zpos[i]-zpos[i-1])*0.5;
        zcnt =(zpos[i]+zpos[i-1])*0.5;
        if( ishape[i] == 0 ) {
 	  J4IRTubs *tmps = new J4IRTubs(nstrb.c_str(), rmax[i]-althick, rmax[i], 
               hzlen, zcnt, material, visatt, icolor, this, 1, 2, j, -1, flag);
	  fComponents.push_back(tmps);

	  tmps=new J4IRTubs(snamec.str().c_str(), 0, rmax[i]-althick-tolerance,
			    hzlen, zcnt, matvac, false, icolvc, this, 1,2,j,-1,flag);
	  fComponents.push_back(tmps);

        }
        else {
          G4double thick=althick;
          if( i==2 ) thick=bethick;
          cons1 = new J4IRCons(nstrb.c_str(), rmax[i-1]-thick, rmax[i-1], 
			rmax[i]-althick, rmax[i], hzlen, zcnt, this, 1, 2, j, -1, flag);
          cons1->SetAttribute(material, visatt, icolor);
          fComponents.push_back(cons1);

          cons1 = new J4IRCons(snamec.str().c_str(), 0.0, rmax[i-1]-thick-tolerance,
		0.0, rmax[i]-althick-tolerance, hzlen, zcnt, this, 1, 2, j, -1, flag);
          cons1->SetAttribute(matvac, visatt, icolvc);
          fComponents.push_back(cons1);

        }

      }           
   }
}


//=====================================================================
//* QC1/Wmask4(Arround QC1)
// ----------------------------------------------------------
void J4IR::Assemble_Qx(const char *name, G4double rmin, G4double rmax, 
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

    G4double thickbp=J4ParameterTable::GetValue("J4IR.BeamPipeQC.Thickness",0.2)*cm;
    G4String matbp=J4ParameterTable::GetValue("J4IR.BeamPipeQC.Material","Aluminum");
    G4bool  visbp = J4ParameterTable::GetValue("J4IR.VisAtt.BeamPipeQC",true);
    std::vector<double> colb=J4ParameterTable::GetDValue("J4IR.Color.BeamPipeQC","0.0 0.5 0.5 1.0",4);
    G4Color colbp(colb[0], colb[1], colb[2], colb[3]);  // cyan
    G4Color colvc(1.0, 1.0, 1.0, 0.0); 
// Small angle case.  QD axis is along Z-axis

    if( std::abs(qcangle) < 0.001 ) {
         G4String n1=G4String(name)+G4String("IronP");
	 J4IRTubs *v=new J4IRTubs(n1, rmin+thickbp, rmax, zlen*0.5,
	    zcnt, material, visatt, icolqc, this, 1, 2, 0, -1, FALSE);
	 fComponents.push_back(v); v->SetMField(qc1fielde);
	 
	 G4String n2=G4String(name)+G4String("BeamPipeP");
	 v=new J4IRTubs(n2, rmin, rmin+thickbp, zlen*0.5,
			zcnt, material, visbp, colbp, this, 1,2,0,-1, FALSE);
	 fComponents.push_back(v); 	// v2->SetMField(qc1fielde);

	 v=new J4IRTubs(G4String(name)+G4String("VacuumP"), 0.0, rmin, zlen*0.5,
			zcnt, "vacuum", false, colvc, this, 1,2,0,-1, FALSE);
	 fComponents.push_back(v); //	 v->SetMField(qc1fielde);


	 G4String n4=G4String(name)+G4String("IronM");
         v=new J4IRTubs(n4, rmin+thickbp, rmax, zlen*0.5,
	    zcnt, material, visatt, icolqc, this, 1, 2, 1, -1, TRUE);
	 fComponents.push_back(v);    v->SetMField(qc1fieldp);

	 v=new J4IRTubs(G4String(name)+G4String("BeamPipeM"), rmin, rmin+thickbp, zlen*0.5,
			zcnt, material, visbp, colbp, this, 1,2,1,-1, TRUE);
	 fComponents.push_back(v); //	 v->SetMField(qc1fielde);

	 v=new J4IRTubs(G4String(name)+G4String("VacuumM"), 0.0, rmin, zlen*0.5,
			zcnt, "vacuum", false, colvc, this, 1,2,1,-1, TRUE);
	 fComponents.push_back(v); //	 v->SetMField(qc1fielde);

    }

// Large angle case.  QC axis is along beam line	
    else {
      if( isDownStream ) { qcangle *= -1.0 ; }
      G4String tname=G4String(name)+G4String(".Itself");
      J4IRSlantTubs *qcp=new J4IRSlantTubs(tname, rmin, rmax, 0.5*zlen,
  	  zcnt, qcangle, this, 1, 2, 0, -1, FALSE);
      qcp->SetAttribute(material, visatt, icolqc);
      fComponents.push_back(qcp);
      qcp->SetMField(qc1fielde);

      J4IRSlantTubs *qcm=new J4IRSlantTubs(tname, rmin, rmax, 0.5*zlen,
	 zcnt, qcangle, this, 1, 2, 1, -1, TRUE);
      qcm->SetAttribute(material, visatt, icolqc);
      fComponents.push_back(qcm);
      qcm->SetMField(qc1fieldp);

   }


}

//=====================================================================
//* Assemble BeamPipe after BCAL for crossing angle is 14mrad
void  J4IR::Assemble_BeamPipeQC()
{
    G4double qcangle=J4ParameterTable::GetValue("J4IR.Q.Angle",0.00)*rad;
    if( std::abs(qcangle) < 0.001 ) return;

    G4String matbp=J4ParameterTable::GetValue("J4IR.BeamPipeQC.Material","Aluminum");
    G4bool  visbp = J4ParameterTable::GetValue("J4IR.VisAtt.BeamPipeQC",true);
    std::vector<double> colb=J4ParameterTable::GetDValue("J4IR.Color.BeamPipeQC","0.0 0.5 0.5 1.0",4);
    G4Color colbp(colb[0], colb[1], colb[2], colb[3]);  // cyan

    G4int nbp=J4ParameterTable::GetValue("J4IR.NumberOfBeamPipeQC",1);
    for(G4int n=0;n<nbp;n++) {
      std::vector<double> bppara;  // thickness, rmax, zlen, zpos, sign
      std::ostringstream sname;
      sname << "J4IR.BeamPipeQC" << n << ".Geometry" << std::ends;
      bppara=J4ParameterTable::GetDValue((sname.str()).c_str(),
		 "0.2  1.0 500.0 451.0 1.0", 5);
      for(G4int j=0;j<4;j++) { bppara[j] *= cm; }
      G4double angle=qcangle;
      if ( bppara[4] < 0.0 ) angle *= -1;

      G4double rmin=bppara[1]-bppara[0];
      G4double rmax=bppara[1];
      G4double hzlen=0.5*bppara[2];
      G4double zcnt=bppara[3]+hzlen;
      G4String tname=sname.str().c_str();
      G4String name=tname+G4String(".Itself");

      std::cerr << "Assembling " << name << " rmin,rmax="
		<< rmin << "," << rmax << "hzlen=" << hzlen
		<< "zcnt=" << zcnt << std::endl;


      J4IRSlantTubs *bpp=new J4IRSlantTubs(name, rmin, rmax, hzlen,
  	  zcnt, angle, this, 1, 2, 0, -1, FALSE);
      bpp->SetAttribute(matbp, visbp, colbp);
      fComponents.push_back(bpp);

      J4IRSlantTubs *bpm=new J4IRSlantTubs(name, rmin, rmax, hzlen,
        	  zcnt, angle, this, 1, 2, 1, -1, TRUE);
      bpm->SetAttribute(matbp, visbp, colbp);
      fComponents.push_back(bpm);

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

	
	

