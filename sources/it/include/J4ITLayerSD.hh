// $Id$
#ifndef __J4ITLAYERSD__
#define __J4ITLAYERSD__
//*************************************************************************
//* --------------------
//* J4ITLayerSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4ITLayer. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J4ITLayerHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4ITLayerSD : public J4VSD<J4ITLayerHit>{
  
public:

  J4ITLayerSD(J4VDetectorComponent* detector);
  ~J4ITLayerSD();

  inline virtual const J4ITLayerSD & operator=(const J4VSD<J4ITLayerHit> &right)
  {
     J4VSD<J4ITLayerHit>::operator=(right);
     return *this;
  }

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J4ITLayerHit>::OutputAll(HCTE);
     }
     else
     {
       G4cerr << "J4ITLayerSD::OutputAll: No HitBuf! " << G4endl;
     }
  }
  
  // set/get functions
   
private:
  static G4int fLastMyID;
  static G4int fLastTrackID;
  static J4ITLayerHit *fLastHit; 
};

#endif

