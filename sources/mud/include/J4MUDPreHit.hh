// $Id$
#ifndef __J4MUDPREHIT__
#define __J4MUDPREHIT__
//*************************************************************************
//* --------------------
//* J4MUDPreHit
//* --------------------
//* (Description)
//*     Hit class for J4CAL 	
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*     2004/08/30  Ono Hiroaki J4MUDPreHit class for CAL front infomation
//*     2004/11/01  Allister Sanchez  Remove redundant data/functions which are in J4VHit.
//*************************************************************************
#include "J4VHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"

//=========================================================================
// TypeDef
class J4CALPostHit;
class J4MUDPreHit;
typedef G4Allocator<J4MUDPreHit> J4MUDPreHitAllocator;
typedef G4THitsCollection<J4MUDPreHit> J4MUDPreHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
class J4MUDPreHit : public J4VHit {

public:
  J4MUDPreHit();

  J4MUDPreHit( J4VComponent*         detector,
	       G4int                 preHitID,
	       //J4CALPostHit*         postHitPtr,
	       G4int                 calPosthitID,
	       G4int                 calPreHitID,
               const G4ThreeVector&  pre,
	       const G4ThreeVector&  momentum,
	       G4double              edep,
	       G4double              tof,
               G4ParticleDefinition* particle,
	       G4int                 trackID,
	       G4int                 motherTrackID );

  virtual ~J4MUDPreHit();
  //  inline const J4MUDPreHit& operator=( const J4MUDPreHit& right );

  inline void* operator new    ( size_t );
  inline void  operator delete ( void* aHit );

  virtual void Output( G4HCofThisEvent* HCTE );
  virtual void Draw();
  virtual void Print();

  // getters
  inline G4int         GetPreHitID()         const { return fMUDPreHitID;     }
  inline J4CALPostHit* GetCALPostHitPtr()    const { return fCALPostHitPtr;   }
  inline G4int         GetCALPostHitID()     const { return fCALPostHitID;    }
  inline G4int         GetCALPreHitID()      const { return fCALPreHitID;     }
  inline G4ThreeVector GetInjectionPoint()   const { return GetPrePosition(); }
  //inline G4ThreeVector GetMomentum()         const { return fMomentum;       }
  //inline G4double      GetKineticEnergy()    const { return fEnergy;         }
  //inline G4double      GetTof()              const { return fTof;            }
  //inline G4int         GetTrackID()          const { return fTrackID;        }
  //inline G4ParticleDefinition* GetParticle() const { return fParticle;       }
  
  // setters
  inline void SetPreHitID( G4int n )                 { fMUDPreHitID   = n;    }
  inline void SetCALPostHitPtr( J4CALPostHit* post ) { fCALPostHitPtr = post; }
  inline void SetCALPostHitID( G4int n )             { fCALPostHitID  = n;    }
  inline void SetCALPreHitID( G4int n )              { fCALPreHitID   = n;    }
  inline void SetInjectionPoint( const G4ThreeVector& p )  { SetPrePosition(p); }
  //inline void SetMomentum( const G4ThreeVector& p )  { fMomentum       = p; }
  //inline void SetKineticEnergy( G4double x )         { fEnergy = x; } 
  //inline void SetTof( G4double x )                   { fTof            = x; }
  //inline void SetTrackID( G4int n )                  { fTrackID        = n; }
  //inline void SetParticle( G4ParticleDefinition *p ) { fParticle       = p; }

  static void SetOutput( J4Output *output )          { fgPreOutput = output; } 
    
  static J4MUDPreHitAllocator  fgPreHitAllocator;
  static J4Output             *fgPreOutput;       // Pointer to Output Module

  J4CALPostHit*          fCALPostHitPtr;
  G4int                  fCALPostHitID;
  G4int                  fCALPreHitID;
  G4int                  fMUDPreHitID;

  // The following data are available from J4VHit
  //G4ThreeVector          fInjectionPoint; // fPrePosition in J4VHit
  //G4ThreeVector          fMomentum;
  //G4double               fEnergy;  // fTotalEnergy in J4VHit
  //G4double               fTof;
  //G4int                  fTrackID;
  //G4ParticleDefinition  *fParticle;
};

//=====================================================================
//----------------------------------------
// inline function for J4MUDPreHit
//----------------------------------------
void* J4MUDPreHit::operator new( size_t )
{
  void* aHit;
  aHit = (void*)fgPreHitAllocator.MallocSingle();
  return aHit;
}

void J4MUDPreHit::operator delete( void* aHit )
{
  fgPreHitAllocator.FreeSingle( (J4MUDPreHit*)aHit );
}

#endif
