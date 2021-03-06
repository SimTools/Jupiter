// $Id$
#ifndef __J4CALHIT__
#define __J4CALHIT__
//*************************************************************************
//* --------------------
//* J4CALHit
//* --------------------
//* (Description)
//*     Hit class for J4CAL 	
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*     2004/08/30  Ono Hiroaki  Add J4CALHitlet class inside of J4CALHit
//*     2004/10/12  A.Sanchez   Make J4CALHit behave as hitlet.
//*                             No more J4CALHit::J4CALHitlet class.
//*     2004/11/01  Allister Sanchez  Remove redundant data/functions which are in J4VHit.
//*************************************************************************
#include "J4VHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"

//=========================================================================
// TypeDef
class J4CALHit;
typedef G4Allocator<J4CALHit> J4CALHitAllocator;
typedef G4THitsCollection<J4CALHit> J4CALHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------

class J4CALHit : public J4VHit {

public:
  J4CALHit();

  J4CALHit( J4VComponent* ptrDetector,
	    G4int         preHitID,
	    //G4int         pdgCode,
	    G4int         cellID,
	    G4bool        isEM,
            G4bool        isBarrel,
            G4double      edep,
            G4double      tof,
	    G4ParticleDefinition *particle,
	    const G4ThreeVector& xcm,
	    const G4ThreeVector& xcell,
	    G4int         trackID=-9999,
	    G4int         motherTrackID=-9999 );
  
  virtual ~J4CALHit();

  inline void* operator new    ( size_t );
  inline void  operator delete ( void* aHit );

  virtual void Output( G4HCofThisEvent* HCTE );
  virtual void Draw();
  virtual void Print();

  // getter/setter
         
  inline G4int         GetPreHitID() const { return fPreHitID; }
  inline G4int         GetCellID()   const { return fCellID;   }   
  inline G4bool        IsEM()        const { return fIsEM;     }
  inline G4bool        IsBarrel()    const { return fIsBarrel; }
  inline G4ThreeVector GetXcell()    const { return fXcell;    }
  inline G4ThreeVector GetXcm()      const { return fXcm;      } // note: this returns energy * position vector
  //inline G4int         GetPDGCode()  const { return fPDGCode; }  // J4VHit::GetPDGEncoding
  //inline G4double      GetEdep()     const { return fEdep;     } // J4VHit::GetEnergyDeposit
  //inline G4double      GetTof()      const { return fTof;      } // J4VHit::GetTof
 
  inline void SetPreHitID( G4int id )    { fPreHitID = id;}
  inline void SetCellID( G4int id )      { fCellID   = id;}
  inline void SetEM( G4bool  b )         { fIsEM     = b; }
  inline void SetBarrel( G4bool  b )     { fIsBarrel = b; }
  inline void SetXcm( G4ThreeVector v )  { fXcm      = v; }
  inline void SetXcell( G4ThreeVector v ){ fXcell    = v; }
  inline void AddXcm( G4ThreeVector v )  { fXcm += v;  } // note: v should be edep*position vector
  //inline void SetPDGCode( G4int id )     { fPDGCode  = id;} // J4VHit::SetParticle
  //inline void SetEdep( G4double x )      { fEdep     = x; } // J4VHit::SetEnergyDeposit
  //inline void SetTof( G4double x )       { fTof      = x; } // J4VHit::SetTof
  //inline void AddEdep( G4double ed )     { fEdep += ed; } //J4VHit::AddEdep

  static void SetOutput( J4Output* output )    { fgOutput = output; } 

  static J4CALHitAllocator  fgHitAllocator;
  static J4Output*          fgOutput;       // Pointer to Output Module
  
private:
  G4int           fPreHitID;
  G4int           fCellID;
  G4bool          fIsEM;
  G4bool          fIsBarrel;
  G4ThreeVector   fXcm;
  G4ThreeVector   fXcell;
  // The following data are available from J4VHit
  //G4int           fPDGCode;
  //G4double        fEdep;
  //G4double        fTof;
};

//----------------------------------------
// Allocator

void* J4CALHit::operator new( size_t )
{
  void* aHit;
  aHit = (void*)fgHitAllocator.MallocSingle();
  return aHit;
}

void J4CALHit::operator delete( void* aHit )
{
  fgHitAllocator.FreeSingle((J4CALHit*) aHit);
}

#endif
