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


#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4RegionStore.hh"

void LCPhysicsList::SetCuts()
{
  // Use default cut values gamma and e processes
  SetCutsWithDefault();   
  //
  // Make region dependant cuts
  // 
  G4Region *region;
  G4String  regname;
  G4ProductionCuts *cuts;

#if G4VERSION_NUMBER < 910

  regname="BPandMask";
  region=G4RegionStore::GetInstance()->GetRegion(regname);
  if( region ){
    cuts  = new G4ProductionCuts;
    cuts->SetProductionCut(5.0*mm,G4ProductionCuts::GetIndex("e+"));
    cuts->SetProductionCut(5.0*mm,G4ProductionCuts::GetIndex("e-"));
    cuts->SetProductionCut(5.0*mm,G4ProductionCuts::GetIndex("gamma"));
    region->SetProductionCuts(cuts);
  }

  
  region=G4RegionStore::GetInstance()->GetRegion("IRRegion");
  if( region ) {
    cuts  = new G4ProductionCuts;
    cuts->SetProductionCut(1.0*cm,G4ProductionCuts::GetIndex("e+"));
    cuts->SetProductionCut(1.0*cm,G4ProductionCuts::GetIndex("e-"));
    cuts->SetProductionCut(1.0*cm,G4ProductionCuts::GetIndex("gamma"));
    region->SetProductionCuts(cuts);
  }
#endif

  if (verboseLevel > 0) DumpCutValuesTable();
}



