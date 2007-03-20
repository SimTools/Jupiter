// $Id$
#ifndef __J4TPCLAYERSD__
#define __J4TPCLAYERSD__
//*************************************************************************
//* --------------------
//* J4TPCDriftRegionSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4TPCLayer. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J4TPCPostHit.hh"
#include "J4TrackingAction.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4TPCDriftRegionSD : public J4VSD<J4TPCPostHit>{
  
public:

  J4TPCDriftRegionSD(J4VDetectorComponent* detector);
  ~J4TPCDriftRegionSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf()) {
       J4VSD<J4TPCPostHit>::OutputAll(HCTE);
     }
     else {
       G4cerr << "J4TPCDriftRegionSD::OutputAll: No HitBuf! " << G4endl;
     }
  }

  inline 
  virtual const J4TPCDriftRegionSD & operator=(const J4VSD<J4TPCPostHit> &right)
  {
     J4VSD<J4TPCPostHit>::operator=(right);
     return *this;
  }

private:
  G4bool IsExiting(const G4ThreeVector &pos, const G4ThreeVector &p) const; 
  
};

#endif

