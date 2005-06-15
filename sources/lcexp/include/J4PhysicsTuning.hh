// J4PhysicsTuning
//
// A Geant4 PhysicsConstructor class to activate G4UserLimits in various
// logical volumes
//
//-------------------------------------------------------------------------
// 2005.05.30  Allister Levi Sanchez  Based on LCDecayPhysics by D.H.Wright
//-------------------------------------------------------------------------

#ifndef J4PhysicsTuning_h
#define J4PhysicsTuning_h 1

#include "G4VPhysicsConstructor.hh"

class J4PhysicsTuning : public G4VPhysicsConstructor
{
public:
    J4PhysicsTuning(const G4String& name = "tuning");
    virtual ~J4PhysicsTuning();

    virtual void ConstructParticle();

    virtual void ConstructProcess();
};

#endif
