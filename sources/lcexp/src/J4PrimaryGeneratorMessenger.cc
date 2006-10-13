// $Id$

#include "J4PrimaryGeneratorMessenger.hh"
#include "J4PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4ios.hh"

J4PrimaryGeneratorMessenger::J4PrimaryGeneratorMessenger(J4PrimaryGeneratorAction *mpga)
:fAction(mpga), fDirectory(0), fGenCmd(0)
{
   fDirectory = new G4UIdirectory("/jupiter/");
   fDirectory->SetGuidance("Jupiter control commands.");

   fGenCmd = new G4UIcmdWithAString("/jupiter/generator",this);
   fGenCmd->SetGuidance("Select primary generator.");
   fGenCmd->SetGuidance(" Available generators : HEPEvt, CAINEvt, ParticleGun, ParticleBeam");
   fGenCmd->SetParameterName("generator",true);
   fGenCmd->SetDefaultValue("ParticleGun");
   fGenCmd->SetCandidates("HEPEvt CAINEvt ParticleGun ParticleBeam");

   fInitialSeedCmd = new G4UIcmdWithAnInteger("/jupiter/generator/initialSeed", this);
   fInitialSeedCmd->SetGuidance("Set Initial Seed of generator");
   fInitialSeedCmd->SetGuidance("  = 0, use default otherwise it is used as an initial seed");
   fInitialSeedCmd->SetParameterName("InitialSeed",true,true);
   fInitialSeedCmd->SetDefaultValue(0);

}

J4PrimaryGeneratorMessenger::~J4PrimaryGeneratorMessenger()
{
   delete fGenCmd;
   delete fDirectory;
}

void J4PrimaryGeneratorMessenger::SetNewValue(G4UIcommand *command, G4String newValue)
{
   if( command==fGenCmd ) {
      if (newValue == "HEPEvt") {
         fAction->SetPrimaryGenerator(kHEPEvt);
      } else if (newValue == "CAINEvt") {
         fAction->SetPrimaryGenerator(kCAINEvt);
      } else if (newValue == "ParticleGun") {
         fAction->SetPrimaryGenerator(kParticleGun);
      } else {
         fAction->SetPrimaryGenerator(kParticleBeam);
      }
   }
   else if ( command == fInitialSeedCmd ) {
     fAction->SetInitialSeed(fInitialSeedCmd->GetNewIntValue(newValue));
   }
}

G4String J4PrimaryGeneratorMessenger::GetCurrentValue(G4UIcommand * command)
{
   G4String cv;
  
   if( command==fGenCmd )
   {
      EPrimaryGeneratorType type = fAction->GetPrimaryGeneratorType();
      switch (type) {
         case kHEPEvt:
            cv = "HEPEvt";
            break;
         case kCAINEvt:
            cv = "CAINEvt";
            break;
         case kParticleGun:
            cv = "ParticleGun";
            break;
         case kParticleBeam:
            cv = "ParticleBeam";
            break;
         default:
            std::cerr << " J4PrimaryGeneratorMessenger::GetCurrrentValue:Generator is not "
                 << "prepared. break." << std::endl;  
            break;
      }
   }
   else if ( command == fInitialSeedCmd ) {
     cv = fInitialSeedCmd->ConvertToString(fAction->GetInitialSeed()); 
   }
  
  return cv;
}

