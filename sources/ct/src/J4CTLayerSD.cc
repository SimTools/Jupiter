// $Id$
//*************************************************************************
//* --------------------
//* J4CTLayerSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CTLayerSD.hh"
#include <math.h>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CTLayerSD::J4CTLayerSD(J4VDetectorComponent* detector)
		   :J4VSD<J4CTLayerHit>(detector)
{  
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CTLayerSD::~J4CTLayerSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4CTLayerSD::Initialize(G4HCofThisEvent* HCTE)
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  
  MakeHitBuf(HCTE);  
  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4CTLayerSD::ProcessHits(G4Step*              aStep, 
                                G4TouchableHistory* /* ROhist */)
{
  //In order to use Get function, you must call SetNewStep() at first.
  
  SetNewStep(aStep);
   
  //Only when a charged particle has just come into a sensitive detector,
  //create a new hit
  
  if(GetCharge() == 0.) return FALSE;
  
      
  //Get perticle information

  J4VComponent*          location      = GetComponent();
  G4int                  trackID       = GetTrackID();
  G4int                  mothertrackID = GetMotherTrackID();
  G4ParticleDefinition  *particle      = GetParticle();
  G4double               tof           = GetTof();
  G4double               edep          = GetEnergyDeposit();
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
  G4cerr << "Layer ID=" << location->GetMyID() << G4endl;
#endif

  // Create a new hit and push them to "Hit Coleltion"
 
     J4CTLayerHit* hit = 
       new J4CTLayerHit( location, trackID, mothertrackID, particle,
       			        tof, edep, etot, p, pre, pos);
 
     ((J4CTLayerHitBuf*)GetHitBuf())->insert(hit);

     return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4CTLayerSD::EndOfEvent(G4HCofThisEvent* /* HCTE */)
{			
}

//=====================================================================
//* clear -------------------------------------------------------------


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4CTLayerSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4CTLayerSD::PrintAll()
{
  G4int nHit= ((J4CTLayerHitBuf*)GetHitBuf())-> entries();
  G4cout << "------------------------------------------" << G4endl
         << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
  ((J4CTLayerHitBuf*)GetHitBuf())-> PrintAllHits();
}

