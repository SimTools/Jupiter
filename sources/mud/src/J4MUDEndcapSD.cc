// $Id$
//*************************************************************************
//* --------------------
//* J4MUDEndcapSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "J4MUDEndcapSD.hh"
#include <math.h>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4MUDEndcapSD::J4MUDEndcapSD( J4VDetectorComponent* detector )
 :J4VSD<J4MUDEndcapHit>( detector )
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4MUDEndcapSD::~J4MUDEndcapSD() { }

//=====================================================================
//* Initialize --------------------------------------------------------
void J4MUDEndcapSD::Initialize( G4HCofThisEvent* HCTE )
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  
  MakeHitBuf(HCTE);  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------
G4bool J4MUDEndcapSD::ProcessHits( G4Step* aStep, G4TouchableHistory* /* ROhist */ )
{
  //In order to use Get function, you must call SetNewStep() at first.
  SetNewStep(aStep);
   
  //Only when a charged particle has just come into a sensitive detector,
  //create a new hit
  
  if ( GetCharge() == 0. ) return FALSE;
      
  //Get perticle information
  J4VComponent*          location      = GetComponent();
  G4int                  trackID       = GetTrackID();
  G4int                  mothertrackID = GetMotherTrackID();
  G4ParticleDefinition * particle      = GetParticle();
  G4double               tof           = GetTof();
  G4double               edep          = GetEnergyDeposit();
  G4double               etot          = GetTotalEnergy();
  G4ThreeVector          p             = GetMomentum();
  const G4ThreeVector&   pre           = GetPrePosition();
  const G4ThreeVector&   pos           = GetPostPosition();

#if 0
  G4cerr << "SDname = " << location->GetName() << " " 
  	 << "TrackID = " << trackID << " " 
  	 << "ParticleName = " << particle->GetParticleName() << " "
  	 << "PreStepPoint(x,y,z) = " << pre.x() << " " 
  	 << pre.y() << " " << pre.z() << G4endl; 
  G4cerr << "Endcap ID=" << location->GetMyID() << G4endl;
#endif

  // Create a new hit and push them to "Hit Coleltion"
  J4MUDEndcapHit* hit =  new J4MUDEndcapHit( location, trackID, mothertrackID, particle,
					   tof, edep, etot, p, pre, pos );
 
  ( (J4MUDEndcapHitBuf*)GetHitBuf() )->insert(hit);

  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------
void J4MUDEndcapSD::EndOfEvent( G4HCofThisEvent* /* HCTE */ ) { }

//=====================================================================
//* DrawAll -----------------------------------------------------------
void J4MUDEndcapSD::DrawAll() { }

//=====================================================================
//* PrintAll ----------------------------------------------------------
void J4MUDEndcapSD::PrintAll()
{
  G4int nHit= ( (J4MUDEndcapHitBuf*)GetHitBuf() )-> entries();
  G4cout << "------------------------------------------" << G4endl
         << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
  ( (J4MUDEndcapHitBuf*)GetHitBuf() )-> PrintAllHits();
}

