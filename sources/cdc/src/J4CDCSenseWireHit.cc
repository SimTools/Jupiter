// $Id$
//*************************************************************************
//* --------------------
//* J4CDCSenseWireHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4CDCSenseWire.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include <iomanip>
#include "J4CDCSenseWireHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J4CDCSenseWireHitAllocator J4CDCSenseWireHit::fHitAllocator ;

//=========================================================================
//* constructor -----------------------------------------------------------

#if 0
J4CDCSenseWireHit::J4CDCSenseWireHit(
                   J4VComponent         *detector,       // He is in "location" now
                   G4int                 cloneID,        // CloneID of detector
                   G4int                 trackID,        // TrackID
                   G4int                 mothertrackID,  // MotherTrackID
                   G4ParticleDefinition *particle,       // particle
                   G4double              tof,            // TOF 
                   G4double              edep,           // Energy Deposit
                   G4double              totalE,         // Total energy
                   const G4ThreeVector  &momentum,       // Momentum of perticle
                   const G4ThreeVector  &pre,            // Pre-position of track
                   const G4ThreeVector  &pos )           // Post-position of track
#else
J4CDCSenseWireHit::J4CDCSenseWireHit(
                   J4VComponent         *,       // He is in "location" now
                   G4int                 ,       // CloneID of detector
                   G4int                 ,       // TrackID
                   G4int                 ,       // MotherTrackID
                   G4ParticleDefinition *,       // particle
                   G4double              ,       // TOF 
                   G4double              ,       // Energy Deposit
                   G4double              ,       // Total energy
                   const G4ThreeVector  &,       // Momentum of perticle
                   const G4ThreeVector  &,       // Pre-position of track
                   const G4ThreeVector  &)       // Post-position of track
#endif
{
  fHitPosition = GetHitPosition();
}

//=========================================================================
//* destructor -----------------------------------------------------------

J4CDCSenseWireHit::~J4CDCSenseWireHit()
{
}

//=========================================================================
//* GetHitPosition --------------------------------------------------

G4ThreeVector J4CDCSenseWireHit::GetHitPosition() const
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
//* Output ------------------------------------------------------------------

void J4CDCSenseWireHit::Output(G4HCofThisEvent *)
{
   std::cerr << "I am SenseWireHit." << std::endl;	
	
}

//=========================================================================
//* Draw ------------------------------------------------------------------

void J4CDCSenseWireHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------

void J4CDCSenseWireHit::Print()
{

  std::cout << std::setiosflags(std::ios::fixed);
  std::cout << std::setw(20) << GetComponentName() << " " << std::endl;
  std::cout << " track#=" << GetTrackID()
         << " charge=" << GetCharge()
         << " position(mm)= " << std::setprecision(2) 
         << std::setw(8) << fHitPosition.x() *(1./mm) << " "
         << std::setw(8) << fHitPosition.y() *(1./mm) << " "
         << std::setw(8) << fHitPosition.z() *(1./mm) << " "
         << " energy(GeV)= " << std::setprecision(2) 
         << std::setw(6) << GetTotalEnergy() *(1./GeV) << " "
         << " TOF(ns)= " << std::setw(4) << std::setprecision(1) 
         << GetTof() /ns 
         << std::endl;  
}

