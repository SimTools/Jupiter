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

#include "J4VHit.hh"
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
 

class J4CDCDriftRegionHit : public J4VHit {

public:
  J4CDCDriftRegionHit();
  J4CDCDriftRegionHit(J4VComponent         *detector,
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
                      const G4ThreeVector  &wireEndpz      = 0,
                      const G4ThreeVector  &wireEndmz      = 0, 
                      const G4double       &rotangle       = 0, 
                      const G4int           hitnumber      = 0); 
  	 	            
  J4CDCDriftRegionHit(const J4CDCDriftRegionHit &right);
  
  virtual ~J4CDCDriftRegionHit();
  
  const J4CDCDriftRegionHit& 
          operator=(const J4CDCDriftRegionHit &right);    
  void* operator new    (size_t    );
  void  operator delete (void *aHit);

  virtual void Output(G4HCofThisEvent *HCTE);
  virtual void Draw();
  virtual void Print();
  
  virtual G4ThreeVector GetHitPosition() const; 
  static  void          SetOutput(J4Output *output) { fOutput = output; }
    
private: 

  G4ThreeVector    fHitPosition;
  G4ThreeVector    fWireEnd[2];
  G4double         fRotAngle;
  static J4CDCDriftRegionHitAllocator  fHitAllocator;
  static J4Output *fOutput; // Pointer to Output Module
  
};

//=====================================================================
//----------------------------------------
// inline function for J4CDCDriftRegionHit
//----------------------------------------

inline J4CDCDriftRegionHit::J4CDCDriftRegionHit(const J4CDCDriftRegionHit &right)
{
  fHitPosition  = right.fHitPosition ;
}

inline const J4CDCDriftRegionHit& 
  J4CDCDriftRegionHit::operator= (const J4CDCDriftRegionHit &right)
{         
  fHitPosition  = right.fHitPosition ;
  return *this;
}
  
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

