// $id: J4VTXPixelAreaSD.cc,v 1.1.1.2 2001/05/31 06:35:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4VTXPixelAreaSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version
//*	2002/11/20  T.Aso       Modify
//*************************************************************************

#include "J4VTXPixelAreaSD.hh"
#include "G4VProcess.hh"
#include <cmath>

//=====================================================================
//---------------------
// class definition
//---------------------
//=====================================================================
//* constructor -------------------------------------------------------

J4VTXPixelAreaSD::J4VTXPixelAreaSD(J4VDetectorComponent* detector)
             :J4VSD<J4VTXPixelAreaHit>(detector),
              fSTrack(-1), fSLayer(-1), fSLadder(-1), fSSensor(-1), 
              fSColNo(0)     
{
  G4cout << " ----- PixelAreaSD ----- " << G4endl;
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
  fSColNo = -1;
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4VTXPixelAreaSD::ProcessHits(G4Step*              aStep, 
                                     G4TouchableHistory* /* ROhist */)
{
  //In order to use Get function of J4VSensitiveDetector,
  // you must call SetNewStep() at first.

  SetNewStep(aStep);
  //Only when a charged particle has just come into a sensitive detector,
  //create a new hit
  //if(GetCharge() == 0.) return FALSE;
      
  //Get particle information
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
      G4double mom =  std::sqrt( orgkinE*orgkinE+2*orgkinE*mass );
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
//  J4VComponent  *pixelarea   = GetComponent();
//  J4VComponent  *epitaxial   = GetComponent(1);//pixelarea->GetMother();
  J4VComponent  *sensor      = GetComponent(2);//epitaxial->GetMother();
  J4VComponent  *ladder      = GetComponent(3);//sensor->GetMother();
  J4VComponent  *layer       = GetComponent(4);//ladder->GetMother();

//  G4VPhysicalVolume* pixelareaPV = pixelarea->GetPV();
//  G4VPhysicalVolume* epitaxialPV = epitaxial->GetPV();//pixelareaPV->GetMother();
  G4VPhysicalVolume* sensorPV = sensor->GetPV();//epitaxialPV->GetMother();
  G4VPhysicalVolume* ladderPV = ladder->GetPV();//sensorPV->GetMother();

  G4int iLayer    =  layer->GetMyID();
  G4int iLadder   =  ladderPV->GetCopyNo();
  G4int iSensor   =  sensorPV->GetCopyNo();

  G4double             edep      = GetEnergyDeposit();
  G4ThreeVector        trkP      = GetMomentum();
  G4double             trkE      = GetTotalEnergy();
  G4double             tof       = GetTof();
#endif
  const G4ThreeVector &inPos	   = GetPrePosition();
  const G4ThreeVector &outPos	   = GetPostPosition();
  G4ThreeVector        localinPos  = GlobalToLocalPosition(inPos);
  G4ThreeVector        localoutPos = GlobalToLocalPosition(outPos);

// Create a new hit and push them to "Hit Collection"
#if 1
  if(! compareID(trackID,iLayer,iLadder,iSensor) ){
        J4VTXPixelAreaHit* hit = new J4VTXPixelAreaHit(
		               GetComponent(),
                               trackID, mothertrackID, particle,
			       weight,
			       origin,origP,procName,
                               iLayer,iLadder,iSensor,
		               edep, trkP, trkE,tof,
                               inPos,outPos,
                               localinPos,localoutPos);
        fSColNo = ((J4VTXPixelAreaHitBuf*)GetHitBuf())-> insert(hit);
        SetID(trackID,iLayer,iLadder,iSensor);
  } else {
       (*(J4VTXPixelAreaHitBuf*)GetHitBuf())[fSColNo-1]->AddEdep(edep);
       (*(J4VTXPixelAreaHitBuf*)GetHitBuf())[fSColNo-1]->SetOutPos(outPos);
       (*(J4VTXPixelAreaHitBuf*)GetHitBuf())[fSColNo-1]->SetLocalOutPos(localoutPos);
  }    
#endif

  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4VTXPixelAreaSD::EndOfEvent(G4HCofThisEvent* /* HCTE */)
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

G4ThreeVector J4VTXPixelAreaSD::GlobalToLocalPosition(G4ThreeVector gpIn){
  G4ThreeVector pos = G4ThreeVector(gpIn);
/*
  G4VPhysicalVolume* pv = GetPreStepPoint()->GetPhysicalVolume();
  while( pv != NULL ){
    G4ThreeVector Ot = pv->GetFrameTranslation();
    G4RotationMatrix Or = (pv->GetObjectRotationValue()).inverse();
  pos = Or*(pos+Ot);
//  pv = pv->GetMother();
  pv = pv->GetMotherLogical();
  }
*/
#if 1
  G4ThreeVector Ot = GetTranslation();
  G4RotationMatrix Or(*GetRotation());
  pos = (Or)*(pos-Ot);
#endif
  return pos;
}

void J4VTXPixelAreaSD::InitID(){
  fSTrack=-1;
  fSLayer=-1;
  fSLadder=-1;
  fSSensor=-1;
}


void J4VTXPixelAreaSD::SetID(G4int trackID,G4int iLayer,G4int iLadder,
G4int iSensor){
  fSTrack=trackID;
  fSLayer=iLayer;
  fSLadder=iLadder;
  fSSensor=iSensor;
}

G4bool J4VTXPixelAreaSD::compareID(G4int trackID, G4int iLayer, G4int iLadder,
G4int iSensor){
  if ( fSTrack==trackID 
       && fSLayer==iLayer
       && fSLadder==iLadder
       && fSSensor==iSensor 
       )
    return TRUE;
  else
    return FALSE;
}


