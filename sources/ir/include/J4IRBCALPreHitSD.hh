// $Id$
#ifndef __J4IRBCALPreHitSD__
#define __J4IRBCALPreHitSD__
//*************************************************************************
//* --------------------
//* J4IRBCALPreHitSD
//* --------------------
//* (Description)
//* 	Sensitive detector class for FCAL
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2006/01/27 A.Miyamoto Original version.
//*************************************************************************
#include "J4VSD.hh"
#include "J4IRBCALPreHit.hh"
#include "J4IRBCAL.hh"

#include <map>

//=====================================================================
//---------------------
// class definition
//---------------------
class J4IRBCALPreHitSD : public J4VSD<J4IRBCALPreHit>{
  
public:

  J4IRBCALPreHitSD( J4IRBCAL* detector );
  ~J4IRBCALPreHitSD();

  virtual G4bool ProcessHits( G4Step* aStep, G4TouchableHistory* ROhist );
  virtual void   Initialize ( G4HCofThisEvent* PreHCTE );
  virtual void   EndOfEvent ( G4HCofThisEvent* PreHCTE );

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll( G4HCofThisEvent* PreHCTE )
  {
    if ( GetHitBuf() )
    {
      J4VSD<J4IRBCALPreHit>::OutputAll( PreHCTE );
    }
    else
    {
      G4cerr << "J4IRBCALPreHitSD::OutputAll: No HitBuf! " << G4endl;
    }
  }

  inline virtual const J4IRBCALPreHitSD& operator=( const J4VSD<J4IRBCALPreHit> &right )
  {
    J4VSD<J4IRBCALPreHit>::operator=( right );
    return *this;
  }

 private:
  // G4bool IsExiting(const G4ThreeVector &pos, const G4ThreeVector &p) const;

 private:

};

#endif
