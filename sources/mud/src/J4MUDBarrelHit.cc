// $Id$
//*************************************************************************
//* --------------------
//* J4MUDBarrelHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4MUDBarrel.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************
#include <iomanip>
#include "J4MUDBarrelHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------
J4MUDBarrelHitAllocator J4MUDBarrelHit::fHitAllocator ;
J4Output*             J4MUDBarrelHit::fOutput = 0 ;

//=========================================================================
//* constructor -----------------------------------------------------------
J4MUDBarrelHit::J4MUDBarrelHit(
                   J4VComponent         *detector,       // He is in "location" now
                   G4int                 trackID,        // TrackID
                   G4int                 mothertrackID,  // MotherTrackID
                   G4ParticleDefinition *particle,       // particle
                   G4double              tof,            // TOF 
                   G4double              edep,           // Energy Deposit
                   G4double              totalE,         // Total energy
                   const G4ThreeVector  &momentum,       // Momentum of perticle
                   const G4ThreeVector  &pre,            // Pre-position of track
                   const G4ThreeVector  &pos )           // Post-position of track
 : J4VTrackerHit( detector, trackID, mothertrackID, particle, tof, edep, totalE, momentum, pre, pos )
{ }

//=========================================================================
//* destructor -----------------------------------------------------------
J4MUDBarrelHit::~J4MUDBarrelHit() { }

//=========================================================================
//* Output ------------------------------------------------------------------
void J4MUDBarrelHit::Output(G4HCofThisEvent* /* HCTE */)
{
  if (fOutput) fOutput->Output(this);
  // output hitdata to output file ....

  std::ofstream& ofs = GetOutputFileStream();
  if (! ofs.good()) {
    G4String errorMessage= "J4MUDBarrelHit::Output(): write error.";
    G4Exception(errorMessage);
  } else {

     G4ThreeVector pre  = GetPrePosition();
     G4ThreeVector post = GetPostPosition();

     ofs << std::setw(8) << "Barrel:"
         << std::setw(1) << GetComponent()->GetMyID() << " " 
         << std::setw(7) << GetTrackID() << " " 
         << std::setw(7) << GetMotherTrackID() << " " 
         << std::setw(6) << GetPDGEncoding() << " " 
         << std::setw(2) << GetCharge() << " " 
         << std::setiosflags(std::ios::scientific) << std::setprecision(14)
         << std::setw(18) << pre.x() << " " 
         << std::setw(18) << pre.y() << " " 
         << std::setw(18) << pre.z() << " "
         << std::setw(18) << post.x() << " " 
         << std::setw(18) << post.y() << " " 
         << std::setw(18) << post.z() << " "
         << std::setw(18) << GetMomentum().x() << " " 
         << std::setw(18) << GetMomentum().y() << " "
         << std::setw(18) << GetMomentum().z() << " " 
         << std::setw(18) << GetTotalEnergy() << " " 
         << std::setw(18) << GetEnergyDeposit() << " " 
         << std::setw(18) << GetTof() << " "
         << std::setiosflags(std::ios::floatfield) 
         << std::setprecision(8)
         << G4endl;
  }
}

//=========================================================================
//* Draw ------------------------------------------------------------------
void J4MUDBarrelHit::Draw() { }

//=========================================================================
//* Print -----------------------------------------------------------------
void J4MUDBarrelHit::Print()
{

  G4cout << std::setiosflags(std::ios::fixed);
  G4cout << std::setw(20) << GetComponentName() << " " << G4endl;
  G4cout << " track#=" << GetTrackID()
         << " charge=" << GetCharge()
         << " energy(GeV)= " << std::setprecision(2) 
         << std::setw(6) << GetTotalEnergy() *(1./GeV) << " "
         << " TOF(ns)= " << std::setw(4) << std::setprecision(1) 
         << GetTof() /ns 
         << G4endl;  
}
