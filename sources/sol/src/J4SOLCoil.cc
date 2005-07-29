// $Id$
//*************************************************************************
//* --------------------
//* J4SOLCoil
//* --------------------
//* (Description)
//* 	Class for describing Detector Solenoid
//*     
//* (Update Record)
//*	2002/10/28  R.Kuboshima  Original version.
//*************************************************************************

#include "globals.hh"
#include "J4SOLCoil.hh"
#include "G4FieldManager.hh"
#include "J4MFieldMapStore.hh"
#include "G4TransportationManager.hh"
#include "G4ChordFinder.hh"
#include "J4SOLMField.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4SOLCoil::fFirstName("SOLCoil");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4SOLCoil::J4SOLCoil(J4VDetectorComponent *parent,
                            G4int  nclones,
                            G4int  nbrothers, 
                            G4int  me,
                            G4int  copyno ) :
       J4VSOLDetectorComponent( fFirstName, parent, nclones,
                                nbrothers, me, copyno)
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4SOLCoil::~J4SOLCoil()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4SOLCoil::Assemble() 
{   
   if (!GetLV()) {
      J4SOLParameterList *list = OpenParameterList();
      G4double rmin = list->GetSOLCoilInnerR();
      G4double rmax = list->GetSOLCoilOuterR();
      G4double len  = list->GetSOLCoilHalfZ();
      G4double dphi = 360.*deg;
 
      // MakeSolid ----------//
      OrderNewTubs( rmin, rmax, len, dphi );

      // MakeLogicalVolume --//  
      MakeLVWith(OpenMaterialStore()->Order(list->GetSOLCoilMaterial()));

      // SetVisAttribute ----//
      PaintLV(list->GetSOLCoilVisAtt(), list->GetSOLCoilColor());
   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4SOLCoil::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4SOLCoil::InstallIn( J4VComponent        *,
                           G4RotationMatrix    *, 
                           const G4ThreeVector & )
{ 
   Assemble();			// You MUST call Assemble(); at first.

   // Placement function into mother object...
   SetPVPlacement();
}

//* Draw  --------------------------------------------------------

void J4SOLCoil::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------

void J4SOLCoil::Print() const
{
}
