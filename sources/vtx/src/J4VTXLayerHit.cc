// $Id$
//*************************************************************************
//* --------------------
//* J4VTXLayerHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4VTXLayer.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include "./iomanip"
#include "./fstream"
#include "J4VTXLayerHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J4VTXLayerHitAllocator J4VTXLayerHit::fHitAllocator ;
J4Output *J4VTXLayerHit::fOutput = 0;

//=========================================================================
//* constructor -----------------------------------------------------------

J4VTXLayerHit::J4VTXLayerHit(
			       J4VComponent         *component,
				     G4int                 trackID ,
				     G4int                 mothertrackID ,
				     G4ParticleDefinition *particle,
				     G4int                 layerID ,
				     G4double              edep,
				     const G4ThreeVector  &momentum,
				     G4double              energy,
				     G4double              tof,
			       const G4ThreeVector  &inPos,
			       const G4ThreeVector  &outPos)

              :J4VHit(component, trackID, mothertrackID,
                      particle, tof, edep, energy, momentum),
               fInPosition(inPos),fOutPosition(outPos),
               fLayerID(layerID)
{  
}

//=========================================================================
//* destructor -----------------------------------------------------------

J4VTXLayerHit::~J4VTXLayerHit()
{
}

//=========================================================================
G4ThreeVector J4VTXLayerHit::GetHitPosition(){
  G4double x  = (fOutPosition.x() + fInPosition.x())/2.;
  G4double y  = (fOutPosition.y() + fInPosition.y())/2.;
  G4double z  = (fOutPosition.z() + fInPosition.z())/2.;
  G4ThreeVector hit(x,y,z);
  return hit;
}
//=========================================================================
//* Output ------------------------------------------------------------------
void J4VTXLayerHit::Output(G4HCofThisEvent* HCTE)
{
  if (fOutput) {
    fOutput->Output(this);
  }
	
  // output hitdata to output file ....
  
  std::ofstream& ofs = GetOutputFileStream();
  if(! ofs.good()) {
    G4String errorMessage= "J4VTXLayerHit::Output(): write error.";
    G4Exception(errorMessage);
  }  
  else
  {
     G4double dE = GetEnergyDeposit()/keV;
     G4int    trk = GetTrackID();
     G4int pid = GetParticle()->GetPDGEncoding();
     G4double trkE = GetTotalEnergy()/keV;
     G4double charge = GetParticle()->GetPDGCharge();
     G4int layer = fLayerID;
     G4double xin = fInPosition.x()/mm;
     G4double yin = fInPosition.y()/mm;
     G4double zin = fInPosition.z()/mm;
     G4double xout = fOutPosition.x()/mm;
     G4double yout = fOutPosition.y()/mm;
     G4double zout = fOutPosition.z()/mm;
     ofs << "Layer " 
	 << trk  << " " << pid << " " << charge << " " << trkE << " " 
	 << layer <<" " << dE <<" " 
	 <<  xin << " " << yin << " " << zin << " " 
	 <<  xout << " " << yout << " " << zout 
	 << G4endl;
  }
}
	
//=========================================================================
//* Draw ------------------------------------------------------------------

void J4VTXLayerHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------
void J4VTXLayerHit::Print()
{

  G4ThreeVector fHitPosition=GetHitPosition();

  G4int prec = G4cerr.precision(2);

  G4cerr << std::setiosflags(std::ios::fixed);
  G4cerr << " track#=" << GetTrackID()
	 << " position(mm)= "  
	 << std::setw(8) << fHitPosition.x() *(1./mm) << " "
	 << std::setw(8) << fHitPosition.y() *(1./mm) << " "
	 << std::setw(8) << fHitPosition.z() *(1./mm) << " "
	 << " Edep(keV)= " 
	 << std::setw(6) << GetEnergyDeposit() *(1./keV) << " "
         << G4endl;  

  G4cerr.precision(prec);
}



