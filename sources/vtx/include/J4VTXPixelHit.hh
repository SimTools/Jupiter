// $Id$
#ifndef __J4VTXPIXELHIT__
#define __J4VTXPIXELHIT__
//*************************************************************************
//* --------------------
//* J4VTXPixelHit
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

class J4VTXPixelHit;
typedef G4Allocator<J4VTXPixelHit> J4VTXPixelHitAllocator;
typedef G4THitsCollection<J4VTXPixelHit> J4VTXPixelHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J4VTXPixelHit : public J4VHit {

public:
  J4VTXPixelHit();
  J4VTXPixelHit(
            J4VComponent         *component,
            G4int                 trackID ,
            G4int                 parenttrackID ,
  	 	      G4ParticleDefinition *particle,
	    G4double              weight,
	    const G4ThreeVector  &origin,
            const G4ThreeVector  &origP,
            const G4String       &process,
		      G4int                 layerID ,
		      G4int                 ladderID ,
		      G4int                 sensorID,
		      G4int                 pixthetaID,
		      G4int                 pixphiID,
		      G4double              edep    ,
  	 	      const G4ThreeVector  &momentum,
  	 	      G4double              energy,
  	 	      G4double              tof,
  	 	      const G4ThreeVector  &pixPos,
  	 	      const G4ThreeVector  &inPos ,
		      const G4ThreeVector  &outPos,
  	 	      const G4ThreeVector  &localpixPos,
  	 	      const G4ThreeVector  &localinPos ,
		      const G4ThreeVector  &localoutPos
		      );
  	 	            
  
  virtual ~J4VTXPixelHit();
  
  const J4VTXPixelHit& 
          operator=(const J4VTXPixelHit& right);    
  void*   operator new    (size_t    );
  void    operator delete (void* aHit);

  virtual void Output(G4HCofThisEvent* HCTE);
  virtual void Draw();
  virtual void Print();

  void SetOutPos(G4ThreeVector out)     { fOutPosition=out; }  
  void SetLocalOutPos(G4ThreeVector out){ fLocalOutPosition=out; }  
  static void SetOutput(J4Output *output) { fOutput=output; } 

  G4ThreeVector         GetOrigin() { return fOrigin; }
  G4ThreeVector         GetHitPosition() ;
  G4String              GetProcessName(){return fProcess;}

  G4ParticleDefinition* GetPID()        { return GetParticle();     }
  G4int                 GetLayerID()    { return fLayerID;          }
  G4int                 GetLadderID()   { return fLadderID;         }
  G4int                 GetSensorID()   { return fSensorID;         }
  G4int                 GetPixThetaID() { return fPixThetaID;       }
  G4int                 GetPixPhiID()   { return fPixPhiID;         }
  G4double              GetEDeposit()   { return GetEnergyDeposit();}
  G4ThreeVector         GetPMomentum()  { return GetMomentum();     }
  G4double              GetPEnergy()    { return GetTotalEnergy();  }
  G4ThreeVector         GetPixelPosition() { return fPixPosition;   }
  G4ThreeVector         GetInPosition() { return fInPosition;       }
  G4ThreeVector         GetOutPosition(){ return fOutPosition;      }
  G4ThreeVector         GetLocalInPos() { return fLocalInPosition;  }
  G4ThreeVector         GetLocalOutPos(){ return fLocalOutPosition; }
  G4ThreeVector         GetLocalPixPos(){ return fLocalPixPosition; }
    
private: 

  G4ThreeVector         fOrigin;
  G4ThreeVector         fOriginP;
  G4double              fWeight;
  G4String              fProcess;

  G4int                 fLayerID;
  G4int                 fLadderID;
  G4int                 fSensorID;
  G4int                 fPixThetaID;
  G4int                 fPixPhiID;
  G4ThreeVector         fPixPosition;  
  G4ThreeVector         fInPosition;
  G4ThreeVector         fOutPosition;
  G4ThreeVector         fLocalInPosition;
  G4ThreeVector         fLocalOutPosition;
  G4ThreeVector         fLocalPixPosition;  

  static J4Output      *fOutput; // Pointer to Output Module
  static J4VTXPixelHitAllocator fHitAllocator;

};

//----------------------------------------
// Allocator

inline void* J4VTXPixelHit::operator new(size_t)
{
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J4VTXPixelHit::operator delete(void* aHit)
{
  fHitAllocator.FreeSingle((J4VTXPixelHit*) aHit);
}



#endif

