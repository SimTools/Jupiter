//
// ********************************************************************
// J4HEPEvtMessenger 
//
// class description:
// 
// This is a concrete class of G4UImessenger to handles commands for 
// J4HEPEvtInterface.
// 
// ********************************************************************
//
// $Id$
// 

#ifndef J4HEPEVTMESSENGER
#define J4HEPEVTMESSENGER

class J4HEPEvtInterface;
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


class J4HEPEvtMessenger: public G4UImessenger
{
  public:
    J4HEPEvtMessenger(J4HEPEvtInterface * cainevt);
    ~J4HEPEvtMessenger();
    
  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:

  private:
    J4HEPEvtInterface *fHEPEvt;

  private: //commands
    G4UIdirectory              *fDirectory;
    G4UIcmdWithAString         *fFileNameCmd;
    G4UIcmdWithAnInteger       *fNskipEventsCmd;
 
  private: // 
};

#endif

