// $Id$
//*************************************************************************
//* --------------------
//* J4VTXPixelHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4VTXPixel.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include <iomanip.h>
#include "J4VTXPixelHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J4VTXPixelHitAllocator J4VTXPixelHit::fHitAllocator ;

//=========================================================================
//* constructor -----------------------------------------------------------

J4VTXPixelHit::J4VTXPixelHit(
                 J4VComponent         *component,
				     G4int                 trackID ,
				     G4int                 mothertrackID ,
				     G4ParticleDefinition *particle,
				     G4int                 layerID ,
				     G4int                 ladderID ,
				     G4int                 sensorID,
				     G4int                 pixthetaID,
				     G4int                 pixphiID,
				     G4double              edep    ,
				     const G4ThreeVector  &momentum,
				     G4double              energy,
				     G4double              tof,
				     const G4ThreeVector  &pixPos,
				     const G4ThreeVector  &inPos ,
				     const G4ThreeVector  &outPos,
				     const G4ThreeVector  &localpixPos,
				     const G4ThreeVector  &localinPos ,
				     const G4ThreeVector  &localoutPos )
              :J4VHit(component, trackID, mothertrackID,
                      particle, tof, edep, energy, momentum),
               fLayerID(layerID),fLadderID(ladderID),
               fSensorID(sensorID),fPixThetaID(pixthetaID),
               fPixPhiID(pixphiID),fPixPosition(pixPos),
               fInPosition(inPos),fOutPosition(outPos),
               fLocalInPosition(localpixPos),
               fLocalOutPosition(localinPos),
               fLocalPixPosition(localoutPos)
{  
}

//=========================================================================
//* destructor -----------------------------------------------------------

J4VTXPixelHit::~J4VTXPixelHit()
{
}

//=========================================================================
G4ThreeVector J4VTXPixelHit::GetHitPosition(){
  G4double x  = (fOutPosition.x() + fInPosition.x())/2.;
  G4double y  = (fOutPosition.y() + fInPosition.y())/2.;
  G4double z  = (fOutPosition.z() + fInPosition.z())/2.;
  G4ThreeVector hit(x,y,z);
  return hit;
}
//=========================================================================
//* Output ------------------------------------------------------------------
void J4VTXPixelHit::Output(G4HCofThisEvent* HCTE)
{
	
  // output hitdata to output file ....
  
  ofstream& ofs = GetOutputFileStream();
  if(! ofs.good()) {
    G4String errorMessage= "J4VTXPixelHit::Output(): write error.";
    G4Exception(errorMessage);
  }  
  else
  {
#if 1
     ofs << "Pixel " 
	 <<  GetEnergyDeposit()/keV << " "
          << GetTrackID() << " " << fLayerID 
	  <<" " << fLadderID <<" "<< fSensorID
         <<" " << fPixThetaID <<" " << fPixPhiID << " " 
         << fInPosition <<" " << fOutPosition << G4endl;  	
#else
     G4double dE = GetEnergyDeposit()/keV;
     G4int    trk = GetTrackID();
     G4int pid = GetParticle()->GetPDGEncoding();
     G4double charge = GetParticle()->GetPDGCharge();
     G4double xin = fInPosition.x()/mm;
     G4double yin = fInPosition.y()/mm;
     G4double zin = fInPosition.z()/mm;
     ofs << "Pixel " 
         << trk  << " " << pid << " " << charge << " " << dE
	 <<" " <<  fLayerID  <<" " << fLadderID <<" "<< fSensorID
         <<" " << fPixThetaID <<" " << fPixPhiID
	 <<" " <<  xin << " " << yin << " " << zin << endl;
#endif
  }
}
	
//=========================================================================
//* Draw ------------------------------------------------------------------

void J4VTXPixelHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------
void J4VTXPixelHit::Print()
{

  G4ThreeVector fHitPosition=GetHitPosition();

  G4cerr << setiosflags(ios::fixed);
  G4cerr << " track#=" << GetTrackID()
	 << " position(mm)= " << setprecision(2) 
	 << G4std::setw(8) << fHitPosition.x() *(1./mm) << " "
	 << G4std::setw(8) << fHitPosition.y() *(1./mm) << " "
	 << G4std::setw(8) << fHitPosition.z() *(1./mm) << " "
	 << " Edep(keV)= " << setprecision(2) 
	 << G4std::setw(6) << GetEnergyDeposit() *(1./keV) << " "
         << G4endl;  
}



