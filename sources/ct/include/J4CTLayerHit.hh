// $Id$
#ifndef __J4CTLAYERHIT__
#define __J4CTLAYERHIT__
//*************************************************************************
//* --------------------
//* J4CTLayerHit
//* --------------------
//* (Description)
//*     Hit class for J4CTLayer 	
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

class J4CTLayerHit;
typedef G4Allocator<J4CTLayerHit> J4CTLayerHitAllocator;
typedef G4THitsCollection<J4CTLayerHit> J4CTLayerHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J4CTLayerHit : public J4VTrackerHit {

public:
  J4CTLayerHit();
  J4CTLayerHit(J4VComponent              *detector,
                    G4int                 trackID       = 0,
                    G4int                 mothertrackID = 0,
                    G4ParticleDefinition *particle      = 0,
                    G4double              tof           = 0,
                    G4double              edep          = 0,
                    G4double              totalE        = 0,
                    const G4ThreeVector  &momentum      = 0,
                    const G4ThreeVector  &pre           = 0,
                    const G4ThreeVector  &pos           = 0  );	
  	 	            
  J4CTLayerHit(const J4CTLayerHit& right);
  
  virtual ~J4CTLayerHit();
  
  const J4CTLayerHit& 
          operator=(const J4CTLayerHit& right);    
  void* operator new    (size_t    );
  void  operator delete (void* aHit);

  virtual void Output(G4HCofThisEvent* HCTE);
  virtual void Draw();
  virtual void Print();
  static void SetOutput(J4Output *output) { fOutput=output; } 
    
private: 

  static J4CTLayerHitAllocator  fHitAllocator;
  static J4Output              *fOutput;       // Pointer to Output Module
  
};

//=====================================================================
//----------------------------------------
// inline function for J4CTLayerHit
//----------------------------------------

inline J4CTLayerHit::J4CTLayerHit(const J4CTLayerHit& right)
{
}

inline const J4CTLayerHit& 
  J4CTLayerHit::operator= (const J4CTLayerHit& right)
{         
  return *this;
}
  
//----------------------------------------
// Allocator

inline void* J4CTLayerHit::operator new(size_t)
{
  
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J4CTLayerHit::operator delete(void* aHit)
{
  fHitAllocator.FreeSingle((J4CTLayerHit*) aHit);
}



#endif

