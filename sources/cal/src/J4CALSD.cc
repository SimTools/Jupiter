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
#include "J4TPCPostHitKeeper.hh"
#include "J4CALSD.hh"
#include "J4CALPreHit.hh"
#include "J4CALPreHitKeeper.hh"
#include "J4CALPostHit.hh"
#include "J4CALPostHitKeeper.hh"
#include "J4CAL.hh"
#include "J4CALCone.hh"
#include "J4VCALMiniTower.hh"
#include "J4CALEM.hh"
#include "J4CALParameterList.hh"
#include "J4TrackingAction.hh"
#include "J4HistoryKeeper.hh"
#include <cmath>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CALSD::J4CALSD( J4VDetectorComponent* detector )
 :J4VSD<J4CALPreHit>( detector )
{
  J4TrackingAction::GetInstance()->Add(J4CALPreHitKeeper::GetInstance());
#if 1
  J4TrackingAction::GetInstance()->Add(J4HistoryKeeper::GetInstance());
  J4HistoryKeeper::GetInstance()->SetPHitKeeperPtr(J4CALPreHitKeeper::GetInstance());
#endif
  J4TrackingAction::GetInstance()->Add(J4CALPostHitKeeper::GetInstance());
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
  G4int                 postHitID = J4TPCPostHitKeeper::GetInstance()->GetCurPostHitID();
  const G4ThreeVector&  pre       = GetPrePosition();
  const G4ThreeVector&  post      = GetPostPosition();
  const G4ThreeVector&  momentum  = GetMomentum();
  //  G4double              edep     = GetEnergyDeposit();
  G4double              energy    = GetKineticEnergy();
  G4double              tof       = GetTof();
  G4int                 trackID   = GetTrackID();
  G4int                 motherTrackID = GetMotherTrackID();
  G4ParticleDefinition* particle = GetParticle(); 
  
  // Create new pre hit --------------------------------------
  J4CALPreHitKeeper *phkp = J4CALPreHitKeeper::GetInstance();
  if ( phkp->IsNext() ) { 
     phkp->IncrementCurrentPreHitID();
     G4int preHitID = phkp->GetCurrentPreHitID();
     // create new hit!
     J4CALPreHit *preHitPtr = new J4CALPreHit( ptrCAL, postHitID, preHitID, pre, momentum, energy, tof, trackID, particle, motherTrackID );
     phkp->SetCurrentPreHitPtr(preHitPtr);
     ( (J4CALPreHitBuf *)GetHitBuf() ) -> insert( preHitPtr );
  }

  // Create new postHit! -------------------------------------
  J4CALPostHitKeeper* postKeeper = J4CALPostHitKeeper::GetInstance();
  if ( IsExiting( post, momentum ) ) {
    G4int calPostHitID = postKeeper->GetCurPostHitID();
    G4int calPreHitID  = phkp->GetCurrentPreHitID();
    J4CALPostHit* postHitPtr = new J4CALPostHit( ptrCAL, calPreHitID, calPostHitID, motherTrackID, particle, tof, energy, momentum, post );
    ( (J4CALPostHitBuf *)GetHitBuf() ) -> insert( postHitPtr );
  }
  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------
void J4CALSD::EndOfEvent( G4HCofThisEvent* /* PreHCTE */ )
{			
  J4CALPreHitKeeper *phkp = J4CALPreHitKeeper::GetInstance();
  phkp->SetCurrentPreHitPtr(0);
  phkp->SetCurrentPreHitID(-1);
  phkp->Reset();
}

//=====================================================================
//* clear -------------------------------------------------------------

//=====================================================================
//* DrawAll -----------------------------------------------------------
void J4CALSD::DrawAll() { }

//=====================================================================
//* PrintAll ----------------------------------------------------------
void J4CALSD::PrintAll()
{
  G4int nHit= ( (J4CALPreHitBuf*)GetHitBuf() ) -> entries();
  std::cout << "------------------------------------------" << std::endl
            << "*** tracker Hit (#hits=" << nHit << ")" << std::endl;
  ( (J4CALPreHitBuf*)GetHitBuf() ) -> PrintAllHits();
}

//======================================================================
//* Is Exiting ---------------------------------------------------------
G4bool J4CALSD::IsExiting( const G4ThreeVector &pos, const G4ThreeVector &p  ) const
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  static G4double tol = 10.;
    
  if ( std::abs( pos.perp() - ptrList->GetCALOuterR() ) <= tol*kCarTolerance && p.x() * pos.x() + p.y() * pos.y() > 0.) 
    return true;

  if ( std::abs( std::abs( pos.z() ) - ptrList->GetCALOuterHalfZ() ) <= tol*kCarTolerance && p.z() * pos.z() > 0.)
     return true;

  return false;
}
