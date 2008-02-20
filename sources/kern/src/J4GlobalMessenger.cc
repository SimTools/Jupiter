// $Id$
// GEANT4 tag $Name$
//

#include "J4GlobalMessenger.hh"
#include "J4Global.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4ios.hh"
#include "G4Tokenizer.hh"

// #include "./iomanip"               
// #include "./strstream"

J4GlobalMessenger::J4GlobalMessenger(J4Global * global)
  :fGlobal(global)
{
  fGlobalDir = new G4UIdirectory("/jupiter/global/");
  fGlobalDir->SetGuidance("Global setting commands.");

  fPrintCmd = new G4UIcmdWithAString("/jupiter/global/print",this);
  fPrintCmd->SetGuidance("Print Information");
  fPrintCmd->SetDefaultValue("Material");

#ifdef __THEBE__

  fErrorOutputFilenameCmd = new G4UIcmdWithAString("/jupiter/global/ErrorOutputFilename",this);
  fErrorOutputFilenameCmd->SetGuidance("Set output filename for error");
  fErrorOutputFilenameCmd->SetGuidance(" (lastevtError.log is default)");
  fErrorOutputFilenameCmd->SetParameterName("errorFileName",true);
  fErrorOutputFilenameCmd->SetDefaultValue("lastevtError.log");

  fErrorNeventsCmd = new G4UIcmdWithAnInteger("/jupiter/global/ErrorStoredEventNumber",this);
  fErrorNeventsCmd->SetGuidance("Set number of event stored in error-output-file.");
  fErrorNeventsCmd->SetGuidance(" (default is 1.)");
  fErrorNeventsCmd->SetParameterName("N",true,true);
  fErrorNeventsCmd->SetRange("N>0");
  
  fErrorOutputDeviceIDCmd = new G4UIcmdWithAnInteger("/jupiter/global/ErrorOutputDeviceID",this);
  fErrorOutputDeviceIDCmd->SetGuidance("Set J4cerr output device ID.");
  fErrorOutputDeviceIDCmd->SetGuidance(" 0: std::cerr, 1: file");
  fErrorOutputDeviceIDCmd->SetGuidance(" (default is 1.)");
  fErrorOutputDeviceIDCmd->SetParameterName("N",true,true);
  fErrorOutputDeviceIDCmd->SetRange("N>-1");
      
  // set initial value to J4Global
  fGlobal->SetErrorOutputFilename("lastevtError.log");
  fGlobal->SetErrorNevents(1);
  fGlobal->SetErrorOutputDeviceID(1);

#endif

}

J4GlobalMessenger::~J4GlobalMessenger()
{

#ifdef __THEBE__

   delete fErrorOutputDeviceIDCmd;
   delete fErrorOutputFilenameCmd;
   delete fErrorNeventsCmd;;

#endif

   delete fPrintCmd;
   delete fGlobalDir;
   
}

#ifdef __THEBE__
void J4GlobalMessenger::SetNewValue(G4UIcommand * command, G4String newValues)
{

  if( command == fErrorOutputFilenameCmd ) {
     fGlobal->SetErrorOutputFilename(newValues);
  } else if( command == fErrorNeventsCmd ) {
     fGlobal->SetErrorNevents(fErrorNeventsCmd->GetNewIntValue(newValues)); 
  } else if( command == fErrorOutputDeviceIDCmd) {
     fGlobal->SetErrorOutputDeviceID(fErrorOutputDeviceIDCmd->GetNewIntValue(newValues)); 
  } else if( command == fPrintCmd ) {
	J4MaterialCatalog::Print();
  }
#else

void J4GlobalMessenger::SetNewValue(G4UIcommand *, G4String)
{
#endif

}

#ifdef __THEBE__   
G4String J4GlobalMessenger::GetCurrentValue(G4UIcommand * command)
#else
G4String J4GlobalMessenger::GetCurrentValue(G4UIcommand *)
#endif
{
   G4String cv;


#ifdef __THEBE__   

   if( command == fErrorOutputFilenameCmd ) {
      cv = fGlobal->GetErrorOutputFilename();
   } else if( command == fErrorNeventsCmd ) {
      cv = fErrorNeventsCmd->ConvertToString(fGlobal->GetErrorNevents()); 
   } else if( command == fErrorOutputDeviceIDCmd) {
      cv = fErrorOutputDeviceIDCmd->ConvertToString(fGlobal->GetErrorOutputDeviceID());
   }

#endif
   
   return cv;
}
