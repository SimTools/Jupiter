//*************************************************************************
//* --------------------
//* J4TPCDriftRegionSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4TPCDriftRegionSD.hh"
#include "J4TPCPostHit.hh"
#include "J4VTPCDetectorComponent.hh"
#include "G4VSolid.hh"
#include "G4RotationMatrix.hh"

G4int J4TPCDriftRegionSD::fgTrackRegID = -1;
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4TPCDriftRegionSD::J4TPCDriftRegionSD(J4VDetectorComponent* detector)
		   :J4VSD<J4TPCLayerHit>(detector)
{  
  SetCurTrackID(INT_MAX);
}

//=====================================================================
//* destructor --------------------------------------------------------

J4TPCDriftRegionSD::~J4TPCDriftRegionSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4TPCDriftRegionSD::Initialize(G4HCofThisEvent* HCTE)
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  
  MakeHitBuf(HCTE);  
  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------

G4bool J4TPCDriftRegionSD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
  //In order to use Get function, you must call SetNewStep() at first.
  
  SetNewStep(aStep);

  const G4ThreeVector     &pos      = GetPostPosition();
  G4ThreeVector            p        = GetMomentum();
  J4VComponent*            location = GetComponent();
  G4int                    trackID  = GetTrackID();
#if 1
  const G4RotationMatrix  *rotp     = GetRotation();
  G4ThreeVector            localp   = rotp ? rotp->inverse() * p : p;
  G4ThreeVector            localpos = (rotp ? rotp->inverse()
                                    * (pos - GetTranslation())
                                    : (pos - GetTranslation()));
  G4double                 distance = location->GetSolid()
                                      ->DistanceToOut(localpos, localp.unit());

  if (distance > kCarTolerance || trackID >= GetCurTrackID()) {
     return FALSE;
  }

  SetCurTrackID(trackID);
#endif
  //Get particle information

  G4int                  mothertrackID = GetMotherTrackID();
  G4ParticleDefinition  *particle      = GetParticle();
  G4double               tof           = GetTof();
  G4double               etot          = GetTotalEnergy();
  
#if 0  
  G4cerr << "SDname = " << GetComponent()->GetName() << " " 
  	 << "TrackID = " << trackID << " " 
  	 << "ParticleName = " << particle->GetParticleName() << " "
  	 << "PreStepPoint(x,y,z) = " << pre.x() << " " 
  	 << pre.y() << " " << pre.z() << G4endl 
         << "PreStepR =  " << pre.perp() << " "
         << "PostStepR = " << pos.perp() << G4endl;
#endif

#if 0
  // write only if hit is not in layer
  if (static_cast<J4VTPCDetectorComponent *>(GetComponent(-1))->IsLayer()) {
     return FALSE;
  }
  
#endif

  // Create a new hit and push them to "Hit Coleltion"
 
  J4TPCPostHit* hitp = 
    new J4TPCPostHit(location, trackID, mothertrackID, particle,
       			        tof, etot, p, pos);
 
  static_cast<J4TPCPostHitBuf *>(GetHitBuf())->insert(hitp);

  return TRUE;
} 

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4TPCDriftRegionSD::EndOfEvent(G4HCofThisEvent *)
{			
  SetCurTrackID(INT_MAX);
}

//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4TPCDriftRegionSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4TPCDriftRegionSD::PrintAll()
{
}

