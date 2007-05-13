// $Id$

#ifndef J4SOLMessenger_h
#define J4SOLMessenger_h 1


#include "G4UImessenger.hh"
#include "globals.hh"

class G4UIcommand;
class J4SOL;
class G4UIdirectory;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;

class J4SOLMessenger: public G4UImessenger
{
  public:
    J4SOLMessenger(J4SOL *sol);
    ~J4SOLMessenger();
    
  public:
    void SetNewValue(G4UIcommand *command, G4String newValues);
    G4String GetCurrentValue(G4UIcommand *command);

  private:
    J4SOL   *fJ4SOL;
    
  private:  //commands
    G4UIdirectory              *fDirectory;
    G4UIcmdWithADouble         *fMaxEpsCmd;
    G4UIcmdWithADouble         *fMinEpsCmd;
    G4UIcmdWithADoubleAndUnit  *fDeltaOneStepCmd;
    G4UIcmdWithADoubleAndUnit  *fDeltaIntersectionCmd;
    G4UIcmdWithADoubleAndUnit  *fDeltaChordCmd;

};

#endif


