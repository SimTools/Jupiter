// $Id$
#ifndef __J4CTLAYERSD__
#define __J4CTLAYERSD__
//*************************************************************************
//* --------------------
//* J4CTLayerSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4CTLayer. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J4CTLayerHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4CTLayerSD : public J4VSD<J4CTLayerHit>{
  
public:

  J4CTLayerSD(J4VDetectorComponent* detector);
  ~J4CTLayerSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J4CTLayerHit>::OutputAll(HCTE);
     }
     else
     {
       G4cerr << "J4CTLayerSD::OutputAll: No HitBuf! " << G4endl;
     }
  }
  
  // set/get functions
   
private:
  
};

#endif

