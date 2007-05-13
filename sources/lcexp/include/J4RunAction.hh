// $Id$
// ====================================================================
//    J4RunAction.hh
//
//    A user's optional action class which defines the user's action 
//    at the begining and the end of each run. 
//
//    The user can override the following two methods;
//      virtual void BeginOfRunAction(const G4Run* aRun);
//      virtual void EndOfRunAction(const G4Run* aRun);
//
//    This class must be set to G4RunManager via 
//    G4RunManager::SetUserAction() method.
//
//                                   .JLC-CDC, 2001
// ====================================================================
#ifndef J4_RUN_ACTION_H
#define J4_RUN_ACTION_H

#include <fstream>
#include "G4UserRunAction.hh"
#include "J4VHit.hh"
#include "J4RunActionMessenger.hh"

// ====================================================================
//
//      class definition
//
// ====================================================================

class G4Run;
class J4Timer;

class J4RunAction : public G4UserRunAction {
public:
  J4RunAction(const G4String& fname="hit.dat");
  ~J4RunAction() { }

  // set/get functions
  void     SetHitFileName(const G4String& fname) { fHitFileName= fname; }
  G4String GetHitFileName() const                { return fHitFileName; }

  std::ofstream& GetOutputFileStream() { return fOfs; }

  // methods
  virtual void BeginOfRunAction(const G4Run* aRun);
  virtual void EndOfRunAction(const G4Run* aRun);

private:
  J4Timer          *fRunTimer;
  G4String        fHitFileName;
  std::ofstream fOfs;
  J4RunActionMessenger  *fMessenger;
};

#endif
