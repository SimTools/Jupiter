// $Id$
//*************************************************************************
//* --------------------
//* J4VTXLadderHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4VTXLadder.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include "./iomanip"
#include "./fstream"
#include "J4VTXLadderHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J4VTXLadderHitAllocator J4VTXLadderHit::fHitAllocator ;

//=========================================================================
//* constructor -----------------------------------------------------------

J4VTXLadderHit::J4VTXLadderHit(
			       J4VComponent         *component,
				     G4int                 trackID ,
				     G4int                 mothertrackID ,
				     G4ParticleDefinition *particle,
				     G4int                 layerID ,
				     G4int                 ladderID ,
				     G4double              edep,
				     const G4ThreeVector  &momentum,
				     G4double              energy,
				     G4double              tof,
			       const G4ThreeVector  &inPos,
			       const G4ThreeVector  &outPos)

              :J4VHit(component, trackID, mothertrackID,
                      particle, tof, edep, energy, momentum),
               fInPosition(inPos),fOutPosition(outPos),
               fLayerID(layerID),fLadderID(ladderID)
{  
}

//=========================================================================
//* destructor -----------------------------------------------------------

J4VTXLadderHit::~J4VTXLadderHit()
{
}

//=========================================================================
G4ThreeVector J4VTXLadderHit::GetHitPosition(){
  G4double x  = (fOutPosition.x() + fInPosition.x())/2.;
  G4double y  = (fOutPosition.y() + fInPosition.y())/2.;
  G4double z  = (fOutPosition.z() + fInPosition.z())/2.;
  G4ThreeVector hit(x,y,z);
  return hit;
}
//=========================================================================
//* Output ------------------------------------------------------------------
void J4VTXLadderHit::Output(G4HCofThisEvent* HCTE)
{
	
  // output hitdata to output file ....
  
  std::ofstream& ofs = GetOutputFileStream();
  if(! ofs.good()) {
    G4String errorMessage= "J4VTXLadderHit::Output(): write error.";
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
     G4int ladder = fLadderID;
     G4double xin = fInPosition.x()/mm;
     G4double yin = fInPosition.y()/mm;
     G4double zin = fInPosition.z()/mm;
     G4double xout = fOutPosition.x()/mm;
     G4double yout = fOutPosition.y()/mm;
     G4double zout = fOutPosition.z()/mm;
     ofs << "Ladder " 
	 << trk  << " " << pid << " " << charge << " " << trkE << " " 
	 << layer <<" " << ladder << " " <<  dE <<" " 
	 <<  xin << " " << yin << " " << zin << " " 
	 <<  xout << " " << yout << " " << zout 
	 << std::endl;
  }
}
	
//=========================================================================
//* Draw ------------------------------------------------------------------

void J4VTXLadderHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------
void J4VTXLadderHit::Print()
{

  G4ThreeVector fHitPosition=GetHitPosition();

  G4int prec = std::cerr.precision(2);

  std::cerr << std::setiosflags(std::ios::fixed);
  std::cerr << " track#=" << GetTrackID()
	 << " position(mm)= "  
	 << std::setw(8) << fHitPosition.x() *(1./mm) << " "
	 << std::setw(8) << fHitPosition.y() *(1./mm) << " "
	 << std::setw(8) << fHitPosition.z() *(1./mm) << " "
	 << " Edep(keV)= " 
	 << std::setw(6) << GetEnergyDeposit() *(1./keV) << " "
         << std::endl;  

  std::cerr.precision(prec);
}



