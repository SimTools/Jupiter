// $Id$
//*************************************************************************
//* --------------------
//* J4CALSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALSD.hh"
#include "J4CAL.hh"
#include "J4CALCone.hh"
#include "J4CALMiniTower.hh"
#include "J4CALEM.hh"
#include <cmath>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALSD::J4CALSD(J4VDetectorComponent* detector)
		   :J4VSD<J4CALHit>(detector)
{  
  //   fNsectionsInPhi = ((J4CALEM *)detector)->GetNsectionsInPhi();
  //   fCalHits = new J4CALHit* [fNsectionsInPhi];
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALSD::~J4CALSD()
{
//#ifndef __GEANT452__
//   if (fCalHits) {
//      for (G4int i=0; i<fNsectionsInPhi; i++) {
//         if (fCalHits[i]) delete fCalHits[i];
//      }
//      delete[] fCalHits;
//   }
//#endif
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4CALSD::Initialize(G4HCofThisEvent* HCTE)
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  
  MakeHitBuf(HCTE);  

  // for (G4int i=0; i<fNsectionsInPhi; i++) {
  //     if (fCalHits[i]) fCalHits[i] = 0;   // Don't delete fCalHits[i]!
                                         // Geant4 deletes hit objects at
                                         // the end of the run.
  //  }

}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4CALSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
  //In order to use Get function, you must call SetNewStep() at first.
  
  SetNewStep(aStep);
   
  // Check SubLayer ID
  ////////////////////////////////////////////////////////////////
  // Calorimeter sub structure and depth-------------------------
  //
  // SubLayer->Layer->MiniTower->MiniCone->Block->Tower->Cone->CAL
  ////////////////////////////////////////////////////////////////
  G4int LayerDepth     = 1;
  G4int MiniTowerDepth = 2;
  G4int MiniConeDepth  = 3;
  G4int BlockDepth     = 4;
  G4int TowerDepth     = 5;
  G4int ConeDepth      = 6;
  //G4int        daughterdepth    = -1;

  // poiters for components -------------------------------------
  J4VComponent*  ptrLayerComponent     = GetComponent(LayerDepth);
  J4VComponent*  ptrMiniTowerComponent = GetComponent(MiniTowerDepth);
  J4VComponent*  ptrMiniConeComponent  = GetComponent(MiniConeDepth);
  J4VComponent*  ptrBlockComponent     = GetComponent(BlockDepth);
  J4VComponent*  ptrTowerComponent     = GetComponent(TowerDepth);
  J4VComponent*  ptrConeComponent      = GetComponent(ConeDepth);

  G4int  myMiniTowrID     = GetCloneID(ptrMiniTowerComponent);
  G4int  myTowerID        = GetCloneID(ptrTowerComponent);
  G4int  myPhiNumber      = GetCloneID(ptrTowerComponent);

  
  G4int  myMiniConeThetaID = ptrMiniTowerComponent -> GetMyID();
  G4int  myThetaID         = ptrTowerComponent     -> GetMyID();
  G4int  myThetaNumber     = ptrConeComponent      -> GetMyID();
  //  G4int  isEM              = ;
  //  G4int  isHD              = ;

  G4int  mothertrackID   = GetMotherTrackID(); 
  G4int  trackID         = GetTrackID(); 
  G4bool isbarrel        = ((J4CALCone *)ptrConeComponent)->IsBarrel();
  G4bool isCAL           = TRUE;

  //Get perticle information

  G4double               tof      = GetTof();
  G4double               edep     = GetEnergyDeposit();
  const G4ThreeVector   &pre      = GetPrePosition();
  G4ParticleDefinition  *particle = GetParticle(); 
  
  // Create new hit

  if (!fCalHits[myPhiNumber]) {

     // create new hit!
     fCalHits[myPhiNumber] = new J4CALHit(ptrLayerComponent, myThetaNumber, myPhiNumber,  
                                         isbarrel, isCAL,  edep, tof, pre, mothertrackID, trackID, particle);
     
     ((J4CALHitBuf *)GetHitBuf())->insert(fCalHits[myPhiNumber]);

  } else {

     fCalHits[myPhiNumber]->AccumulateEdep(edep);

     if (fCalHits[myPhiNumber]->GetMotherTrackID() > mothertrackID &&
         fCalHits[myPhiNumber]->GetTof() > tof) {
         // replace information of first hit
         fCalHits[myPhiNumber]->SetTof(tof);
         fCalHits[myPhiNumber]->SetInjectionPoint(pre);
         fCalHits[myPhiNumber]->SetMotherTrackID(mothertrackID);
         fCalHits[myPhiNumber]->SetTrackID(trackID);
         fCalHits[myPhiNumber]->SetParticle(particle);
     }
  }   

  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4CALSD::EndOfEvent(G4HCofThisEvent* HCTE)
{			
}

//=====================================================================
//* clear -------------------------------------------------------------


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4CALSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4CALSD::PrintAll()
{
  G4int nHit= ((J4CALHitBuf*)GetHitBuf())-> entries();
  std::cout << "------------------------------------------" << std::endl
         << "*** tracker Hit (#hits=" << nHit << ")" << std::endl;
  ((J4CALHitBuf*)GetHitBuf())-> PrintAllHits();
}
