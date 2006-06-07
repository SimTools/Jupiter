// $Id$
//*************************************************************************
//* --------------------
//* J4IRBCALHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4IRBCAL
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*     2006/01/28 A.Miyamoto Original Version, copied from J4CALHit
//*************************************************************************
#include <iomanip>
#include "J4IRBCALHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------
J4IRBCALHitAllocator J4IRBCALHit::fgHitAllocator;
J4Output*         J4IRBCALHit::fgOutput = 0;
 
//=========================================================================
//* constructor -----------------------------------------------------------
J4IRBCALHit::J4IRBCALHit()
  : J4VHit(0), fCellID(0), fXcm(0), fXhit(0)
{ }

J4IRBCALHit::J4IRBCALHit( J4VComponent* ptrDetector,    // He is in "location" now
				 G4int         preHitID,       // PreHitID
      		    G4int         cellID,         // cell address id
                    G4double      edep,           // Energy Deposit
                    G4double      tof,            // TOF
		    G4ParticleDefinition* particle, // Particle data
		    const G4ThreeVector& Xcm,     // Edep*position vector
		    const G4ThreeVector& Xhit,   // 1st hit of the cell
		    G4int         trackID,        // TrackID of inside particle
		    G4int         motherTrackID ) // mother track's ID
  // detector, trackID, motherTrackID, particle, tof, edep, totalE
  : J4VHit(ptrDetector, trackID, motherTrackID, particle, tof, edep),
    fPreHitID(preHitID), fCellID(cellID), fXcm(Xcm), fXhit(Xhit)
{ }

//=========================================================================
//* destructor -----------------------------------------------------------
J4IRBCALHit::~J4IRBCALHit()
{ }

//=========================================================================
//* Output ------------------------------------------------------------------

void J4IRBCALHit::Output( G4HCofThisEvent* /* HCTE */ )
{


  if ( fgOutput ) fgOutput -> Output( this );
  // output hitdata to output file ....
        
  std::ofstream& ofs = GetOutputFileStream();
  if ( !ofs.good() ) {
    const G4String& errorMessage = "J4IRBCALHit::Output(): write error.";
    G4cerr << errorMessage << G4endl;
  } else {
    ofs << "bcalhit "
        << std::setw(5) << GetPDGEncoding() << " "
	<< std::setw(10) << fPreHitID << " "
	<< std::setw(10) << fCellID << " "
	<< std::setw(12) << GetEnergyDeposit() << " "
	<< std::setw(12) << GetTof() << " "
	<< std::setw(12) << fXcm.x()  << " "
	<< std::setw(12) << fXcm.y()  << " "
	<< std::setw(12) << fXcm.z()  << " "
	<< std::setw(12) << fXhit.x() << " "
	<< std::setw(12) << fXhit.y() << " "
	<< std::setw(12) << fXhit.z() << " "
        << std::setw(5)  << GetTrackID() << " "
        << std::setw(5)  << GetMotherTrackID() << " "
	<< std::endl;
  }
}

//=========================================================================
//* Draw ------------------------------------------------------------------

void J4IRBCALHit::Draw()
{ }

//=========================================================================
//* Print -----------------------------------------------------------------

void J4IRBCALHit::Print()
{
  std::cout << "J4IRBCALHit--------------------" << std::endl;
  std::cout 
	    << std::setw(5) << " PDGCode=" << GetPDGEncoding() << " "
	    << std::setw(10) << " PreHitID=" << fPreHitID << " "
	    << std::setw(10) << " CellID=" << fCellID << " "
	    << std::setw(12) << " Edep=" << GetEnergyDeposit() << " "
	    << std::setw(12) << " TOF="<< GetTof() << " "
	    << std::setw(12) << "Xcm=(" << fXcm.x()  << ", "
	    << std::setw(12) << fXcm.y()  << ", "
	    << std::setw(12) << fXcm.z()  << ") "
	    << std::setw(12) << "1stHit=(" << fXhit.x() << ", "
	    << std::setw(12) << fXhit.y() << ", "
	    << std::setw(12) << fXhit.z() << ") "
	    << std::setw(5)  << GetTrackID() << " "
	    << std::setw(5)  << GetMotherTrackID() << " "
	    << std::endl;
}
