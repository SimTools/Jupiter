// $Id$
#ifndef __J4CALHIT__
#define __J4CALHIT__
//*************************************************************************
//* --------------------
//* J4CALHit
//* --------------------
//* (Description)
//*     Hit class for J4CAL 	
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4VHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"

//=========================================================================
// TypeDef

class J4CALHit;
typedef G4Allocator<J4CALHit> J4CALHitAllocator;
typedef G4THitsCollection<J4CALHit> J4CALHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------

class J4CALHit : public J4VHit {

public:
  J4CALHit();

  J4CALHit(
           J4VComponent         *detector,
           G4int                 ConeID,
           G4int                 TowerID,
           G4int                 MiniConeID,
           G4int                 MiniTowerID,
           G4int                 LayerID,
           G4int                 SubLayerID,
           G4bool                isBarrel,
           G4bool                isEM,
           G4double              edep,
           G4double              tof,
           const G4ThreeVector  &pre,
           G4int                 mothertrackID,
           G4int                 trackID,
           G4ParticleDefinition *particle);

  virtual ~J4CALHit();

  //inline J4CALHit(const J4CALHit& right){};
  
  //inline const J4CALHit& 
  //     operator=(const J4CALHit& right);

  inline void* operator new    (size_t);
  inline void  operator delete (void* aHit);

  virtual void Output(G4HCofThisEvent* HCTE);
  virtual void Draw();
  virtual void Print();

  // getters
  inline G4int  GetConeID()          const { return fConeID;        }
  inline G4int  GetTowerID()         const { return fTowerID;       }
  inline G4int  GetMiniConeID()      const { return fMiniConeID;    }
  inline G4int  GetMiniTowerID()     const { return fMiniTowerID;   }
  inline G4int  GetLayerID()         const { return fLayerID;       }
  inline G4int  GetSubLayerID()      const { return fSubLayerID;    }
  inline G4int  GetMotherTrackID()   const { return fMotherTrackID; }
  inline G4int  GetTrackID()         const { return fTrackID;       }
  inline G4bool IsBarrel()           const { return fIsBarrel;      }
  inline G4bool IsEM()               const { return fIsEM;          }
  inline G4double GetEnergyDeposit() const { return fEnergyDep;     }
  inline G4double GetTof()           const { return fTof;           }
  inline G4ThreeVector GetInjectionPoint() const { return fInjectionPoint; }
  inline G4ParticleDefinition * GetParticle() const { return fParticle; }

  // setters 
  inline void SetConeID(G4int n)           { fConeID        = n; }
  inline void SetTowerID(G4int n)          { fTowerID       = n; }
  inline void SetMiniConeID(G4int n)       { fMiniConeID    = n; }
  inline void SetMiniTowerID(G4int n)      { fMiniTowerID   = n; }
  inline void SetLayerID(G4int n)          { fLayerID       = n; }
  inline void SetSubLayerID(G4int n)       { fSubLayerID    = n; }
  inline void SetMotherTrackID(G4int n)    { fMotherTrackID = n; }
  inline void SetTrackID(G4int n)          { fTrackID       = n; }
  inline void SetEnergyDeposit(G4double x) { fEnergyDep     = x; }
  inline void SetTof(G4double x)           { fTof           = x; }
  inline void SetInjectionPoint(G4ThreeVector p) { fInjectionPoint = p; }
  inline void SetParticle(G4ParticleDefinition *p) { fParticle     = p; }
  inline void AccumulateEdep(G4double ed)  { fEnergyDep += ed; }
  static void SetOutput(J4Output *output)  { fOutput=output; } 
    
private: 

  static J4CALHitAllocator  fHitAllocator;
  static J4Output          *fOutput;       // Pointer to Output Module

  G4int          fConeID; 
  G4int          fTowerID; 
  G4int          fMiniConeID; 
  G4int          fMiniTowerID; 
  G4int          fLayerID; 
  G4int          fSubLayerID; 
  G4bool         fIsBarrel;
  G4bool         fIsEM;
  G4double       fEnergyDep;
  G4double       fTof;
  G4ThreeVector  fInjectionPoint;
  G4int          fMotherTrackID;
  G4int          fTrackID;
  G4ParticleDefinition     *fParticle;
  
};

//=====================================================================
//----------------------------------------
// inline function for J4CALHit
//----------------------------------------
  
//----------------------------------------
// Allocator

//const J4CALHit& 
//       J4CALHit::operator=(const J4CALHit& right)
//{
//  return *this;
//}

void* J4CALHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*)fHitAllocator.MallocSingle();
  return aHit;
}

void J4CALHit::operator delete(void* aHit)
{
  fHitAllocator.FreeSingle((J4CALHit*) aHit);
}

#endif
