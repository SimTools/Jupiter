// $Id$
//*************************************************************************
//* --------------------
//* J4MUDPreHit
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
#include "J4MUDPreHit.hh"
#include "J4CALPostHit.hh"
#include "J4CALPreHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------
J4MUDPreHitAllocator J4MUDPreHit::fgPreHitAllocator;
J4Output*            J4MUDPreHit::fgPreOutput = 0;
 
//=========================================================================
//* constructor -----------------------------------------------------------
J4MUDPreHit::J4MUDPreHit( J4VComponent*         detector,     // He is in "location" now
                          G4int                 preHitID,     // HitID of insident particle
                          //J4CALPostHit*         postHitPtr,   // Pointer to CAL post hit
                          G4int                 calPostHitID, // PostHitID of insident particle 
                          G4int                 calPreHitID,  // CAL preHitID of insident particle
                          const G4ThreeVector&  pre,          // Pre-position of track
		          const G4ThreeVector&  momentum,     // Momentum of track
		          G4double              energy,       // Total Energy of insident particle
		          G4double              tof,          // TOF of insident particle
                          G4ParticleDefinition* particle,     // My particle definition
		          G4int                 trackID,      // TrackID of inside particle
			  G4int                 motherTrackID ) // mother track's ID
 // detector, trackID, motherTrackID, particle, TOF, Edep, Energy, Momentum
 : J4VHit(detector, trackID, motherTrackID, particle, tof, 0, energy, momentum, pre ),
   fCALPostHitID(calPostHitID),  fCALPreHitID(calPreHitID),
   /*fCALPostHitPtr(postHitPtr),*/
   fMUDPreHitID(preHitID)
{ }

//=========================================================================
//* destructor -----------------------------------------------------------
J4MUDPreHit::~J4MUDPreHit() { }

//=========================================================================
//* Output ------------------------------------------------------------------
void J4MUDPreHit::Output( G4HCofThisEvent* /* PreHCTE */ )
{
  if ( fgPreOutput ) fgPreOutput -> Output( this );
  // output hitdata to output file ....
        
  std::ofstream& ofs = GetOutputFileStream();
  if ( !ofs.good() ) {
    const G4String& errorMessage = "J4MUDPreHit::Output(): write error.";
    G4cerr << errorMessage << G4endl;
  } else {
    const G4ThreeVector& pre = GetPrePosition();
    ofs << "prehit "
        << std::setw(5)  << GetPreHitID() << " "
        << std::setw(8)  << GetCALPreHitID() << " "
        << std::setw(8)  << GetCALPostHitID() << " "
        << std::setw(10) << GetTrackID() << " "
	<< std::setw(10) << GetMotherTrackID() << " "
        //<< std::setw(6)  << GetParticleName() << " "
        << std::setw(6)  << GetPDGEncoding() << " "
        << std::setw(2)  << GetCharge() << " "
        << std::setw(20) << pre.x() << " "
        << std::setw(20) << pre.y() << " "
        << std::setw(20) << pre.z() << " "
        //<< std::setw(20)  << GetMomentum().x() << " "
	//<< std::setw(20)  << GetMomentum().y() << " "
	//<< std::setw(20)  << GetMomentum().z() << " "
	<< std::setw(18) << GetTotalEnergy() << " "
	<< std::setw(20) << GetTof() << " "
        << std::endl;
  }
}

//=========================================================================
//* Draw ------------------------------------------------------------------
void J4MUDPreHit::Draw() { }

//=========================================================================
//* Print -----------------------------------------------------------------
void J4MUDPreHit::Print() { }
