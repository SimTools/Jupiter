// $Id$
#ifndef __J4VTXLADDERHIT__
#define __J4VTXLADDERHIT__
//*************************************************************************
//* --------------------
//* J4VTXLadderHit
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


//=========================================================================
// TypeDef

class J4VTXLadderHit;
typedef G4Allocator<J4VTXLadderHit> J4VTXLadderHitAllocator;
typedef G4THitsCollection<J4VTXLadderHit> J4VTXLadderHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J4VTXLadderHit : public J4VHit {

public:
  J4VTXLadderHit();
  J4VTXLadderHit(
            J4VComponent         *component,
            G4int                 trackID ,
            G4int                 parenttrackID ,
  	 	      G4ParticleDefinition *particle,
	    G4int                 layerID ,
	    G4int                 ladderID ,
		      G4double              edep    ,
  	 	      const G4ThreeVector  &momentum,
  	 	      G4double              energy,
  	 	      G4double              tof,
  	 	      const G4ThreeVector  &inPos ,
		      const G4ThreeVector  &outPos
		      );
  	 	            
  
  virtual ~J4VTXLadderHit();
  
  const J4VTXLadderHit& 
          operator=(const J4VTXLadderHit& right);    
  void*   operator new    (size_t    );
  void    operator delete (void* aHit);

  virtual void Output(G4HCofThisEvent* HCTE);
  virtual void Draw();
  virtual void Print();

  G4ThreeVector         GetHitPosition() ;  
  G4int                 GetLayerID()    { return fLayerID;   };
  G4int                 GetLadderID()   { return fLadderID;  };

private: 
  G4ThreeVector  fInPosition;
  G4ThreeVector  fOutPosition;
  G4int fLayerID;
  G4int fLadderID;

  static J4VTXLadderHitAllocator fHitAllocator;

};

//----------------------------------------
// Allocator

inline void* J4VTXLadderHit::operator new(size_t)
{
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J4VTXLadderHit::operator delete(void* aHit)
{
  fHitAllocator.FreeSingle((J4VTXLadderHit*) aHit);
}



#endif

