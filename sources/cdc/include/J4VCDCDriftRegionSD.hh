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

  inline 
  virtual const J4VCDCDriftRegionSD & operator=(const J4VSD<HitType> &right)
  {
     J4VSD<HitType>::operator=(right);
     return *this;
  }


  virtual void Initialize (G4HCofThisEvent* HCTE)
  {
     //create hit collection(s) and
     //push H.C. to "Hit Collection of This Event"
     MakeHitBuf(HCTE);
  }

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory*)
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
     G4int                 cloneID  = GetCloneID(locat->GetMother());
     std::cerr << " cloneID = " << cloneID << std::endl;
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

#if 1
     std::cerr << "*J4VCDCDriftRegionSD::ProcessHits -----------------------"
            << std::endl;
     std::cerr << "   SDname        : " << locat->GetName() << std::endl;
     std::cerr << "   TrackID       : " << trackID << std::endl;
     std::cerr << "   ParticleName  : " << particle->GetParticleName()
                                     << std::endl;
     std::cerr << "   PreStepPoint  : " << pre.x() << " " << pre.y() << " "
                                     << pre.z() << std::endl;
     std::cerr << "   PostStepPoint : " << pos.x() << " " << pos.y() << " "
                                     << pos.z() << std::endl;
     std::cerr << "   wireAtPlusZ   : " << wireAtPZ.x() << " "
                                     << wireAtPZ.y() << " "
                                     << wireAtPZ.z() << std::endl;
     std::cerr << "   wireAtMinusZ  : " << wireAtMZ.x() << " "
                                     << wireAtMZ.y() << " "
                                     << wireAtMZ.z() << std::endl;
     std::cerr << "   tanstereo     : " << tanstereo << std::endl; 
     std::cerr << "   rtop          : " << wireEndp.getRho() << std::endl; 
     std::cerr << "   rwaist        : " << rwaist << std::endl; 
     std::cerr << "---------------------------------------------------------"
            << std::endl;
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
       std::cerr << "J4VCDCDriftRegionSD::OutputAll: No Hit! " << std::endl;
     }
  }

  virtual void PrintAll() 
  {
     G4int nHit= ((G4THitsCollection<HitType> *)GetHitBuf())-> entries();
     std::cout << "------------------------------------------" << std::endl
            << "*** tracker Hit (#hits=" << nHit << ")" << std::endl;
     GetHitBuf()-> PrintAllHits();
  }

  virtual void   EndOfEvent (G4HCofThisEvent *) {}
  virtual void   DrawAll() {} 
 
  // set/get functions
   
private:
  
};

#endif

