// $Id$
#ifndef __J4CDCSTEREODRIFTREGIONHIT__
#define __J4CDCSTEREODRIFTREGIONHIT__
//*************************************************************************
//* --------------------
//* J4CDCStereoDriftRegionHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4CDCStereoDriftRegion.
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

class J4CDCStereoDriftRegionHit;
typedef G4Allocator<J4CDCStereoDriftRegionHit> J4CDCStereoDriftRegionHitAllocator;
typedef G4THitsCollection<J4CDCStereoDriftRegionHit> J4CDCStereoDriftRegionHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J4CDCStereoDriftRegionHit : public J4VCDCDriftRegionHit {

public:
  J4CDCStereoDriftRegionHit();
  J4CDCStereoDriftRegionHit(J4VComponent   *detector,
                      G4int                 cloneID, 
                      G4int                 trackID        = 0,
                      G4int                 mothertrackID  = 0,
                      G4ParticleDefinition *particle       = 0,
                      G4double              tof            = 0,
                      G4double              edep           = 0,
                      G4double              totalE         = 0,
                      const G4ThreeVector  &momentum       = 0,
                      const G4ThreeVector  &pre            = 0,
                      const G4ThreeVector  &pos            = 0,
                      G4double              rotangle       = 0, 
                      const G4ThreeVector  &wireEndpz      = 0,
                      const G4ThreeVector  &wireEndmz      = 0, 
                      G4double              stereoangle    = 0, 
                      G4double              rwaist         = 0, 
                      const G4int           hitnumber      = 0); 

  J4CDCStereoDriftRegionHit(const J4CDCStereoDriftRegionHit &right)
           :J4VCDCDriftRegionHit(right) {}
  
  virtual ~J4CDCStereoDriftRegionHit();

  void* operator new    (size_t    );
  void  operator delete (void *aHit);

  virtual void   Output(G4HCofThisEvent *HCTE);
  static  void   SetOutput(J4Output *output) { fOutput=output; }
    
private: 

  static J4Output *fOutput; // Pointer to Output Module
  static J4CDCStereoDriftRegionHitAllocator  fHitAllocator;
  
};

//=====================================================================
//----------------------------------------
// inline function for J4CDCStereoDriftRegionHit
//----------------------------------------
  
//----------------------------------------
// Allocator

inline void* J4CDCStereoDriftRegionHit::operator new(size_t)
{
  
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J4CDCStereoDriftRegionHit::operator delete(void *aHit)
{
  fHitAllocator.FreeSingle((J4CDCStereoDriftRegionHit*) aHit);
}

#endif

