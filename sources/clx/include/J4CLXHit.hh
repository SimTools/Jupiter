// $Id$
#ifndef __J4CLXHIT__
#define __J4CLXHIT__
//*************************************************************************
//* --------------------
//* J4CLXHit
//* --------------------
//* (Description)
//*     Hit class for J4CLX
//*	Mother class : G4VHit
//*
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*     2004/08/30  Ono Hiroaki  Add J4CLXHitlet class inside of J4CLXHit
//*     2004/10/12  A.Sanchez   Make J4CLXHit behave as hitlet.
//*                             No more J4CLXHit::J4CLXHitlet class.
//*     2004/11/01  Allister Sanchez  Remove redundant data/functions which are in J4VHit.
//*************************************************************************
#include "J4VHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"

//=========================================================================
// TypeDef
class J4CLXHit;
typedef G4Allocator<J4CLXHit> J4CLXHitAllocator;
typedef G4THitsCollection<J4CLXHit> J4CLXHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------

class J4CLXHit : public J4VHit {

public:
  J4CLXHit();

  J4CLXHit( J4VComponent* ptrDetector,
	    G4int         preHitID,
	    G4int         layerID,
	    G4int         cellID,
	    G4bool        isEM,
	    const G4ThreeVector& cellPosition,
            G4double      edep,
            G4double      tof,
	    G4ParticleDefinition *particle,
	    const G4ThreeVector& xcm);

  virtual ~J4CLXHit();

  inline void* operator new    ( size_t );
  inline void  operator delete ( void* aHit );

  virtual void Output( G4HCofThisEvent* HCTE );
  virtual void Draw();
  virtual void Print();

  // getter/setter
    inline G4int         GetPreHitID() const {return fPreHitID;}
    inline G4int         GetLayerID()  const {return fLayerID;}
    inline G4int         GetCellID() const { return fCellID; }
    inline G4bool        IsEM()      const {return fIsEM;}
    inline G4ThreeVector GetCellPosition() const { return fCellPosition;}
    inline G4ThreeVector GetXcm()      const { return fXcm;      } // note: this returns energy * position vector
//    inline G4double      GetEdep()     const { return fEdep;     } // J4VHit::GetEnergyDeposit
//    inline G4double      GetTof()      const { return fTof;      } // J4VHit::GetTof

    inline void SetPreHitID(G4int id) {fPreHitID = id;}
    inline void SetLayerID(G4int id) {fLayerID = id;}
  inline void SetCellID( G4int id )    { fCellID = id;}
    inline void SetIsEM(G4bool b) {fIsEM = b;}
    inline void SetCellPotision(G4ThreeVector v) {fCellPosition = v;}
  inline void SetXcm( G4ThreeVector v )  { fXcm      = v; }
  inline void AddXcm( G4ThreeVector v )  { fXcm += v;  } // note: v should be edep*position vector
//  inline void SetEdep( G4double x )      { fEdep     = x; } // J4VHit::SetEnergyDeposit
//  inline void SetTof( G4double x )       { fTof      = x; } // J4VHit::SetTof
//  inline void AddEdep( G4double ed )     { fEdep += ed; } //J4VHit::AddEdep

  static void SetOutput( J4Output* output )    { fgOutput = output; } 

  static J4CLXHitAllocator  fgHitAllocator;
  static J4Output*          fgOutput;       // Pointer to Output Module
  
private:
    G4int           fPreHitID;
    G4int           fLayerID;
    G4int           fCellID;
    G4bool          fIsEM;
    G4ThreeVector   fCellPosition;
  G4ThreeVector   fXcm;
  // The following data are available from J4VHit
  //G4int           fPDGCode;
  //G4double        fEdep;
  //G4double        fTof;
};

//----------------------------------------
// Allocator

void* J4CLXHit::operator new( size_t )
{
  void* aHit;
  aHit = (void*)fgHitAllocator.MallocSingle();
  return aHit;
}

void J4CLXHit::operator delete( void* aHit )
{
  fgHitAllocator.FreeSingle((J4CLXHit*) aHit);
}

#endif
