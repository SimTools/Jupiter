//
// ********************************************************************
// J4CainEvtMessenger 
//
// class description:
// 
// This is a concrete class of G4UImessenger to handles commands for 
// J4CAINEvtInterface.
// 
// ********************************************************************
//
// $Id$
// 

#ifndef J4CAINEvtMessenger_h
#define J4CAINEvtMessenger_h 1

class J4CAINEvtInterface;
class G4ParticleTable;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;

#include "G4UImessenger.hh"
#include "globals.hh"


class J4CAINEvtMessenger: public G4UImessenger
{
  public:
    J4CAINEvtMessenger(J4CAINEvtInterface * cainevt);
    ~J4CAINEvtMessenger();
    
  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:

  private:
    J4CAINEvtInterface *fCAINEvt;

  private: //commands
    G4UIdirectory              *fDirectory;
    G4UIcmdWithAString         *fFileNameCmd;
    G4UIcmdWithABool           *fGenGammaCmd;
    G4UIcmdWithABool           *fGenElectronCmd;
    G4UIcmdWithABool           *fGenPositronCmd;    
    G4UIcmdWithADouble         *fGenDirectionCmd;
    G4UIcmdWithAnInteger       *fVerboseCmd;
    G4UIcmdWithADouble         *fCrossingAngleCmd;
    G4UIcmdWithAnInteger       *fTracksPerEventCmd;

    G4UIcmdWithAnInteger       *fFirstRecordCmd;
    G4UIcmdWithAnInteger       *fLastRecordCmd;
 
  private: // 
};

#endif

