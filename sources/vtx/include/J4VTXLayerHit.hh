// $Id$
#ifndef __J4VTXLAYERHIT__
#define __J4VTXLAYERHIT__
//*************************************************************************
//* --------------------
//* J4VTXLayerHit
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
#include "J4Output.hh"


//=========================================================================
// TypeDef

class J4VTXLayerHit;
typedef G4Allocator<J4VTXLayerHit> J4VTXLayerHitAllocator;
typedef G4THitsCollection<J4VTXLayerHit> J4VTXLayerHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J4VTXLayerHit : public J4VHit {

public:
  J4VTXLayerHit();
  J4VTXLayerHit(
            J4VComponent         *component,
            G4int                 trackID ,
            G4int                 parenttrackID ,
            G4ParticleDefinition *particle,
	    G4int                 layerID ,
            G4double              edep    ,
  	    const G4ThreeVector  &momentum,
  	    G4double              energy,
  	    G4double              tof,
  	    const G4ThreeVector  &inPos ,
	    const G4ThreeVector  &outPos
	    );
  	 	            
  
  virtual ~J4VTXLayerHit();
  
  const J4VTXLayerHit& 
          operator=(const J4VTXLayerHit& right);    
  void*   operator new    (size_t    );
  void    operator delete (void* aHit);

  virtual void Output(G4HCofThisEvent* HCTE);
  virtual void Draw();
  virtual void Print();
  static void SetOutput(J4Output *output) { fOutput=output; } 

  G4ThreeVector         GetHitPosition() ;  
  inline G4int                 GetLayerID()    { return fLayerID;   };
  inline G4ThreeVector         GetInPosition(){ return fInPosition; }
  inline G4ThreeVector         GetOutPosition(){ return fOutPosition; }

private: 
  G4ThreeVector  fInPosition;
  G4ThreeVector  fOutPosition;
  G4int fLayerID;

  static J4VTXLayerHitAllocator fHitAllocator;
  static J4Output      *fOutput; // Pointer to Output Module

};

//----------------------------------------
// Allocator

inline void* J4VTXLayerHit::operator new(size_t)
{
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J4VTXLayerHit::operator delete(void* aHit)
{
  fHitAllocator.FreeSingle((J4VTXLayerHit*) aHit);
}



#endif

