// $Id$
#ifndef __J4VMUDACTIVESD__
#define __J4VMUDACTIVESD__
//*************************************************************************
//* --------------------
//* J4VMUDActiveSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4MUD
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
#include "J4VSD.hh"
#include "J4VComponent.hh"
#include "J4VDetectorComponent.hh"
#include "J4MUDHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4VMUDActiveSD : public J4VSD<J4MUDHit>{
  
public:
  J4VMUDActiveSD( J4VDetectorComponent* detector );
  ~J4VMUDActiveSD();

  virtual G4bool ProcessHits( G4Step* aStep, G4TouchableHistory* ROhist );
  virtual void   Initialize ( G4HCofThisEvent* HCTE );
  virtual void   EndOfEvent ( G4HCofThisEvent* HCTE );

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll( G4HCofThisEvent* HCTE )
  {
     if( GetHitBuf() ) {
       J4VSD<J4MUDHit>::OutputAll( HCTE );
     } else {
       G4cerr << "J4VMUDActiveSD::OutputAll: No HitBuf! " << G4endl;
     }
  }

  using J4VSD<J4MUDHit>::operator=;

#if 0
  virtual const J4VSD<J4MUDHit>& operator=( const J4VSD<J4MUDHit>& right )
  {
     return J4VSD<J4MUDHit>::operator=( right );
  }
#endif

  virtual G4bool IsBarrel() = 0;
  virtual G4bool IsFront()  = 0;
  
private:
  
};

#endif
