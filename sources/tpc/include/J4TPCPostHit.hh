#ifndef __J4TPCPOSTHIT__
#define __J4TPCPOSTHIT__
//*************************************************************************
//* --------------------
//* J4TPCPostHit
//* --------------------
//* (Description)
//*     Hit class for J4TPCLayer 	
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

class J4TPCPostHit;
typedef G4Allocator<J4TPCPostHit> J4TPCPostHitAllocator;
typedef G4THitsCollection<J4TPCPostHit> J4TPCPostHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
 

class J4TPCPostHit : public J4VTrackerHit {

public:
  J4TPCPostHit();
  J4TPCPostHit(J4VComponent              *detector,
                    G4int                 trackID       = 0,
                    G4int                 mothertrackID = 0,
                    G4ParticleDefinition *particle      = 0,
                    G4double              tof           = 0,
                    G4double              totalE        = 0,
                    const G4ThreeVector  &momentum      = G4ThreeVector(0.),
                    const G4ThreeVector  &pos           = G4ThreeVector(0.));	
  	 	            
  J4TPCPostHit(const J4TPCPostHit& right);
  
  virtual ~J4TPCPostHit();
  
  const J4TPCPostHit& 
          operator=(const J4TPCPostHit& right);    
#if 0
  void* operator new    (size_t    );
  void  operator delete (void* aHit);
#endif

  virtual void Output(G4HCofThisEvent* HCTE);
  static  void SetCurPostHitPtr(J4TPCPostHit *hitp = 0) { fgCurPostHitPtr = hitp; }
  static  J4TPCPostHit *GetCurPostHitPtr()   { return fgCurPostHitPtr; }
  inline  virtual G4int GetPostHitID() const { return fPostHitID;      } 
  static          G4int GetCurPostHitID()    { return fgNhits;         }
  static  void SetOutput(J4Output *output)   { fgOutput = output;      }
  virtual void Draw();
  virtual void Print();
    
private: 

  static J4TPCPostHitAllocator  fgHitAllocator;
  static J4Output              *fgOutput;       // Pointer to Output Module
  static G4int                  fgNhits;
  static J4TPCPostHit          *fgCurPostHitPtr;
         G4int                  fPostHitID; 
};

//=====================================================================
//----------------------------------------
// inline function for J4TPCPostHit
//----------------------------------------

inline J4TPCPostHit::J4TPCPostHit()
{
  fPostHitID = ++fgNhits;
}

inline J4TPCPostHit::J4TPCPostHit(const J4TPCPostHit& right) 
     : J4VTrackerHit(right)
{
  fPostHitID = ++fgNhits;
}

inline const J4TPCPostHit& 
  J4TPCPostHit::operator= (const J4TPCPostHit& right)
{         
  J4VTrackerHit::operator=(right);
  return *this;
}
 
#if 0
//----------------------------------------
// Allocator

inline void* J4TPCPostHit::operator new(size_t)
{
  
  void* aHit;
  aHit= (void*)fgHitAllocator.MallocSingle();
  return aHit;
}

inline void J4TPCPostHit::operator delete(void* aHit)
{
  fgHitAllocator.FreeSingle((J4TPCPostHit*) aHit);
}
#endif
#endif

