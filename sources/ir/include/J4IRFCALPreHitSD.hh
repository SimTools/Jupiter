// $Id$
#ifndef __J4IRFCALPreHitSD__
#define __J4IRFCALPreHitSD__
//*************************************************************************
//* --------------------
//* J4IRFCALPreHitSD
//* --------------------
//* (Description)
//* 	Sensitive detector class for FCAL
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2006/01/27 A.Miyamoto Original version.
//*************************************************************************
#include "J4VSD.hh"
#include "J4IRFCALPreHit.hh"
#include "J4IRFCAL.hh"

#include <map>

//=====================================================================
//---------------------
// class definition
//---------------------
class J4IRFCALPreHitSD : public J4VSD<J4IRFCALPreHit>{
  
public:

  J4IRFCALPreHitSD( J4IRFCAL* detector );
  ~J4IRFCALPreHitSD();

  virtual G4bool ProcessHits( G4Step* aStep, G4TouchableHistory* ROhist );
  virtual void   Initialize ( G4HCofThisEvent* PreHCTE );
  virtual void   EndOfEvent ( G4HCofThisEvent* PreHCTE );

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll( G4HCofThisEvent* PreHCTE )
  {
    if ( GetHitBuf() )
    {
      J4VSD<J4IRFCALPreHit>::OutputAll( PreHCTE );
    }
    else
    {
      G4cerr << "J4IRFCALPreHitSD::OutputAll: No HitBuf! " << G4endl;
    }
  }

  inline virtual const J4IRFCALPreHitSD& operator=( const J4VSD<J4IRFCALPreHit> &right )
  {
    J4VSD<J4IRFCALPreHit>::operator=( right );
    return *this;
  }

 private:
  // G4bool IsExiting(const G4ThreeVector &pos, const G4ThreeVector &p) const;

 private:

};

#endif
