// $Id$
#ifndef __J4MUDBARRELSD__
#define __J4MUDBARRELSD__
//*************************************************************************
//* --------------------
//* J4MUDBarrelSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4MUDBarrel. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
#include "J4VSD.hh"
#include "J4MUDBarrelHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4MUDBarrelSD : public J4VSD<J4MUDBarrelHit>{
  
public:

  J4MUDBarrelSD( J4VDetectorComponent* detector );
  ~J4MUDBarrelSD();

#if 1
  virtual const J4VSD<J4MUDBarrelHit>& operator=( const J4VSD<J4MUDBarrelHit>& right )
  {
     return J4VSD<J4MUDBarrelHit>::operator=( right );
  }
#endif

  virtual G4bool ProcessHits( G4Step* aStep, G4TouchableHistory* ROhist );
  virtual void   Initialize ( G4HCofThisEvent* HCTE );
  virtual void   EndOfEvent ( G4HCofThisEvent* HCTE );

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll( G4HCofThisEvent* HCTE )
  {
     if( GetHitBuf() ) {
       J4VSD<J4MUDBarrelHit>::OutputAll( HCTE );
     } else {
       G4cerr << "J4MUDBarrelSD::OutputAll: No HitBuf! " << G4endl;
     }
  }
  
private:
  
};

#endif
