// GEANT4 tag $Name$
//

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

#include "J4SOLMessenger.hh"
#include "J4SOL.hh"



J4SOLMessenger::J4SOLMessenger(J4SOL *asol)
  :fJ4SOL(asol)
{

  fDirectory = new G4UIdirectory("/jupiter/solenoid/");
  fDirectory->SetGuidance("Solenoid Navigation Parameters.");

  fMaxEpsCmd = new G4UIcmdWithADouble("/jupiter/solenoid/MaxEps",this);
  fMaxEpsCmd->SetGuidance("Maximum relative step length in the solenoid");
  fMaxEpsCmd->SetParameterName("MaxEps",true);
  fMaxEpsCmd->SetDefaultValue(fJ4SOL->GetMaxEps());

  fMinEpsCmd = new G4UIcmdWithADouble("/jupiter/solenoid/MinEps",this);
  fMinEpsCmd->SetGuidance("Minimum relative step length in the solenoid");
  fMinEpsCmd->SetParameterName("MinEps",true);
  fMinEpsCmd->SetDefaultValue(fJ4SOL->GetMinEps());

  fDeltaOneStepCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/solenoid/DeltaOneStep",this);
  fDeltaOneStepCmd->SetGuidance("Delta One Step");
  fDeltaOneStepCmd->SetGuidance("Roughly the acceptable possition error in an integration step");
  fDeltaOneStepCmd->SetParameterName("DeltaOneStep",true);
  fDeltaOneStepCmd->SetDefaultValue(fJ4SOL->GetDeltaOneStep());
  fDeltaOneStepCmd->SetDefaultUnit("mm");

  fDeltaIntersectionCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/solenoid/DeltaIntersection",this);
  fDeltaIntersectionCmd->SetGuidance("Delta Intersection");
  fDeltaIntersectionCmd->SetParameterName("DeltaOneStep",true);
  fDeltaIntersectionCmd->SetDefaultValue(fJ4SOL->GetDeltaIntersection());
  fDeltaIntersectionCmd->SetDefaultUnit("mm");

  fDeltaChordCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/solenoid/DeltaChord",this);
  fDeltaChordCmd->SetGuidance("Delta Chord");
  fDeltaChordCmd->SetParameterName("DeltaChord",true);
  fDeltaChordCmd->SetDefaultValue(fJ4SOL->GetDeltaChord());
  fDeltaChordCmd->SetDefaultUnit("mm");

  // Set Initial default value

  G4cerr << " J4SOLMessenger::MaxEps=" << fJ4SOL->GetMaxEps() << G4endl;
  G4cerr << " J4SOLMessenger::MinEps=" << fJ4SOL->GetMinEps() << G4endl;
  G4cerr << " J4SOLMessenger::DeltaOneStep(mm)s=" << fJ4SOL->GetDeltaOneStep()/mm << G4endl;
  G4cerr << " J4SOLMessenger::DeltaIntersection(mm)s=" << fJ4SOL->GetDeltaIntersection()/mm << G4endl;
  G4cerr << " J4SOLMessenger::DeltaChord(mm)s=" << fJ4SOL->GetDeltaChord()/mm << G4endl;

}

J4SOLMessenger::~J4SOLMessenger()
{
  delete fMaxEpsCmd;
  delete fMinEpsCmd;
  delete fDeltaOneStepCmd;
  delete fDeltaIntersectionCmd;
  delete fDeltaChordCmd;
  delete fDirectory;

}

void J4SOLMessenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if( command==fMaxEpsCmd ) { 
    fJ4SOL->SetMaxEps(fMaxEpsCmd->GetNewDoubleValue(newValues)); 
  } else if( command==fMinEpsCmd ) {
    fJ4SOL->SetMinEps(fMinEpsCmd->GetNewDoubleValue(newValues)); 
  } else if( command==fDeltaOneStepCmd ) {
    fJ4SOL->SetDeltaOneStep(fDeltaOneStepCmd->GetNewDoubleValue(newValues)); 
  } else if( command==fDeltaIntersectionCmd ) {
    fJ4SOL->SetDeltaIntersection(fDeltaIntersectionCmd->GetNewDoubleValue(newValues)); 
  } else if( command==fDeltaChordCmd ) {
    fJ4SOL->SetDeltaChord(fDeltaChordCmd->GetNewDoubleValue(newValues)); 
  }
}

G4String J4SOLMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv("");
  
  if( command==fMaxEpsCmd )
  { cv = fMaxEpsCmd->ConvertToString(fJ4SOL->GetMaxEps()); }
  else if( command==fMinEpsCmd )
  { cv = fMinEpsCmd->ConvertToString(fJ4SOL->GetMinEps()); }
  else if( command==fDeltaOneStepCmd )
  { cv = fDeltaOneStepCmd->ConvertToString(fJ4SOL->GetDeltaOneStep(),"mm"); }
  else if( command==fDeltaIntersectionCmd )
  { cv = fDeltaIntersectionCmd->ConvertToString(fJ4SOL->GetDeltaIntersection(),"mm"); }
  else if( command==fDeltaChordCmd )
  { cv = fDeltaChordCmd->ConvertToString(fJ4SOL->GetDeltaChord(),"mm"); }
  return cv;
}

