// $Id$
// ====================================================================
//      J4EventAction.cc
//
//                                 .JLC-CDC, 2001
// ====================================================================
#include <fstream>
#include <iomanip>

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"

#include "J4RunAction.hh"
#include "J4EventAction.hh"

#include "G4VHitsCollection.hh"

#include "J4DetectorConstruction.hh"

// SD of each detector componet

// Visualization
#include "G4UImanager.hh"
#include "G4VVisManager.hh"

  G4int triggered = 0;
  
//#define __VERBOSE__

// ====================================================================
//
// class description
//
// ====================================================================

////////////////////////////////////
J4EventAction::J4EventAction()
////////////////////////////////////
{
}


/////////////////////////////////////////////////////////////////
void J4EventAction::BeginOfEventAction(const G4Event* anEvent)
/////////////////////////////////////////////////////////////////
{
  // printout primary information

#ifdef __VERBOSE__
   G4cout << "%%%%%%%% Primary Information %%%%%%%%%" << G4endl;
   G4int nVtx= anEvent-> GetNumberOfPrimaryVertex();
   G4int i;
   for(i=0; i< nVtx; i++) {
      const G4PrimaryVertex* primaryVertex= anEvent-> GetPrimaryVertex(i);
      primaryVertex-> Print();
   }
   G4cout << "%%%%%%%% Primary Information end EventNo = "
      << anEvent->GetEventID() << " %%%%%%%%%" <<G4endl << G4std::flush;
#endif
J4DetectorConstruction::fExpHall->UnlockOutput();
  HepRandom::saveEngineStatus();
  fEventTimer.Start();
}

///////////////////////////////////////////////////////////////
void J4EventAction::EndOfEventAction(const G4Event* anEvent)
///////////////////////////////////////////////////////////////
{
  const G4RunManager* runManager= G4RunManager::GetRunManager();
  const G4UserRunAction* usrRunAction= runManager-> GetUserRunAction();

  // ====================================================================  
  // printout hit information of each detector

     G4int event = anEvent->GetEventID();

     G4cerr << "**********************************************" << G4endl;
     G4cerr << "******* event number " << event << " *******" <<G4endl;
     G4cerr << "**********************************************" << G4endl;


  // ====================================================================  
  // output "Hit Collection of This Event" to a hit data file
  
  G4HCofThisEvent* HCTE= anEvent-> GetHCofThisEvent();
  
  if(! HCTE) return;  // no hits in this events. nothing to do!
  
  G4cerr << "EventAction :: HCTE = "<< HCTE->GetNumberOfCollections()<<G4endl;
  
  G4std::ofstream& ofs= ((J4RunAction*)usrRunAction)-> GetOutputFileStream();
  if(! ofs.good()) {
    G4String errorMessage= "EventAction::EndOfEventAction(): write error.";
    G4Exception(errorMessage);
  }
  
 
  // =====================================================================
  // Trigger system
  
  // =====================================================================
  // 
  
     ofs << "*******_Start_of_event_" << event << "_*******" <<G4endl;
     
     
     ofs << event << G4endl;
  
     G4cerr << "EventAction::EndOfEvent is called " << G4endl;
     
     J4DetectorConstruction::fExpHall->OutputAll(HCTE);
     
     G4cerr << "EventAction::OutputAll finished " << G4endl;
  
     ofs << "*******_End_of_event_" << event << "_*******" <<G4endl;
  

     fEventTimer.Stop();
     G4cout << "**********************************************" << G4endl;
     G4cout << "******* event "<< event << " finished *******" <<G4endl;
     G4cout << "******* computing time : "
        << fEventTimer.GetRealElapsed() << " [s] *******" <<G4endl;
     G4cout << "**********************************************" << G4endl;
  // ---------------------------------------------------------------------
  // end of event.......
  
          
#if 0

     if(HCTE->GetNumberOfCollections()) {
     	G4int i = 0;
     	for (i; i < HCTE->GetNumberOfCollections() ; i++){
     	  delete HCTE->GetHC(i);		
     	}
     }
     
#endif
    
}
