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
#include "J4SOLMessenger.hh"

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
  SetMaxEps(0.5);
  SetMinEps(1.E-5);
  SetDeltaOneStep(0.0025*mm);
  SetDeltaIntersection(0.001*mm);
//  SetDeltaChord(3.0*mm);
  SetDeltaChord(0.1*mm);

  fMessenger=new J4SOLMessenger(this);
}

//=====================================================================
//* destructor --------------------------------------------------------

J4SOL::~J4SOL()
{
  if ( Deregister( fCoil ) ) delete fCoil;
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

      // Install Daugher volume
      fCoil = new J4SOLCoil( this );
      Register( fCoil );
      fCoil -> InstallIn( this );
      SetDaughter( fCoil );
   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4SOL::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4SOL::InstallIn(J4VComponent        *,
                      G4RotationMatrix    *, 
                      const G4ThreeVector &)
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
    std::cerr << "-----------------------------------------------" << std::endl;
    std::cerr << "-----------------------------------------------" << std::endl;
    std::cerr << "J4DetectorConstruction:: new J4MagneticField!!!" << std::endl;
    std::cerr << "-----------------------------------------------" << std::endl;
    std::cerr << "-----------------------------------------------" << std::endl;


    J4SOLParameterList *list = OpenParameterList(); 
    if (list->GetBField() != 0) {
       SetMField(new J4SOLMField(list)); 

       G4FieldManager* fieldManager= 
       G4TransportationManager::GetTransportationManager()->GetFieldManager();
    
       J4MFieldMapStore* mfManager = J4MFieldMapStore::GetInstance();
       mfManager->NameList();
       Register(mfManager);
       fieldManager->SetDetectorField(mfManager);
       fieldManager->SetDeltaOneStep(GetDeltaOneStep());
       fieldManager->SetDeltaIntersection(GetDeltaIntersection());

       fieldManager->SetMinimumEpsilonStep(GetMinEps());
       fieldManager->SetMaximumEpsilonStep(GetMaxEps());
       fieldManager->CreateChordFinder(mfManager);
       fieldManager->GetChordFinder()-> SetDeltaChord(GetDeltaChord()); // if you need
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
