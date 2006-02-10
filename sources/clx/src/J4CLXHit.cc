// $Id$
//*************************************************************************
//* --------------------
//* J4CLXHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4ITLayer.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*     2004/10/12  A.Sanchez   Make J4CLXHit behave like J4CLXHitlet.
//*     2004/11/01  Allister Sanchez  Remove redundant data/functions which are in J4VHit.
//*************************************************************************
#include <iomanip>
#include "J4CLXHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------
J4CLXHitAllocator J4CLXHit::fgHitAllocator;
J4Output*         J4CLXHit::fgOutput = 0;
 
//=========================================================================
//* constructor -----------------------------------------------------------
J4CLXHit::J4CLXHit()
  : J4VHit(0), fCellID(0), fXcm(0)
{ }

J4CLXHit::J4CLXHit( J4VComponent* ptrDetector,    // He is in "location" now
		    G4int preHitID,
		    G4int         layerID,
		    G4int         cellID,
		    G4bool        isEM,
		    const G4ThreeVector& cellPosition,
                    G4double      edep,           // Energy Deposit
                    G4double      tof,            // TOF
		    G4ParticleDefinition* particle, // Particle data
		    const G4ThreeVector& Xcm)     // Edep*position vector
  // detector, trackID, motherTrackID, particle, tof, edep, totalE
  : J4VHit(ptrDetector, -9999, -9999, particle, tof, edep),
    fPreHitID(preHitID), fLayerID(layerID), fCellID(cellID), fIsEM(isEM),
    fCellPosition(cellPosition), fXcm(Xcm)
{ }

//=========================================================================
//* destructor -----------------------------------------------------------
J4CLXHit::~J4CLXHit()
{ }

//=========================================================================
//* Output ------------------------------------------------------------------

void J4CLXHit::Output( G4HCofThisEvent* /* HCTE */ )
{
  if ( fgOutput ) fgOutput -> Output( this );
  // output hitdata to output file ....

  std::ofstream& ofs = GetOutputFileStream();
  if ( !ofs.good() ) {
    const G4String& errorMessage = "J4CLXHit::Output(): write error.";
    G4cerr << errorMessage << G4endl;
  } else {
    ofs << "clxhit "
	<< std::setw(3)  << fPreHitID << " "
	<< std::setw(5)  << GetPDGEncoding() << " "
	<< std::setw(4)  << std::setfill('0') << fLayerID << " "
	<< std::setw(7)  << std::setfill('0') << fCellID << " "
	<< std::setw(2)  << std::setfill(' ') <<(G4int)fIsEM << " "
	<< std::setw(12) << GetEnergyDeposit() << " "
	<< std::setw(12) << GetTof() << " "
	<< std::setw(12) << fXcm.x()  << " "
	<< std::setw(12) << fXcm.y()  << " "
	<< std::setw(12) << fXcm.z()  << " "
	<< std::setw(12) << fCellPosition.x() << " "
	<< std::setw(12) << fCellPosition.y() << " "
	<< std::setw(12) << fCellPosition.z() << " "
	<< std::endl;
  }
}

//=========================================================================
//* Draw ------------------------------------------------------------------

void J4CLXHit::Draw()
{ }

//=========================================================================
//* Print -----------------------------------------------------------------

void J4CLXHit::Print()
{
  std::cout << "J4CLXHit--------------------" << std::endl;
  std::cout << std::setw(3) << " PreHitID=" << fCellID << " "
	    << std::setw(12) << " Edep=" << GetEnergyDeposit() << " "
	    << std::setw(12) << " TOF="<< GetTof() << " "
	    << std::setw(12) << "Xcm=(" << fXcm.x()  << ", "
	    << std::setw(12) << fXcm.y()  << ", "
	    << std::setw(12) << fXcm.z()  << ") "
	    << std::endl;
}
