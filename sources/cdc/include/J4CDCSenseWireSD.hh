// $Id$
#ifndef __J4CDCSENSEWIRESD__
#define __J4CDCSENSEWIRESD__
//*************************************************************************
//* --------------------
//* J4CDCSenseWireSD
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
#include "J4CDCSenseWireHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4CDCSenseWireSD : public J4VSD<J4CDCSenseWireHit>{
  
public:

  J4CDCSenseWireSD(J4VDetectorComponent* detector);
  ~J4CDCSenseWireSD();

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
       G4int nhits = ((J4CDCSenseWireHitBuf*)GetHitBuf())->entries();
       G4int i;
       std::cerr << "J4CDCSenseWireSD::OutputAll: nhits = " << nhits << std::endl;
       for(i=0; i<nhits; i++)
       {
     	J4CDCSenseWireHitBuf* hcp = (J4CDCSenseWireHitBuf*)GetHitBuf();
     	J4VHit* hp = (J4VHit*)hcp->operator[](i);
     	hp->Output(HCTE);       
       }
#else     	
       J4VSD<J4CDCSenseWireHit>::OutputAll(HCTE);
#endif
     }
     else
     {
//       std::cerr << "J4CDCSenseWireSD::OutputAll: No HitBuf! " << std::endl;
     }
  }
  
  
  // set/get functions
   
private:
  
};

#endif

