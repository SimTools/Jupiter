// $Id$
//*************************************************************************
//* --------------------
//* J4VHit
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
#include "J4VHit.hh"

G4std::ofstream* J4VHit::fOfs = 0;

//=========================================================================
//* constructor -----------------------------------------------------------

J4VHit::J4VHit()
       :fComponent(0), fCloneID(0), fTrackID(0), fMotherTrackID(0),
        fParticle(0), fTof(0), fEnergyDeposit(0), fTotalEnergy(0),
        fMomentum(0), fPrePosition(0), fPostPosition(0), fHitNumber(0)
{ 
}

J4VHit::J4VHit(J4VComponent        *detector,
               const G4ThreeVector &pre,
               const G4ThreeVector &pos,
               G4int                cloneid)
       :fComponent(detector), fCloneID(cloneid), fTrackID(0), 
        fMotherTrackID(0),
        fParticle(0), fTof(0), fEnergyDeposit(0), fTotalEnergy(0),
        fMomentum(0), fPrePosition(pre), fPostPosition(pos), 
        fHitNumber(0)
{
}

J4VHit::J4VHit(J4VComponent         *detector,      // Belonging Component
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
       :fComponent(detector),  fCloneID(0),
        fTrackID(trackID), fMotherTrackID(mothertrackID), 
        fParticle(particle),
        fTof(tof), fEnergyDeposit(edep),
        fTotalEnergy(totalE), fMomentum(p),
        fPrePosition(pre), fPostPosition(pos), 
        fHitNumber(hitnumber)
{
}


J4VHit::J4VHit(J4VComponent         *detector,      // Belonging Component 
               G4int                 trackID,	    // TrackID
	            G4int                 mothertrackID, // MotherTrackID
               G4ParticleDefinition *particle,	    // particle
           		G4double              tof,           // TOF 
               G4double              edep,          // Energy Deposit
	            G4double              totalE,        // Total energy
               const G4ThreeVector  &p,             // Momentum of perticle
               const G4ThreeVector  &pre,           // Pre-position of track
               const G4ThreeVector  &pos)           // Post-position of track
	     :fComponent(detector), fCloneID(-9999), fTrackID(trackID), 
         fMotherTrackID(mothertrackID), fParticle(particle), 
	      fTof(tof), fEnergyDeposit(edep), 
	      fTotalEnergy(totalE), fMomentum(p),
	      fPrePosition(pre), fPostPosition(pos), fHitNumber(-9999)
{  
}


//=========================================================================
//* destructor -----------------------------------------------------------

J4VHit::~J4VHit()
{	
}

