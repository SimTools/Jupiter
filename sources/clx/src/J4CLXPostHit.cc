// $Id$
//*************************************************************************
//* --------------------
//* J4CLXPostHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4TPCDriftRegion.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2004/11/13  A.Yamaguchi	Original version.
//*	2006/05/01  H.Ono       Derived from J4CLAPostHit
//*************************************************************************
#include <iomanip>
#include "J4CLXPostHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------
J4CLXPostHitAllocator J4CLXPostHit::fgHitAllocator;
J4Output*             J4CLXPostHit::fgOutput        =  0;
G4int                 J4CLXPostHit::fgNhits         = -1;
J4CLXPostHit         *J4CLXPostHit::fgCurPostHitPtr =  0;

//=========================================================================
//* constructor -----------------------------------------------------------
J4CLXPostHit::J4CLXPostHit( J4VComponent         *detector,       // He is in "location" now
                            G4int                 preHitID,       // preHitID of the CLX surface
                            G4int                 trackID,        // TrackID
                            G4int                 mothertrackID,  // MotherTrackID
                            G4ParticleDefinition *particle,       // particle
                            G4double              tof,            // TOF 
                            G4double              totalE,         // Total energy
                            const G4ThreeVector  &momentum,       // Momentum of perticle
                            const G4ThreeVector  &post )           // Post-position of track
 : J4VHit(detector, trackID, mothertrackID, particle, tof, 0., totalE, momentum, 0., post ),
   fCLXPreHitID(preHitID)
{
  fCLXPostHitID = ++fgNhits;
}

//=========================================================================
//* destructor -----------------------------------------------------------
J4CLXPostHit::~J4CLXPostHit()
{
  fgNhits--;
}

//=========================================================================
//* Output ------------------------------------------------------------------
void J4CLXPostHit::Output(G4HCofThisEvent *)
{
  if (fgOutput) fgOutput->Output(this);
  // output hitdata to output file ....
#if 0
  std::ofstream& ofs = GetOutputFileStream();
  if (! ofs.good()) {
    G4String errorMessage= "J4CLXPostHit::Output(): write error.";
    G4Exception(errorMessage);
  } else {

     G4ThreeVector pos = GetPostPosition();

     ofs << "PostHit " 
         << std::setw(7) << fCLXPostHitID << " "
         << std::setw(7) << fCLXPreHitID << " "
         << std::setw(7) << GetTrackID() << " " 
         << std::setw(7) << GetMotherTrackID() << " " 
         << std::setw(6) << GetPDGEncoding() << " " 
         << std::setw(2) << GetCharge() << " " 
         << std::setiosflags(std::ios::scientific) << std::setprecision(14)
         << std::setw(18) << pos.x() << " " 
         << std::setw(18) << pos.y() << " " 
         << std::setw(18) << pos.z() << " "
         //<< std::setw(18) << GetMomentum().x() << " " 
         //<< std::setw(18) << GetMomentum().y() << " "
         //<< std::setw(18) << GetMomentum().z() << " " 
         << std::setw(18) << GetTotalEnergy() << " " 
         << std::setw(18) << GetTof() << " "
         << std::setiosflags(std::ios::floatfield) 
         << std::setprecision(8)
         << G4endl;
  }
#endif
}

//=========================================================================
//* Draw ------------------------------------------------------------------
void J4CLXPostHit::Draw() { }

//=========================================================================
//* Print -----------------------------------------------------------------
void J4CLXPostHit::Print()
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
