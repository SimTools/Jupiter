// $Id$
#ifndef __J4CLXSD__
#define __J4CLXSD__
//*************************************************************************
//* --------------------
//* J4CLXSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4CLXEM. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
#include "J4VSD.hh"
#include "J4CLXPreHit.hh"
#include "J4CLXPreHitKeeper.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4CLXSD : public J4VSD<J4CLXPreHit>{
  
public:

  J4CLXSD( J4VDetectorComponent* detector );
  ~J4CLXSD();

  virtual G4bool ProcessHits( G4Step* aStep, G4TouchableHistory* ROhist );
  virtual void   Initialize ( G4HCofThisEvent* PreHCTE );
  virtual void   EndOfEvent ( G4HCofThisEvent* PreHCTE );

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll( G4HCofThisEvent* PreHCTE )
  {
    if ( GetHitBuf() )
    {
      J4VSD<J4CLXPreHit>::OutputAll( PreHCTE );
    }
    else
    {
      G4cerr << "J4CLXSD::OutputAll: No HitBuf! " << G4endl;
    }
  }

  inline virtual const J4CLXSD& operator=( const J4VSD<J4CLXPreHit> &right )
  {
    J4VSD<J4CLXPreHit>::operator=( right );
    return *this;
  }

 private:
  G4bool IsExiting(const G4ThreeVector &pos, const G4ThreeVector &p) const;
};

#endif
