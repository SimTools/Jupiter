// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC2Iron3
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  T.Aso	Original version.
//*************************************************************************

#include "J4IRQC2Iron3.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "J4UnionSolid.hh"
#include <cmath>

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC2Iron3::fName("IRQC2IRON3");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC2Iron3::J4IRQC2Iron3(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
			   G4int  copyno):
            J4VIRAcceleratorComponent( fName, parent, nclones,
				       nbrothers, me, copyno, FALSE  ) 
{   
}
//=====================================================================
//* destructor --------------------------------------------------------

J4IRQC2Iron3::~J4IRQC2Iron3()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC2Iron3::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  	
    // MakeSolid ---------------
    G4String name1( GetName() );
    name1 += ".IronBox";
    G4double y1 = _QC2HBOX_IRON2_*std::sin(pi/4.);
    G4double x2 = _QC2PLTX_IRON3_;
    G4double x1 =  x2+y1;
    G4double Talpha = (x2-x1)/y1/2.;
    if(GetMyID()%2 == 1 ) Talpha = -Talpha;

    G4VSolid *solid1  = new G4Trap(name1,
				 _QC2PZ_IRON3_/2.,0.,0.,
				 y1/2.,x1/2.,x2/2.,
				 Talpha,
				 y1/2.,x1/2.,x2/2.,
				 Talpha);

    G4String name2( GetName() );
    name2 += ".IronTub";
    G4double AX = (x2+x1)/4.;
    G4double AY = y1/2.;
    G4double ANG = atan2(AY,AX);
    G4VSolid *solid2 =  new G4Tubs(name2,
				  0.,
				   std::sqrt(AX*AX+AY*AY),
				   _QC2PZ_IRON3_/2.,
				   0.,2.*ANG);
    G4String name3( GetName() );
    name3 += ".Iron3";
    G4ThreeVector tv;
    G4RotationMatrix* rot=new G4RotationMatrix;
    if(GetMyID()%2==0){    
      rot->rotateZ(pi+ANG);
    }else{
      rot->rotateZ(ANG);
    }
    G4VSolid* solid = new J4UnionSolid(name3,solid1,solid2,rot,tv);

    Register(solid);
    SetSolid(solid);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(_QC2MAT_IRON_));
    
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0,0 ,0 ));

    // Install daughter PV -----------
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRQC2Iron3::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRQC2Iron3::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  switch ( GetMyID()%4 ){
  case 0:
    rotM->rotateZ(-_QC2PHI_COLLAR_);
    break;
  case 1:
    rotM->rotateZ(+_QC2PHI_COLLAR_);
    break;
  case 2:
    rotM->rotateZ(pi-_QC2PHI_COLLAR_);
    break;
  case 3:
    rotM->rotateZ(pi+_QC2PHI_COLLAR_);
    break;
  }
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRQC2Iron3::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 

   G4double y1 = _QC2HBOX_IRON2_*std::sin(pi/4.);
   G4double x2 = _QC2PLTX_IRON3_;
   G4double x1 =  x2+y1;
   G4double dx = x1 - (x1+x2)/4.;
   G4double dy = y1/2.;  

 G4double xx = (80.*mm-
		(std::cos(_QC2PHI_COLLAR_)*dx-std::sin(_QC2PHI_COLLAR_)*(-dy)) );
 G4double yy = (51.666*mm-
		(std::sin(_QC2PHI_COLLAR_)*dx+std::cos(_QC2PHI_COLLAR_)*(-dy)) );

 switch(GetMyID()%4){
  case 0:
    xx = xx;
    yy = yy;
    break;
  case 1:
    xx = -xx;
    yy =  yy;
    break;
  case 2:
    xx = -xx;
    yy = -yy;
    break;
  case 3:
    xx =  xx;
    yy = -yy;
    break;
 }
 position->setX(xx);
 position->setY(yy);
  return *position;
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRQC2Iron3::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRQC2Iron3::Print() const
{
}

	
	

