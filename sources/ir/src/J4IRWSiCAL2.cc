// $Id$
//*************************************************************************
//* --------------------
//* J4IRWSiCAL2
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  T.Aso	Original version.
//*************************************************************************

#include "J4IRWSiCAL2.hh"
#include "J4IRWSiCALParameterList.hh"

#include "G4Tubs.hh"
#include <math.h>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRWSiCAL2::fName("IRWSiCAL2");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRWSiCAL2::J4IRWSiCAL2(J4VAcceleratorComponent *parent,
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

J4IRWSiCAL2::~J4IRWSiCAL2()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRWSiCAL2::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRWSiCALParameterList* wsiList =
      new J4IRWSiCALParameterList(OpenParameterList());
    G4double rmin = wsiList->GetWSiCAL2Radius();
    G4double rmax = wsiList->GetWSiCAL2Radius()+wsiList->GetWSiCAL2Thick();
    G4double zlen = wsiList->GetWSiCAL2ZLength();
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".CH2";

    G4VSolid *tube = new G4Tubs( name, rmin,rmax,zlen/2.,0, 2*M_PI);  
                                       
    Register(tube);
    SetSolid(tube);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(wsiList->GetWSiCALMaterial()));
    
    // SetVisAttribute ---------------
    PaintLV(wsiList->GetWSiCALVisAtt(),wsiList->GetWSiCALColor());
  	
    // Install daughter PV -----------
  		  
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRWSiCAL2::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRWSiCAL2::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRWSiCAL2::GetTranslation(){
  J4IRWSiCALParameterList* wsiList =
    new J4IRWSiCALParameterList(OpenParameterList());
  G4double zpos = wsiList->GetWSiCAL2ZPosition()
    +wsiList->GetWSiCAL2ZLength()/2.;

  G4ThreeVector* position = new G4ThreeVector(0,0.,zpos);

  return *position;
}




//* Draw  --------------------------------------------------------
void J4IRWSiCAL2::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRWSiCAL2::Print() const
{
}

	
	

