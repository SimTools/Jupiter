// $Id$
#ifndef __J4VTXPIXELSD__
#define __J4VTXPIXELSD__
//*************************************************************************
//* --------------------
//* J4VTXPixelSD
//* --------------------
//* (Description)
//* 	Concrate class for DriftRegion sensitive detector.
//*	Mother class : J4VSD <- G4VSensitivePixelector
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************


#include "G4Step.hh"
#include "J4VSD.hh"
#include "J4VTXPixelHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4VTXPixelSD : public J4VSD<J4VTXPixelHit>{
  
public:

  J4VTXPixelSD(J4VDetectorComponent* detector);
  ~J4VTXPixelSD();

#if 1
  virtual const J4VSD<J4VTXPixelHit> & operator=(const J4VSD<J4VTXPixelHit> &r)
  {
     return J4VSD<J4VTXPixelHit>::operator=(r);
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
        J4VSD<J4VTXPixelHit>::OutputAll(HCTE);
     }
     else
     {
        G4cerr << "J4VTXPixelSD::OutputAll: No HitBuf! " << G4endl;
     }
  }
  
  
  // set/get functions
private:

  G4ThreeVector  GlobalToLocalPosition(G4ThreeVector gpIn);
  void   InitID();
  void   SetID(G4int track, G4int layer, G4int ladder, G4int sensor,
	       G4int tpixel,G4int ppixel);
  G4bool compareID(G4int track, G4int layer, G4int ladder, G4int sensor,
	     G4int tpixel,G4int ppixel);
	     
  G4int  fSTrack;
  G4int  fSLayer;
  G4int  fSLadder;
  G4int  fSSensor;
  G4int  fSTpixel;
  G4int  fSPpixel;
  G4int  fSColNo;
  
};

#endif

