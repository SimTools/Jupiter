// $Id$
//*************************************************************************
//* --------------------
//* J4CALPreHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4ITLayer.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include <iomanip>
#include "J4CALPreHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J4CALPreHitAllocator J4CALPreHit::fgPreHitAllocator;
J4Output*            J4CALPreHit::fgPreOutput = 0;
 
//=========================================================================
//* constructor -----------------------------------------------------------
J4CALPreHit::J4CALPreHit( J4VComponent*         detector,  // He is in "location" now
                          G4int                 preHitID,  // HitID of insident particle
                          const G4ThreeVector&  pre,       // Pre-position of track
		          const G4ThreeVector&  momentum,  // Momentum of track
		          G4double              energy,    // Kinetic Energy of insident particle
		          G4double              tof,       // TOF of insident particle
		          G4int                 trackID,   // TrackID of inside particle
                          G4ParticleDefinition* particle ) // My particle definision
 : J4VHit( detector ), fPreHitID( preHitID ),
   fInjectionPoint( pre ), fMomentum( momentum ), fEnergy( energy ), fTof( tof ),
   fTrackID( trackID ), fParticle( particle )
{
}

//=========================================================================
//* destructor -----------------------------------------------------------
J4CALPreHit::~J4CALPreHit()
{
}

//=========================================================================
//* Output ------------------------------------------------------------------

void J4CALPreHit::Output( G4HCofThisEvent* /* PreHCTE */ )
{
  if ( fgPreOutput ) fgPreOutput -> Output( this );
  // output hitdata to output file ....
        
  std::ofstream& ofs = GetOutputFileStream();
  if ( !ofs.good() ) {
    const G4String& errorMessage = "J4CALPreHit::Output(): write error.";
    G4cerr << errorMessage << G4endl;
  } else {
    ofs << std::setw(3)  << fPreHitID << " "
        << std::setw(5)  << fTrackID << " "
	<< std::setw(12) << fEnergy << " "
        << std::setw(7)  << fMomentum.x() << " "
	<< std::setw(7)  << fMomentum.y() << " "
	<< std::setw(7)  << fMomentum.z() << " "
        << std::setw(6)  << fParticle->GetPDGEncoding() << " "
        << std::setw(2)  << fParticle->GetPDGCharge() << " "
	<< std::setw(12) << fTof << " "
        << std::setw(12) << fInjectionPoint.x() << " "
        << std::setw(12) << fInjectionPoint.y() << " "
        << std::setw(12) << fInjectionPoint.z() << " "
        << std::endl;
  }
}

//=========================================================================
//* Draw ------------------------------------------------------------------

void J4CALPreHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------

void J4CALPreHit::Print()
{
}
