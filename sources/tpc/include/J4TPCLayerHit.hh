#ifndef __J4TPCLAYERHIT__
#define __J4TPCLAYERHIT__
//*************************************************************************
//* --------------------
//* J4TPCLayerHit
//* --------------------
//* (Description)
//*     Hit class for J4TPCLayer 	
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

class J4TPCLayerHit;
typedef G4Allocator<J4TPCLayerHit> J4TPCLayerHitAllocator;
typedef G4THitsCollection<J4TPCLayerHit> J4TPCLayerHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J4TPCLayerHit : public J4VTrackerHit {

public:
  J4TPCLayerHit();
  J4TPCLayerHit(J4VComponent              *detector,
                    G4int                 trackID       = 0,
                    G4int                 mothertrackID = 0,
                    G4ParticleDefinition *particle      = 0,
                    G4double              tof           = 0,
                    G4double              edep          = 0,
                    G4double              totalE        = 0,
                    const G4ThreeVector  &momentum      = 0,
                    const G4ThreeVector  &pre           = 0,
                    const G4ThreeVector  &pos           = 0);	
  	 	            
  J4TPCLayerHit(const J4TPCLayerHit& right);
  
  virtual ~J4TPCLayerHit();
  
  const J4TPCLayerHit& 
          operator=(const J4TPCLayerHit& right);    
  void* operator new    (size_t    );
  void  operator delete (void* aHit);

  virtual void Output(G4HCofThisEvent* HCTE);
  static  void SetOutput(J4Output *output) { fOutput = output; }
  virtual void Draw();
  virtual void Print();
    
private: 

  static J4TPCLayerHitAllocator  fHitAllocator;
  static J4Output               *fOutput;       // Pointer to Output Module
  
};

//=====================================================================
//----------------------------------------
// inline function for J4TPCLayerHit
//----------------------------------------

inline J4TPCLayerHit::J4TPCLayerHit(const J4TPCLayerHit& right) 
     : J4VTrackerHit(right)
{
}

inline const J4TPCLayerHit& 
  J4TPCLayerHit::operator= (const J4TPCLayerHit& right)
{         
  J4VTrackerHit::operator=(right);
  return *this;
}
  
//----------------------------------------
// Allocator

inline void* J4TPCLayerHit::operator new(size_t)
{
  
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J4TPCLayerHit::operator delete(void* aHit)
{
  fHitAllocator.FreeSingle((J4TPCLayerHit*) aHit);
}



#endif

