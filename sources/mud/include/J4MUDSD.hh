// $Id$
#ifndef __J4MUDSD__
#define __J4MUDSD__
//*************************************************************************
//* --------------------
//* J4MUDSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4MUDEM. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
#include "J4VSD.hh"
#include "J4MUDPreHit.hh"
#include "J4MUDPreHitKeeper.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4MUDSD : public J4VSD<J4MUDPreHit>{
  
public:

  J4MUDSD( J4VDetectorComponent* detector );
  ~J4MUDSD();

  virtual G4bool ProcessHits( G4Step* aStep, G4TouchableHistory* ROhist );
  virtual void   Initialize ( G4HCofThisEvent* PreHCTE );
  virtual void   EndOfEvent ( G4HCofThisEvent* PreHCTE );

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll( G4HCofThisEvent* PreHCTE )
  {
    if ( GetHitBuf() )
    {
      J4VSD<J4MUDPreHit>::OutputAll( PreHCTE );
    }
    else
    {
      G4cerr << "J4MUDSD::OutputAll: No HitBuf! " << G4endl;
    }
  }

  inline virtual const J4MUDSD& operator=( const J4VSD<J4MUDPreHit> &right )
  {
    J4VSD<J4MUDPreHit>::operator=( right );
    return *this;
  }

  G4bool IsFront( const G4ThreeVector& pos, const G4ThreeVector& p ) const ;
private:
  //J4MUDPreHit*   fMUDPreHits;

};

#endif
