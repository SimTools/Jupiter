// $Id$
#ifndef __J4CLXHIT__
#define __J4CLXHIT__
//*************************************************************************
//* --------------------
//* J4CLXHit
//* --------------------
//* (Description)
//*     Hit class for J4CLX
//*	Mother class : G4VHit
//*
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*     2004/08/30  Ono Hiroaki  Add J4CLXHitlet class inside of J4CLXHit
//*     2004/10/12  A.Sanchez   Make J4CLXHit behave as hitlet.
//*                             No more J4CLXHit::J4CLXHitlet class.
//*     2004/11/01  Allister Sanchez  Remove redundant data/functions which are in J4VHit.
//*************************************************************************
#include "J4VHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"

//=========================================================================
// TypeDef
class J4CLXHit;
typedef G4Allocator<J4CLXHit> J4CLXHitAllocator;
typedef G4THitsCollection<J4CLXHit> J4CLXHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------

class J4CLXHit : public J4VHit {

public:
  J4CLXHit();

  J4CLXHit( J4VComponent* ptrDetector,
	    G4int         preHitID,
	    G4int         globalID,
	    G4bool        isEM,
	    G4bool        isBarrel,
            G4double      edep,
            G4double      tof,
	    G4ParticleDefinition *particle,
	    const G4ThreeVector& xcm,
	    const G4ThreeVector& xcell,
	    G4int         trackID = -9999,
	    G4int         motherTrackID = -9999 );

  virtual ~J4CLXHit();

  inline void* operator new    ( size_t );
  inline void  operator delete ( void* aHit );

  virtual void Output( G4HCofThisEvent* HCTE );
  virtual void Draw();
  virtual void Print();

  // getter/setter
  inline G4int         GetPreHitID() const { return fPreHitID ; }
  inline G4int         GetCellID()   const { return fCellID   ; }
  inline G4bool        IsEM()        const { return fIsEM     ; }
  inline G4bool        IsBarrel()    const { return fIsBarrel ; }
  inline G4ThreeVector GetXcm()      const { return fXcm      ; } // note: this returns energy * position vector
  inline G4ThreeVector GetXcell()    const { return fXcell    ; } // Center of cell position

  inline void SetPreHitID ( G4int id )  { fPreHitID = id ; }
  inline void SetCellID   ( G4int id )  { fCellID   = id ; }
  inline void SetIsEM     ( G4bool b )  { fIsEM     = b  ; }
  inline void SetIsBarrel ( G4bool b )  { fIsBarrel = b  ; }
  inline void SetXcm( G4ThreeVector v ) { fXcm      = v  ; }
  inline void AddXcm( G4ThreeVector v ) { fXcm     += v  ; } // note: v should be edep*position vector
  inline void SetXcell( G4ThreeVector v ) { fXcell = v ; }   // Center of cell position

  static void SetOutput( J4Output* output )    { fgOutput = output; } 

  static J4CLXHitAllocator  fgHitAllocator;
  static J4Output*          fgOutput;       // Pointer to Output Module
  
private:
  G4int           fPreHitID;
  G4int           fCellID;
  G4bool          fIsEM;
  G4bool          fIsBarrel;
  G4ThreeVector   fXcm;
  G4ThreeVector   fXcell;
};

//----------------------------------------
// Allocator

void* J4CLXHit::operator new( size_t )
{
  void* aHit;
  aHit = (void*)fgHitAllocator.MallocSingle();
  return aHit;
}

void J4CLXHit::operator delete( void* aHit )
{
  fgHitAllocator.FreeSingle((J4CLXHit*) aHit);
}

#endif
