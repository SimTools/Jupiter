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
  
  fGenElectronCmd = new G4UIcmdWithABool("/jupiter/cain/genelectron",this);
  fGenElectronCmd->SetGuidance("Electron track is passed to Jupiter");
  fGenElectronCmd->SetParameterName("GenElectron",true);
  fGenElectronCmd->SetDefaultValue(true);
  
  fGenPositronCmd = new G4UIcmdWithABool("/jupiter/cain/genpositron",this);
  fGenPositronCmd->SetGuidance("Positron prack is passed to Jupiter");
  fGenPositronCmd->SetParameterName("GenPositron",true);
  fGenPositronCmd->SetDefaultValue(true);
  
  fGenDirectionCmd = new G4UIcmdWithADouble("/jupiter/cain/gendirection",this);
  fGenDirectionCmd->SetGuidance("Only particles generated in the given direction is passed to Jupiter");
  fGenDirectionCmd->SetGuidance("1.0(+Z direction), -1(-Z direction), 0(+-Z)");
  fGenDirectionCmd->SetParameterName("GenPositron",true);
  fGenDirectionCmd->SetDefaultValue(true);
  
  fVerboseCmd = new G4UIcmdWithAnInteger("/jupiter/cain/verbose",this);
  fVerboseCmd->SetGuidance("Verbose output");
  fVerboseCmd->SetParameterName("Verbose",true);
  fVerboseCmd->SetDefaultValue(0);
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

  return cv;
}
