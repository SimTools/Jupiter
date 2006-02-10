// $Id$
#ifndef __J4IRBCALHIT__
#define __J4IRBCALHIT__
//*************************************************************************
//* --------------------
//* J4IRBCALHit
//* --------------------
//* (Description)
//*     Hit class for J4BCAL
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
class J4IRBCALHit;
typedef G4Allocator<J4IRBCALHit> J4IRBCALHitAllocator;
typedef G4THitsCollection<J4IRBCALHit> J4IRBCALHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------

class J4IRBCALHit : public J4VHit {

public:
  J4IRBCALHit();

  J4IRBCALHit( J4VComponent* ptrDetector,
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
  
  virtual ~J4IRBCALHit();

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

  static J4IRBCALHitAllocator  fgHitAllocator;
  static J4Output*          fgOutput;       // Pointer to Output Module
  
private:
  G4int           fPreHitID;
  G4int           fCellID;
  G4ThreeVector   fXcm;
  G4ThreeVector   fXcell;
};

//----------------------------------------
// Allocator

void* J4IRBCALHit::operator new( size_t )
{
  void* aHit;
  aHit = (void*)fgHitAllocator.MallocSingle();
  return aHit;
}

void J4IRBCALHit::operator delete( void* aHit )
{
  fgHitAllocator.FreeSingle((J4IRBCALHit*) aHit);
}

#endif
