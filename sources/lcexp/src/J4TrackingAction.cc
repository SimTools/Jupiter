//$Id: 
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
#include "J4TrackingActionMessenger.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "J4Global.hh"

J4TrackingAction                   *J4TrackingAction::fgInstance = 0;
//=====================================================================
//* Constructor -------------------------------------------------------
J4TrackingAction::J4TrackingAction()
                : fCurrentTrackID(INT_MAX),
                  fStoredTrajectoryID(1),
                  fMessenger(0),
                  fRegs(2),
                  fTrackCounter(INT_MIN) 
{
   if (fgInstance) {
      G4cerr << ">>>>>>> Error in J4TrackingAction::J4TrackingAction" << G4endl
             << "  duplicateing a singleton!"                         << G4endl
             << "  abort"                                             << G4endl;
      abort();
   }

   fMessenger = new J4TrackingActionMessenger(this);

#ifdef __THEBE__
   fStoredDebugPrintID = -2;   
#endif
   fgInstance = this;

}

//=====================================================================
//* Destructor -------------------------------------------------------
J4TrackingAction::~J4TrackingAction()
{
   if (fMessenger) delete fMessenger;
}

//=====================================================================
//* PreUserTrackingAction ---------------------------------------------
void J4TrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{

  // Create trajectory only for charged particles

  fCurrentTrackID = aTrack->GetTrackID();
  if (fCurrentTrackID > fTrackCounter) fTrackCounter = fCurrentTrackID;

  // Reset current track ID for PreHit making upon starting of a new track

  using namespace std;
  vector<Pair>::iterator iter;
  for (iter = fRegs.begin(); iter != fRegs.end(); iter++) {
    if ((*iter).fSecond != INT_MAX && fCurrentTrackID < (*iter).fSecond) {
        (*iter).fSecond = INT_MAX;
    }
  }
  
#ifdef G4_STORE_TRAJECTORY
//  if (fpTrackingManager && fpTrackingManager->GetStoreTrajectory()) { 
     if (fStoredTrajectoryID == 1) {
        // charged particle only
        if (aTrack->GetDefinition()->GetPDGCharge()) {
            fpTrackingManager->SetStoreTrajectory(true); 
        } else {
            fpTrackingManager->SetStoreTrajectory(false); 
        }
     }
//  }
#endif


#ifdef __THEBE__
   if (J4Global::GetErrorOutputUnit() == "Track") {
  
      static G4int callNo = 0;
 
      std::cerr << "***** J4TrackingAction::PreUserTrackingAction:Track_" 
             << fCurrentTrackID << "_Start ****** "<< std::endl;


      if (fStoredDebugPrintID == -1 || fStoredDebugPrintID == fCurrentTrackID) {
      
         if ( fStoredDebugPrintID == fCurrentTrackID) {
            fErrorOfs.close();
            callNo = 0;
         }

         if ( !fErrorOfs.is_open()) {
            fErrorOfs.open(J4Global::GetErrorOutputFilename().c_str(), std::ios::out);
            if(! fErrorOfs.good()) {
               G4String errorMessage=
               "*** J4TrackingAction::PreUserTrackingAction:fail to open a file ("
               + J4Global::GetErrorOutputFilename() + ").";
               G4Exception(errorMessage);
            } 
         }

      } else {
         // no output.

         // !!!!  ATTENTIOH  !!!ii //
         // temporary treatment !
         // Only in the case of G4Global::StoredNEvents == 0, it works correctly 

         if (callNo == 0) {
            fErrorOfs.open("/dev/null", std::ios::out);
            if(! fErrorOfs.good()) {
               G4String errorMessage=
               "*** J4TrackingAction::PreUserTrackingAction:fail to open a file (/dev/null) .";
               G4Exception(errorMessage);
            }
            callNo++;
         } 

      }

      J4Global::SetErrorOutputStream(fErrorOfs);

   }

#endif
   
}

//=====================================================================
//* PostUserTrackingAction --------------------------------------------
void J4TrackingAction::PostUserTrackingAction(const G4Track* /* aTrack */)
{

#ifdef __THEBE__

   if (fErrorOfs.is_open()) {
      J4Global::GetGlobal()->CloseErrorOutputStream();
   }

#endif
   
}

//=====================================================================
//* IsNext ------------------------------------------------------------

G4bool J4TrackingAction::IsNext(G4int &detid)
{ 
   G4int n2nds   = GetTrackingManager()->GimmeSecondaries()->size();
   G4int trackid = n2nds ? fTrackCounter + n2nds + 1 : fCurrentTrackID;
   if (detid < 0) {
      fRegs.push_back(Pair(fCurrentTrackID, trackid));
      detid = fRegs.size() - 1;
   } else if (fRegs[detid].fFirst == fCurrentTrackID ||
              fRegs[detid].fSecond <= fCurrentTrackID) {
      return FALSE;
   } else {
      fRegs[detid] = Pair(fCurrentTrackID, trackid);
   }
   return TRUE;
}


