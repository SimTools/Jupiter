// $Id$
#ifndef __J4VTXPIXELAREAHIT__
#define __J4VTXPIXELAREAHIT__
//*************************************************************************
//* --------------------
//* J4VTXPixelAreaHit
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

class J4VTXPixelAreaHit;
typedef G4Allocator<J4VTXPixelAreaHit> J4VTXPixelAreaHitAllocator;
typedef G4THitsCollection<J4VTXPixelAreaHit> J4VTXPixelAreaHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J4VTXPixelAreaHit : public J4VHit {

public:
  J4VTXPixelAreaHit();
  J4VTXPixelAreaHit(  G4int		    trackID ,
                      G4int		    parenttrackID ,
  	 	      G4ParticleDefinition* particle,
		      G4int		    layerID ,
		      G4int		    ladderID ,
		      G4int		    sensorID,
		      G4int		    pixthetaID,
		      G4int		    pixphiID,
		      G4double		    edep    ,
  	 	      const G4ThreeVector  momentum,
  	 	      G4double  energy,
  	 	      const G4ThreeVector  pixPos,
  	 	      const G4ThreeVector  inPos ,
		      const G4ThreeVector  outPos,
  	 	      const G4ThreeVector  localpixPos,
  	 	      const G4ThreeVector  localinPos ,
		      const G4ThreeVector  localoutPos
		      );
  	 	            
  
  virtual ~J4VTXPixelAreaHit();
  
  const J4VTXPixelAreaHit& 
          operator=(const J4VTXPixelAreaHit& right);    
  void* operator new    (size_t    );
  void  operator delete (void* aHit);

  virtual void Output(G4HCofThisEvent* HCTE);
  virtual void Draw();
  virtual void Print();

  void AddEdep(G4double edep){ fEdep += edep; }  
  void SetOutPos(G4ThreeVector out){ fOutPosition=out; }  
  void SetLocalOutPos(G4ThreeVector out){ fLocalOutPosition=out; }  

  G4ThreeVector GetHitPosition() ;  
  G4int GetTrackID(){return   fTrackID ; }
  G4ParticleDefinition* GetPID(){ return fPID;}
  G4int GetLayerID(){ return fLayerID; }
  G4int GetLadderID(){ return fLadderID;}
  G4int GetSensorID(){ return fSensorID;}
  G4int GetPixThetaID() { return fPixThetaID;}
  G4int GetPixPhiID() { return fPixPhiID;}
  G4double GetEDeposit(){ return fEdep;}
  G4ThreeVector GetPMomentum() {return fMomentum;}
  G4double GetPEnergy(){ return fEnergy;}
  G4ThreeVector GetPixelPosition() { return fPixPosition; }
  G4ThreeVector GetInPosition() { return fInPosition;}
  G4ThreeVector	GetOutPosition(){ return fOutPosition;}
  G4ThreeVector	GetLocalInPos(){ return fLocalInPosition;}
  G4ThreeVector	GetLocalOutPos() { return fLocalOutPosition;}
  G4ThreeVector GetLocalPixPos(){ return fLocalPixPosition; }
    
private: 

  G4int fTrackID;
  G4ParticleDefinition* fPID;
  G4int fLayerID;
  G4int fLadderID;
  G4int fSensorID;
  G4int fPixThetaID;
  G4int fPixPhiID;
  G4double  fEdep;
  G4ThreeVector fMomentum;
  G4double fEnergy;
  G4ThreeVector fPixPosition;  
  G4ThreeVector	fInPosition;
  G4ThreeVector	fOutPosition;
  G4ThreeVector	fLocalInPosition;
  G4ThreeVector	fLocalOutPosition;
  G4ThreeVector fLocalPixPosition;  

  static J4VTXPixelAreaHitAllocator fHitAllocator;

};

//----------------------------------------
// Allocator

inline void* J4VTXPixelAreaHit::operator new(size_t)
{
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J4VTXPixelAreaHit::operator delete(void* aHit)
{
  fHitAllocator.FreeSingle((J4VTXPixelAreaHit*) aHit);
}



#endif

