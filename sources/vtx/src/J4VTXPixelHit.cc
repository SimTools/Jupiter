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

#include "./iomanip"
#include "./fstream"
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
 		                     G4double             weight,
		                     const G4ThreeVector  &origin,
		                     const G4ThreeVector  &origP,
		                     const G4String       &process,
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
           fOrigin(origin),  fOriginP(origP),fProcess(process),fWeight(weight),
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
  
  std::ofstream& ofs = GetOutputFileStream();
  if(! ofs.good()) {
    G4String errorMessage= "J4VTXPixelHit::Output(): write error.";
    G4Exception(errorMessage);
  }  
  else
  {
#if 0
     ofs << "Pixel " 
	 <<  GetEnergyDeposit()/keV << " "
          << GetTrackID() << " " << fLayerID 
	  <<" " << fLadderID <<" "<< fSensorID
         <<" " << fPixThetaID <<" " << fPixPhiID << " " 
         << fInPosition <<" " << fOutPosition << std::endl;  	
#else
     G4double dE = GetEnergyDeposit()/keV;
     G4int    trk = GetTrackID();
     G4int    mothertrk = GetMotherTrackID();
     G4double   weight   = fWeight;
     G4int pid = GetParticle()->GetPDGEncoding();
     G4double trkE = GetTotalEnergy()/keV;
     G4double charge = GetParticle()->GetPDGCharge();
     G4double xorig = fOrigin.x()/mm;
     G4double yorig = fOrigin.y()/mm;
     G4double zorig = fOrigin.z()/mm;
     G4double xorigP = fOriginP.x()/keV;
     G4double yorigP = fOriginP.y()/keV;
     G4double zorigP = fOriginP.z()/keV;
     G4String procName = fProcess;
     G4double xin = fInPosition.x()/mm;
     G4double yin = fInPosition.y()/mm;
     G4double zin = fInPosition.z()/mm;
     G4double xout = fOutPosition.x()/mm;
     G4double yout = fOutPosition.y()/mm;
     G4double zout = fOutPosition.z()/mm;
     G4double xpix = fPixPosition.x()/mm;
     G4double ypix = fPixPosition.y()/mm;
     G4double zpix = fPixPosition.z()/mm;
     G4double xlpix = fLocalPixPosition.x()/mm;
     G4double ylpix = fLocalPixPosition.y()/mm;
     G4double zlpix = fLocalPixPosition.z()/mm;
     G4double xlin = fLocalInPosition.x()/mm;
     G4double ylin = fLocalInPosition.y()/mm;
     G4double zlin = fLocalInPosition.z()/mm;
     G4double xlout = fLocalOutPosition.x()/mm;
     G4double ylout = fLocalOutPosition.y()/mm;
     G4double zlout = fLocalOutPosition.z()/mm;
     ofs << "Pixel " 
	 << " " << xorig << " " << yorig << " " << zorig
         << " " << xorigP << " " << yorigP << " " << zorigP
         << " " << trk  << " " << mothertrk<<" " << weight
	 << " " << pid << " " << charge << " " << trkE
	 <<" " <<  fLayerID  <<" " << fLadderID <<" "<< fSensorID
         <<" " << fPixThetaID <<" " << fPixPhiID << " " << dE
	 <<" " <<  xin << " " << yin << " " << zin 
	 << " "<<  xout << " " << yout << " " << zout 
	 << " "<<  xpix << " " << ypix << " " << zpix
	 << " "<<  xlpix << " " << ylpix << " " << zlpix
	 << " "<<  xlin << " " << ylin << " " << zlin
	 << " "<<  xlout << " " << ylout << " " << zlout 
	 << " " << procName<< std::endl;
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



