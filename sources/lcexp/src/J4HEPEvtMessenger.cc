//
// ********************************************************************
//
// A handler of J4HEPEvtInterface
//
// ********************************************************************
//
//

#include "J4HEPEvtMessenger.hh"
#include "J4HEPEvtInterface.hh"
#include "G4Geantino.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4ios.hh"
#include "G4Tokenizer.hh"

#include "./iomanip"               

//-------------------------------------------------------------
J4HEPEvtMessenger::J4HEPEvtMessenger(J4HEPEvtInterface * hepevt)
  :fHEPEvt(hepevt)
{

  fDirectory = new G4UIdirectory("/jupiter/hepevt/");
  fDirectory->SetGuidance("Commands to control HEPEvt event interface.");

  fFileNameCmd = new G4UIcmdWithAString("/jupiter/hepevt/file",this);
  fFileNameCmd->SetGuidance("Set a file name of HEPEvt data");
  fFileNameCmd->SetParameterName("FileName",true);
  fFileNameCmd->SetDefaultValue("pythia_event.data");
  fHEPEvt->SetFileName("pythia_event.data");
  fNskipEventsCmd = new G4UIcmdWithAnInteger("/jupiter/hepevt/numberOfSkipEvents",this);
  fNskipEventsCmd->SetGuidance("Set number of skip events.");
  fNskipEventsCmd->SetParameterName("N",true,true);
  fNskipEventsCmd->SetRange("N>-1");
}

//-----------------------------------------------------------------
J4HEPEvtMessenger::~J4HEPEvtMessenger()
{
  if (fFileNameCmd)    delete fFileNameCmd;
  if (fDirectory)      delete fDirectory;
  if (fNskipEventsCmd) delete fNskipEventsCmd;
}

//--------------------------------------------------------------------
void J4HEPEvtMessenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if (command == fFileNameCmd) { 
    fHEPEvt->OpenHEPEvtFile(newValues);
  } else if (command == fNskipEventsCmd) {
    fHEPEvt->SetNskipEvents(fNskipEventsCmd->GetNewIntValue(newValues));
  }
}


//--------------------------------------------------------------------
G4String J4HEPEvtMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  
  if (command == fFileNameCmd) { 
    cv = fHEPEvt->GetFileName();
  } else if (command == fNskipEventsCmd) {
    cv = fNskipEventsCmd->ConvertToString(fHEPEvt->GetNskipEvents());
  }

  return cv;
}
