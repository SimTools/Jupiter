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
#include "J4Global.hh"

//=====================================================================
//* PreUserTrackingAction ---------------------------------------------
void J4TrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
#ifdef __THEBE__
#ifdef __DUMPERRORPERTRACK__
   if ( !fErrorOfs.is_open() ) {
      fErrorOfs.open(J4Global::GetErrorOutputFilename().c_str(), ios::out);
      if(! fErrorOfs.good()) {
         G4String errorMessage=
         "*** J4TrackingAction::PreUserTrackingAction:fail to open a file ("
         + J4Global::GetErrorOutputFilename() + ").";
         G4Exception(errorMessage);
      } else {
         J4Global::SetErrorOutputStream(fErrorOfs);
      }
   }
#endif
#endif
   
#ifdef __REMOVENEUTRALTRAJECTORY__  
  // Create trajectory only for charged particles
  
  if(aTrack->GetDefinition()->GetPDGCharge()!=0)
  { fpTrackingManager->SetStoreTrajectory(true); }
  else
  { fpTrackingManager->SetStoreTrajectory(false); }
#endif
}

//=====================================================================
//* PostUserTrackingAction --------------------------------------------
void J4TrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
#ifdef __THEBE__
#ifdef __DUMPERRORPERTRACK__
   J4Global::GetGlobal()->CloseErrorOutputStream();
#endif
#endif
   
}
