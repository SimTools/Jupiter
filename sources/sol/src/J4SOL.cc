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
#include "J4MFieldMapStore.hh"
#include "G4TransportationManager.hh"
#include "G4ChordFinder.hh"
#include "J4SOLMField.hh"

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
                               nbrothers, me, copyno),
       J4AttMFieldMap()
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4SOL::~J4SOL()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4SOL::Assemble() 
{   
   if (!GetLV()) {
      J4SOLParameterList *list = OpenParameterList();
      G4double rmin = list->GetSOLInnerR();
      G4double rmax = list->GetSOLOuterR();
      G4double len  = list->GetSOLHalfZ();
      G4double dphi = 360.*deg;
 
      // MakeSolid ----------//
      OrderNewTubs (rmin, rmax, len, dphi);

      // MakeLogicalVolume --//  
      MakeLVWith(OpenMaterialStore()->Order(list->GetSOLMaterial()));

      // SetVisAttribute ----//
      PaintLV(list->GetSOLVisAtt(), list->GetSOLColor());
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


    J4SOLParameterList *list = OpenParameterList(); 
    if (list->GetBField() != 0) {
       SetMField(new J4SOLMField(list)); 

       G4FieldManager* fieldManager= 
       G4TransportationManager::GetTransportationManager()->GetFieldManager();
    
       J4MFieldMapStore* mfManager = J4MFieldMapStore::GetInstance();
       mfManager->NameList();
       Register(mfManager);
       fieldManager->SetDetectorField(mfManager);
       fieldManager->CreateChordFinder(mfManager);
       fieldManager->GetChordFinder()-> SetDeltaChord(3.*mm); // if you need
       fieldManager->SetDeltaOneStep(0.0025*mm);
       fieldManager->SetDeltaIntersection(0.001*mm);
       InstallMField(this);
   }
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
