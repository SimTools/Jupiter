//*************************************************************************
//* --------------------
//* J4PHitKeeper
//* --------------------
//* (Description)
//*     Base class to book keep pre or post hits.
//* (Update Record)
//*     2004/12/09  K.Fujii     Original version.
//*************************************************************************

#include "J4PHitKeeper.hh"
#include "J4TrackingAction.hh"
#include "G4TrackingManager.hh"

//=====================================================================
//* Constructor -------------------------------------------------------
J4PHitKeeper::J4PHitKeeper()
            : fInTrackID (INT_MAX),
              fTopTrackID(INT_MAX),
              fIsPHitCreated(false)
{
}

//=====================================================================
//* Destructor -------------------------------------------------------
J4PHitKeeper::~J4PHitKeeper()
{
}

//=====================================================================
//* PreTrackDoIt ------------------------------------------------------
void J4PHitKeeper::PreTrackDoIt(const G4Track *aTrack)
{
  // Create trajectory only for charged particles

  G4int curTrackID = aTrack->GetTrackID();

  // Reset current track ID for PreHit making upon starting of a new track
#ifdef __DEBUG__
  G4cerr << " bfInTrackID = "     << fInTrackID
         << " bfcurTrackID = "    << curTrackID
         << " bfTopTrackID = "    << fTopTrackID
         << " bfisPHitCreated = " << fIsPHitCreated << G4endl;
#endif

  if (curTrackID < fTopTrackID) {
     fInTrackID  = INT_MAX;
     fTopTrackID = INT_MAX;
     fIsPHitCreated = false;
  }
#ifdef __DEBUG__
  G4cerr << " afInTrackID = "     << fInTrackID
         << " afcurTrackID = "    << curTrackID
         << " afTopTrackID = "    << fTopTrackID
         << " afisPHitCreated = " << fIsPHitCreated << G4endl;
#endif
}

//=====================================================================
//* IsNext ------------------------------------------------------------

G4bool J4PHitKeeper::IsNext()
{ 
  J4TrackingAction *tap        = J4TrackingAction::GetInstance();
  G4int             curTrackID = tap->GetCurrentTrackID();
#ifdef __DEBUG__
  G4cerr << " bNCurrentSD = "      << this
         << " bNfInTrackID = "     << fInTrackID
         << " bNfcurTrackID = "    << curTrackID
         << " bNfTopTrackID = "    << fTopTrackID
         << " bNfisPHitCreated = " << fIsPHitCreated << G4endl;
#endif

  if (fInTrackID == curTrackID || fTopTrackID <= curTrackID) {
    return FALSE;
  } else {
    fInTrackID  = curTrackID;
    G4int n2nds = tap->GetTrackingManager()->GimmeSecondaries()->size();
    fTopTrackID = n2nds ? tap->GetTrackCounts() + n2nds + 1 : curTrackID;
  }
  fIsPHitCreated = true;
  return TRUE;
}

//=====================================================================
//* Reset -------------------------------------------------------------

void J4PHitKeeper::Reset(G4int n)
{
  fInTrackID  = n;                
  fTopTrackID = n;               
  fIsPHitCreated = false;
}
