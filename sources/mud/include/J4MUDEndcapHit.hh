// $Id$
#ifndef __J4MUDENDCAPHIT__
#define __J4MUDENDCAPHIT__
//*************************************************************************
//* --------------------
//* J4MUDEndcapHit
//* --------------------
//* (Description)
//*     Hit class for J4MUDEndcap 	
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
class J4MUDEndcapHit;
typedef G4Allocator<J4MUDEndcapHit> J4MUDEndcapHitAllocator;
typedef G4THitsCollection<J4MUDEndcapHit> J4MUDEndcapHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
class J4MUDEndcapHit : public J4VTrackerHit {

public:
  J4MUDEndcapHit();
  J4MUDEndcapHit( J4VComponent*         detector,
                 G4int                 trackID       = 0,
                 G4int                 mothertrackID = 0,
                 G4ParticleDefinition* particle      = 0,
                 G4double              tof           = 0,
                 G4double              edep          = 0,
                 G4double              totalE        = 0,
                 const G4ThreeVector & momentum      = 0,
                 const G4ThreeVector & pre           = 0,
                 const G4ThreeVector & pos           = 0  );	
  	 	            
  J4MUDEndcapHit( const J4MUDEndcapHit& right );
  
  virtual ~J4MUDEndcapHit();
  
  const J4MUDEndcapHit& operator=( const J4MUDEndcapHit& right );    
          
  void* operator new    ( size_t     );
  void  operator delete ( void* aHit );

  virtual void Output( G4HCofThisEvent* HCTE );
  virtual void Draw();
  virtual void Print();
  static  void SetOutput( J4Output *output ) { fOutput = output; } 
    
private: 

  static J4MUDEndcapHitAllocator fHitAllocator;
  static J4Output              *fOutput;       // Pointer to Output Module
  
};

//=====================================================================
//----------------------------------------
// inline function for J4MUDEndcapHit
//----------------------------------------
#if 0
inline J4MUDEndcapHit::J4MUDEndcapHit(const J4MUDEndcapHit& right) { }

inline const J4MUDEndcapHit& J4MUDEndcapHit::operator= (const J4MUDEndcapHit& right)
{         
  return *this;
}
#endif
  
//----------------------------------------
// Allocator

inline void* J4MUDEndcapHit::operator new( size_t )
{
  void* aHit;
  aHit= (void*)fHitAllocator.MallocSingle();
  return aHit;
}

inline void J4MUDEndcapHit::operator delete( void* aHit )
{
  fHitAllocator.FreeSingle((J4MUDEndcapHit*) aHit);
}

#endif

