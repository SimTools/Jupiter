//
// ********************************************************************
//
// A handler of J4RunAction
//
// ********************************************************************
//
//

#include "J4RunActionMessenger.hh"
#include "J4RunAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4ios.hh"
#include "G4Tokenizer.hh"
#include "J4MaterialCatalog.hh"

//-------------------------------------------------------------
J4RunActionMessenger::J4RunActionMessenger(J4RunAction * runaction)
  :fRunAction(runaction)
{
  fDirectory = new G4UIdirectory("/jupiter/run/");
  fDirectory->SetGuidance("Commands to control Jupiter run information.");

  fFileNameCmd = new G4UIcmdWithAString("/jupiter/run/hitfile",this);
  fFileNameCmd->SetGuidance("Set a file name to output hit data");
  fFileNameCmd->SetParameterName("FileName",true);
  fFileNameCmd->SetDefaultValue("hit.dat");

  fPrintCmd = new G4UIcmdWithAString("/jupiter/run/print",this);
  fPrintCmd->SetGuidance("Print information");
  fPrintCmd->SetParameterName("item",true);
  fPrintCmd->SetDefaultValue("material");

}

//-----------------------------------------------------------------
J4RunActionMessenger::~J4RunActionMessenger()
{
  if (fFileNameCmd)    delete fFileNameCmd;
  if (fPrintCmd)       delete fPrintCmd;
  if (fDirectory)      delete fDirectory;
}

//--------------------------------------------------------------------
void J4RunActionMessenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if (command == fFileNameCmd) { 
    fRunAction->SetHitFileName(newValues);
  }
  else if ( command == fPrintCmd ) {
    J4MaterialCatalog::Print();
  }

}


//--------------------------------------------------------------------
G4String J4RunActionMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  
  if (command == fFileNameCmd) { 
    cv = fRunAction->GetHitFileName();
  } 
  else if ( command ==fPrintCmd) {
    cv = " ";
  }

  return cv;
}
