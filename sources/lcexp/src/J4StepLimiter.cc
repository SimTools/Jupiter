// $Id$
//
// J4StepLimiter
//
// A class for limiting the maximum step length.
//
//-----------------------------------------------------------------------------
// 2005.05.30  Allister Levi Sanchez, based on ExN03StepLimiter by H. Kurashige
//-----------------------------------------------------------------------------

#include "J4StepLimiter.hh"
#include "J4SpecialCuts.hh"

#include "G4Step.hh"
#include "G4UserLimits.hh"
#include "G4VParticleChange.hh"
#include "G4Track.hh"

J4StepLimiter::J4StepLimiter(const G4String& aName)
    : G4VProcess(aName)
{
    if(verboseLevel>1) {
	G4cout << GetProcessName() << " is created " << G4endl;
    }
}

J4StepLimiter::~J4StepLimiter()
{
}

J4StepLimiter::J4StepLimiter(J4StepLimiter& right)
    : G4VProcess(right)
{
}

G4double J4StepLimiter::PostStepGetPhysicalInteractionLength(
    const G4Track& aTrack,
    G4double,
    G4ForceCondition* condition)
{
    *condition = NotForced;

    G4double proposedStep = DBL_MAX;
    G4UserLimits* pUserLimits =
	aTrack.GetVolume()->GetLogicalVolume()->GetUserLimits();
    if(pUserLimits) {
	proposedStep = pUserLimits->GetMaxAllowedStep(aTrack);
	if(proposedStep < 0. ) proposedStep = 0.;
    }

    return proposedStep;
}

G4VParticleChange* J4StepLimiter::PostStepDoIt( const G4Track& aTrack,
						const G4Step& )
{
    aParticleChange.Initialize(aTrack);
    return &aParticleChange;
}
