//
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  Title:  Physics List for a Linear Collider Detector                    //
//  Date:   16 June 2004                                                   //
//  Author: D.H. Wright (SLAC)                                             //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//

#include "LCPhysicsList.hh"

#include "LCDecayPhysics.hh"
#include "LCBosonPhysics.hh"
#include "LCLeptonPhysics.hh"
#include "LCHadronPhysics.hh"
#include "LCIonPhysics.hh"

LCPhysicsList::LCPhysicsList():  G4VModularPhysicsList()
{
  // default cut value  (1.0mm) 
  defaultCutValue = 1.0*mm;
  // SetVerboseLevel(1);

  // Particle decays
  RegisterPhysics( new LCDecayPhysics("decay"));

  // Bosons (gamma + geantinos)
  RegisterPhysics( new LCBosonPhysics("boson"));

  // Leptons
  RegisterPhysics( new LCLeptonPhysics("lepton"));

  // Hadron Physics
  RegisterPhysics( new LCHadronPhysics("hadron"));

  // Ion Physics
  RegisterPhysics( new LCIonPhysics("ion"));
}

LCPhysicsList::~LCPhysicsList()
{;}

void LCPhysicsList::SetCuts()
{
  // Use default cut values gamma and e processes
  SetCutsWithDefault();   
}



