// $Id$
//*************************************************************************
//* --------------------
//* J4CALSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4TPCPostHit.hh"
#include "J4CALSD.hh"
#include "J4CALPreHit.hh"
#include "J4CAL.hh"
#include "J4CALCone.hh"
#include "J4VCALMiniTower.hh"
#include "J4CALEM.hh"
#include <cmath>

G4int J4CALSD::fgCurrentPreHitID = -1;
G4int J4CALSD::fgTrackRegID      = -1;
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALSD::J4CALSD( J4VDetectorComponent* detector )
                  :J4VSD<J4CALPreHit>( detector )
{
  SetCurrentTrackID( INT_MAX );
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALSD::~J4CALSD()
{
  //#ifndef __GEANT452__
  //  if ( fCalPreHits )  delete fCalPreHits;
  //#endif
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4CALSD::Initialize( G4HCofThisEvent* PreHCTE )
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  
  MakeHitBuf( PreHCTE );

  // Don't delete fCalPreHits!
  // Geant4 deletes hit objects at
  // the end of the run.

  //if ( fCalPreHits ) fCalPreHits = 0;   

}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4CALSD::ProcessHits( G4Step* aStep, G4TouchableHistory* /* ROhist */ )
{
  //In order to use Get function, you must call SetNewStep() at first.
  
  SetNewStep(aStep);
  
  J4VComponent* ptrCAL = GetComponent(0);

  //Get perticle information
  //G4int                 preHitID = 0;
  G4int                 postHitID = J4TPCPostHit::GetCurPostHitID();
  const G4ThreeVector&  pre       = GetPrePosition();
  const G4ThreeVector&  momentum  = GetMomentum();
  //  G4double              edep     = GetEnergyDeposit();
  G4double              energy    = GetKineticEnergy();
  G4double              tof       = GetTof();
  G4int                 trackID   = GetTrackID();
  G4int                 motherTrackID = GetMotherTrackID();
  G4ParticleDefinition* particle = GetParticle(); 
  
  // Create new hit
  if ( trackID < GetCurrentTrackID() ) { 

     fgCurrentPreHitID++;
     SetCurrentTrackID( trackID );
     // create new hit!

     fCurrentPreHitPtr = new J4CALPreHit( ptrCAL, postHitID, fgCurrentPreHitID, pre, momentum, 
					  energy, tof, trackID, particle, motherTrackID );
     
     ( (J4CALPreHitBuf *)GetHitBuf() ) -> insert( fCurrentPreHitPtr );
          
  }   
  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4CALSD::EndOfEvent( G4HCofThisEvent* /* PreHCTE */ )
{			
  SetCurrentPreHitPtr(0);
  SetCurrentPreHitID(-1);
  SetCurrentTrackID( INT_MAX );
}

//=====================================================================
//* clear -------------------------------------------------------------


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4CALSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4CALSD::PrintAll()
{
  G4int nHit= ( (J4CALPreHitBuf*)GetHitBuf() ) -> entries();
  std::cout << "------------------------------------------" << std::endl
            << "*** tracker Hit (#hits=" << nHit << ")" << std::endl;
  ( (J4CALPreHitBuf*)GetHitBuf() ) -> PrintAllHits();
}
