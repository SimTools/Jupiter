// $Id$
//*************************************************************************
//* --------------------
//* J4VTrackerHit
//* --------------------
//* (Description)
//* 	Abstruct hit class. This class also provide his
//*	proper HitCollection(buffering) class.
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*	2001/03/15  K.Hoshina	Original version.
//*************************************************************************

#include <iomanip>
#include "J4VTrackerHit.hh"

//=========================================================================
//* constructor -----------------------------------------------------------

J4VTrackerHit::J4VTrackerHit()
       :J4VHit(), fCloneID(-9999), fTrackID(-9999), fMotherTrackID(-9999),
        fParticle(0), fTof(-9999), fEnergyDeposit(-9999), fTotalEnergy(-9999),
        fMomentum(0), fPrePosition(0), fPostPosition(0), fHitNumber(-9999)
{ 
}

J4VTrackerHit::J4VTrackerHit(J4VComponent        *detector,
               const G4ThreeVector &pre,
               const G4ThreeVector &pos,
               G4int                cloneid)
       :J4VHit(detector), fCloneID(cloneid), fTrackID(-9999),
        fMotherTrackID(-9999),
        fParticle(0), fTof(-9999), fEnergyDeposit(-9999), fTotalEnergy(-9999),
        fMomentum(0), fPrePosition(pre), fPostPosition(pos),
        fHitNumber(-9999)
{
}

J4VTrackerHit::J4VTrackerHit(J4VComponent  *detector,      // Belonging Component 
               G4int                 trackID,	    // TrackID
               G4int                 mothertrackID, // MotherTrackID
               G4ParticleDefinition *particle,	    // particle
               G4double              tof,           // TOF 
               G4double              edep,          // Energy Deposit
               G4double              totalE,        // Total energy
               const G4ThreeVector  &p,             // Momentum of perticle
               const G4ThreeVector  &pre,           // Pre-position of track
               const G4ThreeVector  &pos,           // Post-position of track
               G4int                 hitnumber)
	     :J4VHit(detector), fCloneID(-9999), fTrackID(trackID), 
              fMotherTrackID(mothertrackID), fParticle(particle), 
	      fTof(tof), fEnergyDeposit(edep), 
	      fTotalEnergy(totalE), fMomentum(p),
	      fPrePosition(pre), fPostPosition(pos), fHitNumber(hitnumber)
{  
}

J4VTrackerHit::J4VTrackerHit(J4VComponent         *detector,      // Belonging Component
               G4int                 cloneID,	    // CloneID of detector
               G4int                 trackID,	    // TrackID
               G4int                 mothertrackID, // MotherTrackID
               G4ParticleDefinition *particle,	    // particle
               G4double              tof,           // TOF
               G4double              edep,          // Energy Deposit
               G4double              totalE,        // Total energy
               const G4ThreeVector  &p,             // Momentum of perticle
               const G4ThreeVector  &pre,           // Pre-position of track
               const G4ThreeVector  &pos,           // Post-position of track
               G4int                 hitnumber)
       :J4VHit(detector),  fCloneID(cloneID),
        fTrackID(trackID), fMotherTrackID(mothertrackID), 
        fParticle(particle),
        fTof(tof), fEnergyDeposit(edep),
        fTotalEnergy(totalE), fMomentum(p),
        fPrePosition(pre), fPostPosition(pos), 
        fHitNumber(hitnumber)
{
}


//=========================================================================
//* destructor -----------------------------------------------------------

J4VTrackerHit::~J4VTrackerHit()
{	
}
