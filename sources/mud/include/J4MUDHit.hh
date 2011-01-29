// $Id$
#ifndef __J4MUDHIT__
#define __J4MUDHIT__
//*************************************************************************
//* --------------------
//* J4MUDHit
//* --------------------
//* (Description)
//*     Hit class for J4MUD 	
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************
#include "J4VComponent.hh"
#include "J4VTrackerHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"

//=========================================================================
// TypeDef
class   J4MUDHit;
typedef G4Allocator<J4MUDHit> J4MUDHitAllocator;
typedef G4THitsCollection<J4MUDHit> J4MUDHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
//class J4MUDHit : public J4VTrackerHit {
class J4MUDHit : public J4VHit {

public:
  J4MUDHit();
  J4MUDHit( J4VComponent*         detector,
            G4int                 blockID       = 0,
            G4int                 layerID       = 0,
            G4bool                isBarrel      = 0,
            G4bool                isFront       = 0,
	    G4int                 preHitID      = 0,
            G4int                 trackID       = 0,
            G4int                 mothertrackID = 0,
            G4ParticleDefinition* particle      = 0,
            G4double              tof           = 0,
            G4double              edep          = 0,
            G4double              totalE        = 0,
            const G4ThreeVector & momentum      = G4ThreeVector(0.),
            const G4ThreeVector & pre           = G4ThreeVector(0.),
            const G4ThreeVector & post          = G4ThreeVector(0.) );
  	 	            
  //J4MUDHit( const J4MUDHit& right );
  
  virtual ~J4MUDHit();
  
  const J4MUDHit& operator=( const J4MUDHit& right );    
          
  void* operator new    ( size_t     );
  void  operator delete ( void* aHit );

  virtual void Output( G4HCofThisEvent* HCTE );
  virtual void Draw();
  virtual void Print();
  static  void SetOutput( J4Output *output ) { fgOutput = output; } 

//private: 
public:
  static J4MUDHitAllocator fgHitAllocator;
  static J4Output*         fgOutput;       // Pointer to Output Module

// Setter/Getter
  inline G4int  GetBlockID()  const   { return fBlockID;  }
  inline G4int  GetLayerID()  const   { return fLayerID;  }
  inline G4bool GetIsBarrel() const   { return fIsBarrel; }
  inline G4bool GetIsFront()  const   { return fIsFront;  }
  inline G4int  GetPreHitID() const   { return fPreHitID; }
  
  inline void SetBlockID( G4int i )   { fBlockID  = i; }
  inline void SetLayerID( G4int i )   { fLayerID  = i; }
  inline void SetIsBarrel( G4bool b ) { fIsBarrel = b; }
  inline void SetIsFront( G4bool b )  { fIsFront  = b; }

  //inline void AddEdep( G4double e )   { fEdep += e;    }

private:
  G4int    fBlockID; 
  G4int    fLayerID;
  G4bool   fIsBarrel;
  G4bool   fIsFront;
  G4int    fPreHitID;
  G4double fEdep;

};
  
//----------------------------------------
// Allocator
inline void* J4MUDHit::operator new( size_t )
{
  void* aHit;
  aHit= (void*)fgHitAllocator.MallocSingle();
  return aHit;
}

inline void J4MUDHit::operator delete( void* aHit )
{
  fgHitAllocator.FreeSingle((J4MUDHit*) aHit);
}

#endif
