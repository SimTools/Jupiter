// $Id$
//*************************************************************************
//* --------------------
//* J4IRBCALPreHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4ITLayer.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*     2004/11/01  Allister Sanchez  Remove redundant data/functions which are in J4VHit.
//*************************************************************************

#include <iomanip>
#include "J4IRBCALPreHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J4IRBCALPreHitAllocator J4IRBCALPreHit::fgPreHitAllocator;
J4Output*            J4IRBCALPreHit::fgPreOutput = 0;
 
//=========================================================================
//* constructor -----------------------------------------------------------
J4IRBCALPreHit::J4IRBCALPreHit( J4VComponent*         detector,  // He is in "location" now
                          G4int                 postHitID, // PostHitID of insident particle 
                          G4int                 preHitID,  // HitID of insident particle
                          const G4ThreeVector&  pre,       // Pre-position of track
		          const G4ThreeVector&  momentum,  // Momentum of track
		          G4double              energy,    // Kinetic Energy of insident particle
		          G4double              tof,       // TOF of insident particle
		          G4int                 trackID,   // TrackID of inside particle
                          G4ParticleDefinition* particle,  // My particle definition
			  G4int                 motherTrackID ) // mother track's ID
  // detector, trackID, motherTrackID, particle, TOF, Edep, Energy, Momentum
  : J4VHit(detector, trackID, motherTrackID, particle, tof, 0, energy, momentum, pre),
    fPreHitID(preHitID),    fPostHitID(postHitID)
{
}

//=========================================================================
//* destructor -----------------------------------------------------------
J4IRBCALPreHit::~J4IRBCALPreHit()
{
}

//=========================================================================
//* Output ------------------------------------------------------------------

void J4IRBCALPreHit::Output( G4HCofThisEvent* /* PreHCTE */ )
{
  if ( fgPreOutput ) fgPreOutput -> Output( this );
  // output hitdata to output file ....
        
  std::ofstream& ofs = GetOutputFileStream();
  if ( !ofs.good() ) {
    const G4String& errorMessage = "J4IRBCALPreHit::Output(): write error.";
    G4cerr << errorMessage << G4endl;
  } else {
    ofs << "bcalphit "
        << std::setw(3)  << fPostHitID << " "
        << std::setw(3)  << fPreHitID << " "
        << std::setw(5)  << GetTrackID() << " "
	<< std::setw(5)  << GetMotherTrackID() << " "

	<< std::setw(12) << GetTotalEnergy() << " "
        << std::setw(7)  << GetMomentum().x() << " "
	<< std::setw(7)  << GetMomentum().y() << " "
	<< std::setw(7)  << GetMomentum().z() << " "
        << std::setw(6)  << GetPDGEncoding() << " "
        << std::setw(2)  << GetCharge() << " "
	<< std::setw(12) << GetTof() << " "
        << std::setw(12) << GetInjectionPoint().x() << " "
        << std::setw(12) << GetInjectionPoint().y() << " "
        << std::setw(12) << GetInjectionPoint().z() << " "
        << std::endl;
  }
}

//=========================================================================
//* Draw ------------------------------------------------------------------

void J4IRBCALPreHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------

void J4IRBCALPreHit::Print()
{
}
