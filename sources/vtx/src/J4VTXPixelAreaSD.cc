// $id: J4VTXPixelAreaSD.cc,v 1.1.1.2 2001/05/31 06:35:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4VTXPixelAreaSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#ifndef __HOSHINA__

#include "J4VTXPixelAreaSD.hh"
#include <math.h>

G4int STrack;
G4int SLayer;
G4int SLadder;
G4int SSensor;
G4int STpixel;
G4int SPpixel;
G4int SColNo; 
//=====================================================================
//---------------------
// class definition
//---------------------
//=====================================================================
//* constructor -------------------------------------------------------

J4VTXPixelAreaSD::J4VTXPixelAreaSD(J4VDetectorComponent* detector)
		   :J4VSD<J4VTXPixelAreaHit>(detector)
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXPixelAreaSD::~J4VTXPixelAreaSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4VTXPixelAreaSD::Initialize(G4HCofThisEvent* HCTE)
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  MakeHitBuf(HCTE);  
  InitID();
  SColNo = -1;
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

J4VTXPixelAreaHit* hit;
G4bool J4VTXPixelAreaSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
  //In order to use Get function, you must call SetNewStep() at first.
  SetNewStep(aStep);
  SetROHist(ROhist);
   
  //Only when a charged particle has just come into a sensitive detector,
  //create a new hit
  if(GetCharge() == 0.) return FALSE;
      
  //Get perticle information
  G4int trackID  		 = GetTrackID();
  G4int mothertrackID  		 = GetMotherTrackID();
  G4ParticleDefinition* particle = GetParticle();
  G4int iLayer  =  GetLayerID();
  G4int iLadder =  GetLadderID();
  G4int iSensor =  GetSensorID();
  G4int iPixelIDT = GetPixelIDTheta();
  G4int iPixelIDP = GetPixelIDPhi();
  G4double edep   = GetEnergyDeposit();
  G4ThreeVector trkP = GetMomentum();
  G4double      trkE = GetTotalEnergy();
  G4ThreeVector pixelPos  =  GetPixelPosition();
  const G4ThreeVector& inPos	 = GetPrePosition();
  const G4ThreeVector& outPos	 = GetPostPosition();
  G4ThreeVector localpixPos = GlobalToLocalPosition(pixelPos);
  G4ThreeVector localinPos = GlobalToLocalPosition(inPos);
  G4ThreeVector localoutPos = GlobalToLocalPosition(outPos);

// Create a new hit and push them to "Hit Collection"
  if(! compareID(trackID,iLayer,iLadder,iSensor,iPixelIDT,iPixelIDP) ){
        hit =new J4VTXPixelAreaHit( trackID, mothertrackID, particle,
			       iLayer,iLadder,iSensor,
			       iPixelIDT,iPixelIDP,
			       edep, trkP, trkE,
			       pixelPos,inPos,outPos,
			       localpixPos,localinPos,localoutPos);
        SColNo = ((J4VTXPixelAreaHitBuf*)GetHitBuf())-> insert(hit);
	SetID(trackID,iLayer,iLadder,iSensor,iPixelIDT,iPixelIDP);
  } else {
       (*(J4VTXPixelAreaHitBuf*)GetHitBuf())[SColNo-1]->AddEdep(edep);
       (*(J4VTXPixelAreaHitBuf*)GetHitBuf())[SColNo-1]->SetOutPos(outPos);
       (*(J4VTXPixelAreaHitBuf*)GetHitBuf())[SColNo-1]->SetLocalOutPos(localoutPos);
      G4double etmp=(*(J4VTXPixelAreaHitBuf*)GetHitBuf())[SColNo-1]->GetEDeposit();
      //     G4cout << "SColNO " << SColNo <<" E "<<etmp/keV<<" keV " << G4endl; 
  }    
     return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4VTXPixelAreaSD::EndOfEvent(G4HCofThisEvent* HCTE)
{
}

//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4VTXPixelAreaSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4VTXPixelAreaSD::PrintAll()
{
  G4int nHit= ((J4VTXPixelAreaHitBuf*)GetHitBuf())-> entries();
  G4cout << "------------------------------------------" << G4endl
         << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
  ((J4VTXPixelAreaHitBuf*)GetHitBuf())-> PrintAllHits();
}

//====================================================================
G4int J4VTXPixelAreaSD::GetLayerID(){
  J4VComponent* pixelarea = GetComponent();
  J4VComponent* epitaxial = pixelarea->GetMother();
  J4VComponent* sensor    = epitaxial->GetMother();
  J4VComponent* ladder    = sensor->GetMother();
  J4VComponent* layer     = ladder->GetMother();
  layer->GetMyID();
}
G4int J4VTXPixelAreaSD::GetLadderID(){
  G4VPhysicalVolume* pixelPV = GetPreStepPoint()->GetPhysicalVolume();
  G4VPhysicalVolume* epitaxPV = pixelPV->GetMother();
  G4VPhysicalVolume* sensorPV = epitaxPV->GetMother();
  G4VPhysicalVolume* ladderPV = sensorPV->GetMother();
  return ladderPV->GetCopyNo();
}
G4int J4VTXPixelAreaSD::GetSensorID(){
  G4VPhysicalVolume* pixelPV = GetPreStepPoint()->GetPhysicalVolume();
  G4VPhysicalVolume* epitaxPV = pixelPV->GetMother();
  G4VPhysicalVolume* sensorPV = epitaxPV->GetMother();
  return sensorPV->GetCopyNo();
}
G4int J4VTXPixelAreaSD::GetPixelIDTheta(){
  return ROH->GetReplicaNumber(1);
}

G4int J4VTXPixelAreaSD::GetPixelIDPhi(){
  return ROH->GetReplicaNumber();
}
G4ThreeVector J4VTXPixelAreaSD::GetPixelPosition(){
  return ROH->GetTranslation();
}

G4ThreeVector J4VTXPixelAreaSD::GlobalToLocalPosition(G4ThreeVector gpIn){
  G4ThreeVector pos = G4ThreeVector(gpIn);
  G4VPhysicalVolume* pv = GetPreStepPoint()->GetPhysicalVolume();
  while( pv != NULL ){
    G4ThreeVector Ot = pv->GetFrameTranslation();
    G4RotationMatrix Or = (pv->GetObjectRotationValue()).inverse();
  pos = Or*(pos+Ot);
  pv = pv->GetMother();
  }
  return pos;
}

void J4VTXPixelAreaSD::InitID(){
  STrack=-1;
  SLayer=-1;
  SLadder=-1;
  SSensor=-1;
  STpixel=-1;
  SPpixel=-1;

}


void J4VTXPixelAreaSD::SetID(G4int trackID,G4int iLayer,G4int iLadder,
G4int iSensor,G4int iPixelIDT, G4int iPixelIDP){
  STrack=trackID;
  SLayer=iLayer;
  SLadder=iLadder;
  SSensor=iSensor;
  STpixel=iPixelIDT;
  SPpixel=iPixelIDP;
}

G4bool J4VTXPixelAreaSD::compareID(G4int trackID,G4int iLayer,G4int iLadder,
G4int iSensor,G4int iPixelIDT, G4int iPixelIDP ){
  if ( STrack==trackID 
       && SLayer==iLayer
       && SLadder==iLadder
       && SSensor==iSensor 
       && STpixel==iPixelIDT
       && SPpixel==iPixelIDP
       )
    return TRUE;
  else
    return FALSE;
}

#endif
