// $Id$
// GEANT4 tag $Name$
//
// 

#ifndef J4GlobalMessenger_h
#define J4GlobalMessenger_h 1

class J4Global;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;

#include "G4UImessenger.hh"
#include "globals.hh"

// class description:
//
//  This is a concrete class of G4UImessenger which handles commands for
// J4Global.
//

class J4GlobalMessenger: public G4UImessenger
{
  public:
    J4GlobalMessenger(J4Global * fGlobal);
    ~J4GlobalMessenger();
    
  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:
    J4Global * fGlobal;

  private: //commands
    G4UIdirectory *             fGlobalDir;
    G4UIcmdWithAnInteger *      fErrorNeventsCmd;
    G4UIcmdWithAnInteger *      fErrorOutputDeviceIDCmd;
    G4UIcmdWithAString *        fErrorOutputFilenameCmd;
    
};

#endif

