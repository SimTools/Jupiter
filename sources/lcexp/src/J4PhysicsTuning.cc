// J4PhysicsTuning
//
// A Geant4 PhysicsConstructor class to activate G4UserLimits in various
// logical volumes
//
//-------------------------------------------------------------------------
// 2005.05.30  Allister Levi Sanchez  Based on LCDecayPhysics by D.H.Wright
//-------------------------------------------------------------------------

#include "J4PhysicsTuning.hh"
#include "J4StepLimiter.hh"
#include "J4SpecialCuts.hh"

J4PhysicsTuning::J4PhysicsTuning(const G4String& name)
    : G4VPhysicsConstructor(name)
{
}

J4PhysicsTuning::~J4PhysicsTuning()
{
}

#include "G4ProcessManager.hh"

void J4PhysicsTuning::ConstructParticle()
{
}

void J4PhysicsTuning::ConstructProcess()
{
    // add step limiting processes
    theParticleIterator->reset();
    while( (*theParticleIterator)() ) {
	G4ParticleDefinition* particle = theParticleIterator->value();
	G4ProcessManager* pmanager = particle->GetProcessManager();
	// set max step length
	pmanager->AddDiscreteProcess(new J4StepLimiter());
	pmanager->AddDiscreteProcess(new J4SpecialCuts());
    }
}
