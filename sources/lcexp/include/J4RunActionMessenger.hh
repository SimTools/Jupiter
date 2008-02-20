// $Id$

#ifndef J4RunActionMessenger_h
#define J4RunActionMessenger_h 1

class J4RunAction;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;

#include "G4UImessenger.hh"
#include "globals.hh"

class J4RunActionMessenger: public G4UImessenger
{
  public:
    J4RunActionMessenger(J4RunAction *mpga);
    ~J4RunActionMessenger();
    
  public:
    void SetNewValue(G4UIcommand *command, G4String newValues);
    G4String GetCurrentValue(G4UIcommand *command);

  private:
    J4RunAction   *fRunAction;
    
  private: //commands
    G4UIdirectory              *fDirectory;
    G4UIcmdWithAString         *fFileNameCmd;
    G4UIcmdWithAString         *fPrintCmd;
    
};

#endif


