// $Id$
#ifndef __J4CDCDRIFTREGIONHIT__
#define __J4CDCDRIFTREGIONHIT__
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

#include "J4VHit.hh"
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
 

class J4CDCStereoDriftRegionHit : public J4VHit {

public:
  J4CDCStereoDriftRegionHit();
  J4CDCStereoDriftRegionHit(J4VComponent         *detector,
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
  	 	            
  J4CDCStereoDriftRegionHit(const J4CDCStereoDriftRegionHit &right);
  
  virtual ~J4CDCStereoDriftRegionHit();
  
  const J4CDCStereoDriftRegionHit& 
          operator=(const J4CDCStereoDriftRegionHit &right);    
  void* operator new    (size_t    );
  void  operator delete (void *aHit);

  virtual void Output(G4HCofThisEvent *HCTE);
  virtual void Draw();
  virtual void Print();
  
  virtual G4ThreeVector GetHitPosition() const; 
  virtual G4double      DistanceToWire(const G4ThreeVector &p,
                                             G4ThreeVector xx) const;
  static  void          SetOutput(J4Output *output) { fOutput=output; }
    
private: 

  G4ThreeVector  fHitPosition;
  G4ThreeVector  fWireEnd[2];
  G4double       fRotAngle;
  static J4CDCStereoDriftRegionHitAllocator  fHitAllocator;
  static J4Output  *fOutput; // Pointer to Output Module
  
};

//=====================================================================
//----------------------------------------
// inline function for J4CDCStereoDriftRegionHit
//----------------------------------------

inline J4CDCStereoDriftRegionHit::J4CDCStereoDriftRegionHit(const J4CDCStereoDriftRegionHit &right)
{
  fHitPosition  = right.fHitPosition ;
}

inline const J4CDCStereoDriftRegionHit& 
  J4CDCStereoDriftRegionHit::operator= (const J4CDCStereoDriftRegionHit &right)
{         
  fHitPosition  = right.fHitPosition ;
  return *this;
}
  
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

