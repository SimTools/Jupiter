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
#include "G4VProcess.hh"
#include <math.h>

//=====================================================================
//---------------------
// class definition
//---------------------
//=====================================================================
//* constructor -------------------------------------------------------

J4VTXPixelSD::J4VTXPixelSD(J4VDetectorComponent* detector)
             :J4VSD<J4VTXPixelHit>(detector),
              fSTrack(-1), fSLayer(-1), fSLadder(-1), fSSensor(-1), 
              fSTpixel(-1), fSPpixel(-1), fSColNo(0)     
{
  G4cout << " ----- PixelSD ----- " << G4endl;
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

G4bool J4VTXPixelSD::ProcessHits(G4Step*              aStep, 
                                 G4TouchableHistory* /* ROhist */)
{
  //In order to use Get function of J4VSensitiveDetector,
  // you must call SetNewStep() at first.
  SetNewStep(aStep);
  // volume information must be gotten from "PreStepPoint"

  //Only when a charged particle has just come into a sensitive detector,
  //create a new hit
  if(GetCharge() == 0.) return FALSE;
      
  //Get perticle information
  G4int                 trackID         = GetTrackID();
#if 1
  G4int                 mothertrackID   = GetMotherTrackID();
  G4ParticleDefinition *particle        = GetParticle();
  G4double             weight           = GetWeight();

  const G4ThreeVector &origin = GetTrack()->GetVertexPosition();
#endif
  G4double orgkinE = GetTrack()->GetVertexKineticEnergy();
  G4ThreeVector  origP;
  if (orgkinE > 0 ){
    const G4ThreeVector &orgPDir = GetTrack()->GetVertexMomentumDirection();
    if ( &orgPDir != NULL ) {
      G4double mass = GetTrack()->GetDynamicParticle()->GetMass();
      G4double mom =  sqrt( orgkinE*orgkinE+2*orgkinE*mass );
      origP =
        G4ThreeVector(mom*orgPDir.x(),mom*orgPDir.y(),mom*orgPDir.z());
    }
  }else{
    origP = G4ThreeVector(0.,0.,0.);
  }

  G4String procName;
  if ( trackID==1 ) {
    procName = "ORIGIN";
  }else{
    const G4VProcess* process = GetTrack()->GetCreatorProcess();
    if ( process == NULL ) procName = "ORIGIN";
    else procName = process->GetProcessName();
  }

#if 1
//  J4VComponent  *pixel       = GetComponent();
  J4VComponent  *pixelarray  = GetComponent(1);//pixel->GetMother();
//  J4VComponent  *pixelarea   = GetComponent(2);//pixelarray->GetMother();
//  J4VComponent  *epitaxial   = GetComponent(3);//pixelarea->GetMother();
  J4VComponent  *sensor      = GetComponent(4);//epitaxial->GetMother();
  J4VComponent  *ladder      = GetComponent(5);//sensor->GetMother();
  J4VComponent  *layer       = GetComponent(6);//ladder->GetMother();

  // Pixel -> PixelArray -> PixelArea -> Epitaxial -> Sensor -> Ladder
//  G4VPhysicalVolume* pixelPV = pixel->GetPV();
//  G4VPhysicalVolume* pixelarrayPV = pixelarray->GetPV();// pixelPV->GetMother();
//  G4VPhysicalVolume* pixelareaPV = pixelarea->GetPV();// pixelarrayPV->GetMother();
//  G4VPhysicalVolume* epitaxialPV = epitaxial->GetPV();// pixelareaPV->GetMother();
  G4VPhysicalVolume* sensorPV = sensor->GetPV();// epitaxialPV->GetMother();
  G4VPhysicalVolume* ladderPV = ladder->GetPV();// sensorPV->GetMother();

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
			       weight,
			       origin,origP,procName,
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

#endif

  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4VTXPixelSD::EndOfEvent(G4HCofThisEvent* /* HCTE */)
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
#if 0
  G4VPhysicalVolume* pv = GetPreStepPoint()->GetPhysicalVolume();
  while( pv != NULL ){
    G4ThreeVector Ot = pv->GetFrameTranslation();
    G4RotationMatrix Or = (pv->GetObjectRotationValue()).inverse();
  pos = Or*(pos+Ot);
  pv = pv->GetMother();
  }
#endif
#if 1
  G4ThreeVector Ot = GetTranslation();
  G4RotationMatrix Or(*GetRotation());
  pos = (Or)*(pos-Ot);
#endif
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


