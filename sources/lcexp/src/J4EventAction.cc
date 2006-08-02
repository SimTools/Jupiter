// $Id$
// ====================================================================
//      J4EventAction.cc
//
//                                 .JLC-CDC, 2001
// ====================================================================
#ifdef __USEISOCXX__
#include <sstream>
#else
#include <sstream>
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
#include "J4TrackingAction.hh"

#include "G4VHitsCollection.hh"

#include "J4DetectorConstruction.hh"

#include "J4HistoryKeeper.hh"
#include "J4BreakPoint.hh"

// SD of each detector componet

// Visualization
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include <stdlib.h>
  
//#define __VERBOSE__

// ====================================================================
//
// class description
//
// ====================================================================

G4int J4EventAction::fEventID=0;

////////////////////////////////////
J4EventAction::J4EventAction()
////////////////////////////////////
{
   std::cerr << "J4EventAction::constructor called" << std::endl;
   G4int timerid = -1;
   G4String classname("J4EventAction");
   G4String timername("EventTimer");
   std::cerr << "J4EventAction::constructor timer new" << std::endl;
   fEventTimer = new J4Timer(timerid, classname, timername);
   std::cerr << "J4EventAction::constructor timer created" << std::endl;
}

////////////////////////////////////
J4EventAction::~J4EventAction()
////////////////////////////////////
{
   delete fEventTimer;
}

/////////////////////////////////////////////////////////////////
#ifdef __THEBE__
void J4EventAction::BeginOfEventAction(const G4Event* anEvent)
#else
// void J4EventAction::BeginOfEventAction(const G4Event*)
void J4EventAction::BeginOfEventAction(const G4Event* anEvent)
#endif
/////////////////////////////////////////////////////////////////
{
  // printout primary information
  std::cerr << "Start of BeginOfEventAction..." << std::endl;
#ifdef __THEBE__
   if ( J4Global::GetErrorOutputUnit() == "Event" ) {
      if ( !fErrorOfs.is_open() ) {
         fErrorOfs.open(J4Global::GetErrorOutputFilename().c_str(), std::ios::out);
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
   std::cout << "%%%%%%%% Primary Information %%%%%%%%%" << std::endl;
   G4int nVtx= anEvent-> GetNumberOfPrimaryVertex();
   G4int i;
   for(i=0; i< nVtx; i++) {
      const G4PrimaryVertex* primaryVertex= anEvent-> GetPrimaryVertex(i);
      primaryVertex-> Print();  
   }
   std::cout << "%%%%%%%% Primary Information end EventNo = " 
          << anEvent->GetEventID() << " %%%%%%%%%" <<std::endl << std::flush;
#endif  

   J4DetectorConstruction::GetEXPHall()->UnlockOutput();
   fEventTimer->Start();
   J4TrackingAction::GetInstance()->ResetTrackCounter();
   J4TrackingAction::GetInstance()->Clear();   
   

   fEventID=anEvent->GetEventID();
   std::cerr << " End  of BeginOfEventAction of event ID" << fEventID<< std::endl;
}

///////////////////////////////////////////////////////////////
void J4EventAction::EndOfEventAction(const G4Event* anEvent)
///////////////////////////////////////////////////////////////
{
   std::cerr << " Start EndOfEventAction ......" << std::endl;
  const G4RunManager* runManager= G4RunManager::GetRunManager();
  const G4UserRunAction* usrRunAction= runManager-> GetUserRunAction();

  // ====================================================================  
  // printout hit information of each detector

     G4int event = anEvent->GetEventID();

     std::cerr << "**********************************************" << std::endl;
     std::cerr << "*******_event_number_" << event << "_*******" <<std::endl;
     std::cerr << "**********************************************" << std::endl;
     
  // ====================================================================  
  // output "J4BreakPointMap"
#ifdef __DEBUG__
     J4BreakPoint::DebugPrint("debug"); 
#endif
     J4BreakPoint::Output(); 

  // ====================================================================  
  // output "Hit Collection of This Event" to a hit data file
  
  G4HCofThisEvent* HCTE= anEvent-> GetHCofThisEvent();
  
  if(! HCTE) return;  // no hits in this events. nothing to do!
  
  std::cerr << "EventAction :: HCTE = "<< HCTE->GetNumberOfCollections()<<std::endl;
  
  std::ofstream& ofs= ((J4RunAction*)usrRunAction)-> GetOutputFileStream();
  if(! ofs.good()) {
    G4String errorMessage= "EventAction::EndOfEventAction(): write error.";
    G4Exception(errorMessage);
  }
  
 
  // =====================================================================
  // Trigger system
  
  // =====================================================================
  // 
  
   ofs << "*******_Start_of_event_" << event << "_*******" <<std::endl;
     
     
   ofs << event << std::endl;
  
   std::cerr << "EventAction::EndOfEvent is called " << std::endl;
     
   J4DetectorConstruction::GetEXPHall()->OutputAll(HCTE, ofs);
     
   std::cerr << "EventAction::OutputAll finished " << std::endl;
  
   ofs << "*******_End_of_event_" << event << "_*******" <<std::endl;

   fEventTimer->Stop();
//   std::cerr << "**********************************************" << std::endl;
   std::cerr << "*******_event_"<< event << "_finished *******" <<std::endl;
//   std::cerr << "**********************************************" << std::endl;

//   J4Timer::PrintAllAccumulatedTimes();
   
  // ---------------------------------------------------------------------
  // end of event.......

#if __CLHEPVERSION__ >= 2
   using namespace CLHEP;
#endif
#ifdef __USEISOCXX__
   std::stringstream tmpstr;
   tmpstr << "seeds/seed.evt." << std::setw(5) << std::setfill('0')
      << event << std::ends;
   HepRandom::saveEngineStatus(tmpstr.str().data());
#else
   char tmpchar[1024];
   std::sstream tmpstr(tmpchar, 1024);
   tmpstr << "seeds/seed.evt." << std::setw(5) << std::setfill('0')
          << event << std::ends;
   HepRandom::saveEngineStatus(tmpchar);
#endif

#ifdef __THEBE__
   if ( J4Global::GetErrorOutputUnit() == "Event" ) {
      J4Global::GetGlobal()->CloseErrorOutputStream();
   }
#endif
              
}
