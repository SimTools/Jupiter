// $Id$
//*************************************************************************
//* --------------------
//* J4VTXSensorHit
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
#include "J4VTXSensorHit.hh"

//=========================================================================
//---------------------
// Allocator
//---------------------

J4VTXSensorHitAllocator J4VTXSensorHit::fHitAllocator ;

//=========================================================================
//* constructor -----------------------------------------------------------

J4VTXSensorHit::J4VTXSensorHit(
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
  fOrigin(origin),  fOriginP(origP),
  fWeight(weight),
  fProcess(process),
  fLayerID(layerID),fLadderID(ladderID),
  fSensorID(sensorID),
  fInPosition(inPos),fOutPosition(outPos),
  fLocalInPosition(localinPos),
  fLocalOutPosition(localoutPos)
{  
}

//=========================================================================
//* destructor -----------------------------------------------------------

J4VTXSensorHit::~J4VTXSensorHit()
{
}

//=========================================================================
G4ThreeVector J4VTXSensorHit::GetHitPosition(){
  G4double x  = (fOutPosition.x() + fInPosition.x())/2.;
  G4double y  = (fOutPosition.y() + fInPosition.y())/2.;
  G4double z  = (fOutPosition.z() + fInPosition.z())/2.;
  G4ThreeVector hit(x,y,z);
  return hit;
}
//=========================================================================
//* Output ------------------------------------------------------------------
void J4VTXSensorHit::Output(G4HCofThisEvent* /* HCTE */)
{
	
  // output hitdata to output file ....
  
  std::ofstream& ofs = GetOutputFileStream();
  if(! ofs.good()) {
    G4String errorMessage= "J4VTXSensorHit::Output(): write error.";
    G4Exception(errorMessage);
  }  
  else
  {
#if 0
     ofs << "Sensor " 
	 <<  GetEnergyDeposit()/keV << " "
          << GetTrackID() << " " << fLayerID 
	 <<" " << fLadderID <<" "<< fSensorID << " " 
         << fInPosition <<" " << fOutPosition << G4endl;  	
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
     G4double xLin = fLocalInPosition.x()/mm;
     G4double yLin = fLocalInPosition.y()/mm;
     G4double zLin = fLocalInPosition.z()/mm;
     G4double xLout= fLocalOutPosition.x()/mm;
     G4double yLout= fLocalOutPosition.y()/mm;
     G4double zLout= fLocalOutPosition.z()/mm;

     ofs << "Sensor " 
	 << " " << xorig << " " << yorig << " " << zorig 
	 << " " << xorigP << " " << yorigP << " " << zorigP 
         << " " << trk  << " " << mothertrk<< " " << weight
	 << " " << pid << " " << charge << " " << trkE
	 <<" " <<  fLayerID  <<" " << fLadderID <<" "<< fSensorID << " " <<dE
	 <<" " <<  xin << " " << yin << " " << zin 
	 <<" " <<  xout << " " << yout << " " << zout 
	 <<" " <<  xLin << " " << yLin << " " << zLin 
	 <<" " <<  xLout << " " << yLout << " " << zLout 
	 <<" " <<  procName<< G4endl;
#endif
  }
}
	
//=========================================================================
//* Draw ------------------------------------------------------------------

void J4VTXSensorHit::Draw()
{
}

//=========================================================================
//* Print -----------------------------------------------------------------
void J4VTXSensorHit::Print()
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



