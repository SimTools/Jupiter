// $id: J4VTXLayerSD.cc,v 1.1.1.2 2001/05/31 06:35:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4VTXLayerSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2002/10/24  T.Aso	Original version.
//*************************************************************************

#include "J4VTXLayerSD.hh"
#include <math.h>

//=====================================================================
//---------------------
// class definition
//---------------------
//=====================================================================
//* constructor -------------------------------------------------------

J4VTXLayerSD::J4VTXLayerSD(J4VDetectorComponent* detector)
             :J4VSD<J4VTXLayerHit>(detector)
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXLayerSD::~J4VTXLayerSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4VTXLayerSD::Initialize(G4HCofThisEvent* HCTE)
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  MakeHitBuf(HCTE);  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4VTXLayerSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
  //In order to use Get function of J4VSensitiveDetector,
  // you must call SetNewStep() at first.

  SetNewStep(aStep);
  //Only when a charged particle has just come into a sensitive detector,
  //create a new hit
  //if(GetCharge() == 0.) return FALSE;
      
  //Get perticle information
  G4int                 trackID         = GetTrackID();
  G4int                 mothertrackID   = GetMotherTrackID();
  G4ParticleDefinition *particle        = GetParticle();

  G4int layerID = GetComponent()->GetMyID();

  G4double             edep      = GetEnergyDeposit();
  G4ThreeVector        trkP      = GetMomentum();
  G4double             trkE      = GetTotalEnergy();
  G4double             tof       = GetTof();
  const G4ThreeVector &inPos	   = GetPrePosition();
  const G4ThreeVector &outPos	   = GetPostPosition();

// Create a new hit and push them to "Hit Collection"
  J4VTXLayerHit* hit = new J4VTXLayerHit(
                               GetComponent(),
                               trackID, mothertrackID, particle,
			       layerID,
                               edep, trkP, trkE, tof,
                               inPos,outPos);
     G4int SColNo = ((J4VTXLayerHitBuf*)GetHitBuf())-> insert(hit);

  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4VTXLayerSD::EndOfEvent(G4HCofThisEvent* HCTE)
{
}

//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4VTXLayerSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4VTXLayerSD::PrintAll()
{
  G4int nHit= ((J4VTXLayerHitBuf*)GetHitBuf())-> entries();
  G4cout << "------------------------------------------" << G4endl
         << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
  ((J4VTXLayerHitBuf*)GetHitBuf())-> PrintAllHits();
}

//====================================================================

