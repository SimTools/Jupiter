// $Id$
// ====================================================================
//    Jupiter.cc
//   
//    Exapmle program provided by JLC-CDC group.
//
//    NOTE:
//    Please contact me(hoshina@jlcux1.kek.jp) if any problems 
//    or questions. DO NOT bother Geant4 developpers and Geant4 Users
//    Group Japan.
//
//                                K.Hoshina , 2001
// ====================================================================

#define __INSTALLIR__  
#define __INSTALLBD__  
#define __INSTALLVTX__  
#define __INSTALLIT__  
#define __INSTALLCDC__  
#define __INSTALLCAL__  
#define __INSTALLSOL__  


#ifdef __USEISOCXX__
#include <sstream>
#else
#include <sstream>
#endif
#include "G4RunManager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "J4DetectorConstruction.hh"
#include "J4PhysicsList.hh"
#include "J4PrimaryGeneratorAction.hh"
#include "J4RunAction.hh"
#include "J4EventAction.hh"
#include "J4TrackingAction.hh"
#include "TBookKeeper.hh"

#ifdef G4VIS_USE
#include "J4VisManager.hh"
#endif

//#include "CLHEP/Random/Random.h"

#include "J4IR.hh"
#include "J4BD.hh"
#include "J4VTX.hh"
#include "J4IT.hh"
#include "J4CDC.hh"
#include "J4CAL.hh"
#include "J4SOL.hh"

TBookKeeper* TBookKeeper::fgBookKeeper = new TBookKeeper(); 

int main(int argc, char** argv) 
{

  //-------------------------
  // Set random engine....
  //-------------------------
  // if you want to change a random engine, for example, ...
  
#if 0
  HepJamesRandom randomEngine;
  //RanecuEngine randomEngine;
  HepRandom::setTheEngine(&randomEngine);
#endif

  //-------------------------
  // Set manager 
  //-------------------------

  G4RunManager* runManager = new G4RunManager;  std::cout << std::endl;
//  runManager->SetVerboseLevel(2);

  //*--------------------------------------------
  //* Install detector components...
  //*--------------------------------------------
  
  J4DetectorConstruction* dtcptr = new J4DetectorConstruction;
  
  //* beam line 
  
#ifdef __INSTALLIR__  
  J4IR *irptr = new J4IR();
  irptr->SetMother(dtcptr->GetEXPHall());
  dtcptr->AddComponent(irptr);
#endif
  
#ifdef __INSTALLBD__  
  J4BD *bdptr = new J4BD();
  bdptr->SetMother(dtcptr->GetEXPHall());
  dtcptr->AddComponent(bdptr);
#endif

  //* vtx 
#ifdef __INSTALLVTX__  
  J4VTX *vtxptr = new J4VTX();
  vtxptr->SetMother(dtcptr->GetEXPHall());
  dtcptr->AddComponent(vtxptr);
#endif
  
  //* intermediate tracker 
  
#ifdef __INSTALLIT__  
  J4IT *itptr = new J4IT();
  itptr->SetMother(dtcptr->GetEXPHall());
  dtcptr->AddComponent(itptr);
#endif
  
  //* cdc 
    
#ifdef __INSTALLCDC__  
  J4CDC *cdcptr = new J4CDC();
  cdcptr->SetMother(dtcptr->GetEXPHall());
  dtcptr->AddComponent(cdcptr);
#endif

  //* calorimeter 
    
#ifdef __INSTALLCAL__  
  J4CAL *calptr = new J4CAL();
  calptr->SetMother(dtcptr->GetEXPHall());
  dtcptr->AddComponent(calptr);
#endif
  
  //* Solenoid Magnet (should come last)
    
#ifdef __INSTALLSOL__  
  J4SOL *solptr = new J4SOL();
  solptr->SetMother(dtcptr->GetEXPHall());
  dtcptr->AddComponent(solptr);
#endif

  //*--------------------------------------------
  //* Installation of detectors end
  //*--------------------------------------------
       
  runManager-> SetUserInitialization(dtcptr);
  
  // particles and physics processes

  runManager-> SetUserInitialization(new J4PhysicsList);

  //---------------------------------------------
  // set mandatory user action class...
  
  //* primary generator

  J4PrimaryGeneratorAction* primarygenerator = new J4PrimaryGeneratorAction;
  
  runManager-> SetUserAction(primarygenerator);

  //* user action classes... (optional)

  runManager-> SetUserAction(new J4RunAction);
  runManager-> SetUserAction(new J4EventAction);
  runManager-> SetUserAction(new J4TrackingAction);

#ifdef G4VIS_USE
  // initialize visualization package
  G4VisManager* visManager= new J4VisManager;
  visManager-> Initialize();
  std::cerr << " ------------------------------- " << std::endl
         << " ---- J4VisManager created! ---- " << std::endl
         << " ------------------------------- " << std::endl;
  std::cerr << std::endl;
#endif

  //-----------------------
  // user session start
  //-----------------------

  runManager-> Initialize();
  
  
  //*--------------------------------------------
  //* SwitchOn/Off your detector...
  //*--------------------------------------------
  //* If you wants call SwitchOn/Off recursively,
  //* call virtual function with resolver, as
  //* "J4VDetectorComponent::SwitchOn()".
  //* SwitchOn/(Off() requires option flag
  //* "recursive" or other strings, however,
  //* default value is set as "recursive".
 
 
  //* vtx 
#ifdef __INSTALLVTX__
  vtxptr->J4VDetectorComponent::SwitchOn();
#endif
   
  //* it 
#ifdef __INSTALLIT__
  itptr->J4VDetectorComponent::SwitchOn();
#endif

  //* cdc 
  
  // SwitchOn all SDs.
#ifdef __INSTALLCDC__
  cdcptr->J4VDetectorComponent::SwitchOn(); 
#if 0 
  // Then, SwitchOff only SenseWires.
  for (G4int i=0; i<10; i++) {
     for (G4int j=0; j<5; j++) {
#ifdef __USEISOCXX__
        stringstream str;
#else
	char tmpst[1024];
        strstream str(tmpst, 1024);
#endif
        str << "EXPName:CDC:Layer0" << i << ":Cell:DriftRegion"
            << j << ":SenseWire" << std::ends;           
        G4String name;
        str >> name;
        J4VDetectorComponent::GetComponentPtrByName(name)->SwitchOff(); 
     }
  }
#endif
#endif

  //* cal 
#ifdef __INSTALLCAL__
  calptr->J4VDetectorComponent::SwitchOn();
#endif
        
  //*--------------------------------------------
  //* Detector Switch end
  //*--------------------------------------------
  
    
  if (argc==1) { 		// interactive session, if no arguments given

#ifdef USE_CSH_TERMINAL    
    // csh-like
    G4UIterminal* session= new G4UIterminal();
    session-> SetPrompt("G4test(%s)[%/]:");
#else
    // tcsh-like
    G4UItcsh* tcsh= new 
      G4UItcsh("[36mJUPITER[33m(%s)[32m[%/][36m[%h][37m:");
    G4UIterminal* session= new G4UIterminal(tcsh);
    tcsh-> SetLsColor(GREEN, CYAN);
#endif

    session-> SessionStart();
    delete session;

  } else { 			// batch mode

    G4UImanager* UImanager= G4UImanager::GetUIpointer();
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager-> ApplyCommand(command+fileName);

  }

  //-----------------------
  // terminating...
  //-----------------------

#ifdef G4VIS_USE
  delete visManager;
#endif

  delete runManager;  std::cout << std::endl;
  return 0;

}

