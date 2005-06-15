#include "J4SpecialCuts.hh"

#include "G4Step.hh"
#include "G4UserLimits.hh"
#include "G4VParticleChange.hh"
#include "G4LossTableManager.hh"

J4SpecialCuts::J4SpecialCuts(const G4String& aName)
    : G4VProcess(aName)
{
    if(verboseLevel>0)
    {
	G4cout << GetProcessName() << " is created " << G4endl;
    }
    theLossTableManager = G4LossTableManager::Instance();
}

J4SpecialCuts::~J4SpecialCuts()
{
}

J4SpecialCuts::J4SpecialCuts(J4SpecialCuts& right)
    : G4VProcess(right)
{
}

G4double J4SpecialCuts::PostStepGetPhysicalInteractionLength(
    const G4Track& aTrack,
    G4double,
    G4ForceCondition* condition )
{
    *condition = NotForced;

    G4double proposedStep = DBL_MAX;
    G4UserLimits* pUserLimits =
	aTrack.GetVolume()->GetLogicalVolume()->GetUserLimits();
    if (pUserLimits)
    {
	// max track length
	proposedStep = (pUserLimits->GetUserMaxTrackLength(aTrack)
			- aTrack.GetTrackLength());
	if(proposedStep < 0.) return 0.;

	// max time limit
	G4double beta = (aTrack.GetDynamicParticle()->GetTotalMomentum())/(aTrack.GetTotalEnergy());
	G4double dTime = (pUserLimits->GetUserMaxTime(aTrack) - aTrack.GetGlobalTime());
	G4double temp = beta*c_light*dTime;
	if (temp < 0.) return 0.;
	if (proposedStep > temp) proposedStep = temp;

	// min remaining range
	// only for charged particle except for charged geantino
	G4ParticleDefinition* Particle = aTrack.GetDefinition();
	if( (Particle->GetPDGCharge() != 0.)
	    && (Particle->GetParticleType() != "geantino") )
	{
	    G4double Ekine = aTrack.GetKineticEnergy();
	    const G4MaterialCutsCouple* couple = aTrack.GetMaterialCutsCouple();
	    G4double RangeNow = theLossTableManager->GetRange(Particle,Ekine,couple);
	    G4double Rmin = pUserLimits->GetUserMinRange(aTrack);
	    if(Rmin > DBL_MIN) {
		temp = RangeNow - Rmin;
		if(temp < 0.) return 0.;
		if(proposedStep > temp) proposedStep = temp;
	    }

	    G4double Emin = pUserLimits->GetUserMinEkine(aTrack);
	    if(Emin > DBL_MIN) {
		Rmin = theLossTableManager->GetRange(Particle,Emin,couple);
		temp = RangeNow - Rmin;
		if(temp < 0.) return 0.;
		if(proposedStep > temp) proposedStep = temp;
	    }
	}
    }
    return proposedStep;
}

G4VParticleChange* J4SpecialCuts::PostStepDoIt(
    const G4Track& aTrack,
    const G4Step& )
{   // kill the current particle, if requested by G4UserLimits
    aParticleChange.Initialize(aTrack);
    aParticleChange.ProposeEnergy(0.);
    aParticleChange.ProposeLocalEnergyDeposit(aTrack.GetKineticEnergy());
    aParticleChange.ProposeTrackStatus(fStopAndKill);
    return &aParticleChange;
}
