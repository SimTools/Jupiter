// $Id$
#ifndef __J4VTXPIXELAREASD__
#define __J4VTXPIXELAREASD__
//*************************************************************************
//* --------------------
//* J4VTXPixelAreaSD
//* --------------------
//* (Description)
//* 	Concrate class for DriftRegion sensitive detector.
//*	Mother class : J4VSD <- G4VSensitivePixelector
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*	2002/11/20  T.Aso       Modify 
//*************************************************************************


#include "G4Step.hh"
#include "J4VSD.hh"
#include "J4VTXPixelAreaHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4VTXPixelAreaSD : public J4VSD<J4VTXPixelAreaHit>{
  
public:

  J4VTXPixelAreaSD(J4VDetectorComponent* detector);
  ~J4VTXPixelAreaSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void DrawAll();
  virtual void PrintAll(); 
  virtual void OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
        J4VSD<J4VTXPixelAreaHit>::OutputAll(HCTE);
     }
     else
     {
        G4cerr << "J4VTXPixelAreaSD::OutputAll: No HitBuf! " << G4endl;
     }
  }

  // set/get functions
private:

  G4ThreeVector  GlobalToLocalPosition(G4ThreeVector gpIn);
  void   InitID();
  void   SetID(G4int track, G4int layer, G4int ladder, G4int sensor);
  G4bool compareID(G4int track, G4int layer, G4int ladder, G4int sensor);
	     
  G4int  fSTrack;
  G4int  fSLayer;
  G4int  fSLadder;
  G4int  fSSensor;
  G4int  fSColNo;
  
};

#endif

