// $Id$
#ifndef __J4CALSUBLAYERSD__
#define __J4CALSUBLAYERSD__
//*************************************************************************
//* --------------------
//* J4CALSubLayerSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4CALEM. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J4CALHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALSubLayerSD : public J4VSD<J4CALHit>{
  
public:

  J4CALSubLayerSD(J4VDetectorComponent* detector);
  ~J4CALSubLayerSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll();
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J4CALHit>::OutputAll(HCTE);
     }
     else
     {
       G4cerr << "J4CALSubLayerSD::OutputAll: No HitBuf! " << G4endl;
     }
  }
 
 inline virtual const J4CALSubLayerSD& operator=( const J4VSD<J4CALHit> &right )
 {
   J4VSD<J4CALHit>::operator=( right );
   return *this;
 } 
 
  // set/get functions
   
private:
  J4CALHit    **fCalHits; 
  G4int       fTowerNClones;

};

#endif
