// $Id$
//*************************************************************************
//* --------------------
//* J4VCDCDriftRegionHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4VCDCDriftRegion.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include <iomanip>
#include <math.h>
#include "J4VCDCDriftRegionHit.hh"
#include "J4VCDCDriftRegion.hh"

using namespace std;

G4bool J4VCDCDriftRegionHit::fIsRoundDriftRegion = FALSE;

//=========================================================================
//* constructor -----------------------------------------------------------

J4VCDCDriftRegionHit::J4VCDCDriftRegionHit(
     J4VComponent         *detector,      // Belonging DetectorComponent
     G4int                 cloneID,       // CloneID
     G4int                 trackID,       // TrackID
     G4int                 mothertrackID, // MotherTrackID
     G4ParticleDefinition *particle,      // Particle
     G4double              tof,           // TOF
     G4double              edep,          // Energy Deposit
     G4double              totalE,        // Total energy
     const G4ThreeVector  &momentum,      // Momentum of perticle
     const G4ThreeVector  &pre,           // Pre-position of track
     const G4ThreeVector  &pos,           // Post-position of track
     G4double              rotangle,      // rotation angle of cell 
     const G4ThreeVector  &wireEndpz,     // wire position at +ve z endcap
     const G4ThreeVector  &wireEndmz,     // wire position at -ve z endcap
     G4double              tanstereo,     // stereo angle of cell 
     G4double              rwaist,        // stereo angle of cell 
     const G4int           hitnumber)     // unique hit number
   : J4VHit(detector, cloneID, trackID, mothertrackID, particle, 
            tof, edep, totalE, momentum, pre, pos, hitnumber),
     fTanStereo(tanstereo), fRwaist(rwaist),fRotAngle(rotangle)
{
   fHitPosition = GetHitPosition(); 
   fWireEnd[0] = wireEndmz;
   fWireEnd[1] = wireEndpz;
}

//=========================================================================
//* destructor -----------------------------------------------------------

J4VCDCDriftRegionHit::~J4VCDCDriftRegionHit()
{
}

//=========================================================================
//* GetHitPosition --------------------------------------------------

G4ThreeVector J4VCDCDriftRegionHit::GetHitPosition() const
{
  G4ThreeVector pre  = GetPrePosition();
  G4ThreeVector post = GetPostPosition();
  G4double x = (pre.x() + post.x()) / 2.0 ;
  G4double y = (pre.y() + post.y()) / 2.0 ;
  G4double z = (pre.z() + post.z()) / 2.0 ;
  
  G4ThreeVector hit(x, y, z);
  return hit;
}

//=========================================================================
//* DistanceToWire --------------------------------------------------------

G4double J4VCDCDriftRegionHit::DistanceToWire(const G4ThreeVector &p,
                                                   G4ThreeVector xx) const
{
   // Equation
   //
   //    distance^2 = |(xx - p)|^2
   //    with
   //       xx = x0 + t*d
   //            x0 is a reference point of the boudary
   //            d  is the direction vector of the boundary
   //
   //   (d/dt)distance^2 = (d/dt)|((x0 + t*d) - p)|^2
   //                    = 2*t*|d|^2 + 2*d*(x0 - p)
   //                    = 0  //at smallest distance
   //   then
   //      t = - d*(x0 - p) / |d|^2
   //
   
   G4ThreeVector d;  // direction vector of the boundary
   G4double      t;

   d  = (fWireEnd[1] - fWireEnd[0]).unit();
   t  = - d * (fWireEnd[0] - p);
   xx = fWireEnd[0] + t * d;
   
   G4ThreeVector dist = xx - p;
   
   return (xx.x()*p.y() - p.x()*xx.y() > 0 ? 1 : -1) * dist.mag();

}


