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
#include "J4TPCLayerHit.hh"
#include "J4TrackingAction.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4TPCDriftRegionSD : public J4VSD<J4TPCLayerHit>{
  
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
       J4VSD<J4TPCLayerHit>::OutputAll(HCTE);
     }
     else {
       G4cerr << "J4TPCDriftRegionSD::OutputAll: No HitBuf! " << G4endl;
     }
  }

  inline 
  virtual const J4TPCDriftRegionSD & operator=(const J4VSD<J4TPCLayerHit> &right)
  {
     J4VSD<J4TPCLayerHit>::operator=(right);
     return *this;
  }

  // set/get functions
  static G4int GetCurTrackID()       { return J4TrackingAction::GetCurTrackID(fgTrackRegID); }
  static void  SetCurTrackID(G4int id) { J4TrackingAction::SetCurTrackID(fgTrackRegID, id); }
   
private:
  G4bool IsOnSurface(const G4ThreeVector &pos, const G4ThreeVector &p) const; 
private:
  static G4int fgTrackRegID;
  
};

#endif

