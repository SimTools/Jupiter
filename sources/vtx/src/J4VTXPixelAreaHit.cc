// $Id$
//*************************************************************************
//* --------------------
//* J4VTXPixelAreaHit
//* --------------------
//* (Description)
//* 	Derivated concreate hit class for J4VTXPixel.
//*	Mother class : J4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************

#include <iomanip.h>
#include "J4VTXPixelAreaHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J4VTXPixelAreaHitAllocator J4VTXPixelAreaHit::fHitAllocator ;

//=========================================================================
//* constructor -----------------------------------------------------------

J4VTXPixelAreaHit::J4VTXPixelAreaHit(
                 J4VComponent         *component,
				     G4int                 trackID ,
				     G4int                 mothertrackID ,
				     G4ParticleDefinition *particle,
				     G4int                 layerID ,
				     G4int                 ladderID ,
				     G4int                 sensorID,
				     G4double              edep    ,
				     const G4ThreeVector  &momentum,
				     G4double              energy,
				     G4double              tof,
				     const G4ThreeVector  &inPos ,
				     const G4ThreeVector  &outPos,
				     const G4ThreeVector  &localinPos ,
				     const G4ThreeVector  &localoutPos )
              :J4VHit(component, trackID, mothertrackID,
                      particle, tof, edep, energy, momentum),
               fLayerID(layerID),fLadderID(ladderID),
               fSensorID(sensorID),
               fInPosition(inPos),fOutPosition(outPos),
               fLocalInPosition(localinPos),
               fLocalOutPosition(localoutPos)
{  
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
    G4String errorMessage= "J4VTXPixelAreaHit::Output(): write error.";
    G4Exception(errorMessage);
  }  
  else
  {
#if 0
     ofs << "PixelArea " 
	 <<  GetEnergyDeposit()/keV << " "
          << GetTrackID() << " " << fLayerID 
	 <<" " << fLadderID <<" "<< fSensorID << " " 
         << fInPosition <<" " << fOutPosition << G4endl;  	
#else
     G4double dE = GetEnergyDeposit()/keV;
     G4int    trk = GetTrackID();
     G4int pid = GetParticle()->GetPDGEncoding();
     G4double charge = GetParticle()->GetPDGCharge();
     G4double xin = fInPosition.x()/mm;
     G4double yin = fInPosition.y()/mm;
     G4double zin = fInPosition.z()/mm;
     ofs << "PixelArea " 
         << trk  << "\t" << pid << "\t" << charge << "\t" << dE
	 <<"\t" <<  fLayerID  <<"\t" << fLadderID <<"\t"<< fSensorID
	 <<"\t" <<  xin << "\t" << yin << "\t" << zin << G4endl;
#endif
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



