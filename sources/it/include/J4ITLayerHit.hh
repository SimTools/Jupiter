// $Id$
#ifndef __J4ITLAYERHIT__
#define __J4ITLAYERHIT__
//*************************************************************************
//* --------------------
//* J4ITLayerHit
//* --------------------
//* (Description)
//*     Hit class for J4ITLayer 	
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4VTrackerHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"


//=========================================================================
// TypeDef

class J4ITLayerHit;
typedef G4Allocator<J4ITLayerHit> J4ITLayerHitAllocator;
typedef G4THitsCollection<J4ITLayerHit> J4ITLayerHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J4ITLayerHit : public J4VTrackerHit {

public:
  J4ITLayerHit();
  J4ITLayerHit(J4VComponent              *detector,
                    G4int                 trackID       = 0,
                    G4int                 mothertrackID = 0,
                    G4ParticleDefinition *particle      = 0,
                    G4double              tof           = 0,
                    G4double              edep          = 0,
                    G4double              totalE        = 0,
                    const G4ThreeVector  &momentum      = G4ThreeVector(0.),
                    const G4ThreeVector  &pre           = G4ThreeVector(0.),
                    const G4ThreeVector  &pos           = G4ThreeVector(0.));	
  	 	            
  J4ITLayerHit(const J4ITLayerHit& right);
  
  virtual ~J4ITLayerHit();
  
  const J4ITLayerHit& 
          operator=(const J4ITLayerHit& right);    
  void* operator new    (size_t    );
  void  operator delete (void* aHit);

  virtual void Output(G4HCofThisEvent* HCTE);
  virtual void Draw();
  virtual void Print();
  static void SetOutput(J4Output *output) { fOutput=output; } 
    
private: 

  static J4ITLayerHitAllocator  fHitAllocator;
  static J4Output              *fOutput;       // Pointer to Output Module
  
};

//=====================================================================
//----------------------------------------
// inline function for J4ITLayerHit
//----------------------------------------

inline J4ITLayerHit::J4ITLayerHit(const J4ITLayerHit& right)
     : J4VTrackerHit(right)
{
}

inline const J4ITLayerHit& 
  J4ITLayerHit::operator= (const J4ITLayerHit& right)
{         
  J4VTrackerHit::operator=(right);
  return *this;
}
  
//----------------------------------------
// Allocator

inline void* J4ITLayerHit::operator new(size_t)
{
  
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J4ITLayerHit::operator delete(void* aHit)
{
  fHitAllocator.FreeSingle((J4ITLayerHit*) aHit);
}



#endif

