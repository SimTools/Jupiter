//*************************************************************************
//* --------------------
//* J4TPCPostHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4TPCDriftRegion.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2004/11/13  A.Yamaguchi	Original version.
//*************************************************************************

#include <iomanip>
#include "J4TPCPostHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J4TPCPostHitAllocator J4TPCPostHit::fgHitAllocator;
J4Output*             J4TPCPostHit::fgOutput        =  0;
G4int                 J4TPCPostHit::fgNhits         = -1;
J4TPCPostHit         *J4TPCPostHit::fgCurPostHitPtr =  0;


//=========================================================================
//* constructor -----------------------------------------------------------

J4TPCPostHit::J4TPCPostHit(
                   J4VComponent         *detector,       // He is in "location" now
                   G4int                 trackID,        // TrackID
                   G4int                 mothertrackID,  // MotherTrackID
                   G4ParticleDefinition *particle,       // particle
                   G4double              tof,            // TOF 
                   G4double              totalE,         // Total energy
                   const G4ThreeVector  &momentum,       // Momentum of perticle
                   const G4ThreeVector  &pos )           // Post-position of track
             : J4VTrackerHit(detector, trackID, mothertrackID, particle,
                      tof, 0., totalE, momentum, pos, pos)
{
  fPostHitID = ++fgNhits;
}

//=========================================================================
//* destructor -----------------------------------------------------------

J4TPCPostHit::~J4TPCPostHit()
{
  fgNhits--;
}


//=========================================================================
//* Output ------------------------------------------------------------------

void J4TPCPostHit::Output(G4HCofThisEvent *)
{
  if (fgOutput) fgOutput->Output(this);
  // output hitdata to output file ....
        
  std::ofstream& ofs = GetOutputFileStream();
  if (! ofs.good()) {
    G4String errorMessage= "J4TPCPostHit::Output(): write error.";
    G4Exception(errorMessage);
  } else {

     G4ThreeVector pos = GetPostPosition();

     ofs << "PostHit " 
         << std::setw(7) << fPostHitID << " "
         << std::setw(7) << GetTrackID() << " " 
         << std::setw(7) << GetMotherTrackID() << " " 
         << std::setw(6) << GetPDGEncoding() << " " 
         << std::setw(2) << GetCharge() << " " 
         << std::setiosflags(std::ios::scientific) << std::setprecision(14)
         << std::setw(18) << pos.x() << " " 
         << std::setw(18) << pos.y() << " " 
         << std::setw(18) << pos.z() << " "
         << std::setw(18) << GetMomentum().x() << " " 
         << std::setw(18) << GetMomentum().y() << " "
         << std::setw(18) << GetMomentum().z() << " " 
         << std::setw(18) << GetTotalEnergy() << " " 
         << std::setw(18) << GetTof() << " "
         << std::setiosflags(std::ios::floatfield) 
         << std::setprecision(8)
         << G4endl;
  }

	
}

//=========================================================================
//* Draw ------------------------------------------------------------------

void J4TPCPostHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------

void J4TPCPostHit::Print()
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

