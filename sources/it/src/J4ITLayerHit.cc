// $Id$
//*************************************************************************
//* --------------------
//* J4ITLayerHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4ITLayer.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include <iomanip>
#include "J4ITLayerHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J4ITLayerHitAllocator J4ITLayerHit::fHitAllocator ;
J4Output*             J4ITLayerHit::fOutput = 0 ;

//=========================================================================
//* constructor -----------------------------------------------------------

J4ITLayerHit::J4ITLayerHit(
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
             : J4VTrackerHit(detector, trackID, mothertrackID, particle,
                      tof, edep, totalE, momentum, pre, pos)
{
}

//=========================================================================
//* destructor -----------------------------------------------------------

J4ITLayerHit::~J4ITLayerHit()
{
}


//=========================================================================
//* Output ------------------------------------------------------------------

void J4ITLayerHit::Output(G4HCofThisEvent* HCTE)
{
  if (fOutput) fOutput->Output(this);
  // output hitdata to output file ....
        
  G4std::ofstream& ofs = GetOutputFileStream();
  if (! ofs.good()) {
    G4String errorMessage= "J4ITLayerHit::Output(): write error.";
    G4Exception(errorMessage);
  } else {

     G4ThreeVector pre  = GetPrePosition();
     G4ThreeVector post = GetPostPosition();

     ofs << G4std::setw(1) << GetComponent()->GetMyID() << " " 
         << G4std::setw(7) << GetTrackID() << " " 
         << G4std::setw(7) << GetMotherTrackID() << " " 
         << G4std::setw(6) << GetPDGEncoding() << " " 
         << G4std::setw(2) << GetCharge() << " " 
         << G4std::setiosflags(G4std::ios::scientific) << G4std::setprecision(14)
         << G4std::setw(18) << pre.x() << " " 
         << G4std::setw(18) << pre.y() << " " 
         << G4std::setw(18) << pre.z() << " "
         << G4std::setw(18) << post.x() << " " 
         << G4std::setw(18) << post.y() << " " 
         << G4std::setw(18) << post.z() << " "
         << G4std::setw(18) << GetMomentum().x() << " " 
         << G4std::setw(18) << GetMomentum().y() << " "
         << G4std::setw(18) << GetMomentum().z() << " " 
         << G4std::setw(18) << GetTotalEnergy() << " " 
         << G4std::setw(18) << GetEnergyDeposit() << " " 
         << G4std::setw(18) << GetTof() << " "
         << G4std::setiosflags(G4std::ios::floatfield) 
         << G4std::setprecision(8)
         << G4endl;
  }

	
}

//=========================================================================
//* Draw ------------------------------------------------------------------

void J4ITLayerHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------

void J4ITLayerHit::Print()
{


  G4cout << G4std::setiosflags(G4std::ios::fixed);
  G4cout << G4std::setw(20) << GetComponentName() << " " << G4endl;
  G4cout << " track#=" << GetTrackID()
         << " charge=" << GetCharge()
         << " energy(GeV)= " << G4std::setprecision(2) 
         << G4std::setw(6) << GetTotalEnergy() *(1./GeV) << " "
         << " TOF(ns)= " << G4std::setw(4) << G4std::setprecision(1) 
         << GetTof() /ns 
         << G4endl;  
}

