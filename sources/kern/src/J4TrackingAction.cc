// $Id: 
//*************************************************************************
//* --------------------
//* J4TrackingAction
//* --------------------
//* (Description)
//*    Derivated class for UserTrackingAction. 
//*
//* (Update Record)
//*     2000/12/08  K.Hoshina   Original version.
//*************************************************************************

#include "J4TrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"

void J4TrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
#if 1  
  // Create trajectory only for primaries
  
  if(aTrack->GetDefinition()->GetPDGCharge()!=0)
  { fpTrackingManager->SetStoreTrajectory(true); }
  else
  { fpTrackingManager->SetStoreTrajectory(false); }
#endif
}


