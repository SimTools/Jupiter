// $Id$
#ifndef __J4OptDetHit__
#define __J4OptDetHit__
//*************************************************************************
//* --------------------
//* J4OptDetHit
//* --------------------
//* (Description)
//*     Hit class for J4OptDet
//*     
//* (Update Record)
//*   2006/06/04 A.Miyamoto  Original version
//*************************************************************************
#include "J4VHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"

//=========================================================================
// TypeDef
class J4OptDetHit;
typedef G4Allocator<J4OptDetHit> J4OptDetHitAllocator;
typedef G4THitsCollection<J4OptDetHit> J4OptDetHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------

class J4OptDetHit : public J4VHit {

public:
  J4OptDetHit();

  J4OptDetHit(J4VComponent         *detector,      // Belonging Component 
	       G4int                 detid,         // detector ID
	       G4int                 serialdetid,   // serialdetector ID ( unique in all )
               G4int                 trackID,	    // TrackID
               G4int                 mothertrackID, // MotherTrackID
               G4ParticleDefinition *particle,	    // particle
               G4double              tof,           // TOF 
               G4double              edep,          // Energy Deposit
               G4double              totalE,        // Total energy
               const G4ThreeVector  &p,             // Momentum of perticle
               const G4ThreeVector  &pre,           // Pre-position of track
               const G4ThreeVector  &pos,           // Post-position of track
	   G4int                 hitnumber);

  
  virtual ~J4OptDetHit();

  inline void* operator new    ( size_t );
  inline void  operator delete ( void* aHit );

  virtual void Output( G4HCofThisEvent* HCTE );
  virtual void Draw();
  virtual void Print();

  // getter/setter
         
  static void SetOutput( J4Output* output )    { fgOutput = output; } 

  static J4OptDetHitAllocator  fgHitAllocator;
  static J4Output*          fgOutput;       // Pointer to Output Module

  inline G4int GetDetID(){ return fDetID;}
  inline G4int GetDetSerialID(){ return fDetSerialID;}
  void SetDetID(G4int id){ fDetID=id; }
  void SetDetSerialID(G4int id){ fDetSerialID=id; }

private:
  G4int  fDetID;
  G4int  fDetSerialID;
};

//----------------------------------------
// Allocator

void* J4OptDetHit::operator new( size_t )
{
  void* aHit;
  aHit = (void*)fgHitAllocator.MallocSingle();
  return aHit;
}

void J4OptDetHit::operator delete( void* aHit )
{
  fgHitAllocator.FreeSingle((J4OptDetHit*) aHit);
}

#endif
