// $Id$
//*************************************************************************
//* --------------------
//* J4VMUDActiveSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include <iomanip>
#include "J4VSD.hh"
#include "J4MUDHit.hh"
#include "J4VMUDActiveSD.hh"
#include "J4VDetectorComponent.hh"
#include "J4VMUDDetectorComponent.hh"
#include "J4VMUDEndcapTrap.hh"
#include "J4MUDEndcapActive.hh"
#include "J4MUDFrontEndcapActive.hh"
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4VMUDActiveSD::J4VMUDActiveSD( J4VDetectorComponent* detector )
: J4VSD<J4MUDHit>( detector )
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4VMUDActiveSD::~J4VMUDActiveSD() { }

//=====================================================================
//* Initialize --------------------------------------------------------
void J4VMUDActiveSD::Initialize( G4HCofThisEvent* HCTE )
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  
  MakeHitBuf( HCTE );  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------
G4bool J4VMUDActiveSD::ProcessHits( G4Step* aStep, G4TouchableHistory* /* ROhist */ )
{

  //In order to use Get function, you must call SetNewStep() at first.
  SetNewStep(aStep);
   
  //Only when a charged particle has just come into a sensitive detector,
  //create a new hit
  
  if ( GetCharge() == 0. ) return false;

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
  
#ifdef __MUDREPLICA__
  G4int                  blockID       = GetCloneID( location->GetMother() );
#else
  G4int                  blockID       = location->GetMother()->GetMyID();
#endif
 
  G4bool                 isBarrel      = IsBarrel();
  G4bool                 isFront       = IsFront();
  G4int                  layerID       = location->GetMyID();
  
#if 0
  G4String name  = "";
  
  // Barrel Part
  if ( isBarrel ) {
    name = "Barrel";
    layerID = location->GetMyID();
  } else {

    // FrontEndcap part
    if ( isFront ) {
      if ( location->GetMyID() < ((J4MUDFrontEndcapActive*)location)->GetNLayers() ) {
	name    = "FrontL";
	layerID = location->GetMyID();
      } else { 
	name    = "FrontR";
	layerID = location->GetMyID() - ((J4MUDFrontEndcapActive*)location)->GetNLayers();
      }
    } else {
      // Endcap part
      if ( location->GetMyID() < ((J4MUDEndcapActive*)location)->GetNLayers() ) {
	name    = "EndcapL";
	layerID = location->GetMyID();
      } else {
	name    = "EndcapR";
	layerID = location->GetMyID() - ((J4MUDEndcapActive*)location)->GetNLayers();
      }
    }
  }
 
  G4cerr << "Name = " << std::setw(7) << name << " "
	 << "blockID = " << blockID << " "
	 << "layerID = " << layerID << " "
  	 << "ParticleName = " << particle->GetParticleName() << " "
	 << G4endl;
#endif

  // Create a new hit and push them to "Hit Coleltion"
  //J4MUDHit* hit =  new J4MUDHit( location, trackID, mothertrackID, particle, tof, edep, etot, p, pre, pos );
  J4MUDHit* hit =  new J4MUDHit( location, blockID, layerID, isBarrel, isFront, trackID, mothertrackID, particle, tof, edep, etot, p, pre, pos );
 
  ( (J4MUDHitBuf*)GetHitBuf() )->insert(hit);

  return true;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------
void J4VMUDActiveSD::EndOfEvent( G4HCofThisEvent* /* HCTE */ ) { }

//=====================================================================
//* DrawAll -----------------------------------------------------------
void J4VMUDActiveSD::DrawAll() { }

//=====================================================================
//* PrintAll ----------------------------------------------------------
void J4VMUDActiveSD::PrintAll()
{
  G4int nHit= ( (J4MUDHitBuf*)GetHitBuf() )-> entries();
  G4cout << "------------------------------------------" << G4endl
         << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
  ( (J4MUDHitBuf*)GetHitBuf() )-> PrintAllHits();
}
