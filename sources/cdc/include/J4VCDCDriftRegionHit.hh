// $Id$
#ifndef __J4VCDCDRIFTREGIONHIT__
#define __J4VCDCDRIFTREGIONHIT__
//*************************************************************************
//* --------------------
//* J4VCDCDriftRegionHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4VCDCDriftRegion.
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4RotationMatrix.hh"
#include "J4Output.hh"


//=========================================================================
//---------------------
// class definition
//---------------------
 

class J4VCDCDriftRegionHit : public J4VHit 
{

 public:
  J4VCDCDriftRegionHit();
  J4VCDCDriftRegionHit(J4VComponent         *detector,
                      G4int                 cloneID, 
                      G4int                 trackID        = 0,
                      G4int                 mothertrackID  = 0,
                      G4ParticleDefinition *particle       = 0,
                      G4double              tof            = 0,
                      G4double              edep           = 0,
                      G4double              totalE         = 0,
                      const G4ThreeVector  &momentum       = 0,
                      const G4ThreeVector  &pre            = 0,
                      const G4ThreeVector  &pos            = 0,
                      G4double              rotangle       = 0, 
                      const G4ThreeVector  &wireEndpz      = 0,
                      const G4ThreeVector  &wireEndmz      = 0, 
                      G4double              tanstereo      = 0, 
                      G4double              rwaist         = 0, 
                      const G4int           hitnumber      = 0); 

  inline J4VCDCDriftRegionHit(const J4VCDCDriftRegionHit &right);
  
  virtual ~J4VCDCDriftRegionHit();
  
  virtual const J4VCDCDriftRegionHit& 
          operator=(const J4VCDCDriftRegionHit &right);    

  virtual void Output(G4HCofThisEvent *HCTE) = 0;
  virtual void Draw() {}
  virtual void Print() {}
  
  virtual G4ThreeVector GetHitPosition() const; 
  virtual G4double      DistanceToWire(const G4ThreeVector &p,
                                             G4ThreeVector xx) const;

 protected: 

  G4ThreeVector    fHitPosition;
  G4ThreeVector    fWireEnd[2];
  G4double         fTanStereo;
  G4double         fRwaist;
  G4double         fRotAngle;

  static G4bool    fIsRoundDriftRegion;
  
};

//=====================================================================
//----------------------------------------
// inline function for J4VCDCDriftRegionHit
//----------------------------------------

J4VCDCDriftRegionHit::J4VCDCDriftRegionHit(const J4VCDCDriftRegionHit &right)
{
  fHitPosition  = right.fHitPosition ;
  fWireEnd[0]   = right.fWireEnd[0];
  fWireEnd[1]   = right.fWireEnd[1];
  fTanStereo    = right.fTanStereo;
  fRwaist       = right.fRwaist;
  fRotAngle     = right.fRotAngle;
}

inline const J4VCDCDriftRegionHit& 
  J4VCDCDriftRegionHit::operator= (const J4VCDCDriftRegionHit &right)
{         
  fHitPosition  = right.fHitPosition ;
  fWireEnd[0]   = right.fWireEnd[0];
  fWireEnd[1]   = right.fWireEnd[1];
  fTanStereo    = right.fTanStereo;
  fRwaist       = right.fRwaist;
  fRotAngle     = right.fRotAngle;
  return *this;
}

#endif

