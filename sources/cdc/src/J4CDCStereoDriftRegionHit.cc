// $Id$
//*************************************************************************
//* --------------------
//* J4CDCStereoDriftRegionHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4CDCStereoDriftRegion.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include <iomanip>
#include <math.h>
#include "J4CDCStereoDriftRegionHit.hh"
#include "J4CDCStereoDriftRegion.hh"

using namespace std;

//=========================================================================
//---------------------
// Allocator
//---------------------

J4CDCStereoDriftRegionHitAllocator J4CDCStereoDriftRegionHit::fHitAllocator ;
J4Output *J4CDCStereoDriftRegionHit::fOutput = 0;

//=========================================================================
//* constructor -----------------------------------------------------------

J4CDCStereoDriftRegionHit::J4CDCStereoDriftRegionHit(
     J4VComponent         *detector,      // Belonging DetectorComponent
     G4int                 cloneID,       // CloneID
     G4int                 trackID,       // TrackID
     G4int                 mothertrackID, // MotherTrackID
     G4ParticleDefinition *particle,      // Particle
     G4double              tof,           // TOF
     G4double              edep,          // Energy Deposit
     G4double              totalE,        // Total energy
     const G4ThreeVector  &momentum,      // Momentum of perticle
     const G4ThreeVector  &pre,           // Pre-position of track
     const G4ThreeVector  &pos,           // Post-position of track
     G4double              rotangle,      // rotation angle of cell 
     const G4ThreeVector  &wireEndpz,     // wire position at +ve z endcap
     const G4ThreeVector  &wireEndmz,     // wire position at -ve z endcap
     G4double              tanstereo,     // stereo angle of cell 
     G4double              rwaist,        // waist radius of sense wire surface 
     const G4int           hitnumber)     // unique hit number
   : J4VCDCDriftRegionHit(detector, cloneID, trackID, mothertrackID, particle, 
                          tof, edep, totalE, momentum, pre, pos, rotangle,
                          wireEndpz, wireEndmz, tanstereo, rwaist, hitnumber)
{
}

//=========================================================================
//* destructor -----------------------------------------------------------

J4CDCStereoDriftRegionHit::~J4CDCStereoDriftRegionHit()
{
}

//=========================================================================
//* Output ----------------------------------------------------------------

void J4CDCStereoDriftRegionHit::Output(G4HCofThisEvent* HCTE)
{

  if (fOutput) fOutput->Output(this);

  J4VCDCDriftRegion *cpt = (J4VCDCDriftRegion *)GetComponent();

  G4int         wireNo   = cpt->GetMyID();
  G4int         layerNo  = cpt->GetGlobalLayerNumber();
  G4double      dphi     = cpt->GetDeltaPhi(cpt);
  G4double      sphi     = -0.5 * dphi;

  G4int         cellID   = GetCloneID();
  G4String      pname    = GetParticle()->GetParticleName();
  G4int         pdid     = GetParticle()->GetPDGEncoding();
  G4ThreeVector pre      = GetPrePosition();
  G4ThreeVector post     = GetPostPosition();

  // output hitdata to output file ....
	
  G4std::ofstream& ofs = GetOutputFileStream();
  if(! ofs.good()) {
    G4String errorMessage= "J4CDCStereoDriftRegionHit::Output(): write error.";
    G4Exception(errorMessage);
  }  
  else
  {
     ofs << G4std::setw(1) << layerNo << " "
     << G4std::setw(1) << wireNo << " "
     << G4std::setw(3) << cellID << " "
     << G4std::setw(7) << GetTrackID() << " "
     << G4std::setw(7) << GetMotherTrackID() << " "
     << G4std::setw(7) << GetHitNumber() << " "
     << G4std::setw(6) << pdid << " "
     << G4std::setw(2) << GetCharge() << " "
     << setiosflags(G4std::ios::scientific) 
     << G4std::setprecision(14)
     << G4std::setw(18) << dphi << " "
     << G4std::setw(18) << sphi << " "
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
     << G4std::setw(18) << fWireEnd[0].x() << " "
     << G4std::setw(18) << fWireEnd[0].y() << " "
     << G4std::setw(18) << fWireEnd[0].z() << " "
     << G4std::setw(18) << fWireEnd[1].x() << " "
     << G4std::setw(18) << fWireEnd[1].y() << " "
     << G4std::setw(18) << fWireEnd[1].z() << " "
     << G4std::setw(18) << fTanStereo << " "
     << G4std::setw(18) << fRwaist << " "
     << G4std::setiosflags(G4std::ios::floatfield) 
     << G4std::setprecision(8)
     << G4endl;
  }

}  

