// $Id$
// ====================================================================
//    J4RunAction.cc
//
//                                   .JLC-CDC, 2001
// ====================================================================
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4Run.hh"

#include "J4RunAction.hh"

// ====================================================================
//
//      class description
//
// ====================================================================

///////////////////////////////////////////////////////////////
J4RunAction::J4RunAction(const G4String& fname)
  : fHitFileName(fname) 
///////////////////////////////////////////////////////////////
{
}


////////////////////////////////////////////////////////
void J4RunAction::BeginOfRunAction(const G4Run* /* aRun */)
////////////////////////////////////////////////////////
{
  fOfs.open(fHitFileName.c_str(), std::ios::out);
  if (! fOfs.good()) {
    G4String errorMessage=
      "*** RunAction::BeginOfRunAtcion(): fail to open a file (" 
      + fHitFileName + ").";
    G4Exception(errorMessage);
  }
  else
  {
    J4VHit::SetOutputFileStream(fOfs);
  }

  // uncomment the following lines, if you want to 
  // automatically clear trajectories etc. in the current view.
//  G4UImanager* UI= G4UImanager::GetUIpointer();
//    UI-> ApplyCommand("/vis/scene/notifyHandlers");
//  if(G4VVisManager::GetConcreteInstance()) 
//    UI-> ApplyCommand("/vis/clear/view");

}

//////////////////////////////////////////////////////
void J4RunAction::EndOfRunAction(const G4Run* aRun)
//////////////////////////////////////////////////////
{
  G4UImanager* UI= G4UImanager::GetUIpointer();
  if (G4VVisManager::GetConcreteInstance()) {
    UI-> ApplyCommand("/vis/scene/notifyHandlers");
    G4UImanager::GetUIpointer()-> ApplyCommand("/vis/draw/update");
  }  
    
  fOfs.close();
  std::cout << "#events generated= " << aRun-> GetNumberOfEvent() << std::endl;
}

