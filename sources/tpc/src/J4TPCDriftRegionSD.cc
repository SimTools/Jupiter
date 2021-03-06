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

#include "G4Version.hh"
#if G4VERSION_NUMBER >= 900
#include "G4GeometryTolerance.hh"
#endif

#include "J4TPCDriftRegionSD.hh"
#include "J4TPCPostHit.hh"
#include "J4TPCPostHitKeeper.hh"
#include "J4TPCParameterList.hh"
#include "J4VTPCDetectorComponent.hh"
#include "J4TrackingAction.hh"
#include "G4VSolid.hh"
#include "G4RotationMatrix.hh"

//#define __DEBUG__

//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4TPCDriftRegionSD::J4TPCDriftRegionSD(J4VDetectorComponent* detector)
		   :J4VSD<J4TPCPostHit>(detector)
{  
  J4TrackingAction::GetInstance()->Add(J4TPCPostHitKeeper::GetInstance());
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

  if (!IsExiting(pos, p) ||
      !J4TPCPostHitKeeper::GetInstance()->IsNext()) {
    return FALSE;
  }

  //Get particle information

  G4int                  mothertrackID = GetMotherTrackID();
  G4ParticleDefinition  *particle      = GetParticle();
  G4double               tof           = GetTof();
  G4double               etot          = GetTotalEnergy();

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
  
#ifdef __DEBUG__
  const G4ThreeVector     &pre      = GetPrePosition();
  G4cerr << "SDname       = "  << GetComponent()->GetName()   << G4endl 
  	 << "TrackID      = "  << trackID                     << G4endl 
  	 << "Mom TrackID  = "  << mothertrackID               << G4endl 
  	 << "ParticleName = "  << particle->GetParticleName() << G4endl
  	 << "Etot         = "  << etot/GeV      << " [GeV]"   << G4endl
  	 << "P            = (" << p.x()/GeV     << ", " 
  	                       << p.y()/GeV     << ", " 
                               << p.z()/GeV     << ") [GeV]"  << G4endl 
  	 << "PreStepPoint = (" << pre.x()/cm    << ", " 
  	                       << pre.y()/cm    << ", " 
                               << pre.z()/cm    << ") [cm]"   << G4endl 
  	 << "PosStepPoint = (" << pos.x()/cm    << ", " 
  	                       << pos.y()/cm    << ", " 
                               << pos.z()/cm    << ") [cm]"   << G4endl 
         << "PreStepR     = "  << pre.perp()/cm << " [cm]"    << G4endl 
         << "PreStepZ     = "  << pre.z()/cm    << " [cm]"    << G4endl 
         << "PostStepR    = "  << pos.perp()/cm << " [cm]"    << G4endl
         << "PostStepZ    = "  << pos.z()/cm    << " [cm]"    << G4endl;
#endif

  return TRUE;
} 

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4TPCDriftRegionSD::EndOfEvent(G4HCofThisEvent *)
{			
   J4TPCPostHitKeeper::GetInstance()->Reset();
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
  static G4double tol = 10.;
    
#if G4VERSION_NUMBER < 900
  if (std::abs(pos.perp() - list->GetOuterSupportTubInnerR()) <= tol*kCarTolerance &&
#else
  if (std::abs(pos.perp() - list->GetOuterSupportTubInnerR()) <= tol*G4GeometryTolerance::GetInstance()->GetSurfaceTolerance() &&
#endif
      p.x() * pos.x() + p.y() * pos.y() > 0.) {
     return TRUE;
  }
  static G4double zend = list->GetPadPlaneFrontZ() + 0.5*list->GetTPCHalfZ();
#if G4VERSION_NUMBER < 900
  if (std::abs(std::abs(pos.z()) - zend) <= tol*kCarTolerance && p.z() * pos.z() > 0.) {
#else
  if (std::abs(std::abs(pos.z()) - zend) <= tol*G4GeometryTolerance::GetInstance()->GetSurfaceTolerance() && p.z() * pos.z() > 0.) {
#endif
     return TRUE;
  }
  return FALSE;
}

