// $Id$
#ifndef __J4VTXSENSORHIT__
#define __J4VTXSENSORHIT__
//*************************************************************************
//* --------------------
//* J4VTXSensorHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4CDCDriftRegion.
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*	2002/11/20  T.Aso   Original version
//*************************************************************************

#include "J4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"

//=========================================================================
// TypeDef

class J4VTXSensorHit;
typedef G4Allocator<J4VTXSensorHit> J4VTXSensorHitAllocator;
typedef G4THitsCollection<J4VTXSensorHit> J4VTXSensorHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J4VTXSensorHit : public J4VHit {

public:
  J4VTXSensorHit();
  J4VTXSensorHit(
            J4VComponent         *component,
            G4int                 trackID ,
            G4int                 parenttrackID ,
	    G4ParticleDefinition *particle,
	    G4double             weight,
	    const G4ThreeVector  &origin,
	    const G4ThreeVector  &origP,
	    const G4String       &process, 
	    G4int                 layerID ,
	    G4int                 ladderID ,
	    G4int                 sensorID,
	    G4double              edep    ,
	    const G4ThreeVector  &momentum,
	    G4double              energy,
	    G4double              tof,
	    const G4ThreeVector  &inPos ,
	    const G4ThreeVector  &outPos,
	    const G4ThreeVector  &localinPos ,
	    const G4ThreeVector  &localoutPos
	    );
  	 	            
  
  virtual ~J4VTXSensorHit();
  
  const J4VTXSensorHit& 
          operator=(const J4VTXSensorHit& right);    
  void*   operator new    (size_t    );
  void    operator delete (void* aHit);

  virtual void Output(G4HCofThisEvent* HCTE);
  virtual void Draw();
  virtual void Print();

  void SetOutPos(G4ThreeVector out)     { fOutPosition=out; }  
  void SetLocalOutPos(G4ThreeVector out){ fLocalOutPosition=out; }  
  G4ThreeVector         GetOrigin() { return fOrigin; }
  G4ThreeVector         GetHitPosition() ;  
  G4String              GetProcessName(){return fProcess;}
  G4ParticleDefinition* GetPID()        { return GetParticle();     }
  
  G4int                 GetLayerID()    { return fLayerID;          }
  G4int                 GetLadderID()   { return fLadderID;         }
  G4int                 GetSensorID()   { return fSensorID;         }
  G4double              GetEDeposit()   { return GetEnergyDeposit();}
  G4ThreeVector         GetPMomentum()  { return GetMomentum();     }
  G4double              GetPEnergy()    { return GetTotalEnergy();  }
  G4ThreeVector         GetInPosition() { return fInPosition;       }
  G4ThreeVector         GetOutPosition(){ return fOutPosition;      }
  G4ThreeVector         GetLocalInPos() { return fLocalInPosition;  }
  G4ThreeVector         GetLocalOutPos(){ return fLocalOutPosition; }
    
private: 

  G4ThreeVector         fOrigin;
  G4ThreeVector         fOriginP;
  G4double              fWeight;
  G4String              fProcess;
  G4int                 fLayerID;
  G4int                 fLadderID;
  G4int                 fSensorID;
  G4ThreeVector         fInPosition;
  G4ThreeVector         fOutPosition;
  G4ThreeVector         fLocalInPosition;
  G4ThreeVector         fLocalOutPosition;

  static J4VTXSensorHitAllocator fHitAllocator;

};

//----------------------------------------
// Allocator

inline void* J4VTXSensorHit::operator new(size_t)
{
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J4VTXSensorHit::operator delete(void* aHit)
{
  fHitAllocator.FreeSingle((J4VTXSensorHit*) aHit);
}



#endif

