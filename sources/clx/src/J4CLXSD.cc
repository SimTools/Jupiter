// $Id$
//*************************************************************************
//* --------------------
//* J4CLXSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2006/05/01  H.Ono Original version.
//*************************************************************************
//#include "J4CLXEM.hh"
#include "J4TPCPostHit.hh"
#include "J4TPCPostHitKeeper.hh"
#include "J4CLXSD.hh"
#include "J4CLXPreHit.hh"
#include "J4CLXPreHitKeeper.hh"
#include "J4CLXPostHit.hh"
#include "J4CLXPostHitKeeper.hh"
#include "J4CLX.hh"
#include "J4CLXParameterList.hh"
#include "J4TrackingAction.hh"
#include <cmath>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXSD::J4CLXSD( J4VDetectorComponent* detector )
 :J4VSD<J4CLXPreHit>( detector )
{
  J4TrackingAction::GetInstance()->Add(J4CLXPreHitKeeper::GetInstance());
  J4TrackingAction::GetInstance()->Add(J4CLXPostHitKeeper::GetInstance());
}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXSD::~J4CLXSD()
{
  //#ifndef __GEANT452__
  //  if ( fCalPreHits )  delete fCalPreHits;
  //#endif
}

//=====================================================================
//* Initialize --------------------------------------------------------
void J4CLXSD::Initialize( G4HCofThisEvent* PreHCTE )
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
G4bool J4CLXSD::ProcessHits( G4Step* aStep, G4TouchableHistory* /* ROhist */ )
{
  //In order to use Get function, you must call SetNewStep() at first.
  SetNewStep(aStep);

  J4VComponent* ptrCLX = GetComponent(0);

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
  G4ParticleDefinition* particle  = GetParticle(); 
  
  // Create new pre hit --------------------------------------
  J4CLXPreHitKeeper *phkp = J4CLXPreHitKeeper::GetInstance();
  if ( phkp->IsNext() ) { 
     phkp->IncrementCurrentPreHitID();
     G4int preHitID = phkp->GetCurrentPreHitID();
     // create new hit!
     J4CLXPreHit *preHitPtr = new J4CLXPreHit( ptrCLX, postHitID, preHitID, pre, momentum, energy, tof, trackID, particle, motherTrackID );
     phkp->SetCurrentPreHitPtr(preHitPtr);
     ( (J4CLXPreHitBuf *)GetHitBuf() ) -> insert( preHitPtr );
  }

  // Create new postHit! -------------------------------------
  J4CLXPostHitKeeper* postKeeper = J4CLXPostHitKeeper::GetInstance();
  if ( IsExiting( post, momentum ) ) {
    G4int calPostHitID = postKeeper->GetCurPostHitID();
    G4int calPreHitID  = phkp->GetCurrentPreHitID();
    J4CLXPostHit* postHitPtr = new J4CLXPostHit( ptrCLX, calPreHitID, calPostHitID, motherTrackID, particle, tof, energy, momentum, post );
    ( (J4CLXPostHitBuf *)GetHitBuf() ) -> insert( postHitPtr );
  }
  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------
void J4CLXSD::EndOfEvent( G4HCofThisEvent* /* PreHCTE */ )
{			
  J4CLXPreHitKeeper *phkp = J4CLXPreHitKeeper::GetInstance();
  phkp->SetCurrentPreHitPtr(0);
  phkp->SetCurrentPreHitID(-1);
  phkp->Reset();
}

//=====================================================================
//* clear -------------------------------------------------------------

//=====================================================================
//* DrawAll -----------------------------------------------------------
void J4CLXSD::DrawAll() { }

//=====================================================================
//* PrintAll ----------------------------------------------------------
void J4CLXSD::PrintAll()
{
  G4int nHit= ( (J4CLXPreHitBuf*)GetHitBuf() ) -> entries();
  std::cout << "------------------------------------------" << std::endl
            << "*** tracker Hit (#hits=" << nHit << ")" << std::endl;
  ( (J4CLXPreHitBuf*)GetHitBuf() ) -> PrintAllHits();
}

//======================================================================
//* Is Exiting ---------------------------------------------------------
G4bool J4CLXSD::IsExiting( const G4ThreeVector &pos, const G4ThreeVector &p  ) const
{
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();
  static G4double tol = 10.;
    
  if ( std::abs( pos.perp() - ptrList->GetCLXOuterR() ) <= tol*kCarTolerance && p.x() * pos.x() + p.y() * pos.y() > 0.) 
    return true;

  if ( std::abs( std::abs( pos.z() ) - ptrList->GetCLXOuterHalfZ() ) <= tol*kCarTolerance && p.z() * pos.z() > 0.)
     return true;

  return false;
}
