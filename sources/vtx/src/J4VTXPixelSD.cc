// $id: J4VTXPixelSD.cc,v 1.1.1.2 2001/05/31 06:35:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4VTXPixelSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VTXPixelSD.hh"
#include <math.h>

//=====================================================================
//---------------------
// class definition
//---------------------
//=====================================================================
//* constructor -------------------------------------------------------

J4VTXPixelSD::J4VTXPixelSD(J4VDetectorComponent* detector)
             :J4VSD<J4VTXPixelHit>(detector),
              fSTrack(0), fSLayer(0), fSLadder(0), fSSensor(0), 
              fSTpixel(0), fSPpixel(0), fSColNo(0)     
{
  cout << " XXXX PixelSD XXXX " << endl;
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXPixelSD::~J4VTXPixelSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4VTXPixelSD::Initialize(G4HCofThisEvent* HCTE)
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  MakeHitBuf(HCTE);  
  InitID();
  fSColNo = -1;
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4VTXPixelSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
  //In order to use Get function of J4VSensitiveDetector,
  // you must call SetNewStep() at first.
  SetNewStep(aStep);
  // volume information must be gotten from "PreStepPoint"
 
  //Only when a charged particle has just come into a sensitive detector,
  //create a new hit
  //if(GetCharge() == 0.) return FALSE;
      
  //Get perticle information
  G4int                 trackID         = GetTrackID();
  G4int                 mothertrackID   = GetMotherTrackID();
  G4ParticleDefinition *particle        = GetParticle();

  J4VComponent  *pixel       = GetComponent();
  J4VComponent  *pixelarray  = pixel->GetMother();
  J4VComponent  *pixelarea   = pixelarray->GetMother();
  J4VComponent  *epitaxial   = pixelarea->GetMother();
  J4VComponent  *sensor      = epitaxial->GetMother();
  J4VComponent  *ladder      = sensor->GetMother();
  J4VComponent  *layer       = ladder->GetMother();

  // Pixel -> PixelArray -> PixelArea -> Epitaxial -> Sensor -> Ladder
  G4VPhysicalVolume* pixelPV = pixel->GetPV();
  G4VPhysicalVolume* pixelarrayPV = pixelPV->GetMother();
  G4VPhysicalVolume* pixelareaPV = pixelarrayPV->GetMother();
  G4VPhysicalVolume* epitaxialPV = pixelareaPV->GetMother();
  G4VPhysicalVolume* sensorPV = epitaxialPV->GetMother();
  G4VPhysicalVolume* ladderPV = sensorPV->GetMother();

  G4int iLayer = layer->GetMyID();
  G4int iLadder = ladderPV->GetCopyNo();
  G4int iSensor = sensorPV->GetCopyNo();
  G4int iPixelIDT =  GetCloneID(pixelarray);
  G4int iPixelIDP =  GetCloneID();

  G4double             edep      = GetEnergyDeposit();
  G4ThreeVector        trkP      = GetMomentum();
  G4double             trkE      = GetTotalEnergy();
  G4double             tof       = GetTof();
  G4ThreeVector        pixelPos  = GetTranslation();
  const G4ThreeVector &inPos	   = GetPrePosition();
  const G4ThreeVector &outPos	   = GetPostPosition();
  G4ThreeVector        localpixPos = GlobalToLocalPosition(pixelPos);
  G4ThreeVector        localinPos  = GlobalToLocalPosition(inPos);
  G4ThreeVector        localoutPos = GlobalToLocalPosition(outPos);

// Create a new hit and push them to "Hit Collection"
  if(! compareID(trackID,iLayer,iLadder,iSensor,iPixelIDT,iPixelIDP) ){
        J4VTXPixelHit* hit = new J4VTXPixelHit(
                               GetComponent(),
                               trackID, mothertrackID, particle,
                               iLayer,iLadder,iSensor,
                               iPixelIDT,iPixelIDP,
                               edep, trkP, trkE, tof,
                               pixelPos,inPos,outPos,
                               localpixPos,localinPos,localoutPos);
        fSColNo = ((J4VTXPixelHitBuf*)GetHitBuf())-> insert(hit);
        SetID(trackID,iLayer,iLadder,iSensor,iPixelIDT,iPixelIDP);
  } else {
       (*(J4VTXPixelHitBuf*)GetHitBuf())[fSColNo-1]->AddEdep(edep);
       (*(J4VTXPixelHitBuf*)GetHitBuf())[fSColNo-1]->SetOutPos(outPos);
       (*(J4VTXPixelHitBuf*)GetHitBuf())[fSColNo-1]->SetLocalOutPos(localoutPos);
  }    

  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4VTXPixelSD::EndOfEvent(G4HCofThisEvent* HCTE)
{
}

//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4VTXPixelSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4VTXPixelSD::PrintAll()
{
  G4int nHit= ((J4VTXPixelHitBuf*)GetHitBuf())-> entries();
  G4cout << "------------------------------------------" << G4endl
         << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
  ((J4VTXPixelHitBuf*)GetHitBuf())-> PrintAllHits();
}

//====================================================================

G4ThreeVector J4VTXPixelSD::GlobalToLocalPosition(G4ThreeVector gpIn){
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

void J4VTXPixelSD::InitID(){
  fSTrack=-1;
  fSLayer=-1;
  fSLadder=-1;
  fSSensor=-1;
  fSTpixel=-1;
  fSPpixel=-1;

}


void J4VTXPixelSD::SetID(G4int trackID,G4int iLayer,G4int iLadder,
G4int iSensor,G4int iPixelIDT, G4int iPixelIDP){
  fSTrack=trackID;
  fSLayer=iLayer;
  fSLadder=iLadder;
  fSSensor=iSensor;
  fSTpixel=iPixelIDT;
  fSPpixel=iPixelIDP;
}

G4bool J4VTXPixelSD::compareID(G4int trackID, G4int iLayer, G4int iLadder,
G4int iSensor,G4int iPixelIDT, G4int iPixelIDP ){
  if ( fSTrack==trackID 
       && fSLayer==iLayer
       && fSLadder==iLadder
       && fSSensor==iSensor 
       && fSTpixel==iPixelIDT
       && fSPpixel==iPixelIDP
       )
    return TRUE;
  else
    return FALSE;
}


