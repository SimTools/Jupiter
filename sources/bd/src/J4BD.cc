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
  
  if (!GetLV()) {
    // MakeSolid ----------//
    OrderNewBox (_BDOUTERHALFX_, _BDOUTERHALFY_, _BDOUTERHALFZ_,
                 0, 0, 0, _BDINNERHALFX_, _BDINNERHALFY_, _BDINNERHALFZ_);
                     
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(_BDMATERIAL_));
    
    // SetVisAttribute ----//
    PaintLV(_BDVISATT_, G4Color(1, 0, 1));
  	
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

	
	
