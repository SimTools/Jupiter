// $Id$
#ifndef __J4MUDBARRELHIT__
#define __J4MUDBARRELHIT__
//*************************************************************************
//* --------------------
//* J4MUDBarrelHit
//* --------------------
//* (Description)
//*     Hit class for J4MUDBarrel 	
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************
#include "J4VTrackerHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"

//=========================================================================
// TypeDef
class J4MUDBarrelHit;
typedef G4Allocator<J4MUDBarrelHit> J4MUDBarrelHitAllocator;
typedef G4THitsCollection<J4MUDBarrelHit> J4MUDBarrelHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
class J4MUDBarrelHit : public J4VTrackerHit {

public:
  J4MUDBarrelHit();
  J4MUDBarrelHit( J4VComponent*         detector,
                 G4int                 trackID       = 0,
                 G4int                 mothertrackID = 0,
                 G4ParticleDefinition* particle      = 0,
                 G4double              tof           = 0,
                 G4double              edep          = 0,
                 G4double              totalE        = 0,
                 const G4ThreeVector & momentum      = 0,
                 const G4ThreeVector & pre           = 0,
                 const G4ThreeVector & pos           = 0  );	
  	 	            
  J4MUDBarrelHit( const J4MUDBarrelHit& right );
  
  virtual ~J4MUDBarrelHit();
  
  const J4MUDBarrelHit& operator=( const J4MUDBarrelHit& right );    
          
  void* operator new    ( size_t     );
  void  operator delete ( void* aHit );

  virtual void Output( G4HCofThisEvent* HCTE );
  virtual void Draw();
  virtual void Print();
  static  void SetOutput( J4Output *output ) { fOutput = output; } 
    
private: 

  static J4MUDBarrelHitAllocator fHitAllocator;
  static J4Output              *fOutput;       // Pointer to Output Module
  
};

//=====================================================================
//----------------------------------------
// inline function for J4MUDBarrelHit
//----------------------------------------
#if 0
inline J4MUDBarrelHit::J4MUDBarrelHit(const J4MUDBarrelHit& right) { }

inline const J4MUDBarrelHit& J4MUDBarrelHit::operator= (const J4MUDBarrelHit& right)
{         
  return *this;
}
#endif
  
//----------------------------------------
// Allocator

inline void* J4MUDBarrelHit::operator new( size_t )
{
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J4MUDBarrelHit::operator delete( void* aHit )
{
  fHitAllocator.FreeSingle((J4MUDBarrelHit*) aHit);
}

#endif

