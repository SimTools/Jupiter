// $id: J4VTXSensorSD.cc,v 1.1.1.2 2001/05/31 06:35:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4VTXSensorSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version
//*	2002/11/20  T.Aso       Modify
//*************************************************************************

#include "J4VTXSensorSD.hh"
#include "G4VProcess.hh"
#include <math.h>

//=====================================================================
//---------------------
// class definition
//---------------------
//=====================================================================
//* constructor -------------------------------------------------------

J4VTXSensorSD::J4VTXSensorSD(J4VDetectorComponent* detector)
             :J4VSD<J4VTXSensorHit>(detector),
              fSTrack(-1), fSLayer(-1), fSLadder(-1), fSSensor(-1), 
              fSColNo(0)     
{
  G4cout << " ------ SensorSD ------ " << G4endl;
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXSensorSD::~J4VTXSensorSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4VTXSensorSD::Initialize(G4HCofThisEvent* HCTE)
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  MakeHitBuf(HCTE);
  InitID();
  fSColNo = -1;
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4VTXSensorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
  //In order to use Get function of J4VSensitiveDetector,
  // you must call SetNewStep() at first.

  SetNewStep(aStep);
  //Only when a charged particle has just come into a sensitive detector,
  //create a new hit
  //if(GetCharge() == 0.) return FALSE;
      
  //Get particle information
  G4int                 trackID         = GetTrackID();
  G4int                 mothertrackID   = GetMotherTrackID();
  G4ParticleDefinition *particle        = GetParticle();
  G4double             weight           = GetWeight(); 

  const G4ThreeVector &origin = GetTrack()->GetVertexPosition();
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
    procName = process->GetProcessName();
  }

  J4VComponent  *sensor      = GetComponent();
  J4VComponent  *ladder      = sensor->GetMother();
  J4VComponent  *layer       = ladder->GetMother();
#if 0
  G4VPhysicalVolume* sensorPV = sensor->GetPV();
  G4VPhysicalVolume* ladderPV = sensorPV->GetMother();

  G4int iLayer    =  layer->GetMyID();
  G4int iLadder   =  ladderPV->GetCopyNo();
  G4int iSensor   =  sensorPV->GetCopyNo();

  G4double             edep      = GetEnergyDeposit();
  G4ThreeVector        trkP      = GetMomentum();
  G4double             trkE      = GetTotalEnergy();
  G4double             tof       = GetTof();
  const G4ThreeVector &inPos	   = GetPrePosition();
  const G4ThreeVector &outPos	   = GetPostPosition();
  G4ThreeVector        localinPos  = GlobalToLocalPosition(inPos);
  G4ThreeVector        localoutPos = GlobalToLocalPosition(outPos);
#endif
// Create a new hit and push them to "Hit Collection"
#if 0
  if(! compareID(trackID,iLayer,iLadder,iSensor) ){
        J4VTXSensorHit* hit = new J4VTXSensorHit(
		               GetComponent(),
                               trackID, mothertrackID, particle,
			       weight,
			       origin,origP,procName,
                               iLayer,iLadder,iSensor,
		               edep, trkP, trkE,tof,
                               inPos,outPos,
                               localinPos,localoutPos);
        fSColNo = ((J4VTXSensorHitBuf*)GetHitBuf())-> insert(hit);
        SetID(trackID,iLayer,iLadder,iSensor);
  } else {
       (*(J4VTXSensorHitBuf*)GetHitBuf())[fSColNo-1]->AddEdep(edep);
       (*(J4VTXSensorHitBuf*)GetHitBuf())[fSColNo-1]->SetOutPos(outPos);
       (*(J4VTXSensorHitBuf*)GetHitBuf())[fSColNo-1]->SetLocalOutPos(localoutPos);
  }    
#endif

  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4VTXSensorSD::EndOfEvent(G4HCofThisEvent* HCTE)
{
}

//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4VTXSensorSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4VTXSensorSD::PrintAll()
{
  G4int nHit= ((J4VTXSensorHitBuf*)GetHitBuf())-> entries();
  G4cout << "------------------------------------------" << G4endl
         << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
  ((J4VTXSensorHitBuf*)GetHitBuf())-> PrintAllHits();
}

//====================================================================

G4ThreeVector J4VTXSensorSD::GlobalToLocalPosition(G4ThreeVector gpIn){
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
  return pos;
}

void J4VTXSensorSD::InitID(){
  fSTrack=-1;
  fSLayer=-1;
  fSLadder=-1;
  fSSensor=-1;
}


void J4VTXSensorSD::SetID(G4int trackID,G4int iLayer,G4int iLadder,
G4int iSensor){
  fSTrack=trackID;
  fSLayer=iLayer;
  fSLadder=iLadder;
  fSSensor=iSensor;
}

G4bool J4VTXSensorSD::compareID(G4int trackID, G4int iLayer, G4int iLadder,
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


