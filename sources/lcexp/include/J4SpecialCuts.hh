#ifndef J4SpecialCuts_h
#define J4SpecialCuts_h 1

#include "G4ios.hh"
#include "globals.hh"
#include "G4VProcess.hh"

class G4LossTableManager;

class J4SpecialCuts : public G4VProcess
{
public:
    J4SpecialCuts(const G4String& processName = "J4SpecialCut" );

    ~J4SpecialCuts();

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
	){ return -1.0; };

    virtual G4VParticleChange* AlongStepDoIt(
	const G4Track& ,
	const G4Step&
	) {return 0;};

private:
    J4SpecialCuts(J4SpecialCuts&);
    J4SpecialCuts& operator=(const J4SpecialCuts& right);

    G4LossTableManager* theLossTableManager;
};

#endif
