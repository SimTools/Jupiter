// $Id$
//*************************************************************************
//* --------------------
//* J4CALHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4ITLayer.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*     2004/10/12  A.Sanchez   Make J4CALHit behave like J4CALHitlet.
//*************************************************************************
#include <iomanip>
#include "J4CALHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------
J4CALHitAllocator J4CALHit::fgHitAllocator;
J4Output*         J4CALHit::fgOutput = 0;
 
//=========================================================================
//* constructor -----------------------------------------------------------
J4CALHit::J4CALHit()
  : J4VHit(0), fPreHitID(0), fPDGCode(0), fCellID(0), fIsEM(0), fIsBarrel(0), fEdep(0), fTof(0), fXcm(0)
{ }

J4CALHit::J4CALHit( J4VComponent* ptrDetector,    // He is in "location" now
		    G4int         preHitID,       // pre Hit ID
		    G4int         pdgCode,       // preHit Track ID
      		    G4int         cellID,         // cell address id
		    G4bool        isEM,           // ( 0, 1 ) = ( HD, EM )
		    G4bool        isBarrel,       // ( 0, 1 ) = ( Endcap, barrel )
                    G4double      edep,           // Energy Deposit
                    G4double      tof,            // TOF
		    const G4ThreeVector& Xcm,     // Edep*position vector
		    const G4ThreeVector& Xcell )  // cell center position    
  : J4VHit( ptrDetector ), fPreHitID( preHitID ), fPDGCode( pdgCode ), fCellID( cellID ),
    fIsEM( isEM ), fIsBarrel( isBarrel ), fEdep( edep ), fTof( tof ), fXcm( Xcm ), fXcell( Xcell )
{ }

//=========================================================================
//* destructor -----------------------------------------------------------
J4CALHit::~J4CALHit()
{ }

//=========================================================================
//* Output ------------------------------------------------------------------

void J4CALHit::Output( G4HCofThisEvent* /* HCTE */ )
{
  if ( fgOutput ) fgOutput -> Output( this );
  // output hitdata to output file ....
        
  std::ofstream& ofs = GetOutputFileStream();
  if ( !ofs.good() ) {
    const G4String& errorMessage = "J4CALHit::Output(): write error.";
    G4cerr << errorMessage << G4endl;
  } else {
    ofs << std::setw(3) << fPreHitID << " "
	<< std::setw(5) << fPDGCode << " "
	<< std::setw(10) << fCellID << " "
	<< std::setw(2) << (G4int)fIsEM << " "
	<< std::setw(2) << (G4int)fIsBarrel << " "
	<< std::setw(12) << fEdep << " "
	<< std::setw(12) << fTof << " "
	<< std::setw(12) << GetXcm().x()  << " "
	<< std::setw(12) << GetXcm().y()  << " "
	<< std::setw(12) << GetXcm().z()  << " "
	<< std::setw(12) << GetXcell().x() << " "
	<< std::setw(12) << GetXcell().y() << " "
	<< std::setw(12) << GetXcell().z() << " "
	<< std::endl;
  }
}

//=========================================================================
//* Draw ------------------------------------------------------------------

void J4CALHit::Draw()
{ }

//=========================================================================
//* Print -----------------------------------------------------------------

void J4CALHit::Print()
{
  std::cout << "J4CALHit--------------------" << std::endl;
  std::cout << std::setw(3) << " PreHitID=" << fPreHitID << " "
	    << std::setw(5) << " PDGCode=" << fPDGCode << " "
	    << std::setw(10) << " CellID=" << fCellID << " "
	    << std::setw(2) << " EM=" << (G4int)fIsEM << " "
	    << std::setw(2) << " Barrel=" << (G4int)fIsBarrel << " "
	    << std::setw(12) << " Edep=" << fEdep << " "
	    << std::setw(12) << " TOF="<< fTof << " "
	    << std::setw(12) << "Xcm=(" << GetXcm().x()  << ", "
	    << std::setw(12) << GetXcm().y()  << ", "
	    << std::setw(12) << GetXcm().z()  << ") "
	    << std::setw(12) << "Xcell=(" << GetXcell().x() << ", "
	    << std::setw(12) << GetXcell().y() << ", "
	    << std::setw(12) << GetXcell().z() << ") "
	    << std::endl;
}
