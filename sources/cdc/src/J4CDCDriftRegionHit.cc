// $Id$
//*************************************************************************
//* --------------------
//* J4CDCDriftRegionHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4CDCDriftRegion.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include <iomanip>
#include <math.h>
#include "J4CDCDriftRegionHit.hh"
#include "J4CDCDriftRegion.hh"

using namespace std;

//=========================================================================
//---------------------
// Allocator
//---------------------

J4CDCDriftRegionHitAllocator J4CDCDriftRegionHit::fHitAllocator;
J4Output *J4CDCDriftRegionHit::fOutput = 0;

//=========================================================================
//* constructor -----------------------------------------------------------

J4CDCDriftRegionHit::J4CDCDriftRegionHit(
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
     const G4double        tanstereo,     // stereo angle of cell 
     const G4double        rwaist,        // waist radius of sense-wire plane
     const G4int           hitnumber)     // unique hit number
 	: J4VCDCDriftRegionHit(detector, cloneID, trackID, mothertrackID, particle,
                               tof, edep, totalE, momentum, pre, pos, rotangle,
                               wireEndpz, wireEndmz, tanstereo, rwaist, 
                               hitnumber)
{
}

//=========================================================================
//* destructor -----------------------------------------------------------

J4CDCDriftRegionHit::~J4CDCDriftRegionHit()
{
}

//=========================================================================
//* Output ----------------------------------------------------------------

void J4CDCDriftRegionHit::Output(G4HCofThisEvent* HCTE)
{

  if (fOutput) fOutput->Output(this);

  J4VCDCDriftRegion *cpt = (J4VCDCDriftRegion *)GetComponent();

  G4int         wireNo   = cpt->GetMyID();
  G4int         layerNo  = cpt->GetGlobalLayerNumber();
  G4double      dphi     = cpt->GetDeltaPhi(cpt);
  G4double      sphi     = -0.5 * dphi;

  G4int         cellID   = GetCloneID();
  G4String      pname    = GetParticleName();
  G4int         pdid     = GetPDGEncoding();   
  G4ThreeVector pre      = GetPrePosition();
  G4ThreeVector post     = GetPostPosition();

  // output hitdata to output file ....
	
  std::ofstream& ofs = GetOutputFileStream();
  if (! ofs.good()) {
    G4String errorMessage= "J4CDCDriftRegionHit::Output(): write error.";
    G4Exception(errorMessage);
  } else {
     ofs << std::setw(1) << layerNo << " " 
         << std::setw(1) << wireNo << " " 
         << std::setw(3) << cellID << " " 
         << std::setw(7) << GetTrackID() << " " 
         << std::setw(7) << GetMotherTrackID() << " " 
         << std::setw(7) << GetHitNumber() << " " 
         << std::setw(6) << pdid << " " 
         << std::setw(2) << GetCharge() << " " 
         << std::setiosflags(std::ios::scientific) 
         << std::setprecision(14)
         << std::setw(18) << dphi << " " 
         << std::setw(18) << sphi << " "
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
         << std::setw(18) << fWireEnd[0].x() << " "
         << std::setw(18) << fWireEnd[0].y() << " "
         << std::setw(18) << fWireEnd[0].z() << " "
         << std::setw(18) << fWireEnd[1].x() << " "
         << std::setw(18) << fWireEnd[1].y() << " "
         << std::setw(18) << fWireEnd[1].z() << " "
         << std::setw(18) << fTanStereo << " "
         << std::setw(18) << fRwaist << " "
         << std::setiosflags(std::ios::floatfield) 
         << std::setprecision(8)
         << G4endl;
  }

#if 0
     G4cerr << "LayerNo   : " << layerNo << G4endl; 
     G4cerr << "WireNo    : " << wireNo << G4endl; 
     G4cerr << "CellID    : " << cellID << G4endl;
     G4cerr << "TrackID   : " << GetTrackID() << G4endl; 
     G4cerr << "MotherTrackID : " << GetMotherTrackID() << G4endl; 
     G4cerr << "HitNumber : " << GetHitNumber() << G4endl; 
     G4cerr << "PDID      : " << pdid << G4endl; 
     G4cerr << "Charge    : " << GetCharge() << G4endl; 
     G4cerr << "DPhi      : " << dphi << G4endl; 
     G4cerr << "SPhi      : " << sphi << G4endl; 
     G4cerr << "Pre       : " << pre << G4endl; 
     G4cerr << "Post      : " << post << G4endl; 
     G4cerr << "Momentum  : " << GetMomentum() << G4endl; 
     G4cerr << "TotalE    : " << GetTotalEnergy() << G4endl; 
     G4cerr << "EDep      : " << GetEnergyDeposit() << G4endl; 
     G4cerr << "Tof       : " << GetTof() << G4endl; 
     G4cerr << "WireEndm  : " << fWireEnd[0] << G4endl; 
     G4cerr << "WireEndp  : " << fWireEnd[1] << G4endl; 
     G4cerr << "TanStereo : " << fTanStereo << G4endl; 
     G4cerr << "RWaist    : " << fRwaist << G4endl; 
#endif

}


