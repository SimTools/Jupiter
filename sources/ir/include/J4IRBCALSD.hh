// $Id$
#ifndef __J4IRBCALSD__
#define __J4IRBCALSD__
//*************************************************************************
//* --------------------
//* J4IRBCALSD
//* --------------------
//* (Description)
//* 	Sensitive detector class for BCAL
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2006/01/27 A.Miyamoto Original version.
//*************************************************************************
#include "J4VSD.hh"
#include "J4IRBCALHit.hh"
#include "J4IRBCALSensor.hh"
#include <map>

//=====================================================================
//---------------------
// class definition
//---------------------
class J4IRBCALSD : public J4VSD<J4IRBCALHit>{
  
public:

  J4IRBCALSD( J4IRBCALSensor* detector );
  ~J4IRBCALSD();

  virtual G4bool ProcessHits( G4Step* aStep, G4TouchableHistory* ROhist );
  virtual void   Initialize ( G4HCofThisEvent* PreHCTE );
  virtual void   EndOfEvent ( G4HCofThisEvent* PreHCTE );

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll( G4HCofThisEvent* PreHCTE )
  {
    if ( GetHitBuf() )
    {
      J4VSD<J4IRBCALHit>::OutputAll( PreHCTE );
    }
    else
    {
      G4cerr << "J4IRBCALSD::OutputAll: No HitBuf! " << G4endl;
    }
  }

  inline virtual const J4IRBCALSD& operator=( const J4VSD<J4IRBCALHit> &right )
  {
    J4VSD<J4IRBCALHit>::operator=( right );
    return *this;
  }

 private:
  //  G4bool IsExiting(const G4ThreeVector &pos, const G4ThreeVector &p) const;
  void DefineCells(J4IRBCALSensor *detector);

 private:
  // Silicon sensor is arrange in tower structure.
  // Segmentation in r and phi is defined by the size of the first layer,
  // i.e., closest to the IP
  J4IRBCALLayer *fLayer; 
  J4IRBCAL      *fBCAL;
  static J4IRBCALHit   *fLastHit;
  static std::multimap<G4int, J4IRBCALHit*> fgBCALHits;  // Keep cellID and Hit information  < cellID, map<prehitID, J4IRBCALHit*>>
  G4int fNDivR;   // Division in R direction
  std::vector<G4int> fNDivPhi; // Division in Phi direction, size equal to fNDivR
  std::vector<G4double> fPhiStep; 
  std::vector<G4double> fRbound; // defines Rmin and Rmax of cells at sensor position

  inline void GetRPhiBin(const G4ThreeVector x, G4int &ir, G4int &iphi);


};

#endif
