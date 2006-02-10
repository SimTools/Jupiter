#ifndef __J4CLXPOSTHIT__
#define __J4CLXPOSTHIT__
//*************************************************************************
//* --------------------
//* J4CLXPostHit
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
class J4CLXPostHit;
class J4CLXPreHit;
typedef G4Allocator<J4CLXPostHit> J4CLXPostHitAllocator;
typedef G4THitsCollection<J4CLXPostHit> J4CLXPostHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------
//class J4CLXPostHit : public J4VTrackerHit {
class J4CLXPostHit : public J4VHit {

public:
  J4CLXPostHit();
  J4CLXPostHit( J4VComponent         *detector,
                G4int                 preHitID      = 0,
                G4int                 trackID       = 0,
                G4int                 mothertrackID = 0,
                G4ParticleDefinition *particle      = 0,
                G4double              tof           = 0,
                G4double              totalE        = 0,
                const G4ThreeVector  &momentum      = 0,
                const G4ThreeVector  &post          = 0);	
  	 	            
  J4CLXPostHit( const J4CLXPostHit& right );
  
  virtual ~J4CLXPostHit();
  
  const J4CLXPostHit& operator=( const J4CLXPostHit& right );
  void* operator new    ( size_t     );
  void  operator delete ( void* aHit );

  virtual void Output( G4HCofThisEvent* HCTE );
  static  void SetCurPostHitPtr( J4CLXPostHit *hitp = 0 ) { fgCurPostHitPtr = hitp; }
  static  J4CLXPostHit* GetCurPostHitPtr()   { return fgCurPostHitPtr; }
  //inline  virtual G4int GetPostHitID() const { return fCLXPostHitID;      } 
  //inline        G4int GetPostHitID() const { return fCLXPostHitID;      } 
  inline        G4int GetPostHitID()    { return fCLXPostHitID;      } 
  static        G4int GetCurPostHitID() { return fgNhits;         }
  static  void SetOutput( J4Output *output ) { fgOutput = output;      }
  virtual void Draw();
  virtual void Print();
    
  //inline  G4int GetCLXPreHitID() const { return fCLXPreHitID; }
  inline  G4int GetCLXPreHitID() { return fCLXPreHitID; }
  inline  void  SetCLXPreHitID( G4int i ) { fCLXPreHitID = i; }
  inline  J4CLXPreHit* GetCLXPreHitPtr() { return fCLXPreHitPtr; }
  inline  void  SetCLXPreHitPtr( J4CLXPreHit* p ) { fCLXPreHitPtr = p; }

private: 
  static J4CLXPostHitAllocator  fgHitAllocator;
  static J4Output              *fgOutput;       // Pointer to Output Module
  static G4int                  fgNhits;
  static J4CLXPostHit          *fgCurPostHitPtr;
         G4int                  fCLXPostHitID; 
         G4int                  fCLXPreHitID;  // data members of the preitID
         J4CLXPreHit*           fCLXPreHitPtr; // Pointer to the CLXPreHit
};

//=====================================================================
//----------------------------------------
// inline function for J4CLXPostHit
//----------------------------------------
inline J4CLXPostHit::J4CLXPostHit()
{
  fCLXPostHitID = ++fgNhits;
}

inline J4CLXPostHit::J4CLXPostHit(const J4CLXPostHit& right) 
: J4VHit(right)
//: J4VTrackerHit(right)
{
  fCLXPostHitID = ++fgNhits;
}

inline const J4CLXPostHit& J4CLXPostHit::operator= (const J4CLXPostHit& right)
{         
  //J4VTrackerHit::operator=(right);
  J4VHit::operator=(right);
  return *this;
}
  
//----------------------------------------
// Allocator
inline void* J4CLXPostHit::operator new(size_t)
{
  void* aHit;
  aHit= (void*)fgHitAllocator.MallocSingle();
  return aHit;
}

inline void J4CLXPostHit::operator delete(void* aHit)
{
  fgHitAllocator.FreeSingle((J4CLXPostHit*) aHit);
}

#endif
