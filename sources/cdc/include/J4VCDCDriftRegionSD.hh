// $Id$
#ifndef __J4VCDCDRIFTREGIONSD__
#define __J4VCDCDRIFTREGIONSD__
//*************************************************************************
//* --------------------
//* J4VCDCDriftRegionSD
//* --------------------
//* (Description)
//* 	abstract base class for DriftRegion sensitive detector.
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "G4Step.hh"
#include "J4VSD.hh"
#include "J4VCDCDriftRegion.hh"


//=====================================================================
//---------------------
// class definition
//---------------------

template <class HitType>
class J4VCDCDriftRegionSD : public J4VSD< HitType >{
  
public:

  J4VCDCDriftRegionSD(J4VDetectorComponent* detector)
      :J4VSD< HitType >(detector) {} 

  ~J4VCDCDriftRegionSD() {}


  virtual void Initialize (G4HCofThisEvent* HCTE)
  {
     //create hit collection(s) and
     //push H.C. to "Hit Collection of This Event"
     MakeHitBuf(HCTE);
  }

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
  {

     //In order to use Get function, you must call SetNewStep() at first.
     SetNewStep(aStep);

     //Only when a charged particle has just come into a sensitive detector,
     //create a new hit
     if(!GetCharge()) return FALSE;

     IncrementHitNumber();

     //Get perticle information
     J4VCDCDriftRegion    *locat    = (J4VCDCDriftRegion *)GetComponent();
     G4int                 trackID  = GetTrackID();
     G4int                 mtrackID = GetMotherTrackID();
     G4int                 cloneID  = GetCloneID();
     G4ParticleDefinition *particle = GetParticle();
     G4double              tof      = GetTof();
     G4double              edep     = GetEnergyDeposit();
     G4double              etot     = GetTotalEnergy();
     G4ThreeVector         p        = GetMomentum();
     const G4ThreeVector   pre      = GetPrePosition();
     const G4ThreeVector   pos      = GetPostPosition();
     G4double              tanstereo= locat->GetTanStereo();
     G4double              rwaist   = locat->GetRwaist();

     G4ThreeVector         tlate    = GetTranslation();  // global to local
     G4RotationMatrix      rot      = *GetRotation();    // global to local
     G4double              rotang   = GetRotation()->getDelta();
     G4ThreeVector         wireEndp = locat->GetSenseWire()->GetLocalWireEnd(1);
     G4ThreeVector         wireEndm = locat->GetSenseWire()->GetLocalWireEnd(-1);
     G4ThreeVector         wireAtPZ = rot.inverse()*(wireEndp) - tlate;
     G4ThreeVector         wireAtMZ = rot.inverse()*(wireEndm) - tlate;

#ifdef __DEBUG__
     G4cerr << "*J4VCDCDriftRegionSD::ProcessHits -----------------------"
            << G4endl;
     G4cerr << "   SDname        : " << locat->GetName() << G4endl;
     G4cerr << "   TrackID       : " << trackID << G4endl;
     G4cerr << "   ParticleName  : " << particle->GetParticleName()
                                     << G4endl;
     G4cerr << "   PreStepPoint  : " << pre.x() << " " << pre.y() << " "
                                     << pre.z() << G4endl;
     G4cerr << "   PostStepPoint : " << pos.x() << " " << pos.y() << " "
                                     << pos.z() << G4endl;
     G4cerr << "   wireAtPlusZ   : " << wireAtPZ.x() << " "
                                     << wireAtPZ.y() << " "
                                     << wireAtPZ.z() << G4endl;
     G4cerr << "   wireAtMinusZ  : " << wireAtMZ.x() << " "
                                     << wireAtMZ.y() << " "
                                     << wireAtMZ.z() << G4endl;
     G4cerr << "   tanstereo     : " << tanstereo << G4endl; 
     G4cerr << "   rtop          : " << wireEndp.getRho() << G4endl; 
     G4cerr << "   rwaist        : " << rwaist << G4endl; 
     G4cerr << "---------------------------------------------------------"
            << G4endl;
#endif


     // Create a new hit and push them to "Hit Coleltion"
     HitType* hit = new HitType(locat, cloneID, trackID, mtrackID, particle,
                                tof, edep, etot, p, pre, pos, rotang, wireAtPZ,
                                wireAtMZ, tanstereo, rwaist, GetHitNumber());
     ((G4THitsCollection<HitType> *)GetHitBuf())-> insert(hit);
     return TRUE;
  }

  virtual void OutputAll(G4HCofThisEvent* HCTE)
  {
     if(GetHitBuf())
     {
       J4VSD< HitType >::OutputAll(HCTE);
     }
     else
     {
       G4cerr << "J4VCDCDriftRegionSD::OutputAll: No Hit! " << G4endl;
     }
  }

  virtual void PrintAll() 
  {
     G4int nHit= ((G4THitsCollection<HitType> *)GetHitBuf())-> entries();
     G4cout << "------------------------------------------" << G4endl
            << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
     GetHitBuf()-> PrintAllHits();
  }

  virtual void   EndOfEvent (G4HCofThisEvent* HCTE) {}
  virtual void   DrawAll() {} 
 
  // set/get functions
   
private:
  
};

#endif

