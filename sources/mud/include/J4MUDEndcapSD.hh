// $Id$
#ifndef __J4MUDENDCAPSD__
#define __J4MUDENDCAPSD__
//*************************************************************************
//* --------------------
//* J4MUDEndcapSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4MUDEndcap. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
#include "J4VSD.hh"
#include "J4MUDEndcapHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4MUDEndcapSD : public J4VSD<J4MUDEndcapHit>{
  
public:

  J4MUDEndcapSD( J4VDetectorComponent* detector );
  ~J4MUDEndcapSD();

#if 1
  virtual const J4VSD<J4MUDEndcapHit>& operator=( const J4VSD<J4MUDEndcapHit>& right )
  {
     return J4VSD<J4MUDEndcapHit>::operator=( right );
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
       J4VSD<J4MUDEndcapHit>::OutputAll( HCTE );
     } else {
       G4cerr << "J4MUDEndcapSD::OutputAll: No HitBuf! " << G4endl;
     }
  }
  
private:
  
};

#endif
