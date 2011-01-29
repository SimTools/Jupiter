#ifndef __J4CALPOSTHIT__
#define __J4CALPOSTHIT__
//*************************************************************************
//* --------------------
//* J4CALPostHit
//* --------------------
//* (Description)
//*     Hit class for J4TPCLayer 	
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************
#include "J4VHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"

//=========================================================================
// TypeDef
class J4CALPostHit;
class J4CALPreHit;
typedef G4Allocator<J4CALPostHit> J4CALPostHitAllocator;
typedef G4THitsCollection<J4CALPostHit> J4CALPostHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
//class J4CALPostHit : public J4VTrackerHit {
class J4CALPostHit : public J4VHit {

public:
  J4CALPostHit();
  J4CALPostHit( J4VComponent         *detector,
                G4int                 preHitID      = 0,
                G4int                 trackID       = 0,
                G4int                 mothertrackID = 0,
                G4ParticleDefinition *particle      = 0,
                G4double              tof           = 0,
                G4double              totalE        = 0,
                const G4ThreeVector  &momentum      = G4ThreeVector(0.),
                const G4ThreeVector  &post          = G4ThreeVector(0.));	
  	 	            
  J4CALPostHit( const J4CALPostHit& right );
  
  virtual ~J4CALPostHit();
  
  const J4CALPostHit& operator=( const J4CALPostHit& right );
  void* operator new    ( size_t     );
  void  operator delete ( void* aHit );

  virtual void Output( G4HCofThisEvent* HCTE );
  static  void SetCurPostHitPtr( J4CALPostHit *hitp = 0 ) { fgCurPostHitPtr = hitp; }
  static  J4CALPostHit* GetCurPostHitPtr()   { return fgCurPostHitPtr; }
  //inline  virtual G4int GetPostHitID() const { return fCALPostHitID;      } 
  //inline        G4int GetPostHitID() const { return fCALPostHitID;      } 
  inline        G4int GetPostHitID()    { return fCALPostHitID;      } 
  static        G4int GetCurPostHitID() { return fgNhits;         }
  static  void SetOutput( J4Output *output ) { fgOutput = output;      }
  virtual void Draw();
  virtual void Print();
    
  //inline  G4int GetCALPreHitID() const { return fCALPreHitID; }
  inline  G4int GetCALPreHitID() { return fCALPreHitID; }
  inline  void  SetCALPreHitID( G4int i ) { fCALPreHitID = i; }
  inline  J4CALPreHit* GetCALPreHitPtr() { return fCALPreHitPtr; }
  inline  void  SetCALPreHitPtr( J4CALPreHit* p ) { fCALPreHitPtr = p; }

private: 
  static J4CALPostHitAllocator  fgHitAllocator;
  static J4Output              *fgOutput;       // Pointer to Output Module
  static G4int                  fgNhits;
  static J4CALPostHit          *fgCurPostHitPtr;
         G4int                  fCALPostHitID; 
         G4int                  fCALPreHitID;  // data members of the preitID
         J4CALPreHit*           fCALPreHitPtr; // Pointer to the CALPreHit
};

//=====================================================================
//----------------------------------------
// inline function for J4CALPostHit
//----------------------------------------
inline J4CALPostHit::J4CALPostHit()
{
  fCALPostHitID = ++fgNhits;
}

inline J4CALPostHit::J4CALPostHit(const J4CALPostHit& right) 
: J4VHit(right)
//: J4VTrackerHit(right)
{
  fCALPostHitID = ++fgNhits;
}

inline const J4CALPostHit& J4CALPostHit::operator= (const J4CALPostHit& right)
{         
  //J4VTrackerHit::operator=(right);
  J4VHit::operator=(right);
  return *this;
}
  
//----------------------------------------
// Allocator
inline void* J4CALPostHit::operator new(size_t)
{
  void* aHit;
  aHit= (void*)fgHitAllocator.MallocSingle();
  return aHit;
}

inline void J4CALPostHit::operator delete(void* aHit)
{
  fgHitAllocator.FreeSingle((J4CALPostHit*) aHit);
}

#endif
