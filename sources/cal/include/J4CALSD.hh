// $Id$
#ifndef __J4CALSD__
#define __J4CALSD__
//*************************************************************************
//* --------------------
//* J4CALSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4CALEM. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J4CALHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALSD : public J4VSD<J4CALHit>{
  
public:

  J4CALSD(J4VDetectorComponent* detector);
  ~J4CALSD();

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void   Initialize (G4HCofThisEvent* HCTE);
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE);

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD<J4CALHit>::OutputAll(HCTE);
     }
     else
     {
       std::cerr << "J4CALSD::OutputAll: No HitBuf! " << std::endl;
     }
  }
  
  // set/get functions
   
private:

  //std::vector< std::vector<J4CALHit *> > fCalHits;
  J4CALHit       **fCalHits;

};

#endif
