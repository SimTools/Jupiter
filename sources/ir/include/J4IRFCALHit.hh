// $Id$
#ifndef __J4IRFCALHIT__
#define __J4IRFCALHIT__
//*************************************************************************
//* --------------------
//* J4IRFCALHit
//* --------------------
//* (Description)
//*     Hit class for J4FCAL
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*   2006/01/28 A.Miyamoto  Original version, modified from J4CALHit
//*************************************************************************
#include "J4VHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"

//=========================================================================
// TypeDef
class J4IRFCALHit;
typedef G4Allocator<J4IRFCALHit> J4IRFCALHitAllocator;
typedef G4THitsCollection<J4IRFCALHit> J4IRFCALHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------

class J4IRFCALHit : public J4VHit {

public:
  J4IRFCALHit();

  J4IRFCALHit( J4VComponent* ptrDetector,
	       G4int         preHitID,
	    //G4int         pdgCode,
	    G4int         cellID,
            G4double      edep,
            G4double      tof,
	    G4ParticleDefinition *particle,
	    const G4ThreeVector& xcm,
	    const G4ThreeVector& xcell,
	    G4int         trackID=-9999,
	    G4int         motherTrackID=-9999 );
  
  virtual ~J4IRFCALHit();

  inline void* operator new    ( size_t );
  inline void  operator delete ( void* aHit );

  virtual void Output( G4HCofThisEvent* HCTE );
  virtual void Draw();
  virtual void Print();

  // getter/setter
         
  inline G4int         GetPreHitID()   const { return fPreHitID;   }   
  inline G4int         GetCellID()   const { return fCellID;   }   
  inline G4ThreeVector GetXcell()    const { return fXcell;    }
  inline G4ThreeVector GetXcm()      const { return fXcm;      }
 // note: this returns energy * position vector

  inline void SetPrehitID(G4int id)      { fPreHitID = id; }
  inline void SetCellID( G4int id )      { fCellID   = id;}
  inline void SetXcm( G4ThreeVector v )  { fXcm      = v; }
  inline void SetXcell( G4ThreeVector v ){ fXcell    = v; }
  inline void AddXcm( G4ThreeVector v )  { fXcm += v;  } 

  static void SetOutput( J4Output* output )    { fgOutput = output; } 

  static J4IRFCALHitAllocator  fgHitAllocator;
  static J4Output*          fgOutput;       // Pointer to Output Module
  
private:
  G4int           fPreHitID;
  G4int           fCellID;
  G4ThreeVector   fXcm;
  G4ThreeVector   fXcell;
};

//----------------------------------------
// Allocator

void* J4IRFCALHit::operator new( size_t )
{
  void* aHit;
  aHit = (void*)fgHitAllocator.MallocSingle();
  return aHit;
}

void J4IRFCALHit::operator delete( void* aHit )
{
  fgHitAllocator.FreeSingle((J4IRFCALHit*) aHit);
}

#endif
