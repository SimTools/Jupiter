// $id: J4VTXLadderSD.cc,v 1.1.1.2 2001/05/31 06:35:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4VTXLadderSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2002/10/24  T.Aso	Original version.
//*************************************************************************

#include "J4VTXLadderSD.hh"
#include <math.h>

//=====================================================================
//---------------------
// class definition
//---------------------
//=====================================================================
//* constructor -------------------------------------------------------

J4VTXLadderSD::J4VTXLadderSD(J4VDetectorComponent* detector)
             :J4VSD<J4VTXLadderHit>(detector)
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXLadderSD::~J4VTXLadderSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4VTXLadderSD::Initialize(G4HCofThisEvent* HCTE)
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  MakeHitBuf(HCTE);  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4VTXLadderSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
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

  G4int layerID = GetComponent()->GetMother()->GetMyID();
  G4int ladderID = GetCloneID();

  G4double             edep      = GetEnergyDeposit();
  G4ThreeVector        trkP      = GetMomentum();
  G4double             trkE      = GetTotalEnergy();
  G4double             tof       = GetTof();
  const G4ThreeVector &inPos	   = GetPrePosition();
  const G4ThreeVector &outPos	   = GetPostPosition();

// Create a new hit and push them to "Hit Collection"
  J4VTXLadderHit* hit = new J4VTXLadderHit(
                               GetComponent(),
                               trackID, mothertrackID, particle,
			       layerID,ladderID,
                               edep, trkP, trkE, tof,
                               inPos,outPos);
     G4int SColNo = ((J4VTXLadderHitBuf*)GetHitBuf())-> insert(hit);

  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4VTXLadderSD::EndOfEvent(G4HCofThisEvent* HCTE)
{
}

//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4VTXLadderSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4VTXLadderSD::PrintAll()
{
  G4int nHit= ((J4VTXLadderHitBuf*)GetHitBuf())-> entries();
  std::cout << "------------------------------------------" << std::endl
         << "*** tracker Hit (#hits=" << nHit << ")" << std::endl;
  ((J4VTXLadderHitBuf*)GetHitBuf())-> PrintAllHits();
}

//====================================================================


