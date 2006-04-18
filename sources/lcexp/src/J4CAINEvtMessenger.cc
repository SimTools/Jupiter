//
// ********************************************************************
//
// A handler of J4CAINEvtInterface
//
// ********************************************************************
//
//

#include "J4CAINEvtMessenger.hh"
#include "J4CAINEvtInterface.hh"
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

//-------------------------------------------------------------
J4CAINEvtMessenger::J4CAINEvtMessenger(J4CAINEvtInterface * cainevt)
  :fCAINEvt(cainevt)
{

  fDirectory = new G4UIdirectory("/jupiter/cain/");
  fDirectory->SetGuidance("Commands to control CAIN event interface.");

  fFileNameCmd = new G4UIcmdWithAString("/jupiter/cain/file",this);
  fFileNameCmd->SetGuidance("Set a file name of CAIN data");
  fFileNameCmd->SetParameterName("FileName",true);
  fFileNameCmd->SetDefaultValue("cain.dat");
  fCAINEvt->SetFileName("cain.dat");

  fGenGammaCmd = new G4UIcmdWithABool("/jupiter/cain/gengamma",this);
  fGenGammaCmd->SetGuidance("Gamma track is passed to Jupiter");
  fGenGammaCmd->SetParameterName("GenGamma",true);
  fGenGammaCmd->SetDefaultValue(true);
  fCAINEvt->SetGenGamma(true);
  
  fGenElectronCmd = new G4UIcmdWithABool("/jupiter/cain/genelectron",this);
  fGenElectronCmd->SetGuidance("Electron track is passed to Jupiter");
  fGenElectronCmd->SetParameterName("GenElectron",true);
  fGenElectronCmd->SetDefaultValue(true);
  fCAINEvt->SetGenElectron(true);
  
  fGenPositronCmd = new G4UIcmdWithABool("/jupiter/cain/genpositron",this);
  fGenPositronCmd->SetGuidance("Positron prack is passed to Jupiter");
  fGenPositronCmd->SetParameterName("GenPositron",true);
  fGenPositronCmd->SetDefaultValue(true);
  fCAINEvt->SetGenPositron(true);
  
  fGenDirectionCmd = new G4UIcmdWithADouble("/jupiter/cain/gendirection",this);
  fGenDirectionCmd->SetGuidance("Only particles generated in the given direction is passed to Jupiter");
  fGenDirectionCmd->SetGuidance("1.0(+Z direction), -1(-Z direction), 0(+-Z)");
  fGenDirectionCmd->SetParameterName("GenPositron",true);
  fGenDirectionCmd->SetDefaultValue(1.0);
  fCAINEvt->SetGenDirection(1.0);
  
  fVerboseCmd = new G4UIcmdWithAnInteger("/jupiter/cain/verbose",this);
  fVerboseCmd->SetGuidance("Verbose output");
  fVerboseCmd->SetParameterName("Verbose",true);
  fVerboseCmd->SetDefaultValue(0);
  fCAINEvt->SetVerboseLevel(0);
  
  fTracksPerEventCmd = new G4UIcmdWithAnInteger("/jupiter/cain/tracks_per_event",this);
  fTracksPerEventCmd->SetGuidance("Tracks per event");
  fTracksPerEventCmd->SetParameterName("TracksPerEvent",true);
  fTracksPerEventCmd->SetDefaultValue(500);
  fCAINEvt->SetTracksPerEvent(500);

  fFirstRecordCmd = new G4UIcmdWithAnInteger("/jupiter/cain/first_record",this);
  fFirstRecordCmd->SetGuidance("First record to simulate event");
  fFirstRecordCmd->SetParameterName("FirstRecord",true);
  fFirstRecordCmd->SetDefaultValue(1);
  fCAINEvt->SetFirstRecord(1);

  fLastRecordCmd = new G4UIcmdWithAnInteger("/jupiter/cain/last_record",this);
  fLastRecordCmd->SetGuidance("Last record to simulate event");
  fLastRecordCmd->SetParameterName("LastRecord",true);
  fLastRecordCmd->SetDefaultValue(1999999999);
  fCAINEvt->SetLastRecord(1999999999);

  fCrossingAngleCmd = new G4UIcmdWithADouble("/jupiter/cain/crossing_angle",this);
  fCrossingAngleCmd->SetGuidance("Transfer particle momentum according to the crossing_angle");
  fCrossingAngleCmd->SetGuidance("Crossing angle is twice the angle between beam line and Z-axis");
  fCrossingAngleCmd->SetParameterName("CrossingAngle",true);
  fCrossingAngleCmd->SetDefaultValue(0.0000001*rad); 
  fCAINEvt->SetCrossingAngle(0.0000001*rad); 


}

//-----------------------------------------------------------------
J4CAINEvtMessenger::~J4CAINEvtMessenger()
{
  delete fGenDirectionCmd;
  delete fGenGammaCmd;
  delete fGenElectronCmd;
  delete fGenPositronCmd;
  delete fFileNameCmd;
  delete fDirectory;
  delete fCrossingAngleCmd;
  delete fTracksPerEventCmd;
  delete fFirstRecordCmd;
  delete fLastRecordCmd;
}

//--------------------------------------------------------------------
void J4CAINEvtMessenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if( command==fFileNameCmd ){ 
    fCAINEvt->OpenCainFile(newValues);
  }
  else if( command==fGenDirectionCmd ){ 
    fCAINEvt->SetGenDirection(fGenDirectionCmd->GetNewDoubleValue(newValues));
  }
  else if( command==fGenGammaCmd ){ 
    fCAINEvt->SetGenGamma(fGenGammaCmd->GetNewBoolValue(newValues));
  }
  else if( command==fGenElectronCmd ){ 
    fCAINEvt->SetGenElectron(fGenElectronCmd->GetNewBoolValue(newValues));
  }
  else if( command==fGenPositronCmd ){ 
    fCAINEvt->SetGenPositron(fGenPositronCmd->GetNewBoolValue(newValues));
  }
  else if( command==fVerboseCmd ){ 
    fCAINEvt->SetVerboseLevel(fVerboseCmd->GetNewIntValue(newValues));
  }
  else if( command==fTracksPerEventCmd ) {
    fCAINEvt->SetTracksPerEvent(fTracksPerEventCmd->GetNewIntValue(newValues));
  }
  else if( command==fFirstRecordCmd ) {
    fCAINEvt->SetFirstRecord(fFirstRecordCmd->GetNewIntValue(newValues));
  }
  else if( command==fLastRecordCmd ) {
    fCAINEvt->SetLastRecord(fLastRecordCmd->GetNewIntValue(newValues));
  }
  else if( command==fCrossingAngleCmd ) {
    fCAINEvt->SetCrossingAngle(fCrossingAngleCmd->GetNewDoubleValue(newValues));
  }
}


//--------------------------------------------------------------------
G4String J4CAINEvtMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  
  if( command==fFileNameCmd ){ 
    cv = fCAINEvt->GetFileName();
  }
  else if( command==fGenDirectionCmd ){ 
    cv = fGenDirectionCmd->ConvertToString(fCAINEvt->GetGenDirection());
  }
  else if ( command==fGenGammaCmd ){ 
    cv = fGenGammaCmd->ConvertToString(fCAINEvt->GetGenGamma());
  }
  else if ( command==fGenElectronCmd ){ 
    cv = fGenElectronCmd->ConvertToString(fCAINEvt->GetGenElectron());
  }
  else if ( command==fGenPositronCmd ){ 
    cv = fGenPositronCmd->ConvertToString(fCAINEvt->GetGenPositron());
  }
  else if ( command==fVerboseCmd ){ 
    cv = fVerboseCmd->ConvertToString(fCAINEvt->GetVerboseLevel());
  }
  else if ( command==fTracksPerEventCmd ){ 
    cv = fTracksPerEventCmd->ConvertToString(fCAINEvt->GetVerboseLevel());
  }
  else if ( command==fFirstRecordCmd ){ 
    cv = fFirstRecordCmd->ConvertToString(fCAINEvt->GetFirstRecord());
  }
  else if ( command==fLastRecordCmd ){ 
    cv = fLastRecordCmd->ConvertToString(fCAINEvt->GetLastRecord());
  }
  else if ( command==fCrossingAngleCmd ) {
    cv = fCrossingAngleCmd->ConvertToString(fCAINEvt->GetCrossingAngle());
  }
  return cv;
}
