// $Id$
// GEANT4 tag $Name$
// 

#ifndef J4TrackingActionMessenger_h
#define J4TrackingActionMessenger_h 1

class J4TrackingAction;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;

#include "G4UImessenger.hh"
#include "globals.hh"

// class description:
//
//  This is a concrete class of G4UImessenger which handles commands for
// J4TrackingAction.
//

class J4TrackingActionMessenger: public G4UImessenger
{
  public:
    J4TrackingActionMessenger(J4TrackingAction * fTrackingAction);
    ~J4TrackingActionMessenger();
    
  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:
    J4TrackingAction * fTrackingAction;

  private: //commands
    G4UIdirectory *             fTrackingActionDir;
    G4UIcmdWithAnInteger *      fChooseStoredTrajectoryCmd;

#ifdef __THEBE__
    G4UIcmdWithAnInteger *      fStoreDebugPrintFromCmd;
#endif
    
};

#endif

