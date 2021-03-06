// $Id$
#ifndef __J4CLXPREHIT__
#define __J4CLXPREHIT__
//*************************************************************************
//* --------------------
//* J4CLXPreHit
//* --------------------
//* (Description)
//*     Hit class for J4CLX 	
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*     2004/08/30  Ono Hiroaki J4CLXPreHit class for CLX front infomation
//*     2004/11/01  Allister Sanchez  Remove redundant data/functions which are in J4VHit.
//*************************************************************************

#include "J4VHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"

//=========================================================================
// TypeDef

class J4CLXPreHit;
typedef G4Allocator<J4CLXPreHit> J4CLXPreHitAllocator;
typedef G4THitsCollection<J4CLXPreHit> J4CLXPreHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------

class J4CLXPreHit : public J4VHit {

public:
  J4CLXPreHit();

  J4CLXPreHit( J4VComponent*         detector,
	       G4int                 posthitID,
	       G4int                 hitID,
               const G4ThreeVector&  pre,
	       const G4ThreeVector&  momentum,
	       G4double              edep,
	       G4double              tof,
	       G4int                 trackID,
               G4ParticleDefinition* particle,
	       G4int                 motherTrackID );

  virtual ~J4CLXPreHit();
  //  inline const J4CLXPreHit& operator=( const J4CLXPreHit& right );

  inline void* operator new    ( size_t );
  inline void  operator delete ( void* aHit );

  virtual void Output( G4HCofThisEvent* HCTE );
  virtual void Draw();
  virtual void Print();

  // getters
  inline G4int         GetPostHitID()        const { return fPostHitID       ; }
  inline G4int         GetPreHitID()         const { return fPreHitID        ; }
  inline G4ThreeVector GetInjectionPoint()   const { return GetPrePosition() ; }
  
  // setters
  inline void SetPostHitID( G4int n )                { fPostHitID      = n   ; }
  inline void SetPreHitID( G4int n )                 { fPreHitID       = n   ; }
  inline void SetInjectionPoint( G4ThreeVector p )   { SetPrePosition( p )   ; }

  static void SetOutput( J4Output *output )          { fgPreOutput = output  ; } 

  //* static data member
  static J4CLXPreHitAllocator  fgPreHitAllocator;
  static J4Output             *fgPreOutput;       // Pointer to Output Module

  G4int                  fPostHitID;
  G4int                  fPreHitID;

};

//=====================================================================
//----------------------------------------
// inline function for J4CLXPreHit
//----------------------------------------

void* J4CLXPreHit::operator new( size_t )
{
  void* aHit;
  aHit = (void*)fgPreHitAllocator.MallocSingle();
  return aHit;
}

void J4CLXPreHit::operator delete( void* aHit )
{
  fgPreHitAllocator.FreeSingle( (J4CLXPreHit*)aHit );
}

#endif
