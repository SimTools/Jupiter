// $Id$
//*************************************************************************
//* --------------------
//* J4IRFCALPreHitSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2006/06/03  A.Miyamoto For FCALPreHit
//*************************************************************************
#include "J4IRFCALPreHitSD.hh"
#include "J4IRFCALPreHitKeeper.hh"
#include "J4IRFCALPreHit.hh"
#include "J4IRFCAL.hh"
#include "J4TrackingAction.hh"
#include "J4HistoryKeeper.hh"
#include "J4ParameterTable.hh"
#include <cmath>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4IRFCALPreHitSD::J4IRFCALPreHitSD( J4IRFCAL* detector )
 :J4VSD<J4IRFCALPreHit>( detector )
{
  J4TrackingAction::GetInstance()->Add(J4IRFCALPreHitKeeper::GetInstance());
#if 1
  if( JSFParameterTable::GetValue("J4IR.FCAL.KeepHistory",true) ) {
    J4TrackingAction::GetInstance()->Add(J4HistoryKeeper::GetInstance());
    J4HistoryKeeper::GetInstance()->SetPHitKeeperPtr(J4IRFCALPreHitKeeper::GetInstance());
  }
#endif
  //  J4TrackingAction::GetInstance()->Add(J4IRFCALPostHitKeeper::GetInstance());
}

//=====================================================================
//* destructor --------------------------------------------------------
J4IRFCALPreHitSD::~J4IRFCALPreHitSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------
void J4IRFCALPreHitSD::Initialize( G4HCofThisEvent* PreHCTE )
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
G4bool J4IRFCALPreHitSD::ProcessHits( G4Step* aStep, G4TouchableHistory* /* ROhist */ )
{
  //In order to use Get function, you must call SetNewStep() at first.
  SetNewStep(aStep);

  J4VComponent* ptrCAL = GetComponent(0);

  //Get perticle information
  // G4int                 preHitID = 0;
  G4int                 postHitID = 0;
  const G4ThreeVector&  pre       = GetPrePosition();
  //  const G4ThreeVector&  post      = GetPostPosition();
  const G4ThreeVector&  momentum  = GetMomentum();
  //  G4double              edep     = GetEnergyDeposit();
  G4double              energy    = GetKineticEnergy();
  G4double              tof       = GetTof();
  G4int                 trackID   = GetTrackID();
  G4int                 motherTrackID = GetMotherTrackID();
  G4ParticleDefinition* particle = GetParticle(); 
  
  //  std::cerr << "IRFCALPreHitSD::ProcessHit is called " ;
  //  std::cerr << " trackID=" << trackID << std::endl;

  // Create new pre hit --------------------------------------
  J4IRFCALPreHitKeeper *phkp = J4IRFCALPreHitKeeper::GetInstance();
  if ( phkp->IsNext() ) { 
     phkp->IncrementCurrentPreHitID();
     G4int preHitID = phkp->GetCurrentPreHitID();
     // create new hit!
     J4IRFCALPreHit *preHitPtr = new J4IRFCALPreHit( ptrCAL, postHitID, preHitID, pre, momentum, energy, tof, trackID, particle, motherTrackID );
     phkp->SetCurrentPreHitPtr(preHitPtr);
     ( (J4IRFCALPreHitBuf *)GetHitBuf() ) -> insert( preHitPtr );
  }

#if 0
  // Create new postHit! -------------------------------------
  J4CALPostHitKeeper* postKeeper = J4CALPostHitKeeper::GetInstance();
  if ( IsExiting( post, momentum ) ) {
    G4int calPostHitID = postKeeper->GetCurPostHitID();
    G4int calPreHitID  = phkp->GetCurrentPreHitID();
    J4CALPostHit* postHitPtr = new J4CALPostHit( ptrCAL, calPreHitID, calPostHitID, motherTrackID, particle, tof, energy, momentum, post );
    ( (J4CALPostHitBuf *)GetHitBuf() ) -> insert( postHitPtr );
  }
#endif
  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------
void J4IRFCALPreHitSD::EndOfEvent( G4HCofThisEvent* /* PreHCTE */ )
{			
  J4IRFCALPreHitKeeper *phkp = J4IRFCALPreHitKeeper::GetInstance();
  phkp->SetCurrentPreHitPtr(0);
  phkp->SetCurrentPreHitID(-1);
  phkp->Reset();
}

//=====================================================================
//* clear -------------------------------------------------------------

//=====================================================================
//* DrawAll -----------------------------------------------------------
void J4IRFCALPreHitSD::DrawAll() { }

//=====================================================================
//* PrintAll ----------------------------------------------------------
void J4IRFCALPreHitSD::PrintAll()
{
  G4int nHit= ( (J4IRFCALPreHitBuf*)GetHitBuf() ) -> entries();
  std::cout << "------------------------------------------" << std::endl
            << "*** tracker Hit (#hits=" << nHit << ")" << std::endl;
  ( (J4IRFCALPreHitBuf*)GetHitBuf() ) -> PrintAllHits();
}
#if 0
//======================================================================
//* Is Exiting ---------------------------------------------------------
G4bool J4IRFCALPreHitSD::IsExiting( const G4ThreeVector &pos, const G4ThreeVector &p  ) const
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  static G4double tol = 10.;
    
  if ( std::abs( pos.perp() - ptrList->GetCALOuterR() ) <= tol*kCarTolerance && p.x() * pos.x() + p.y() * pos.y() > 0.) 
    return true;

  if ( std::abs( std::abs( pos.z() ) - ptrList->GetCALOuterHalfZ() ) <= tol*kCarTolerance && p.z() * pos.z() > 0.)
     return true;
  return false;
}
#endif
