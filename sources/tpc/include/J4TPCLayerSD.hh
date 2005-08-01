// $Id$
#ifndef __J4TPCLAYERSD__
#define __J4TPCLAYERSD__
//*************************************************************************
//* --------------------
//* J4TPCLayerSD
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

//=====================================================================
//---------------------
// class definition
//---------------------


class J4TPCLayerSD : public J4VSD<J4TPCLayerHit>{
private:
  static G4int fLastMyID;
  static G4int fLastTrackID;
  static J4TPCLayerHit *fLastHit;
  
public:

  J4TPCLayerSD(J4VDetectorComponent* detector);
  ~J4TPCLayerSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J4TPCLayerHit>::OutputAll(HCTE);
     }
     else
     {
       G4cerr << "J4TPCLayerSD::OutputAll: No HitBuf! " << G4endl;
     }
  }

  inline 
  virtual const J4TPCLayerSD & operator=(const J4VSD<J4TPCLayerHit> &right)
  {
     J4VSD<J4TPCLayerHit>::operator=(right);
     return *this;
  }
  
  // set/get functions
   
private:
  
};

#endif

