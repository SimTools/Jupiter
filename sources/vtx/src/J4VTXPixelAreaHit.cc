// $Id$
//*************************************************************************
//* --------------------
//* J4VTXPixelAreaHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4VTXPixelArea.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include <iomanip>
#include "J4VTXPixelAreaHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J4VTXPixelAreaHitAllocator J4VTXPixelAreaHit::fHitAllocator ;

//=========================================================================
//* constructor -----------------------------------------------------------

J4VTXPixelAreaHit::J4VTXPixelAreaHit(
				     G4int                 trackID ,
				     G4int                 mothertrackID ,
				     G4ParticleDefinition* particle,
				     G4int                 layerID ,
				     G4int                 ladderID ,
				     G4int                 sensorID,
				     G4int                 pixthetaID,
				     G4int                 pixphiID,
				     G4double              edep    ,
				     const G4ThreeVector  momentum,
				     G4double  energy,
				     const G4ThreeVector  pixPos,
				     const G4ThreeVector  inPos ,
				     const G4ThreeVector  outPos,
				     const G4ThreeVector  localpixPos,
				     const G4ThreeVector  localinPos ,
				     const G4ThreeVector  localoutPos ):
  fTrackID(trackID),fPID(particle),
  fLayerID(layerID),fLadderID(ladderID),
  fSensorID(sensorID),fPixThetaID(pixthetaID),fPixPhiID(pixphiID),
  fEdep(edep),fMomentum(momentum),fEnergy(energy),fPixPosition(pixPos),
  fInPosition(inPos),fOutPosition(outPos),fLocalInPosition(localpixPos),
  fLocalOutPosition(localinPos),fLocalPixPosition(localoutPos)
{  
  SetMotherTrackID(mothertrackID); 
}

//=========================================================================
//* destructor -----------------------------------------------------------

J4VTXPixelAreaHit::~J4VTXPixelAreaHit()
{
}

//=========================================================================
G4ThreeVector J4VTXPixelAreaHit::GetHitPosition(){
  G4double x  = (fOutPosition.x() + fInPosition.x())/2.;
  G4double y  = (fOutPosition.y() + fInPosition.y())/2.;
  G4double z  = (fOutPosition.z() + fInPosition.z())/2.;
  G4ThreeVector hit(x,y,z);
  return hit;
}
//=========================================================================
//* Output ------------------------------------------------------------------
void J4VTXPixelAreaHit::Output(G4HCofThisEvent* HCTE)
{
	
  // output hitdata to output file ....
  
  G4std::ofstream& ofs = GetOutputFileStream();
  if(! ofs.good()) {
    G4String errorMessage= "J4CDCDriftRegionHit::Output(): write error.";
    G4Exception(errorMessage);
  }  
  else
  {
     ofs << fEdep/keV << " keV" <<G4endl;
     ofs << fTrackID << " " << fLayerID 
	 <<" " << fLadderID <<" "<< fSensorID
     	 <<" " << fPixThetaID <<" " << fPixPhiID <<G4endl;
     ofs << fInPosition <<" " << fOutPosition << G4endl;  	
  }
}
	
//=========================================================================
//* Draw ------------------------------------------------------------------

void J4VTXPixelAreaHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------
void J4VTXPixelAreaHit::Print()
{

  G4ThreeVector fHitPosition=GetHitPosition();

  G4cerr << setiosflags(G4std::ios::fixed);
  G4cerr << " track#=" << fTrackID
	 << " position(mm)= " << G4std::setprecision(2) 
	 << G4std::setw(8) << fHitPosition.x() *(1./mm) << " "
	 << G4std::setw(8) << fHitPosition.y() *(1./mm) << " "
	 << G4std::setw(8) << fHitPosition.z() *(1./mm) << " "
	 << " Edep(keV)= " << G4std::setprecision(2) 
	 << G4std::setw(6) << fEdep *(1./keV) << " "
         << G4endl;  
}



