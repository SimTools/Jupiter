// $Id$
//*************************************************************************
//* --------------------
//* J4OptDetHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4IRFCAL
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*     2006/06/04 A.Miyamoto Original Version
//*************************************************************************
#include <iomanip>
#include "J4OptDetHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------
J4OptDetHitAllocator J4OptDetHit::fgHitAllocator;
J4Output*         J4OptDetHit::fgOutput = 0;
 
//=========================================================================
//* constructor -----------------------------------------------------------
J4OptDetHit::J4OptDetHit()
  : J4VHit(0)
{ }

//=========================================================================
J4OptDetHit::J4OptDetHit(J4VComponent         *detector,      // Belonging Component 
	       G4int                 detid, // Detector ID		 
               G4int                 serialid,	    // 
               G4int                 trackID,	    // TrackID
               G4int                 mothertrackID, // MotherTrackID
               G4ParticleDefinition *particle,	    // particle
               G4double              tof,           // TOF 
               G4double              edep,          // Energy Deposit
               G4double              totalE,        // Total energy
               const G4ThreeVector  &p,             // Momentum of perticle
               const G4ThreeVector  &pre,           // Pre-position of track
               const G4ThreeVector  &pos,           // Post-position of track
               G4int                 hitnumber)
  : J4VHit(detector, trackID, mothertrackID, particle, tof, edep, totalE,
	   p, pre, pos, hitnumber), fDetID(detid), fDetSerialID(serialid)
{
}


//=========================================================================
//* destructor -----------------------------------------------------------
J4OptDetHit::~J4OptDetHit()
{ }

//=========================================================================
//* Output ------------------------------------------------------------------

void J4OptDetHit::Output( G4HCofThisEvent* /* HCTE */ )
{


  if ( fgOutput ) fgOutput -> Output( this );
  // output hitdata to output file ....
        
  std::ofstream& ofs = GetOutputFileStream();
  if ( !ofs.good() ) {
    const G4String& errorMessage = "J4OptDetHit::Output(): write error.";
    G4cerr << errorMessage << G4endl;
  } else {
    ofs << "opthit "
        << std::setw(5) << GetDetID() << " "
        << std::setw(5) << GetDetSerialID() << " "
        << std::setw(5)  << GetTrackID() << " "
        << std::setw(5)  << GetMotherTrackID() << " "
        << std::setw(5)  << GetHitNumber() << " "
        << std::setw(5)  << GetPDGEncoding() << " "
	<< std::setw(12) << GetEnergyDeposit() << " "
	<< std::setw(12) << GetTotalEnergy() << " "
	<< std::setw(12) << GetTof() << " "
	<< std::setw(12) << GetMomentum().x()  << " "
	<< std::setw(12) << GetMomentum().y()  << " "
	<< std::setw(12) << GetMomentum().z()  << " "
	<< std::setw(12) << GetPrePosition().x()  << " "
	<< std::setw(12) << GetPrePosition().y()  << " "
	<< std::setw(12) << GetPrePosition().z()  << " "
	<< std::setw(12) << GetPostPosition().x()  << " "
	<< std::setw(12) << GetPostPosition().y()  << " "
	<< std::setw(12) << GetPostPosition().z()  << " "
	<< std::endl;
  }
}

//=========================================================================
//* Draw ------------------------------------------------------------------

void J4OptDetHit::Draw()
{ }

//=========================================================================
//* Print -----------------------------------------------------------------

void J4OptDetHit::Print()
{
  std::cout << "J4OptDetHit--------------------" << std::endl;
  std::cout 
    << std::setw(5) << "Detector ID=" << GetDetID() << " "
    << std::setw(5) << " SerialID=" << GetDetSerialID() << " "
    << std::setw(5)  << " TrackID=" << GetTrackID() << " "
    << std::setw(5) << " MotherTrackID=" << GetMotherTrackID() << " "
    << std::setw(5) << " HitNumber="  << GetHitNumber() << " "
    << std::setw(5)  << " PDGCode=" << GetPDGEncoding() << " "
    << std::setw(12) << " EnergyDeposit(MeV)" << GetEnergyDeposit()/MeV << " "
    << std::setw(12) << " TotalEnergy(GeV)" << GetTotalEnergy()/GeV << " "
    << std::setw(12) << " Tof(ns)" << GetTof()/nanosecond  
    << std::endl;
  std::cout
    << std::setw(12) << " P(GeV)=("<< GetMomentum().x()/GeV  << ","
    << std::setw(12) << GetMomentum().y()/GeV  << ","
    << std::setw(12) << GetMomentum().z()/GeV  << "), "
    << std::setw(12) << " PrePos(cm)=(" << GetPrePosition().x()/cm  << ","
	<< std::setw(12) << GetPrePosition().y()/cm  << ","
	<< std::setw(12) << GetPrePosition().z()/cm  << "), "
    << std::setw(12) << " PostPos(cm)=("<< GetPostPosition().x()/cm  << ","
	<< std::setw(12) << GetPostPosition().y()/cm  << ","
	<< std::setw(12) << GetPostPosition().z()/cm  << ") "
	<< std::endl;
}
