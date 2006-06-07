// $Id$
#ifndef __J4OptDetSD__
#define __J4OptDetSD__
//*************************************************************************
//* --------------------
//* J4OptDetSD
//* --------------------
//* (Description)
//* 	Sensitive detector class for FCAL
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2006/01/27 A.Miyamoto Original version.
//*************************************************************************
#include "J4VSD.hh"
#include "J4OptDetHit.hh"
#include "J4OptDet.hh"
#include <map>

//=====================================================================
//---------------------
// class definition
//---------------------
class J4OptDetSD : public J4VSD<J4OptDetHit>{
  
public:

  J4OptDetSD( J4OptDet* detector );
  ~J4OptDetSD();

  virtual G4bool ProcessHits( G4Step* aStep, G4TouchableHistory* ROhist );
  virtual void   Initialize ( G4HCofThisEvent* PreHCTE );
  virtual void   EndOfEvent ( G4HCofThisEvent* PreHCTE );

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll( G4HCofThisEvent* PreHCTE )
  {
    if ( GetHitBuf() )
    {
      J4VSD<J4OptDetHit>::OutputAll( PreHCTE );
    }
    else
    {
      G4cerr << "J4OptDetSD::OutputAll: No HitBuf! " << G4endl;
    }
  }

  inline virtual const J4OptDetSD& operator=( const J4VSD<J4OptDetHit> &right )
  {
    J4VSD<J4OptDetHit>::operator=( right );
    return *this;
  }

  inline G4int GetOptDetID(){ return fOptDetID;}
  inline G4int GetOptDetSerialID(){ return fOptDetSerialID; }

 private:
  static G4int fNumberOfOptDet;
  static G4int fHitNumber;
  G4int fOptDetID;
  G4int fOptDetSerialID;
};

#endif
