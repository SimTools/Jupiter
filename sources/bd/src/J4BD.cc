// $Id$
//*************************************************************************
//* --------------------
//* J4BD
//* --------------------
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2002/05/15  K.Hoshina	Argument changed in InstallIn().
//*************************************************************************

#include "J4BD.hh"
#include "J4BDParameterList.hh"


//====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4BD::fFirstName("BD");

//=====================================================================
//* constructor -------------------------------------------------------

J4BD::J4BD(J4VAcceleratorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
           J4VBDAcceleratorComponent( fFirstName, parent, nclones,
                                   nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4BD::~J4BD()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4BD::Assemble() 
{ 
  // Assemble your LogicalVolume here.

  J4BDParameterList *list = J4BDParameterList::GetInstance(); 
  
  if (!GetLV()) {
    // MakeSolid ----------//
    OrderNewBox (list->GetOuterHalfX(), list->GetOuterHalfY(), list->GetOuterHalfZ(), 
                 0, 0, 0, 
                 list->GetInnerHalfX(), list->GetInnerHalfY(), list->GetInnerHalfZ());
                     
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(list->GetMaterial()));
    
    // SetVisAttribute ----//
    PaintLV(list->GetVisAtt(), *list->GetColor());
  	
    // Install daughter PV //
    
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4BD::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4BD::InstallIn(J4VComponent* mother,
                     G4RotationMatrix     *prot, 
                     const G4ThreeVector  &tlate )
{ 
  // before installation, you must call Assemble() first.
  
  Assemble();			
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}


//* Draw  --------------------------------------------------------
void J4BD::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4BD::Print() const
{
}

	
	
