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
J4Output*             J4CALHit::fOutput = 0 ;

//=========================================================================
//* constructor -----------------------------------------------------------

J4CALHit::J4CALHit(
                   J4VComponent         *detector,       // He is in "location" now
                   G4int                 thetaNumber,    // section No. in theta  
                   G4int                 phiNumber,      // section No. in phi
                   G4bool                isbarrel,       // (0, 1) = (endcap, barrel) 
                   G4bool                isEM,           // (0, 1) = (EM, Hadron) 
                   G4double              edep,           // Energy Deposit
                   G4double              tof,            // TOF 
                   const G4ThreeVector  &pre,            // Pre-position of track
                   G4int                 mothertrackID,  // Mother track id
                   G4int                 trackID,        // My track id 
                   G4ParticleDefinition *particle)       // My particle definision 

             : J4VHit(detector), fThetaNumber(thetaNumber), fPhiNumber(phiNumber),
               fIsBarrel(isbarrel), fIsEM(isEM), fEnergyDep(edep), fTof(tof), fInjectionPoint(pre), 
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

void J4CALHit::Output(G4HCofThisEvent* HCTE)
{
  if (fOutput) fOutput->Output(this);
  // output hitdata to output file ....
        
  std::ofstream& ofs = GetOutputFileStream();
  if (! ofs.good()) {
    G4String errorMessage= "J4CALHit::Output(): write error.";
    G4Exception(errorMessage);
  } else {

     ofs << std::setw(7) << fThetaNumber << " " 
         << std::setw(7) << fPhiNumber << " " 
         << std::setw(3) << fIsBarrel << " " 
         << std::setw(3) << fIsEM << " " 
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
         << G4endl;
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

  G4cout << std::setiosflags(std::ios::fixed);
  G4cout << std::setw(20) << GetComponentName() << " " << G4endl;
  G4cout << " track#=" << fTrackID
         << " charge=" << fParticle->GetPDGCharge()
         << " energy(GeV)= " << std::setprecision(2) 
         << std::setw(6) << fEnergyDep *(1./GeV) << " "
         << " TOF(ns)= " << std::setw(4) << std::setprecision(1) 
         << fTof /ns 
         << G4endl;  
}

