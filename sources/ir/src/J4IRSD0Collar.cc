// $Id$
//*************************************************************************
//* --------------------
//* J4IRSD0Collar
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  T.Aso	Original version.
//*************************************************************************

#include "J4IRSD0Collar.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "J4UnionSolid.hh"
#include <cmath>

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRSD0Collar::fName("IRSD0Collar");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRSD0Collar::J4IRSD0Collar(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
			       G4int  copyno):
            J4VIRAcceleratorComponent( fName, parent, nclones,
				       nbrothers, me, copyno  ) 
{   
}
//=====================================================================
//* destructor --------------------------------------------------------

J4IRSD0Collar::~J4IRSD0Collar()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRSD0Collar::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  	
    // MakeSolid ---------------
    G4String name1( GetName() );
    name1 += ".Collar";
    G4VSolid *solid1 = new G4Box( name1, 
				   _SD0HBOX_IRON_/2.,
				   _SD0VBOX_IRON_/2.,
				   _SD0ZLEN_/2.);

    G4String name2( GetName() );
    name2 += ".Tub";
    G4double AX = _SD0HBOX_IRON_/2.;
    G4double AY = _SD0VBOX_IRON_/2.;
    G4double ANG = atan2(AY,AX);
    G4VSolid *solid2 =  new G4Tubs(name2,
				  0.,
				   std::sqrt(AX*AX+AY*AY),
				   _SD0ZLEN_/2.,
				   0.,2.*ANG);
    G4String name3( GetName() );
    name3 += ".collar";
    G4ThreeVector tv;
    G4RotationMatrix* rot=new G4RotationMatrix;
    rot->rotateZ(pi+ANG);

    G4VSolid* solid = new J4UnionSolid(name3,solid1,solid2,rot,tv);
    Register(solid);
    SetSolid(solid);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(_SD0MAT_COLLAR_));
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 0, 1));

    // Install daughter PV -----------
  }     
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRSD0Collar::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  rotM->rotateZ(GetMyID()*_SD0PHI_SUS_*2+_SD0PHI_SUS_);
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRSD0Collar::GetTranslation(){

  G4ThreeVector* position= new G4ThreeVector; 

  G4double xx=0,yy=0;

  G4double radius = 
    ( (_SD0INRADIUS_+_SD0THICK_)-(_SD0Y1_SUS_/std::cos(_SD0PHI_SUS_/2.)) )
    *std::cos(_SD0PHI_SUS_/2.)
    - _SD0HBOX_IRON_/2.;

  xx = radius*std::cos(GetMyID()*_SD0PHI_SUS_*2.+_SD0PHI_SUS_);
  yy = -radius*std::sin(GetMyID()*_SD0PHI_SUS_*2.+_SD0PHI_SUS_);

 position->setX(xx);
 position->setY(yy);
  return *position;
}
//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRSD0Collar::Cabling()
{
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRSD0Collar::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRSD0Collar::Print() const
{
}

	
	

