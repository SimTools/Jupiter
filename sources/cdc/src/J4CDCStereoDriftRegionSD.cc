// $Id$
//*************************************************************************
//* --------------------
//* J4CDCStereoDriftRegionSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CDCStereoDriftRegionSD.hh"
#include "J4CDCStereoDriftRegion.hh"
#include "J4CDCSenseWire.hh"
#include <math.h>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CDCStereoDriftRegionSD::J4CDCStereoDriftRegionSD(J4VDetectorComponent* detector)
		                   :J4VSD<J4CDCStereoDriftRegionHit>(detector)
{  
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CDCStereoDriftRegionSD::~J4CDCStereoDriftRegionSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4CDCStereoDriftRegionSD::Initialize(G4HCofThisEvent* HCTE)
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  
  MakeHitBuf(HCTE);  
  
// G4cerr <<" J4CDCStereoDriftRegion:Initialize is called " << G4endl;
  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------


// !! ATTENTION !!
// This is test varsion. You MUST change it.


G4bool J4CDCStereoDriftRegionSD::ProcessHits(G4Step* aStep, 
                                           G4TouchableHistory* ROhist)
{
	
  //In order to use Get function, you must call SetNewStep() at first.
  
  SetNewStep(aStep);
   
  //Only when a charged particle has just come into a sensitive detector,
  //create a new hit
  
  if(!GetCharge()) return FALSE;
  
  //Increment HitNumber
  
  IncrementHitNumber();
      
  //Get perticle information

  J4VComponent         *locat         = GetComponent();
  G4int                 trackID       = GetTrackID();
  G4int                 mothertrackID = GetMotherTrackID();
  G4int	               cloneID       = GetCloneID();  
  G4ParticleDefinition *particle      = GetParticle();
  G4double              tof           = GetTof();
  G4double              edep          = GetEnergyDeposit();
  G4double              etot          = GetTotalEnergy();
  G4ThreeVector         p             = GetMomentum();
  const G4ThreeVector   pre           = GetPrePosition();
  const G4ThreeVector   pos           = GetPostPosition();
  
  G4ThreeVector    tlate      = GetTranslation();  // global to local
  G4RotationMatrix rot        = *GetRotation();    // global to local
  G4double         rotangle   = GetRotation()->getDelta();
  
  G4ThreeVector wireEndp =
     ((J4CDCStereoDriftRegion *)locat)->GetSenseWire()->GetLocalWireEnd(1);
  G4ThreeVector wireEndm =
     ((J4CDCStereoDriftRegion *)locat)->GetSenseWire()->GetLocalWireEnd(-1);
  G4ThreeVector wirepAtPlusZ  = rot.inverse()*(wireEndp) - tlate;
  G4ThreeVector wirepAtMinusZ = rot.inverse()*(wireEndm) - tlate;
  
#ifdef __DEBUG__
  G4cerr << "*J4CDCStereoDriftRegionSD::ProcessHits -----------------" 
         << G4endl;
  G4cerr << "   SDname        : " << locat->GetName() << G4endl;
  G4cerr << "   TrackID       : " << trackID << G4endl;
  G4cerr << "   ParticleName  : " << particle->GetParticleName() 
                                  << G4endl;
  G4cerr << "   PreStepPoint  : " << pre.x() << " " << pre.y() << " " 
                                  << pre.z() << G4endl; 
  G4cerr << "   PostStepPoint : " << pos.x() << " " << pos.y() << " " 
                                  << pos.z() << G4endl; 
  G4cerr << "   wireAtPlusZ   : " << wirepAtPlusZ.x() << " " 
                                  << wirepAtPlusZ.y() << " " 
                                  << wirepAtPlusZ.z() << G4endl; 
  G4cerr << "   wireAtMinusZ  : " << wirepAtMinusZ.x() << " " 
                                  << wirepAtMinusZ.y() << " " 
                                  << wirepAtMinusZ.z() << G4endl; 
  G4cerr << "---------------------------------------------------------" 
         << G4endl;
#endif


  // Create a new hit and push them to "Hit Coleltion"
 
  J4CDCStereoDriftRegionHit* hit = 
    new J4CDCStereoDriftRegionHit(locat, cloneID, trackID, 
        mothertrackID, particle, tof, edep, etot, p, pre, pos, 
        wirepAtPlusZ, wirepAtMinusZ, rotangle, GetHitNumber());
       			      
  ((J4CDCStereoDriftRegionHitBuf*)GetHitBuf())-> insert(hit);

  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4CDCStereoDriftRegionSD::EndOfEvent(G4HCofThisEvent* HCTE)
{			
}

//=====================================================================
//* clear -------------------------------------------------------------


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4CDCStereoDriftRegionSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4CDCStereoDriftRegionSD::PrintAll()
{
  G4int nHit= ((J4CDCStereoDriftRegionHitBuf*)GetHitBuf())-> entries();
  G4cout << "------------------------------------------" << G4endl
         << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
  ((J4CDCStereoDriftRegionHitBuf*)GetHitBuf())-> PrintAllHits();
}

