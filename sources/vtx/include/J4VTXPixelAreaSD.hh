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
//*************************************************************************
 
#ifndef __HOSHINA__

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
#if 0
       G4int nhits = ((J4VTXPixelAreaHitBuf*)GetHitBuf())->entries();
       G4int i;
       G4cerr << "J4VTXPixelAreaSD::OutputAll: nhits = " << nhits << G4endl;
       for(i=0; i<nhits; i++)
       {
     	J4VTXPixelAreaHitBuf* hcp = (J4VTXPixelAreaHitBuf*)GetHitBuf();
     	J4VTXPixelAreaHit* hp = (J4VTXPixelAreaHit*)hcp->operator[](i);
     	
#ifdef __HOSHINA__     	
     	(J4VHit *)hp->Output(HCTE);
#endif

       }
#else     	
       J4VSD<J4VTXPixelAreaHit>::OutputAll(HCTE);
#endif
     }
     else
     {
        G4cerr << "J4VTXPixelAreaSD::OutputAll: No HitBuf! " << G4endl;
     }
  }
  
  
  // set/get functions
private:
   G4TouchableHistory* ROH;

  void SetROHist(G4TouchableHistory* ROhist){ ROH = ROhist; }
  G4int GetLayerID();
  G4int GetLadderID();
  G4int GetSensorID();
  G4int GetPixelIDTheta();
  G4int GetPixelIDPhi();
  G4ThreeVector  GetPixelPosition();
  G4ThreeVector  GlobalToLocalPosition(G4ThreeVector gpIn);
  void InitID();
  void SetID(G4int track, G4int layer, G4int ladder, G4int sensor,
	     G4int tpixel,G4int ppixel);
  G4bool compareID(G4int track, G4int layer, G4int ladder, G4int sensor,
	     G4int tpixel,G4int ppixel);
  
};


#endif
#endif
