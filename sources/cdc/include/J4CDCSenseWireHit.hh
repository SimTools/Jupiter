// $Id$
#ifndef __J4CDCSENSEWIREHIT__
#define __J4CDCSENSEWIREHIT__
//*************************************************************************
//* --------------------
//* J4CDCSenseWireHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4CDCDriftRegion.
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4VTrackerHit.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"


//=========================================================================
// TypeDef

class J4CDCSenseWireHit;
typedef G4Allocator<J4CDCSenseWireHit> J4CDCSenseWireHitAllocator;
typedef G4THitsCollection<J4CDCSenseWireHit> J4CDCSenseWireHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J4CDCSenseWireHit : public J4VTrackerHit {

public:
  J4CDCSenseWireHit();
  J4CDCSenseWireHit(J4VComponent         *detector,
                    G4int                 cloneNo,
                    G4int                 trackID       = 0,
                    G4int                 mothertrackID = 0,
                    G4ParticleDefinition *particle      = 0,
                    G4double              tof           = 0,
                    G4double              edep          = 0,
                    G4double              totalE        = 0,
                    const G4ThreeVector  &momentum      = 0,
                    const G4ThreeVector  &pre           = 0,
                    const G4ThreeVector  &pos           = 0  );	
  	 	            
  J4CDCSenseWireHit(const J4CDCSenseWireHit& right);
  
  virtual ~J4CDCSenseWireHit();
  
  const J4CDCSenseWireHit& 
          operator=(const J4CDCSenseWireHit& right);    
  void* operator new    (size_t    );
  void  operator delete (void* aHit);

  virtual void Output(G4HCofThisEvent* HCTE);
  virtual void Draw();
  virtual void Print();
  
  G4ThreeVector GetHitPosition() const;  
    
private: 

  G4ThreeVector                     fHitPosition;
  static J4CDCSenseWireHitAllocator fHitAllocator;
  
};

//=====================================================================
//----------------------------------------
// inline function for J4CDCSenseWireHit
//----------------------------------------

inline J4CDCSenseWireHit::J4CDCSenseWireHit(const J4CDCSenseWireHit& right)
     : J4VTrackerHit(right) 
{
  fHitPosition  = right.fHitPosition ;                       
}

inline const J4CDCSenseWireHit& 
  J4CDCSenseWireHit::operator= (const J4CDCSenseWireHit& right)
{         
  J4VTrackerHit::operator=(right);
  fHitPosition  = right.fHitPosition ;                       
  return *this;
}
  
//----------------------------------------
// Allocator

inline void* J4CDCSenseWireHit::operator new(size_t)
{
  
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J4CDCSenseWireHit::operator delete(void* aHit)
{
  fHitAllocator.FreeSingle((J4CDCSenseWireHit*) aHit);
}



#endif

