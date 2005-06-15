// $Id$
//
// J4StepLimiter
//
// A physics process class for limiting the maximum
// step length in a logical volume
//
//-----------------------------------------------------------------------------
// 2005.05.30  Allister Levi Sanchez, based on ExN03StepLimiter by H. Kurashige
//-----------------------------------------------------------------------------

#ifndef J4StepLimiter_h
#define J4StepLimiter_h 1

#include "G4ios.hh"
#include "globals.hh"
#include "G4VProcess.hh"

class J4StepLimiter : public G4VProcess
{
public:
    J4StepLimiter(const G4String& processName = "J4StepLimiter");

    ~J4StepLimiter();

    virtual G4double PostStepGetPhysicalInteractionLength(
	const G4Track& track,
	G4double previousStepSize,
	G4ForceCondition* condition
	);

    virtual G4VParticleChange* PostStepDoIt(
	const G4Track& ,
	const G4Step&
	);

public:
    virtual G4double AtRestGetPhysicalInteractionLength(
	const G4Track& ,
	G4ForceCondition*
	) { return -1.0; };

    virtual G4VParticleChange* AtRestDoIt(
	const G4Track& ,
	const G4Step&
	) { return 0; };

    virtual G4double AlongStepGetPhysicalInteractionLength(
	const G4Track&,
	G4double  ,
	G4double  ,
	G4double& ,
	G4GPILSelection*
	) {return -1.0; };

    virtual G4VParticleChange* AlongStepDoIt(
	const G4Track& ,
	const G4Step&
	) {return 0; };

private:
    J4StepLimiter(J4StepLimiter&);
    J4StepLimiter& operator=(const J4StepLimiter& right);
};

#endif
