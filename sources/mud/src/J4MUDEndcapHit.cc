// $Id$
//*************************************************************************
//* --------------------
//* J4MUDEndcapHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4MUDEndcap.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************
#include <iomanip>
#include "J4MUDEndcapHit.hh"
#include "J4MUDParameterList.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------
J4MUDEndcapHitAllocator J4MUDEndcapHit::fHitAllocator ;
J4Output*             J4MUDEndcapHit::fOutput = 0 ;

//=========================================================================
//* constructor -----------------------------------------------------------
J4MUDEndcapHit::J4MUDEndcapHit(
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
J4MUDEndcapHit::~J4MUDEndcapHit() { }


//=========================================================================
//* Output ------------------------------------------------------------------
void J4MUDEndcapHit::Output(G4HCofThisEvent* /* HCTE */)
{
  if (fOutput) fOutput->Output(this);
  // output hitdata to output file ....

  std::ofstream& ofs = GetOutputFileStream();
  if (! ofs.good()) {
    G4String errorMessage= "J4MUDEndcapHit::Output(): write error.";
    G4Exception(errorMessage);
  } else {
     G4ThreeVector pre  = GetPrePosition();
     G4ThreeVector post = GetPostPosition();


     G4int nLayers = J4MUDParameterList::GetInstance()->GetNEndcapLayers();
     G4int myid = GetComponent()->GetMyID();

     if ( myid < nLayers ) {
       ofs << std::setw(8) << "EndcapR:";
     } else {
       ofs << std::setw(8) << "EndcapL:";
       myid -= nLayers;
     }
     
     ofs << std::setw(1) << myid << " "
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
void J4MUDEndcapHit::Draw() { }

//=========================================================================
//* Print -----------------------------------------------------------------
void J4MUDEndcapHit::Print()
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

