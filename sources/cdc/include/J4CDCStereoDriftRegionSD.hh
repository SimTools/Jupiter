// $Id$
#ifndef __J4CDCDRIFTREGIONSD__
#define __J4CDCDRIFTREGIONSD__
//*************************************************************************
//* --------------------
//* J4CDCStereoDriftRegionSD
//* --------------------
//* (Description)
//* 	Concrate class for DriftRegion sensitive detector.
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "G4Step.hh"
#include "J4VSD.hh"
#include "J4CDCStereoDriftRegionHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4CDCStereoDriftRegionSD : public J4VSD<J4CDCStereoDriftRegionHit>{
  
public:

  J4CDCStereoDriftRegionSD(J4VDetectorComponent* detector);
  ~J4CDCStereoDriftRegionSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J4CDCStereoDriftRegionHit>::OutputAll(HCTE);
     }
     else
     {
       G4cerr << "J4CDCStereoDriftRegionSD::OutputAll: No Hit! " << G4endl;
     }
  }

  virtual void DrawAll();
  virtual void PrintAll(); 
 
  // set/get functions
   
private:
  
};

#endif

