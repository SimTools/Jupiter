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
#include "J4TPCParameterList.hh"
#include "J4VTPCDetectorComponent.hh"
#include "G4VSolid.hh"
#include "G4RotationMatrix.hh"

//#define __DEBUG__

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
  const G4RotationMatrix  *rotp     = GetRotation();
  G4ThreeVector            localp   = rotp ? rotp->inverse() * p : p;
  G4ThreeVector            localpos = (rotp ? rotp->inverse()
                                    * (pos - GetTranslation())
                                    : (pos - GetTranslation()));

  if (!IsExiting(localpos, localp) || !J4TrackingAction::IsNext(fgTrackRegID)) {
    return FALSE;
  }

  //Get particle information

  G4int                  mothertrackID = GetMotherTrackID();
  G4ParticleDefinition  *particle      = GetParticle();
  G4double               tof           = GetTof();
  G4double               etot          = GetTotalEnergy();
  
#if 0  
  G4cerr << "SDname       = " << GetComponent()->GetName()   << G4endl 
  	 << "TrackID      = " << trackID                     << G4endl 
  	 << "ParticleName = " << particle->GetParticleName() << G4endl
  	 << "PreStepPoint = " << pre.x() << " " 
  	                      << pre.y() << " " << pre.z()   << G4endl 
         << "PreStepR     = " << pre.perp()                  << G4endl 
         << "PostStepR    = " << pos.perp()                  << G4endl;
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
 
#ifdef __DEBUG__
  G4int nhits = static_cast<J4TPCPostHitBuf *>(GetHitBuf())->insert(hitp);
  G4cerr << " posthit id (fgNhits) = " << hitp->GetPostHitID() << G4endl;
  G4cerr << " posthit id (entries) = " << nhits - 1            << G4endl;
#else
  static_cast<J4TPCPostHitBuf *>(GetHitBuf())->insert(hitp);
#endif

  return TRUE;
} 

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4TPCDriftRegionSD::EndOfEvent(G4HCofThisEvent *)
{			
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

//=====================================================================
//* IsExiting ---------------------------------------------------------

G4bool J4TPCDriftRegionSD::IsExiting(const G4ThreeVector &pos,
                                     const G4ThreeVector &p) const
{
  J4TPCParameterList *list = J4TPCParameterList::GetInstance();
    
  if (abs(pos.perp() - list->GetOuterSupportTubInnerR()) <= kCarTolerance &&
      p.x() * pos.x() + p.y() * pos.y() > 0.) {
     return TRUE;
  }
  if (abs(abs(pos.z()) - list->GetPadPlaneFrontZ()) <= kCarTolerance &&
      p.z() * pos.z() > 0.) {
     return TRUE;
  }
  return FALSE;
}

