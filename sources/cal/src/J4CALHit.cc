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

//=========================================================================
//---------------------
// Allocator
//---------------------

J4CALHitAllocator J4CALHit::fHitAllocator ;
J4Output*         J4CALHit::fOutput = 0 ;
 
//=========================================================================
//* constructor -----------------------------------------------------------
J4CALHit::J4CALHit(
                   J4VComponent         *detector,       // He is in "location" now
                   G4int                 ConeID,         // Cone ID  
                   G4int                 TowerID,        // Tower ID
                   G4int                 MiniConeID,     // MiniCone ID 
                   G4int                 MiniTowerID,    // MiniTower ID 
                   G4int                 LayerID,        // Layer ID 
                   G4int                 SubLayerID,     // SubLayer ID 
                   G4bool                isBarrel,       // (0, 1) = (endcap, barrel) 
                   G4bool                isEM,           // (0, 1) = (HD, EM) 
                   G4double              edep,           // Energy Deposit
                   G4double              tof,            // TOF 
                   const G4ThreeVector  &pre,            // Pre-position of track
                   G4int                 mothertrackID,  // Mother track id
                   G4int                 trackID,        // My track id 
                   G4ParticleDefinition *particle )      // My particle definision 
 : J4VHit(detector), 
   fConeID(ConeID), fTowerID(TowerID),
   fMiniConeID(MiniConeID), fMiniTowerID(MiniTowerID), 
   fLayerID(LayerID), fSubLayerID(SubLayerID),
   fIsBarrel(isBarrel), fIsEM(isEM),
   fEnergyDep(edep), fTof(tof), fInjectionPoint(pre),
   fMotherTrackID(mothertrackID), fTrackID(trackID), fParticle(particle)
{
}

//=========================================================================
//* destructor -----------------------------------------------------------

J4CALHit::~J4CALHit()
{
}


//=========================================================================
//* Output ------------------------------------------------------------------

void J4CALHit::Output(G4HCofThisEvent* /* HCTE */ )
{
  if ( fOutput ) fOutput->Output( this );
  // output hitdata to output file ....
        
  std::ofstream& ofs = GetOutputFileStream();
  if ( !ofs.good() ) {
    const G4String& errorMessage = "J4CALHit::Output(): write error.";
    G4cerr << errorMessage << G4endl;
  } else {
     ofs << std::setw(3) << fConeID  << " " 
         << std::setw(3) << fTowerID << " " 
         << std::setw(2) << fMiniConeID << " " 
         << std::setw(2) << fMiniTowerID << " " 
         << std::setw(3) << fLayerID << " " 
         << std::setw(2) << fSubLayerID << " " 
         << std::setw(2) << fIsBarrel << " " 
         << std::setw(2) << fIsEM << " " 
         << std::setw(7) << fMotherTrackID << " " 
         << std::setw(7) << fTrackID << " " 
         << std::setw(6) << fParticle->GetPDGEncoding() << " " 
         << std::setw(2) << fParticle->GetPDGCharge() << " " 
         << std::setiosflags(std::ios::scientific) << std::setprecision(14)
         << std::setw(18) << fEnergyDep << " " 
         << std::setw(18) << fTof << " "
         << std::setw(18) << fInjectionPoint.x() << " " 
         << std::setw(18) << fInjectionPoint.y() << " " 
         << std::setw(18) << fInjectionPoint.z() << " "
         << std::setiosflags(std::ios::floatfield) 
         << std::setprecision(8)
         << std::endl;
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
  std::cout << std::setiosflags(std::ios::fixed);
  std::cout << std::setw(20) << GetComponentName() << " " << std::endl;
  std::cout << " track#=" << fTrackID
         << " charge=" << fParticle->GetPDGCharge()
         << " energy(GeV)= " << std::setprecision(2) 
         << std::setw(6) << fEnergyDep *(1./GeV) << " "
         << " TOF(ns)= " << std::setw(4) << std::setprecision(1) 
         << fTof /ns 
         << std::endl;  
}
