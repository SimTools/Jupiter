// $Id$
#ifndef __J4IRBCALPREHIT__
#define __J4IRBCALPREHIT__
//*************************************************************************
//* --------------------
//* J4CALPreHit
//* --------------------
//* (Description)
//*     Hit class for J4CAL 	
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*     2004/08/30  Ono Hiroaki J4CALPreHit class for CAL front infomation
//*     2004/11/01  Allister Sanchez  Remove redundant data/functions which are in J4VHit.
//*     2006/06/03  A.Miyamoto Prepared for FCAL PreHit
//*************************************************************************

#include "J4VHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"

//=========================================================================
// TypeDef

class J4IRBCALPreHit;
typedef G4Allocator<J4IRBCALPreHit> J4IRBCALPreHitAllocator;
typedef G4THitsCollection<J4IRBCALPreHit> J4IRBCALPreHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------

class J4IRBCALPreHit : public J4VHit {

public:
  J4IRBCALPreHit();

  J4IRBCALPreHit( J4VComponent*         detector,
	       G4int                 posthitID,
	       G4int                 hitID,
               const G4ThreeVector&  pre,
	       const G4ThreeVector&  momentum,
	       G4double              edep,
	       G4double              tof,
	       G4int                 trackID,
               G4ParticleDefinition* particle,
	       G4int                 motherTrackID );

  virtual ~J4IRBCALPreHit();
  //  inline const J4CALPreHit& operator=( const J4CALPreHit& right );

  inline void* operator new    ( size_t );
  inline void  operator delete ( void* aHit );

  virtual void Output( G4HCofThisEvent* HCTE );
  virtual void Draw();
  virtual void Print();

  // getters
  inline G4int         GetPostHitID()        const { return fPostHitID;       }
  inline G4int         GetPreHitID()         const { return fPreHitID;       }
  inline G4ThreeVector GetInjectionPoint()   const { return GetPrePosition(); }
  
  // setters
  inline void SetPostHitID( G4int n )                { fPostHitID      = n; }
  inline void SetPreHitID( G4int n )                 { fPreHitID       = n; }
  inline void SetInjectionPoint( G4ThreeVector p )   { SetPrePosition(p); }

  static void SetOutput( J4Output *output )          { fgPreOutput = output; } 
    
  static J4IRBCALPreHitAllocator  fgPreHitAllocator;
  static J4Output             *fgPreOutput;       // Pointer to Output Module

  G4int                  fPreHitID;
  G4int                  fPostHitID;

};

//=====================================================================
//----------------------------------------
// inline function for J4IRBCALPreHit
//----------------------------------------

void* J4IRBCALPreHit::operator new( size_t )
{
  void* aHit;
  aHit = (void*)fgPreHitAllocator.MallocSingle();
  return aHit;
}

void J4IRBCALPreHit::operator delete( void* aHit )
{
  fgPreHitAllocator.FreeSingle( (J4IRBCALPreHit*)aHit );
}

#endif
