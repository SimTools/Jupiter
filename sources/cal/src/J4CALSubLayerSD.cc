// $Id$
//*************************************************************************
//* --------------------
//* J4CALSubLayerSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALCone.hh"
#include "J4CALSubLayerSD.hh"
#include "J4CALSubLayer.hh"
#include "J4CALMiniTower.hh"
#include <cmath>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALSubLayerSD::J4CALSubLayerSD(J4VDetectorComponent* detector)
		   :J4VSD<J4CALHit>(detector)
{  
  //   fNsectionsInPhi = ((J4CALEM *)detector)->GetNsectionsInPhi();
  //   fCalHits = new J4CALHit* [fNsectionsInPhi];
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALSubLayerSD::~J4CALSubLayerSD()
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

void J4CALSubLayerSD::Initialize(G4HCofThisEvent* HCTE)
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  
  MakeHitBuf(HCTE);  

  //  for (G4int i=0; i<fNsectionsInPhi; i++) {
  //if (fCalHits[i]) fCalHits[i] = 0;   // Don't delete fCalHits[i]!
                                         // Geant4 deletes hit objects at
                                         // the end of the run.
  //}

}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4CALSubLayerSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
  //In order to use Get function, you must call SetNewStep() at first.
  
  SetNewStep(aStep);
   
  // Check CALSubLayer ID
 
  G4int          motherdepth      = 1;
  G4int          grandmotherdepth = 2;
  //G4int        daughterdepth    = -1;

  J4VComponent*  component       = GetComponent();                 // SubLayer 
  J4VComponent*  mothercomp      = GetComponent(motherdepth);      // Tower
  J4VComponent*  grandmothercomp = GetComponent(grandmotherdepth); // Cone 
  G4int          myPhiNumber     = GetCloneID(mothercomp); 
  G4int          myThetaNumber   = grandmothercomp->GetMyID(); 
  G4int          mothertrackID   = GetMotherTrackID(); 
  G4int          trackID         = GetTrackID(); 
  //G4bool         isbarrel        = ((J4CALMiniCone *)grandmothercomp)->IsBarrel();
  G4bool         isbarrel        = ((J4CALCone *)grandmothercomp)->IsBarrel();
  G4bool         isSubLayer      = TRUE; 

  //Get perticle information
  G4double               tof           = GetTof();
  G4double               edep          = GetEnergyDeposit();
  const G4ThreeVector   &pre           = GetPrePosition();
  G4ParticleDefinition  *particle      = GetParticle(); 
    
  // Create new hit

  if (!fCalHits[myPhiNumber]) {

     // create new hit!
     fCalHits[myPhiNumber] = new J4CALHit(component, myThetaNumber, myPhiNumber,  
                                         isbarrel, isSubLayer,  edep, tof, pre, mothertrackID, 
                                         trackID, particle);
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

void J4CALSubLayerSD::EndOfEvent(G4HCofThisEvent* HCTE)
{			
}

//=====================================================================
//* clear -------------------------------------------------------------


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4CALSubLayerSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4CALSubLayerSD::PrintAll()
{
  G4int nHit= ((J4CALHitBuf*)GetHitBuf())-> entries();
  std::cout << "------------------------------------------" << std::endl
         << "*** tracker Hit (#hits=" << nHit << ")" << std::endl;
  ((J4CALHitBuf*)GetHitBuf())-> PrintAllHits();
}
