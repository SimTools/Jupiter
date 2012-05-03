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

#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4HCtable.hh"
#include "G4SDManager.hh"

#include "J4TrackingAction.hh"
#include "J4TrackingActionMessenger.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "J4Global.hh"
#include "J4BreakPoint.hh"
#include <vector>
#include "J4Timer.hh"

J4TrackingAction                   *J4TrackingAction::fgInstance = 0;
//G4int                              J4TrackingAction::fgLastTrackID=-99999;
//=====================================================================
//* Constructor -------------------------------------------------------
J4TrackingAction::J4TrackingAction()
                : fCurrentTrackID(std::numeric_limits<int>::max()),
                  fStoredTrajectoryID(1),
                  fMessenger(0),
                  fTrackCounts(std::numeric_limits<int>::min()) 
{
   if (fgInstance) {
      G4cerr << ">>>>>>> Error in J4TrackingAction::J4TrackingAction" << G4endl
             << "  duplicateing a singleton!"                         << G4endl
             << "  abort"                                             << G4endl;
      abort();
   }

   fMessenger = new J4TrackingActionMessenger(this);

   G4int timerid = -1;
   G4String classname("J4TrackingAction");
   G4String timername("J4TrackingTimer");
   fTrackingTimer = new J4Timer(timerid, classname, timername);

   G4int timerid1=-1;
   G4String cname1("J4TrackingActionTracker");
   G4String tname1("TrackerTimer");
   fTimerTracker=new J4Timer(timerid1, cname1, tname1);

   G4int timerid2=-1;
   G4String cname2("J4TrackingActionCal");
   G4String tname2("CalTimer");
   fTimerCal=new J4Timer(timerid2, cname2, tname2);

   G4int timerid3=-1;
   G4String cname3("J4TrackingActionIRBD");
   G4String tname3("IRBDTimer");
   fTimerIRBD=new J4Timer(timerid3, cname3, tname3);


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

  fTrackingTimer->Start();
  G4double bgnz=(aTrack->GetPosition().z())/cm;
  G4double bgnr=(aTrack->GetPosition().perp())/cm;
  fTimerType=0;
  if( bgnr > 205.0 || ( bgnr > 45.0 && ( bgnz > 260.0 || bgnz < -260.0) ) ) {
    fTimerCal->Start();
    fTimerType=1;
  }
  else if ( ( bgnr <= 205. && bgnr > 40.0 ) 
	    && ( bgnz >= -260.0 && bgnz <= 260.0 ) ) {
    fTimerTracker->Start();
    fTimerType=2;
  }
  else if ( bgnr <= 40.0 ) {
    fTimerIRBD->Start();
    fTimerType=3;
  }

  fCurrentTrack   = aTrack;
  fCurrentTrackID = aTrack->GetTrackID();
  if (fCurrentTrackID > fTrackCounts) fTrackCounts = fCurrentTrackID;

#if 0
  G4cerr << "J4TA__PreUT__1" 
	<< " TID=" << fCurrentTrackID 
	 << " TE(keV)=" << aTrack->GetTotalEnergy()/keV
	 << " KE(keV)=" << aTrack->GetKineticEnergy()/keV
	 << " X(cm)=" << aTrack->GetPosition().x()/cm 
	 << " ," << aTrack->GetPosition().y()/cm
	 << " ," << aTrack->GetPosition().z()/cm
	 << " r=" << aTrack->GetPosition().perp()/cm 
	 << " pid=" << aTrack->GetDefinition()->GetPDGEncoding()
	 << " V=" << aTrack->GetVolume()->GetName()
	<< G4endl;
#endif

#if 0
  G4cerr << "J4Trackingaction..PreUserTrackingAction.1." 
	 << " trackID=" << fCurrentTrackID 
	 << " kinetic energy=" << aTrack->GetKineticEnergy()/MeV << "(MeV)" << G4endl;
  G4cerr << "J4TrackingAction::PreUserTrackingAction.2. time=" 
	 << aTrack->GetGlobalTime()/nanosecond
	 << " position(cm)=" << aTrack->GetPosition().x()/cm 
	 << " ," << aTrack->GetPosition().y()/cm
	 << " ," << aTrack->GetPosition().z()/cm
	 << " r=" << aTrack->GetPosition().perp()/cm 
	 << " pid=" << aTrack->GetDefinition()->GetPDGEncoding() 
	 << G4endl;
#endif

  // Reset current track ID for PreHit making upon starting of a new track

  using namespace std;
  vector<J4VSubTrackingAction *>::iterator iter;
  for (iter = fRegs.begin(); iter != fRegs.end(); iter++) {
    (*iter)->PreTrackDoIt(aTrack);
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
     else if (fStoredTrajectoryID == 0 ) {
       fpTrackingManager->SetStoreTrajectory(false);
     }
     else if (fStoredTrajectoryID == 2 ) {
       fpTrackingManager->SetStoreTrajectory(true);
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
               "*** fail to open a file ("
               + J4Global::GetErrorOutputFilename() + ").";
               G4Exception("J4TrackingAction::UserPreTrackingAction",
	                   "", FatalException,
	                   errorMessage);
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
               "*** fail to open a file (/dev/null) .";
               G4Exception("J4TrackingAction::UserPreTrackingAction",
	                   "", FatalException,
	                   errorMessage);
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
  // void J4TrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{

#if 0
  G4cerr << "J4TrackingAction::PostUserTrackingAction-1-" 
	 << " trackID=" << aTrack->GetTrackID() 
	 << " kinetic energy=" << aTrack->GetKineticEnergy()/MeV << "(MeV)" 
	 << " LastStepNumber=" << aTrack->GetCurrentStepNumber()
	 << " TrackLength=" << aTrack->GetTrackLength()/cm
	 << G4endl;
  G4cerr << "J4TrackingAction::PostUserTrackingAction-2- time=" 
	 << aTrack->GetGlobalTime()/nanosecond
	 << " position(cm)=" << aTrack->GetPosition().x()/cm 
	 << " ," << aTrack->GetPosition().y()/cm
	 << " ," << aTrack->GetPosition().z()/cm
	 << " r=" << aTrack->GetPosition().perp()/cm 
	 << " pid=" << aTrack->GetDefinition()->GetPDGEncoding() 
	 << G4endl;
#endif

  fTrackingTimer->Stop();
  if ( fTimerType == 1 ) {
    fTimerCal->Stop();
  }
  else if ( fTimerType == 2 ) {
    fTimerTracker->Stop();
  }
  else if ( fTimerType == 3 ){
    fTimerIRBD->Stop();
  }

#ifdef __THEBE__

   if (fErrorOfs.is_open()) {
      J4Global::GetGlobal()->CloseErrorOutputStream();
   }

#endif
   
}

//=====================================================================
//* Clear -------------------------------------------------------------
void J4TrackingAction::Clear()
{
  using namespace std;
  vector<J4VSubTrackingAction *>::iterator iter;
  for (iter = fRegs.begin(); iter != fRegs.end(); iter++) {
    (*iter)->Clear();
  }
}

//=====================================================================
//* Clear -------------------------------------------------------------
void J4TrackingAction::Add(J4VSubTrackingAction *stap)
{
  std::vector<J4VSubTrackingAction *>::iterator iter;

  for(iter=fRegs.begin();iter!=fRegs.end();iter++) {
    if( *iter == stap ) { 
      fRegs.erase(iter);
      break;
    }
  } 
  fRegs.push_back(stap);    

  /*
  for(iter=fRegs.begin();iter!=fRegs.end();iter++) {
    if( *iter == stap ) { return ; }
  } 
  fRegs.push_back(stap);    
  */

}
