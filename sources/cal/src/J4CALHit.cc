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
//*************************************************************************

#include <iomanip>
#include "J4CALHit.hh"
#include "TVAddress.hh"
//#include "J4CALHitlet.hh"
//#include "J4CALPreHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------
J4CALHitAllocator J4CALHit::fgHitAllocator;
J4Output*         J4CALHit::fgOutput = 0;
 
//=========================================================================
//* constructor -----------------------------------------------------------
J4CALHit::J4CALHit()
  : J4VHit(0), /*fPreHitID(0),*/ fAddress(0), fCellEdep(0), fCellTof(0), fCellXcm(0)
{
}

J4CALHit::J4CALHit( J4VComponent* ptrDetector,    // He is in "location" now
		    //	    G4int         preHitID,       // pre Hit ID
      		    TVAddress*    ptrAddress,     // ptr to cell address
                    G4double      edep,           // Energy Deposit
                    G4double      tof,            // TOF
		    const G4ThreeVector& Xcm  )		    
  : J4VHit( ptrDetector ), /* fPreHitID( preHitID ),*/ fAddress( ptrAddress ),
    fCellEdep( edep ), fCellTof( tof ), fCellXcm( Xcm )
{
}

//=========================================================================
//* destructor -----------------------------------------------------------
J4CALHit::~J4CALHit()
{
}

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

    for ( G4int i = 0; i < GetNHitlets(); i++ ) {
      ofs << std::setw(3) << "cell: "
	  //<< std::setw(i+2) << GetNHitlets() << " "
	  << std::setw(i+2) << GetPreHitID(i) << " "
	  << std::setw(3) << fAddress -> GetConeID() << " "
	  << std::setw(3) << fAddress -> GetTowerID() << " "
	  << std::setw(3) << fAddress -> GetMiniConeID() << " "
	  << std::setw(3) << fAddress -> GetMiniTowerID() << " "
	  << std::setw(3) << fAddress -> GetLayerID() << " "
	  << std::setw(3) << fAddress -> GetSubLayerID() << " "
	  << std::setw(3) << fAddress -> IsBarrel() << " "
	  << std::setw(3) << fAddress -> IsEM() << " "
	  << std::setw(12) << GetHitletEdep(i) << " "
	  << std::setw(12) << GetHitletTof(i) << " "
	  << std::setw(12) << GetHitletXcm(i).x()  << " "
	  << std::setw(12) << GetHitletXcm(i).y()  << " "
	  << std::setw(12) << GetHitletXcm(i).z()  << " "
	  << std::endl;
    }
    //    ofs /* << std::setw(3) << fPreHitID << " " */
//	<< std::setw(3) << fAddress -> GetConeID() << " "
//        << std::setw(3) << fAddress -> GetTowerID() << " "
//        << std::setw(3) << fAddress -> GetMiniConeID() << " "
//        << std::setw(3) << fAddress -> GetMiniTowerID() << " "
//	<< std::setw(3) << fAddress -> GetLayerID() << " "
//	<< std::setw(3) << fAddress -> GetSubLayerID() << " "
//	<< std::setw(3) << fAddress -> IsBarrel() << " "
//	<< std::setw(3) << fAddress -> IsEM() << " "
//        << std::setw(12) << fCellEdep << " " 
//        << std::setw(12) << fCellTof << " "
//	<< std::setw(12) << fCellXcm.x() << " "
//	<< std::setw(12) << fCellXcm.y() << " "
//	<< std::setw(12) << fCellXcm.z() << " "
//        << std::endl;
  }
}

//=========================================================================
//* Draw ------------------------------------------------------------------

void J4CALHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------

void J4CALHit::Print()
{
  std::cout << std::setw(20) << GetComponentName() << " "
            << "energy(GeV)= " << std::setprecision(2)
            << std::setw(6) << fCellEdep *(1./GeV) << " "
            << "TOF(ns)= " << std::setw(4) << std::setprecision(1) 
            << fCellTof /ns 
            << std::endl;  
}
