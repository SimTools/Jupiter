// $Id$
//*************************************************************************
//* --------------------
//* J4IRBPMiddle
//* --------------------
//* (Description)
//* 	Describe beampipe from Beliliums beam pipe to infront of CH2 mask
//*     This describe beam pipe by Al
//*     
//*     Corners of beam pipe shapes are given by parameters, 
//*        J4IR.BeamPipe.NumSolids:   4
//*        J4IR.BeamPipe.REdges:     1.9  8.1   8.1     38.0   
//*        J4IR.BeamPipe.ZEdges:     7.0  80.0 220.0   410.0  
//*        J4IR.BeamPipe.Shapes:   0     1    0      1  
//*      ( Shapes  0=Tubs, 1=Cons ) 
//*     Other parameters relevant to BeamPipe geometry is
//*        J4IR.BeamPipe.BeThickness:  0.025
//*        J4IR.BeamPipe.AlThickness:  0.2
//*     Note that the first part is Bellium and the rest are Aluminium 
//*     Redges difines the outer radius of beam pipe.  They has to be inside IR  region
//*   defined by parameters below.  Inner radiuses are defined as Rmax - thickness.
//*     Since thickness of Bellilium and Aluminium are different, Thickness of 
//*   the first cone shape beam pipe changes with Z.
//*     All IR region has to be defined as Vacume, since solid inside beampipe 
//*   is not defined.
//*
//*     Note that outer shape of IR geometry is given by parameters,
//*        J4.IR.NumSolids:  4
//*        J4.IR.REdges:  1.9 8.1 38.0  38.0
//*        J4.IR.ZEdges:  7.0 80.0  220.0  500.0
//*        J4.IR.Shapes:   0  1  0  0  ( 0=Tubs, 1=Cons )
//* 
//*               
//* (Update Record)
//*	2005/07/24  A.Miyamoto 	Original version.
//*************************************************************************

#include "J4IRBPMiddle.hh"
#include "J4ParameterTable.hh"

#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "J4UnionSolid.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBPMiddle::fName("IRBPMiddle");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBPMiddle::J4IRBPMiddle(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno,
		                          G4bool reflect) :
            J4VIRAcceleratorComponent( fName, parent, nclones,
                                    nbrothers, me, copyno, reflect  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRBPMiddle::~J4IRBPMiddle()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBPMiddle::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    G4String myname=GetName()+"_p";
    if( IsReflected() ) { myname=GetName()+"_m"; }

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
	rmax[i] *= cm;
        zpos[i] *= cm;
        std::cerr << "J4IRBPMiddle::Assemble  i=" << i << " rmax=" << rmax[i] << " zpos=" << zpos[i] ;
	std::cerr << " shape=" << ishape[i] << std::endl;
    }

// First entry of shapes are for Be beam pipe and not considered here

    G4VSolid *tmps=0;
    G4String conname=myname+".cons";
    G4VSolid *lastsolid=new G4Cons(conname, rmax[0]-bethick, rmax[0], 
	rmax[1]-althick, rmax[1], (zpos[1]-zpos[0])*0.5, 0, 2*M_PI);

    std::cerr << " conname=" << conname << std::endl;
    std::ostringstream sname;
    G4double lastrmin=rmax[1]-althick;
    G4double lastrmax=rmax[1];

//    G4double margin=1.0*mm;	
    for(G4int i=2;i<nsolids;i++) {
	sname.str(myname);
        sname << ".v" << i << std::ends;	
       if( ishape[i] == 0 ) {
          if( lastrmin >= rmax[i] || lastrmax <= rmax[i]-althick ) {
             std::cerr << "Warning in J4IRBPMiddle::Assemble" << std::endl;
             std::cerr << " lastrmin(" << lastrmin << ") >= rmax[" << i << "](";
	     std::cerr << rmax[i] << " or " ;
             std::cerr << " lastrmax(" << lastrmax << ") <= rmin[" << i << "](";
             std::cerr << rmax[i]-althick << std::endl;
             std::cerr << " Corner number is " << i << std::endl;
             std::cerr << "This will generate separated JointSolid " << std::endl;
          }
	  tmps = new G4Tubs(sname.str(), rmax[i]-althick, rmax[i], 
		(zpos[i]-zpos[i-1])/2+0.1*mm, 0, 2*M_PI);
       }
       else {
          tmps = new G4Cons(sname.str(), lastrmin, lastrmax, 
		rmax[i]-althick, rmax[i], (zpos[i]-zpos[i-1])/2, 0, 2*M_PI);
       }
       lastrmin=rmax[i]-althick;
       lastrmax=rmax[i];
       
       G4double  zcnt = (zpos[i]+zpos[i-1])*0.5;
       G4double  zshift = zcnt - (zpos[1]+zpos[0])*0.5; 
       G4ThreeVector tmptrans(0.0, 0.0,zshift);
       sname.str(myname);
       if( i < nsolids-1 ) { sname << ".SolidJoin" << i  << std::ends; }
       G4VSolid *tmp = new J4UnionSolid(sname.str(), lastsolid, tmps, 0, tmptrans);
       lastsolid = tmp;
     }           

    Register(lastsolid);
    SetSolid(lastsolid);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    G4String material = J4ParameterTable::GetValue("J4IR.BeamPipeMiddle.Material","Aluminum");
    MakeLVWith(OpenMaterialStore()->Order(material));
    
    // SetVisAttribute ---------------
    G4bool visatt = J4ParameterTable::GetValue("J4IR.VisAtt.BeamPipeMiddle",true);
    std::vector<double> col=J4ParameterTable::GetDValue("J4IR.Color.BeamPipeMiddle","0.0 0.5 0.5 1.0",4);
    G4Color icolor(col[0], col[1], col[2], col[3]);  // cyan

    PaintLV(visatt, icolor);
  	
    // Install daughter PV -----------
  }     
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRBPMiddle::Cabling()
{
}

//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRBPMiddle::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRBPMiddle::GetTranslation()
{
  G4int nsolids  = J4ParameterTable::GetValue("J4IR.BeamPipeMiddle.NumSolides", 4);
  std::vector<double> zpos;
  zpos = J4ParameterTable::GetDValue("J4IR.BeamPipeMiddle.ZEdges","7.0 80.0 320.0 410.0", nsolids);
  G4ThreeVector* position= new G4ThreeVector(0, 0, (zpos[1]+zpos[0])*0.5*cm); 
  
  return *position;
}

void J4IRBPMiddle::InstallIn(J4VComponent      *, // mother
                                          G4RotationMatrix  *prot,
                                    const G4ThreeVector     &tlate) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  G4UserLimits* myLimits = new G4UserLimits;
  //myLimits->SetMaxAllowedStep(100.*micrometer);
  //myLimits->SetMaxAllowedStep(1000.*micrometer);
  //myLimits->SetMaxAllowedStep(1.*mm);
  //myLimits->SetMaxAllowedStep(1.*cm);
  G4double umaxtime= J4ParameterTable::GetValue("J4IR.UserMaxTime",1000.0)*nanosecond;
  myLimits->SetUserMaxTime(umaxtime);
  GetLV()->SetUserLimits(myLimits);
  
  // Placement function into mother object...
  G4ThreeVector position = tlate;
  G4RotationMatrix* rotation = prot;
  if ( prot == 0 && tlate==0 ) {
    rotation = GetRotation();
    position = GetTranslation();
    if ( IsReflected() ){
      position.setZ(-position.z());
//      G4double angle = (rotation->getAxis()).y()*rotation->getDelta();
//      angle = 180.*degree - angle*2.;
      G4double angle = 180.0*degree; 
      rotation->rotateY(angle);
    } 
  }
    SetPVPlacement(rotation,position);
}



//* Draw  --------------------------------------------------------
void J4IRBPMiddle::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRBPMiddle::Print() const
{
}

