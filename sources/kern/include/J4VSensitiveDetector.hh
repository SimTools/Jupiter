// $Id$
#ifndef __J4VSENSITIVEDETECTOR__
#define __J4VSENSITIVEDETECTOR__
//*************************************************************************
//* --------------------
//* J4VSensitiveDetector
//* --------------------
//* (Description)
//* 	Abstract class template for his/her sensitive detector.
//*	You must use template class for derivation.
//*	Mother class : G4VSensitiveDetector
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*	2002/05/15  K.Hoshina	Moved fHitNumber datamember to private,
//*                             then removed SetNitNumber() method.
//*                             Changede argument of constructor. 
//*                             Added GetComponent() method.
//*************************************************************************


//  !!! HOMEWORK !!!
//  Change a fHitBuf pointer to an fHitBuf* pointer array.
//  SensitiveDetector can have several HitBuffer class.

#include "G4HCofThisEvent.hh"
#include "G4VSensitiveDetector.hh"
#include "J4VComponent.hh"
#include "J4PVPlacement.hh"
#include "J4PVReplica.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VDetectorComponent;
class J4Object;

class J4VSensitiveDetector : public G4VSensitiveDetector, public J4Object 
{ 

 public:
  J4VSensitiveDetector(J4VComponent *detector);
  virtual ~J4VSensitiveDetector();
      
  virtual void         OutputAll(G4HCofThisEvent* HCTE) = 0; 

  inline virtual void  SetNewStep(G4Step *aStep)              {fNewStep = aStep;}
  inline virtual void  SetROHist (G4TouchableHistory *rohist) {fROHist = rohist;}
      

  virtual void         DrawAll(){}
  virtual void         PrintAll(){} 

  // get functions
   
  inline virtual       J4VComponent *GetDetectorComponent() const
  {
    std::cerr << "********************************************" << std::endl;
    std::cerr << " J4VSensitiveDetector::GetDetectorComponent " << std::endl;
    std::cerr << " this method will vanish at next major update." << std::endl;
    std::cerr << " Use GetComponent(). " << std::endl;
    std::cerr << "********************************************" << std::endl;
    return GetComponent(0);
  }
  
  inline virtual       J4VComponent         *GetComponent    (G4int depth = 0) const;   
  inline virtual       G4VPhysicalVolume    *GetPVfromTrack  (G4int depth = 0) const;
  inline virtual       G4VHitsCollection    *GetHitBuf       () const { return fHitBuf;    }
  inline virtual       G4StepPoint          *GetPreStepPoint () const;
  inline virtual       G4StepPoint          *GetPostStepPoint() const;
  inline virtual       G4Track              *GetTrack        () const;
  inline virtual       G4int                 GetTrackID      () const;
  inline virtual       G4int                 GetMotherTrackID() const;
  inline virtual const G4String             &GetParticleName () const;
  inline virtual       G4double              GetCharge       () const;
  inline virtual       G4double              GetMass         () const;
  inline virtual       G4double              GetTof          () const;
  inline virtual       G4double              GetEnergyDeposit() const;
  inline virtual       G4double              GetKineticEnergy() const;
  inline virtual       G4double              GetTotalEnergy  () const;
  inline virtual       G4ThreeVector         GetMomentum     () const;
  inline virtual const G4ThreeVector        &GetPrePosition  () const;
  inline virtual const G4ThreeVector        &GetPostPosition () const;
  inline virtual       G4ParticleDefinition *GetParticle     () const;
  inline virtual       G4int                 GetHitNumber    () const { return fHitNumber; }
  inline virtual       G4double              GetWeight       () const;
  inline virtual       G4bool                IsOutputLocked  () const { return fIsOutputLocked; }

  // getters for replicated or copied volume 
  inline virtual       G4int                 GetCloneID      (J4VComponent *cptr = 0) const;
  inline virtual const G4ThreeVector        &GetTranslation  (J4VComponent *cptr = 0) const;
  inline virtual const G4RotationMatrix     *GetRotation     (J4VComponent *cptr = 0) const;
  
  // set functions
  virtual void         SetHitBuf(G4VHitsCollection* hitbuf) { fHitBuf = hitbuf; }
  virtual void         IncrementHitNumber()                 { fHitNumber++; }

  inline virtual void  LockOutput()              { fIsOutputLocked = TRUE;  }
  inline virtual void  UnlockOutput()            { fIsOutputLocked = FALSE; }
  
 private:

  G4LogicalVolume    *fLV;
  G4VHitsCollection  *fHitBuf;       // Hit buffer 
  G4Step             *fNewStep;
  G4TouchableHistory *fROHist;
  G4bool              fIsOutputLocked;

  static G4int        fHitNumber;
  
};

//=====================================================================
//---------------------
// inline function for J4VSensitiveDetector
//---------------------

inline J4VComponent* J4VSensitiveDetector::GetComponent(G4int depth) const
{
  if (fNewStep) {
     G4VPhysicalVolume *pv = fNewStep->GetTrack()->GetTouchable()->GetVolume(depth);
     if (dynamic_cast<J4PVPlacement *>(pv)) {
        return dynamic_cast<J4PVPlacement *>(pv)->GetComponent();
     } else if (dynamic_cast<J4PVReplica *>(pv)) {
        return dynamic_cast<J4PVReplica *>(pv)->GetComponent();
     } else {
        std::cerr << "J4VSensitiveDetector::GetComponent: unsupported physicalvolume. abort." << std::endl;
        abort();
     }
   } else {
      std::cerr << "J4VSensitiveDetector::GetComponent: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
      abort();
   }
}
  
inline G4VPhysicalVolume* J4VSensitiveDetector::GetPVfromTrack(G4int depth) const
{
   if (fNewStep) {
      return fNewStep->GetTrack()->GetTouchable()->GetVolume(depth);
   } else {
      std::cerr << "J4VSensitiveDetector::GetPVfromTrack: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
      abort();
   }
}


inline G4StepPoint* J4VSensitiveDetector::GetPreStepPoint() const 
{
   if (fNewStep) {
      return fNewStep->GetPreStepPoint();
   } else {
      std::cerr << "J4VSensitiveDetector::GetPreStepPosition: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
      abort();
   } 
}
  
inline G4StepPoint* J4VSensitiveDetector::GetPostStepPoint() const 
{
  if (fNewStep) {
      return fNewStep->GetPostStepPoint();
  } else {
      std::cerr << "J4VSensitiveDetector::GetPostStepPosition: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
      abort();
  }
}

inline G4Track* J4VSensitiveDetector::GetTrack() const 
{
  if (fNewStep) {
      return fNewStep->GetTrack(); 
  } else {
      std::cerr << "J4VSensitiveDetector::GetTrack: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
      abort();
  }
} 

inline G4int J4VSensitiveDetector::GetTrackID() const 
{
  if (fNewStep) {
      return fNewStep->GetTrack()->GetTrackID(); 
  } else {
      std::cerr << "J4VSensitiveDetector::GetTrackID: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
      abort();
  }
}
  
inline G4int J4VSensitiveDetector::GetMotherTrackID() const 
{
  if (fNewStep) {
      return fNewStep->GetTrack()->GetParentID(); 
  } else {
      std::cerr << "J4VSensitiveDetector::GetMotherTrackID: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
      abort();
  }
}

inline const G4String& J4VSensitiveDetector::GetParticleName() const 
{
  if (fNewStep) {
     return fNewStep->GetTrack()->GetDefinition()->GetParticleName();  
  } else {
      std::cerr << "J4VSensitiveDetector::GetParticleName: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
      abort();
  }
}
  

inline G4double J4VSensitiveDetector::GetCharge() const 
{
  if (fNewStep) {
      return fNewStep->GetTrack()->GetDefinition()->GetPDGCharge();
  } else {
      std::cerr << "J4VSensitiveDetector::GetCharge: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
      abort();
  }
}

inline G4double J4VSensitiveDetector::GetMass() const 
{
  if (fNewStep) {
      return fNewStep->GetTrack()->GetDefinition()->GetPDGMass(); 
  } else {
      std::cerr << "J4VSensitiveDetector::GetMass: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
      abort();
  }
}
  

inline G4double J4VSensitiveDetector::GetTof () const 
{
  if (fNewStep) {
      return fNewStep->GetPreStepPoint()->GetGlobalTime();
  } else {
      std::cerr << "J4VSensitiveDetector::GetTof: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
      abort();
  }
}
  

inline G4double J4VSensitiveDetector::GetEnergyDeposit () const 
{
  if (fNewStep) {
      return fNewStep->GetTotalEnergyDeposit(); 
  } else {
      std::cerr << "J4VSensitiveDetector::GetEnergyDeposit: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
      abort();
  }
}
  

inline G4double J4VSensitiveDetector::GetKineticEnergy () const 
{
  if (fNewStep) {
     return fNewStep->GetTrack()->GetKineticEnergy(); 
  } else {
      std::cerr << "J4VSensitiveDetector::GetKineticDeposit: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
      abort();
  }
}
  

inline G4double J4VSensitiveDetector::GetTotalEnergy () const 
{
  if (fNewStep) {
      return fNewStep->GetTrack()->GetTotalEnergy(); 
  } else {
      std::cerr << "J4VSensitiveDetector::GetTotalEnergy: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
      abort();
  }
}
  

inline G4ThreeVector J4VSensitiveDetector::GetMomentum () const 
{
  if (fNewStep) {
     return fNewStep->GetPreStepPoint()->GetMomentum(); 
  } else {
     std::cerr << "J4VSensitiveDetector::GetMomentum: fNewStep is empty! "
          << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
     abort();
  }
}

inline const G4ThreeVector& J4VSensitiveDetector::GetPrePosition() const 
{
  if (fNewStep) {
     return fNewStep->GetPreStepPoint()->GetPosition(); 
  } else {
     std::cerr << "J4VSensitiveDetector::GetPrePosition: fNewStep is empty! "
          << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
     abort();
  }
} 
  

inline const G4ThreeVector& J4VSensitiveDetector::GetPostPosition() const 
{
  if (fNewStep) {
     return fNewStep->GetPostStepPoint()->GetPosition(); 
  } else {
     std::cerr << "J4VSensitiveDetector::GetPostPosition: fNewStep is empty! "
          << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
     abort();
  }
}


inline G4ParticleDefinition* J4VSensitiveDetector::GetParticle () const 
{
  if (fNewStep) {
     return fNewStep->GetTrack()->GetDefinition();  
  } else {
     std::cerr << "J4VSensitiveDetector::GetParticle: fNewStep is empty! "
          << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
     abort();
  }
}

inline G4double J4VSensitiveDetector::GetWeight() const
{
  if (fNewStep) {
     return fNewStep->GetPreStepPoint()->GetWeight();
  } else {
     std::cerr << "J4VSensitiveDetector::GetWeight: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
     abort();
  }
}

inline G4int J4VSensitiveDetector::GetCloneID(J4VComponent *cptr) const
{
  if (fNewStep) {
     if (!cptr) {
         EPlacementType type = GetComponent()->GetPlacementType();
         switch (type) {
            case kReplicated: return fNewStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber();
            case kCopied    : return GetComponent()->GetCopyNo();
            case kSingle    : return 0;
         }      
      } else {
         EPlacementType type = cptr->GetPlacementType();
         switch (type) {
            case kReplicated: {
               G4int depth = cptr->GetMyDepth() - GetComponent()->GetMyDepth();
               return fNewStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(depth);
            }
            case kCopied    : return cptr->GetCopyNo();
            case kSingle    : return 0;
         }      
      }
   } else {
      std::cerr << "J4VSensitiveDetector::GetCloneID: fNewStep is empty! "
           << "Call SetNewStep(aStep) at ProcessHit() in your SensitiveDetector." << std::endl;
      abort();
   }
   return -9999;
}
  
inline const  G4ThreeVector& J4VSensitiveDetector::GetTranslation (J4VComponent *cptr) const 
{
  if (fROHist) {
     if (cptr == 0) { // return translation of current volume
        return fROHist->GetTranslation();  
     } else {
        G4int depth = cptr->GetMyDepth() - GetComponent()->GetMyDepth();
        return fROHist->GetTranslation(depth);
     } 
  } else if (fNewStep) {
     if (cptr == 0) { // return translation of current volume
        return fNewStep->GetPreStepPoint()->GetTouchable()->GetTranslation();  
     } else {
        G4int depth = cptr->GetMyDepth() - GetComponent()->GetMyDepth();
        return fNewStep->GetPreStepPoint()->GetTouchable()->GetTranslation(depth);
     } 

  } else {
     std::cerr << "J4VSensitiveDetector::GetTranslation: both fROHist and fNewStep are empty! "
          << "Call SetNewStep(aStep) or, if you have ROgeometry, call SetROHist(rohist) "
          << "at ProcessHit() in your SensitiveDetector." << std::endl;
        abort();
  }
}

inline const G4RotationMatrix* J4VSensitiveDetector::GetRotation (J4VComponent *cptr) const 
{
  if (fROHist) {
     if (cptr == 0) { // return rotation matrix of current volume
        return fROHist->GetRotation();  
     } else {
        G4int depth = cptr->GetMyDepth() - GetComponent()->GetMyDepth();
        return fROHist->GetRotation(depth);
     } 
  } else if (fNewStep) {
     if (cptr == 0) { // return rotation matrix of current volume
        return fNewStep->GetPreStepPoint()->GetTouchable()->GetRotation();  
     } else {
        G4int depth = cptr->GetMyDepth() - GetComponent()->GetMyDepth();
        return fNewStep->GetPreStepPoint()->GetTouchable()->GetRotation(depth);
     } 
  } else {
     std::cerr << "J4VSensitiveDetector::GetRotation: both fROHist and fNewStep are empty! "
          << "Call SetNewStep(aStep) or, if you have ROgeometry, call SetROHist(rohist) "
          << "at ProcessHit() in your SensitiveDetector." << std::endl;
        abort();
  }
}

#endif

