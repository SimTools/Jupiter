// $Id$
//*************************************************************************
//* --------------------
//* J4IRWSiCAL1
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  T.Aso	Original version.
//*************************************************************************

#include "J4IRWSiCAL1.hh"
#include "J4IRWSiCALParameterList.hh"

#include "G4Cons.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRWSiCAL1::fName("IRWSiCAL1");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRWSiCAL1::J4IRWSiCAL1(J4VAcceleratorComponent *parent,
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

J4IRWSiCAL1::~J4IRWSiCAL1()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRWSiCAL1::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRWSiCALParameterList* fwsiList = J4IRWSiCALParameterList::GetInstance();
    G4double rmin = fwsiList->GetWSiCAL1Radius();
    G4double rmax1 = fwsiList->GetWSiCAL1Radius()+fwsiList->GetWSiCAL1Thick();
    G4double rmax2 = OpenParameterList()->GetIRSupportInnerRadius();
    G4double zlen = fwsiList->GetWSiCAL1ZLength();
    // MakeSolid ---------------
    G4String cname( GetName() );
    cname += ".CH2";

   G4VSolid *cone = new G4Cons(cname,rmin,rmax1,rmin,rmax2,zlen/2.,0, 2*M_PI); 

    Register(cone);
    SetSolid(cone);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(fwsiList->GetWSiCALMaterial()));
    
    // SetVisAttribute ---------------
    PaintLV(fwsiList->GetWSiCALVisAtt(),fwsiList->GetWSiCALColor());
  	
    // Install daughter PV -----------
  		  
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRWSiCAL1::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRWSiCAL1::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRWSiCAL1::GetTranslation(){
  J4IRWSiCALParameterList* wsiList=J4IRWSiCALParameterList::GetInstance();
  G4double zpos = 
    wsiList->GetWSiCAL1ZPosition()+wsiList->GetWSiCAL1ZLength()/2.;

  G4ThreeVector* position = new G4ThreeVector(0,0.,zpos);

  //G4ThreeVector* position = new G4ThreeVector(0,0.,
  //				      _WSICAL1ZPOS_+_WSICAL1ZLEN_/2.);
  return *position;
}




//* Draw  --------------------------------------------------------
void J4IRWSiCAL1::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRWSiCAL1::Print() const
{
}

	
	

