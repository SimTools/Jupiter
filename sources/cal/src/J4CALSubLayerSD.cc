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
#include "J4CALTower.hh"
#include "J4CALBlock.hh"
#include "J4CALMiniCone.hh"
#include "J4CALMiniTower.hh"
#include "J4CALLayer.hh"
#include "J4CALHit.hh"
#include "J4CALSubLayer.hh"
#include "J4CALSubLayerSD.hh"
#include <cmath>
#include "J4Timer.hh"
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALSubLayerSD::J4CALSubLayerSD(J4VDetectorComponent* detector)
		   :J4VSD<J4CALHit>(detector)
{  
  fTowerNClones = ( (J4CALSubLayer *)detector )->GetTowerNClones();

  fCalHits = new J4CALHit* [fTowerNClones];
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALSubLayerSD::~J4CALSubLayerSD()
{
#ifndef __GEANT452__
   if (fCalHits[fTowerNClones]) {
     delete[] fCalHits;
   }
#endif
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4CALSubLayerSD::Initialize( G4HCofThisEvent* HCTE )
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  
  MakeHitBuf(HCTE);  

  // Don't "delete" fCalHits[i]!
  // Geant4 deletes hit objects at
  // the end of the run.
  for (G4int i = 0; i < fTowerNClones; i++) {
    if ( fCalHits[i] ) {
         fCalHits[i]  = 0;
   }
  }
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4CALSubLayerSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
  //In order to use Get function, you must call SetNewStep() at first.
  SetNewStep(aStep);

  // Check SubLayer ID
  ////////////////////////////////////////////////////////////////
  // Calorimeter sub structure and depth-------------------------
  //
  // SubLayer->Layer->MiniTower->MiniCone->Block->Tower->Cone->CAL
  ////////////////////////////////////////////////////////////////
 // G4int SubLayerDepth  = 0;
  const G4int LayerDepth     = 1;
  const G4int MiniTowerDepth = 2;
  const G4int MiniConeDepth  = 3;
  const G4int BlockDepth     = 4;
  const G4int TowerDepth     = 5;
  const G4int ConeDepth      = 6;

  // poiters for components -------------------------------------
  J4VComponent*  ptrSubLayerComponent  = GetComponent();
  J4VComponent*  ptrLayerComponent     = GetComponent(LayerDepth);
  J4VComponent*  ptrMiniTowerComponent = GetComponent(MiniTowerDepth);
  J4VComponent*  ptrMiniConeComponent  = GetComponent(MiniConeDepth);
  J4VComponent*  ptrBlockComponent     = GetComponent(BlockDepth);
  J4VComponent*  ptrTowerComponent     = GetComponent(TowerDepth);
  J4VComponent*  ptrConeComponent      = GetComponent(ConeDepth);

  G4int  myConeID      = ptrConeComponent      -> GetMyID();
  G4int  myTowerID     = GetCloneID( ptrTowerComponent );
  G4int  myMiniConeID  = ptrMiniConeComponent  -> GetMyID();
  G4int  myMiniTowerID = ptrMiniTowerComponent -> GetMyID();
  G4int  myLayerID     = ptrLayerComponent     -> GetMyID();
  G4int  mySubLayerID  = ptrSubLayerComponent  -> GetMyID();

  G4int  trackID       = GetTrackID();
  G4int  mothertrackID = GetMotherTrackID(); 
  
  G4bool isBarrel      = ( (J4CALCone *)ptrConeComponent ) -> IsBarrel();
  const G4String &firstName = ( (J4CALBlock *)ptrBlockComponent ) -> GetFirstName();

  G4bool isEM; 
  if ( firstName == "EM" ) {
     isEM = TRUE;
  } else { 
     isEM = FALSE;
  }

  //Get perticle information
  G4double               tof      = GetTof();
  G4double               edep     = GetEnergyDeposit();
  const G4ThreeVector   &pre      = GetPrePosition();
  G4ParticleDefinition  *particle = GetParticle(); 

#if 0
  G4cerr << ptrSubLayerComponent -> GetName() << " "
         << G4endl;
#endif

#if 0
  G4cerr << "fTowerNCloens = " << fTowerNClones 
         << ", fMiniTowerNClones = " << fMiniTowerNClones << G4endl;

  G4cerr << "ConeID : "      << myConeID << " "
         << "TowerID : "     << myTowerID << " "
         << "MiniConeID : "  << myMiniConeID << " " 
         << "MiniTowerID : " << myMiniTowerID << " " 
         << "LayerID : "     << myLayerID << " " 
         << "SubLayerID : "  << mySubLayerID << " " 
         << "ClonesID : "    << myTowerID << " " 
         << "TrackID : "     << trackID << " " 
         << "motherTrackID : " << mothertrackID << " " 
         << "isBarrel : "    << isBarrel << " " 
         << "isEM : "        << isEM << " " 
         << "TOF : "         << tof << " "
         << "edep : "        << edep << " "
         << "pre  : "        << pre << " "
         << "particle  : "   << particle->GetParticleName() << " "
         << G4endl;
#endif

  // Create new hit
  //IncrementHitNumber();

  if ( !fCalHits[myTowerID] ) {

    // create new hit!
    fCalHits[myTowerID] = new J4CALHit(
                                                ptrSubLayerComponent,
                                                 myConeID, myTowerID,
                                         myMiniConeID, myMiniTowerID,
                                             myLayerID, mySubLayerID,
                                                      isBarrel, isEM,
                                       edep, tof, pre, mothertrackID,
                                                   trackID, particle );

   ((J4CALHitBuf *)GetHitBuf())->insert( fCalHits[myTowerID] );

  } else {

     fCalHits[myTowerID]->AccumulateEdep(edep);

     if ( fCalHits[myTowerID]->GetMotherTrackID() > mothertrackID
          &&fCalHits[myTowerID]->GetTof() > tof)
        {
         // replace information of first hit
         fCalHits[myTowerID]->SetTof(tof);
         fCalHits[myTowerID]->SetInjectionPoint(pre);
         fCalHits[myTowerID]->SetMotherTrackID(mothertrackID);
         fCalHits[myTowerID]->SetTrackID(trackID);
         fCalHits[myTowerID]->SetParticle(particle);
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
  G4cout << "------------------------------------------" << G4endl; 
  G4cout << "*** tracker Hit (#hits=" << nHit << ")" <<G4endl;
  ( (J4CALHitBuf*)GetHitBuf() )-> PrintAllHits();
}
