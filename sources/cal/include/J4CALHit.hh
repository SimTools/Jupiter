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
  J4CALHit(J4VComponent         *detector,   
           G4int                 thetaNumber,
           G4int                 phiNumber,
           G4bool                isbarrel,
           G4bool                isEM,
           G4double              edep,
           G4double              tof,
           const G4ThreeVector  &pre,
           G4int                 mothertrackID,
           G4int                 trackID,
           G4ParticleDefinition *particle);
  	 	            
  virtual ~J4CALHit();
  
  void* operator new    (size_t    );
  void  operator delete (void* aHit);

  virtual void Output(G4HCofThisEvent* HCTE);
  virtual void Draw();
  virtual void Print();

  // getters
  inline G4int         GetThetaNumber()    const { return fThetaNumber;   }
  inline G4int         GetPhiNumber()      const { return fPhiNumber;     }
  inline G4int         GetMotherTrackID()  const { return fMotherTrackID; }
  inline G4int         GetTrackID()        const { return fTrackID;       }
  inline G4bool        IsBarrel()          const { return fIsBarrel;      }
  inline G4bool        IsEM()              const { return fIsEM;          }
  inline G4double      GetEnerygDeposit()  const { return fEnergyDep;     }
  inline G4double      GetTof()            const { return fTof;           }
  inline G4ThreeVector GetInjectionPoint() const { return fInjectionPoint; }
  inline G4ParticleDefinition * GetParticle() const { return fParticle; }

  // setters 
  inline void SetThetaNumber  (G4int n) { fThetaNumber   = n; }
  inline void SetPhiNumber    (G4int n) { fPhiNumber     = n; }
  inline void SetMotherTrackID(G4int n) { fMotherTrackID = n; }
  inline void SetTrackID      (G4int n) { fTrackID       = n; }
  inline void SetEnergyDeposit(G4double x) { fEnergyDep  = x; }
  inline void SetTof          (G4double x) { fTof        = x; }
  inline void SetInjectionPoint(G4ThreeVector p)   { fInjectionPoint = p; }
  inline void SetParticle(G4ParticleDefinition *p) { fParticle       = p; }

  inline void AccumulateEdep(G4double ed) { fEnergyDep += ed; }
    
private: 

  static J4CALHitAllocator  fHitAllocator;
  static J4Output          *fOutput;       // Pointer to Output Module

  G4int                     fThetaNumber; 
  G4int                     fPhiNumber;
  G4bool                    fIsBarrel;
  G4bool                    fIsEM;
  G4double                  fEnergyDep;
  G4double                  fTof;
  G4ThreeVector             fInjectionPoint;
  G4int                     fMotherTrackID;
  G4int                     fTrackID;
  G4ParticleDefinition     *fParticle;
  
};

//=====================================================================
//----------------------------------------
// inline function for J4CALHit
//----------------------------------------
  
//----------------------------------------
// Allocator

inline void* J4CALHit::operator new(size_t)
{
  
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J4CALHit::operator delete(void* aHit)
{
  fHitAllocator.FreeSingle((J4CALHit*) aHit);
}



#endif

