// $Id$
#ifndef __J4CDCDRIFTREGIONHIT__
#define __J4CDCDRIFTREGIONHIT__
//*************************************************************************
//* --------------------
//* J4CDCDriftRegionHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4CDCDriftRegion.
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCDCDriftRegionHit.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4RotationMatrix.hh"
#include "J4Output.hh"


//=========================================================================
// TypeDef

class J4CDCDriftRegionHit;
typedef G4Allocator<J4CDCDriftRegionHit> J4CDCDriftRegionHitAllocator;
typedef G4THitsCollection<J4CDCDriftRegionHit> J4CDCDriftRegionHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J4CDCDriftRegionHit : public J4VCDCDriftRegionHit {

public:
  J4CDCDriftRegionHit(
            J4VComponent         *detector,          // Belonging DetectorComponent
            G4int                 cloneID,           // CloneID
            G4int                 trackID       = 0, // TrackID
            G4int                 mothertrackID = 0, // MotherTrackID
            G4ParticleDefinition *particle      = 0, // Particle 
            G4double              tof           = 0, // TOF
            G4double              edep          = 0, // Energy Deposit
            G4double              totalE        = 0, // Total energy
            const G4ThreeVector  &momentum      = G4ThreeVector(0.), // Momentum of perticle
            const G4ThreeVector  &pre           = G4ThreeVector(0.), // Pre-position of track
            const G4ThreeVector  &pos           = G4ThreeVector(0.), // Post-position of track
            const G4double        rotangle      = 0, // rotation angle of cell 
            const G4ThreeVector  &wireEndpz     = G4ThreeVector(0.), // wire position at +ve z endcap
            const G4ThreeVector  &wireEndmz     = G4ThreeVector(0.), // wire position at -ve z endcap 
            const G4double        stereoangle   = 0, // stereo angle of cell 
            const G4double        rwaist        = 0, // waist radius of sense wire surface 
            const G4int           hitnumber     = 0); // unique hit number 
  	 	            
  inline J4CDCDriftRegionHit(const J4CDCDriftRegionHit &right)
            :J4VCDCDriftRegionHit(right) {} 
  
  virtual ~J4CDCDriftRegionHit();
  
  void* operator   new    (size_t    );
  void  operator   delete (void *aHit);

  virtual void     Output(G4HCofThisEvent *HCTE);

  static  void     SetOutput(J4Output *output) { fOutput = output; }
    
private: 

  static J4CDCDriftRegionHitAllocator  fHitAllocator;
  static J4Output *fOutput; // Pointer to Output Module
  
};

//=====================================================================
//----------------------------------------
// inline function for J4CDCDriftRegionHit
//----------------------------------------

//----------------------------------------
// Allocator

inline void* J4CDCDriftRegionHit::operator new(size_t)
{
  
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J4CDCDriftRegionHit::operator delete(void *aHit)
{
  fHitAllocator.FreeSingle((J4CDCDriftRegionHit*) aHit);
}

#endif

