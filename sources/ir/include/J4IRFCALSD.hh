// $Id$
#ifndef __J4IRFCALSD__
#define __J4IRFCALSD__
//*************************************************************************
//* --------------------
//* J4IRFCALSD
//* --------------------
//* (Description)
//* 	Sensitive detector class for FCAL
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2006/01/27 A.Miyamoto Original version.
//*************************************************************************
#include "J4VSD.hh"
#include "J4IRFCALHit.hh"
#include "J4IRFCALSensor.hh"
#include <map>

//=====================================================================
//---------------------
// class definition
//---------------------
class J4IRFCALSD : public J4VSD<J4IRFCALHit>{
  
public:

  J4IRFCALSD( J4IRFCALSensor* detector );
  ~J4IRFCALSD();

  virtual G4bool ProcessHits( G4Step* aStep, G4TouchableHistory* ROhist );
  virtual void   Initialize ( G4HCofThisEvent* PreHCTE );
  virtual void   EndOfEvent ( G4HCofThisEvent* PreHCTE );

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll( G4HCofThisEvent* PreHCTE )
  {
    if ( GetHitBuf() )
    {
      J4VSD<J4IRFCALHit>::OutputAll( PreHCTE );
    }
    else
    {
      G4cerr << "J4IRFCALSD::OutputAll: No HitBuf! " << G4endl;
    }
  }

  inline virtual const J4IRFCALSD& operator=( const J4VSD<J4IRFCALHit> &right )
  {
    J4VSD<J4IRFCALHit>::operator=( right );
    return *this;
  }

 private:
  //  G4bool IsExiting(const G4ThreeVector &pos, const G4ThreeVector &p) const;
  void DefineCells(J4IRFCALSensor *detector);

 private:
  // Silicon sensor is arrange in tower structure.
  // Segmentation in r and phi is defined by the size of the first layer,
  // i.e., closest to the IP
  J4IRFCALLayer *fLayer; 
  J4IRFCAL      *fFCAL;
  static J4IRFCALHit   *fLastHit;
  static std::multimap<G4int, J4IRFCALHit*> fgFCALHits;  // Keep cellID and Hit information  < cellID, map<prehitID, J4IRFCALHit*>>
  G4int fNDivR;   // Division in R direction
  std::vector<G4int> fNDivPhi; // Division in Phi direction, size equal to fNDivR
  std::vector<G4double> fPhiStep; 
  std::vector<G4double> fRbound; // defines Rmin and Rmax of cells at sensor position

  inline void GetRPhiBin(const G4ThreeVector x, G4int &ir, G4int &iphi);


};

#endif
