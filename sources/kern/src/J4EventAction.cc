// $Id$
// ====================================================================
//      J4EventAction.cc
//
//                                 .JLC-CDC, 2001
// ====================================================================
#ifdef __USEISOCXX__
#include <sstream>
#else
#include <strstream>
#endif
#include <fstream>
#include <iomanip>
#include "J4Global.hh"
#include "J4Timer.hh"

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
   G4cerr << "J4EventAction::constructor called" << G4endl;
   G4int timerid = -1;
   G4String classname("J4EventAction");
   G4String timername("EventTimer");
   G4cerr << "J4EventAction::constructor timer new" << G4endl;
   fEventTimer = new J4Timer(timerid, classname, timername);
   G4cerr << "J4EventAction::constructor timer created" << G4endl;
}

////////////////////////////////////
J4EventAction::~J4EventAction()
////////////////////////////////////
{
   delete fEventTimer;
}

/////////////////////////////////////////////////////////////////
void J4EventAction::BeginOfEventAction(const G4Event* anEvent)
/////////////////////////////////////////////////////////////////
{
  // printout primary information
#ifdef __THEBE__
   if ( J4Global::GetErrorOutputUnit() == "Event" ) {
      if ( !fErrorOfs.is_open() ) {
         fErrorOfs.open(J4Global::GetErrorOutputFilename().c_str(), ios::out);
         if(! fErrorOfs.good()) {
            G4String errorMessage=
            "*** EventAction::BeginOfEventAction():fail to open a file ("
            + J4Global::GetErrorOutputFilename() + ").";
            G4Exception(errorMessage);
         } else {
            J4Global::SetErrorOutputStream(fErrorOfs);
         }
      }
   }
#endif
         
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
   fEventTimer->Start();
   
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
     G4cerr << "*******_event_number_" << event << "_*******" <<G4endl;
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

   fEventTimer->Stop();
   G4cerr << "**********************************************" << G4endl;
   G4cerr << "*******_event_"<< event << "_finished *******" <<G4endl;
   G4cerr << "**********************************************" << G4endl;

   J4Timer::PrintAllAccumulatedTimes();
   
  // ---------------------------------------------------------------------
  // end of event.......

#ifdef __USEISOCXX__
   G4std::stringstream tmpstr;
   tmpstr << "seeds/seed.evt." << G4std::setw(5) << G4std::setfill('0')
      << event << G4std::ends;
   HepRandom::saveEngineStatus(tmpstr.str().data());
#else
   char tmpchar[1024];
   G4std::strstream tmpstr(tmpchar, 1024);
   tmpstr << "seeds/seed.evt." << G4std::setw(5) << G4std::setfill('0')
          << event << G4std::ends;
   HepRandom::saveEngineStatus(tmpchar);
#endif

#ifdef __THEBE__
   if ( J4Global::GetErrorOutputUnit() == "Event" ) {
      J4Global::GetGlobal()->CloseErrorOutputStream();
   }
#endif
              
}
