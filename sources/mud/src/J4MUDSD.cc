// $Id$
//*************************************************************************
//* --------------------
//* J4MUDSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "J4CALPreHit.hh"
#include "J4CALPreHitKeeper.hh"
#include "J4CALPostHit.hh"
#include "J4CALPostHitKeeper.hh"
#include "J4MUDSD.hh"
#include "J4MUDPreHit.hh"
#include "J4MUDPreHitKeeper.hh"
#include "J4MUD.hh"
#include "J4TrackingAction.hh"
#include <cmath>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4MUDSD::J4MUDSD( J4VDetectorComponent* detector )
 : J4VSD<J4MUDPreHit>( detector ) /*, fMUDPreHits(-1) */
{
  J4TrackingAction::GetInstance()->Add(J4MUDPreHitKeeper::GetInstance());
}

//=====================================================================
//* destructor --------------------------------------------------------
J4MUDSD::~J4MUDSD()
{
  //#ifndef __GEANT452__
  //  if ( fCalPreHits )  delete fCalPreHits;
  //#endif
}

//=====================================================================
//* Initialize --------------------------------------------------------
void J4MUDSD::Initialize( G4HCofThisEvent* PreHCTE )
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  
  MakeHitBuf( PreHCTE );

  // Don't delete fCalPreHits!
  // Geant4 deletes hit objects at
  // the end of the run.
  //if ( fCalPreHits ) fCalPreHits = 0;   
  //if ( fMUDPreHits ) fMUDPreHits = 0;   
}

//=====================================================================
//* ProcessHits -------------------------------------------------------
G4bool J4MUDSD::ProcessHits( G4Step* aStep, G4TouchableHistory* /* ROhist */ )
{
  //In order to use Get function, you must call SetNewStep() at first.
  SetNewStep(aStep);
  
  J4VComponent* ptrMUD = GetComponent();

  //Get perticle information
  G4int                 calPostHitID  = J4CALPostHitKeeper::GetInstance()->GetCurPostHitID();
  G4int                 calPreHitID   = J4CALPreHitKeeper::GetInstance()->GetCurrentPreHitID();
  const G4ThreeVector&  pre           = GetPrePosition();
  const G4ThreeVector&  momentum      = GetMomentum();
  G4double              energy        = GetTotalEnergy();
  G4double              tof           = GetTof();
  G4int                 trackID       = GetTrackID();
  G4int                 motherTrackID = GetMotherTrackID();
  G4ParticleDefinition* particle      = GetParticle(); 
  
  // Create new hit
  J4MUDPreHitKeeper *phkp = J4MUDPreHitKeeper::GetInstance();
  if ( phkp->IsNext() && IsFront( pre, momentum ) ) { 

     phkp->IncrementCurrentPreHitID();
     G4int preHitID = phkp->GetCurrentPreHitID();

     // create new hit!
     J4MUDPreHit *preHitPtr = new J4MUDPreHit( ptrMUD, preHitID, calPostHitID, calPreHitID, pre, momentum, 
                                               energy, tof, particle, trackID, motherTrackID );

     phkp->SetCurrentPreHitPtr(preHitPtr);
     ( (J4MUDPreHitBuf *)GetHitBuf() ) -> insert( preHitPtr );
  }   
  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------
void J4MUDSD::EndOfEvent( G4HCofThisEvent* /* PreHCTE */ )
{			
  J4MUDPreHitKeeper *phkp = J4MUDPreHitKeeper::GetInstance();
  phkp->SetCurrentPreHitPtr(0);
  phkp->SetCurrentPreHitID(-1);
  phkp->Reset();
}

//=====================================================================
//* clear -------------------------------------------------------------

//=====================================================================
//* DrawAll -----------------------------------------------------------
void J4MUDSD::DrawAll() { }

//=====================================================================
//* PrintAll ----------------------------------------------------------
void J4MUDSD::PrintAll()
{
  G4int nHit= ( (J4MUDPreHitBuf*)GetHitBuf() ) -> entries();
  std::cout << "------------------------------------------" << std::endl
            << "*** tracker Hit (#hits=" << nHit << ")" << std::endl;
  ( (J4MUDPreHitBuf*)GetHitBuf() ) -> PrintAllHits();
}

//=====================================================================
//* IsFront -----------------------------------------------------------
G4bool J4MUDSD::IsFront( const G4ThreeVector& pos, const G4ThreeVector& p ) const
{
  J4MUDParameterList* ptrList = J4MUDParameterList::GetInstance();
  static G4double tolerance = 5.;
   
  if ( abs( pos.perp() - ptrList->GetMUDInnerR() ) <= tolerance*kCarTolerance && p.x() * pos.x() + p.y() * pos.y() > 0. ) 
    return true;
  if ( abs( abs(pos.z()) - ptrList->GetMUDFrontEndcapFrontZ() ) <= tolerance*kCarTolerance && p.z() * pos.z() > 0. ) 
    return true;
  
  return false;
}
