// $Id$
//*************************************************************************
//* --------------------
//* J4IRWMask2
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4IRWMask2.hh"
#include "J4IRWMaskParameterList.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRWMask2::fName("IRWMask2");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRWMask2::J4IRWMask2(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno,G4bool reflect ) :
            J4VIRAcceleratorComponent( fName, parent, nclones,
                                    nbrothers, me, copyno,reflect  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRWMask2::~J4IRWMask2()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRWMask2::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRWMaskParameterList* wmList =
      new J4IRWMaskParameterList(OpenParameterList());
    G4double rmin = wmList->GetWMask2Radius();
    G4double rmax = wmList->GetWMask2Radius()+wmList->GetWMask2Thick();
    G4double zlen  = wmList->GetWMask2ZLength();
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".CH2";
    G4VSolid *tube = new G4Tubs( name, rmin,rmax,zlen/2.,0,2*M_PI);  
                                       
    Register(tube);
    SetSolid(tube);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(wmList->GetWMaskMaterial()));
    
    // SetVisAttribute ---------------
    PaintLV(wmList->GetWMaskVisAtt(),wmList->GetWMaskColor());
  	
    // Install daughter PV -----------
  		  
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRWMask2::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRWMask2::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRWMask2::GetTranslation(){
  J4IRWMaskParameterList* wmList = 
    new J4IRWMaskParameterList(OpenParameterList());
  G4double zpos = wmList->GetWMask2ZPosition()+wmList->GetWMask2ZLength()/2.;

  G4ThreeVector* position = new G4ThreeVector(0,0.,zpos);
  // G4ThreeVector* position = new G4ThreeVector(0,0.,
  //			      _WMASK2ZPOS_+_WMASK2ZLEN_/2.);
  return *position;
}




//* Draw  --------------------------------------------------------
void J4IRWMask2::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRWMask2::Print() const
{
}

	
	

