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
     const G4ThreeVector  &wireEndpz,     // wire position at +ve z endcap
     const G4ThreeVector  &wireEndmz,     // wire position at -ve z endcap
     const G4double       &rotangle,      // rotation angle of cell 
     const G4int           hitnumber)     // unique hit number
 	: J4VHit(detector, cloneID, trackID, mothertrackID, particle, tof, edep, 
            totalE, momentum, pre, pos, hitnumber), 
          fRotAngle(rotangle)
 		
{
  fWireEnd[0] = wireEndmz;
  fWireEnd[1] = wireEndpz;
  fHitPosition = GetHitPosition();
}

//=========================================================================
//* destructor -----------------------------------------------------------

J4CDCDriftRegionHit::~J4CDCDriftRegionHit()
{
}

//=========================================================================
//* GetHitPosition --------------------------------------------------

G4ThreeVector J4CDCDriftRegionHit::GetHitPosition() const
{
  G4ThreeVector pre  = GetPrePosition();
  G4ThreeVector post = GetPostPosition();
  G4double x = (pre.x() + post.x()) / 2.0 ;
  G4double y = (pre.y() + post.y()) / 2.0 ;
  G4double z = (pre.z() + post.z()) / 2.0 ;
  
  G4ThreeVector hit(x, y, z);
  return hit;
}


//=========================================================================
//* Output ----------------------------------------------------------------

void J4CDCDriftRegionHit::Output(G4HCofThisEvent* HCTE)
{

  if (fOutput) fOutput->Output(this);

  J4VCDCDetectorComponent *cpt 
            = (J4VCDCDetectorComponent *)GetComponent();
  G4int wireNo  = cpt->GetMyID();
  G4int layerNo = ((J4CDCDriftRegion *)cpt)->GetGlobalLayerNumber();
  G4int cellID  = GetCloneID();

  G4String pid  = GetParticle()->GetParticleName();
  G4int    pdid = GetParticle()->GetPDGEncoding();   
  
  G4double dphi = cpt->GetDeltaPhi(cpt);
  G4double sphi = -0.5 * dphi;
  
  G4double rmin = cpt->GetInnerRadius(cpt); 
  G4double rmax = cpt->GetOuterRadius(cpt); 
  
  G4double rwire    = (rmax + rmin) * 0.5;
  G4double gwirephi = fWireEnd[1].getPhi();
  G4double ghitphi  = fHitPosition.getPhi();
  G4double cellphi  = fRotAngle - sphi;
  while (cellphi < 0)      cellphi += 2*M_PI;
  while (cellphi > 2*M_PI) cellphi -= 2*M_PI;   
  
  G4double driftphi = ghitphi - gwirephi;
  G4double driftlen = rwire * driftphi;
  
  G4ThreeVector pre  = GetPrePosition();
  G4ThreeVector post = GetPostPosition();
  
  // output hitdata to output file ....
	
  G4std::ofstream& ofs = GetOutputFileStream();
  if (! ofs.good()) {
    G4String errorMessage= "J4CDCDriftRegionHit::Output(): write error.";
    G4Exception(errorMessage);
  } else {
     ofs << G4std::setw(1) << layerNo << " " 
         << G4std::setw(1) << wireNo << " " 
         << G4std::setw(3) << cellID << " " 
         << G4std::setw(7) << GetTrackID() << " " 
         << G4std::setw(7) << GetMotherTrackID() << " " 
         << G4std::setw(7) << GetHitNumber() << " " 
         << G4std::setw(6) << pdid << " " 
         << G4std::setw(2) << GetCharge() << " " 
         << G4std::setiosflags(G4std::ios::scientific) << G4std::setprecision(14)
         << G4std::setw(18) << dphi << " " 
         << G4std::setw(18) << sphi << " "
         << G4std::setw(18) << gwirephi << " " 
         << G4std::setw(18) << rwire << " " 
         << G4std::setw(18) << driftlen << " "
         << G4std::setw(18) << pre.x() << " " 
         << G4std::setw(18) << pre.y() << " " 
         << G4std::setw(18) << pre.z() << " "
         << G4std::setw(18) << post.x() << " " 
         << G4std::setw(18) << post.y() << " " 
         << G4std::setw(18) << post.z() << " "
         << G4std::setw(18) << fHitPosition.x() << " " 
         << G4std::setw(18) << fHitPosition.y() << " " 
         << G4std::setw(18) << fHitPosition.z() << " "
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
         << G4std::setiosflags(G4std::ios::floatfield) << setprecision(8)
         << G4endl;
  }
}

//=========================================================================
//* Draw ------------------------------------------------------------------

void J4CDCDriftRegionHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------

void J4CDCDriftRegionHit::Print()
{

  G4cout << G4std::setiosflags(G4std::ios::fixed);
  G4cout << G4std::setw(20) << GetComponentName() << " " << G4endl;
  G4cout << " track#=" << GetTrackID()
	 << " charge=" << GetCharge()
	 << " position(mm)= " << G4std::setprecision(2) 
	 << G4std::setw(8) << fHitPosition.x() *(1./mm) << " "
	 << G4std::setw(8) << fHitPosition.y() *(1./mm) << " "
	 << G4std::setw(8) << fHitPosition.z() *(1./mm) << " "
	 << " energy(GeV)= " << G4std::setprecision(2) 
	 << G4std::setw(6) << GetTotalEnergy() *(1./GeV) << " "
         << " TOF(ns)= " << G4std::setw(4) << G4std::setprecision(1) 
         << GetTof() /ns 
         << G4endl;  
}

