// $Id$
//*************************************************************************
//* --------------------
//* J4SOL
//* --------------------
//* (Description)
//* 	Class for describing Detector Solenoid
//*     
//* (Update Record)
//*	2002/10/28  R.Kuboshima  Original version.
//*************************************************************************

#include "globals.hh"
#include "J4SOL.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4ChordFinder.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4SOL::fFirstName("SOL");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4SOL::J4SOL(J4VDetectorComponent *parent,
                            G4int  nclones,
                            G4int  nbrothers, 
                            G4int  me,
                            G4int  copyno ) :
       J4VSOLDetectorComponent(fFirstName, parent, nclones,
                               nbrothers, me, copyno)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4SOL::~J4SOL()
{
   if (Deregister(fMagField)) delete fMagField;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4SOL::Assemble() 
{   
   if (!GetLV()) {
      G4double rmin = OpenParameterList()->GetIR();
      G4double rmax = OpenParameterList()->GetOR();
      G4double len  = OpenParameterList()->GetLength();
      G4double dphi = 360.*deg;
 
      // MakeSolid ----------//
      OrderNewTubs (rmin, rmax, len, dphi);

      // MakeLogicalVolume --//  
      MakeLVWith(OpenMaterialStore()->Order(OpenParameterList()->GetMaterial()));

      // SetVisAttribute ----//
      PaintLV(OpenParameterList()->GetVisAtt(), OpenParameterList()->GetColor());
   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4SOL::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4SOL::InstallIn(J4VComponent         *mother,
                      G4RotationMatrix     *prot, 
                      const G4ThreeVector  &tlate )
{ 
   Assemble();			// You MUST call Assemble(); at first.

   // Placement function into mother object...

   SetPVPlacement();

   // Set Magnetic field
   
   SetMagField(); 
}

//=====================================================================
//* SetMagField  ------------------------------------------------------

void J4SOL::SetMagField()
{
   G4cerr << "-----------------------------------------------" << G4endl;
   G4cerr << "-----------------------------------------------" << G4endl;
   G4cerr << "J4DetectorConstruction:: new J4MagneticField!!!" << G4endl;
   G4cerr << "-----------------------------------------------" << G4endl;
   G4cerr << "-----------------------------------------------" << G4endl;
   G4FieldManager* fieldManager 
     = G4TransportationManager::GetTransportationManager()->GetFieldManager();

   fMagField= new J4MagneticField(OpenParameterList());
   Register(fMagField);
   fieldManager-> SetDetectorField(fMagField);
   fieldManager-> CreateChordFinder(fMagField);
   fieldManager-> GetChordFinder()-> SetDeltaChord(3.*mm);  // if you need
}

//* Draw  --------------------------------------------------------
void J4SOL::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4SOL::Print() const
{
}
