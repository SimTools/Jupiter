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
#include "TVAddress.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------
J4CALHitAllocator J4CALHit::fgHitAllocator;
J4Output*         J4CALHit::fgOutput = 0;
 
//=========================================================================
//* constructor -----------------------------------------------------------
J4CALHit::J4CALHit()
  : J4VHit(0), fPreHitID(0), fCellID(0), fIsEM(0), fIsBarrel(0), fEdep(0), fTof(0), fXcm(0)
{ }

J4CALHit::J4CALHit( J4VComponent* ptrDetector,    // He is in "location" now
		    G4int         preHitID,       // pre Hit ID
		    G4int         preTrkID,       // preHit Track ID
      		    G4int         cellID,         // cell address id
		    G4bool        isEM,           // ( 0, 1 ) = ( HD, EM )
		    G4bool        isBarrel,       // ( 0, 1 ) = ( Endcap, barrel )
                    G4double      edep,           // Energy Deposit
                    G4double      tof,            // TOF
		    const G4ThreeVector& Xcm  )		    
  : J4VHit( ptrDetector ), fPreHitID( preHitID ), fPreTrkID( preTrkID ), fCellID( cellID ),
    fIsEM( isEM ), fIsBarrel( isBarrel ), fEdep( edep ), fTof( tof ), fXcm( Xcm )
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
    ofs << "iPiTiCiTMcMtiLiSiEiBETXYZ: "
	<< std::setw(3) << fPreHitID << " "
	<< std::setw(5) << fPreTrkID << " "
	<< std::setw(3) << TVAddress::GetCellConeID( fCellID ) << " "
	<< std::setw(3) << TVAddress::GetCellTowerID( fCellID ) << " "
	<< std::setw(3) << TVAddress::GetCellMiniConeID( fCellID, fIsEM ) << " "
	<< std::setw(3) << TVAddress::GetCellMiniTowerID( fCellID, fIsEM ) << " "
	<< std::setw(3) << TVAddress::GetCellLayerID( fCellID, fIsEM ) << " "
	<< std::setw(3) << TVAddress::GetCellSubLayerID( fCellID, fIsEM ) << " "
	<< std::setw(2) << (G4int)fIsEM << " "
	<< std::setw(2) << (G4int)fIsBarrel << " "
	<< std::setw(12) << fEdep << " "
	<< std::setw(12) << fTof << " "
	<< std::setw(12) << GetXcm().x()  << " "
	<< std::setw(12) << GetXcm().y()  << " "
	<< std::setw(12) << GetXcm().z()  << " "
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

}
