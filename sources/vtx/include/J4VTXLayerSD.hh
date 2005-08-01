// $Id$
#ifndef __J4VTXLAYERSD__
#define __J4VTXLAYERSD__
//*************************************************************************
//* --------------------
//* J4VTXLayerSD
//* --------------------
//* (Description)
//* 	Concrate class for DriftRegion sensitive detector.
//*	Mother class : J4VSD <- G4VSensitiveLayerector
//*     
//* (Update Record)
//*	2002/10/23  T.Aso	Original version.
//*************************************************************************


#include "G4Step.hh"
#include "J4VSD.hh"
#include "J4VTXLayerHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4VTXLayerSD : public J4VSD<J4VTXLayerHit>{
  
public:

  J4VTXLayerSD(J4VDetectorComponent* detector);
  ~J4VTXLayerSD();

#if 1
  virtual const J4VSD<J4VTXLayerHit> & operator=(const J4VSD<J4VTXLayerHit> &r)
  {
     return J4VSD<J4VTXLayerHit>::operator=(r);
  }
#endif

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void DrawAll();
  virtual void PrintAll(); 
  virtual void OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
        J4VSD<J4VTXLayerHit>::OutputAll(HCTE);
     }
     else
     {
        G4cerr << "J4VTXLayerSD::OutputAll: No HitBuf! " << G4endl;
     }
  }
  
  
  // set/get functions
private:
  static G4int  fLastMyID;
  static G4int  fLastTrackID;
  static J4VTXLayerHit  *fLastHit;
 
};

#endif

