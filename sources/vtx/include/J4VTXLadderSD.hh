// $Id$
#ifndef __J4VTXLADDERSD__
#define __J4VTXLADDERSD__
//*************************************************************************
//* --------------------
//* J4VTXLadderSD
//* --------------------
//* (Description)
//* 	Concrate class for DriftRegion sensitive detector.
//*	Mother class : J4VSD <- G4VSensitiveLadderector
//*     
//* (Update Record)
//*	2002/10/23  T.Aso	Original version.
//*************************************************************************


#include "G4Step.hh"
#include "J4VSD.hh"
#include "J4VTXLadderHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4VTXLadderSD : public J4VSD<J4VTXLadderHit>{
  
public:

  J4VTXLadderSD(J4VDetectorComponent* detector);
  ~J4VTXLadderSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void DrawAll();
  virtual void PrintAll(); 
  virtual void OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
        J4VSD<J4VTXLadderHit>::OutputAll(HCTE);
     }
     else
     {
        std::cerr << "J4VTXLadderSD::OutputAll: No HitBuf! " << std::endl;
     }
  }
  
  
  // set/get functions
private:
  
};

#endif

