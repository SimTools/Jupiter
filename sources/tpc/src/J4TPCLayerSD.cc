//*************************************************************************
//* --------------------
//* J4TPCLayerSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4TPCLayerSD.hh"
#include <cmath>
 
//=====================================================================
//---------------------
// class definition
//---------------------

G4int J4TPCLayerSD::fLastMyID=-1;
G4int J4TPCLayerSD::fLastTrackID=-1;
J4TPCLayerHit *J4TPCLayerSD::fLastHit=0;

//=====================================================================
//* constructor -------------------------------------------------------

J4TPCLayerSD::J4TPCLayerSD(J4VDetectorComponent* detector)
		   :J4VSD<J4TPCLayerHit>(detector)
{  
}

//=====================================================================
//* destructor --------------------------------------------------------

J4TPCLayerSD::~J4TPCLayerSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4TPCLayerSD::Initialize(G4HCofThisEvent* HCTE)
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  
  MakeHitBuf(HCTE);  
  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4TPCLayerSD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
  //In order to use Get function, you must call SetNewStep() at first.
  
  SetNewStep(aStep);
   
  //Only when a charged particle has just come into a sensitive detector,
  //create a new hit
  
  //Get particle information
  G4double               edep          = GetEnergyDeposit();
  if (edep <= 0) return FALSE;
  J4VComponent*          location      = GetComponent();
  G4int                  myID          = location->GetMyID();
  G4int                  trackID       = GetTrackID();
  G4int                  mothertrackID = GetMotherTrackID();
  G4ParticleDefinition  *particle      = GetParticle();
  G4double               tof           = GetTof();
  G4double               etot          = GetTotalEnergy();
  G4ThreeVector          p             = GetMomentum();
  const G4ThreeVector   &pre           = GetPrePosition();
  const G4ThreeVector   &pos           = GetPostPosition();
  
#if 0  
  G4cerr << "SDname = " << location->GetName() << " " 
  	 << "TrackID = " << trackID << " " 
  	 << "ParticleName = " << particle->GetParticleName() << " "
  	 << "PreStepPoint(x,y,z) = " << pre.x() << " " 
  	 << pre.y() << " " << pre.z() << G4endl; 
#endif
#if 0
  if ( abs(particle->GetPDGEncoding()) == 11 ) {
     G4cerr << " PDG=" << particle->GetPDGEncoding() ;
     G4cerr << " TotalEnergy=" << GetTotalEnergy();
     G4cerr << " Mass =" << GetMass();
     G4cerr << " Pabs=" << p.mag() ;
     G4cerr << G4endl;
  }

  // Create a new hit and push them to "Hit Coleltion"
  std::cerr << " trackID=" << trackID << " last= " << fLastTrackID;
  std::cerr << " MyID=" << myID << " last=" << fLastMyID ;
  std::cerr << " edep=" << edep ;
  std::cerr << std::endl;
#endif

  if ( trackID != fLastTrackID || myID != fLastMyID )  { 
    fLastHit = new J4TPCLayerHit( location, trackID, mothertrackID, particle,
    			        tof, edep, etot, p, pre, pos);
    ((J4TPCLayerHitBuf*)GetHitBuf())->insert(fLastHit);
    fLastTrackID=trackID;
    fLastMyID=myID;
  }
  else {
    edep += fLastHit->GetEnergyDeposit();    
    fLastHit->SetEnergyDeposit(edep);
  }



  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4TPCLayerSD::EndOfEvent(G4HCofThisEvent *)
{			
}

//=====================================================================
//* clear -------------------------------------------------------------


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4TPCLayerSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4TPCLayerSD::PrintAll()
{
  G4int nHit= ((J4TPCLayerHitBuf*)GetHitBuf())-> entries();
  G4cout << "------------------------------------------" << G4endl
         << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
  ((J4TPCLayerHitBuf*)GetHitBuf())-> PrintAllHits();
}

