// $Id$
#ifndef __J4VHit__
#define __J4VHit__
//*************************************************************************
//* --------------------
//* J4VHit
//* --------------------
//* (Description)
//* 	Pure abstruct hit class. This class also provide his
//*	proper HitCollection(buffering) class.
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*	2001/03/15  K.Hoshina	Original version.
//*	2002/05/15  K.Hoshina	.
//*************************************************************************

#include <fstream>

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "J4VComponent.hh"

//=========================================================================
//---------------------
// Class definition
//---------------------

class J4VDetectorComponent;
class J4Object;

class J4VHit : public G4VHit, public J4Object {
public:
  J4VHit();
  J4VHit(J4VComponent * detector);

  J4VHit(J4VComponent        *detector,
         const G4ThreeVector &pre, 
         const G4ThreeVector &pos,
         G4int                cloneid = -1);
         
  J4VHit(J4VComponent          *detector,
         G4int                  trackID ,
         G4int                  mothertrackID,
         G4ParticleDefinition  *particle,
         G4double               tof       = 0,
         G4double               edep      = 0,
         G4double               totalE    = 0,
         const G4ThreeVector   &momentum  = G4ThreeVector(0.),
         const G4ThreeVector   &pre       = G4ThreeVector(0.),
         const G4ThreeVector   &pos       = G4ThreeVector(0.),      
         G4int                  hitnumber = -9999);	      

  J4VHit(J4VComponent          *detector,
         G4int                  cloneID,
         G4int                  trackID,
         G4int                  mothertrackID,
         G4ParticleDefinition  *particle,
         G4double               tof       = 0,
         G4double               edep      = 0,
         G4double               totalE    = 0,
         const G4ThreeVector   &momentum  = G4ThreeVector(0.),
         const G4ThreeVector   &pre       = G4ThreeVector(0.),
         const G4ThreeVector   &pos       = G4ThreeVector(0.),
         G4int                  hitnumber = -9999);	      
		       
  J4VHit(const J4VHit &right);		       
  virtual ~J4VHit();
  
  inline const J4VHit& operator=(const J4VHit &right); 
  
  virtual void Output(G4HCofThisEvent *HCTE) = 0;
    
  // Set functions

  inline virtual void SetDetectorComponent (J4VComponent* dtc)
                       {
                         std::cerr << "********************************************" << std::endl;
                         std::cerr << " J4VHit::SetDetectorComponent() will vanish " << std::endl;
                         std::cerr << " at next major update. Use SetComponent(). " << std::endl;
                         std::cerr << "********************************************" << std::endl;
                         fComponent = dtc; 
                       }

  inline virtual void SetComponent     (J4VComponent* dtc)       { fComponent      = dtc; } 
  inline virtual void SetParticle      (G4ParticleDefinition* p ){ fParticle       = p  ; } 
  inline virtual void SetCloneID       (G4int cID)               { fCloneID        = cID; } 
  inline virtual void SetTrackID       (G4int tID)               { fTrackID        = tID; }
  inline virtual void SetMotherTrackID (G4int mID)               { fMotherTrackID  = mID; }
  inline virtual void SetTof           (G4double tof )           { fTof            = tof; }	
  inline virtual void SetEnergyDeposit (G4double edp)            { fEnergyDeposit  = edp; }
  inline virtual void SetTotalEnergy   (G4double tot)            { fTotalEnergy    = tot; }
  inline virtual void SetMomentum      (const G4ThreeVector& m)  { fMomentum       = m;   }
  inline virtual void SetPrePosition   (const G4ThreeVector& pre){ fPrePosition    = pre; }
  inline virtual void SetPostPosition  (const G4ThreeVector& pos){ fPostPosition   = pos; }
  inline virtual void SetHitNumber     (G4int hno)               { fHitNumber      = hno; }
  static void         SetOutputFileStream(std::ofstream& ofs)  { fOfs = &ofs; }
  
  // inclement functions
  inline virtual void AddEdep          (G4double edep)           { fEnergyDeposit += edep;}  
  
  
  // Get functions
  inline virtual       J4VDetectorComponent* GetDetectorComponent() const 
                       {
                         std::cerr << "********************************************" << std::endl;
                         std::cerr << " J4VHit::GetDetectorComponent() will vanish " << std::endl;
                         std::cerr << " at next major update. Use GetComponent(). " << std::endl;
                         std::cerr << "********************************************" << std::endl;
                         return (J4VDetectorComponent *)fComponent; 
                       }
  inline virtual const G4String& GetDetectorComponentName() const 
                       { 
                         std::cerr << "************************************************" << std::endl;
                         std::cerr << " J4VHit::GetDetectorComponentName() will vanish " << std::endl;
                         std::cerr << " at next major update. Use GetComponentName(). " << std::endl;
                         std::cerr << "************************************************" << std::endl;
                         return fComponent->GetName(); 
                       }

  inline virtual       J4VComponent*         GetComponent()     const { return fComponent;                  }
  inline virtual const G4String&             GetComponentName() const { return fComponent->GetName();       }
  inline virtual       G4ParticleDefinition* GetParticle()      const { return fParticle;                   }
  inline virtual       G4int                 GetCloneID()       const { return fCloneID;                    }
  inline virtual       G4int                 GetTrackID()       const { return fTrackID;                    }
  inline virtual       G4int                 GetMotherTrackID() const { return fMotherTrackID;              } 
  inline virtual       G4double              GetTof()           const { return fTof;                        }
  inline virtual       G4double              GetEnergyDeposit() const { return fEnergyDeposit;              }
  inline virtual       G4double              GetTotalEnergy()   const { return fTotalEnergy;                }
  inline virtual       G4double              GetMass()          const { return fParticle->GetPDGMass();     }
  inline virtual       G4double              GetCharge()        const { return fParticle->GetPDGCharge();   } 
  inline virtual       G4ThreeVector         GetMomentum()      const { return fMomentum;                   }
  inline virtual       G4ThreeVector         GetPrePosition()   const { return fPrePosition;                }
  inline virtual       G4ThreeVector         GetPostPosition()  const { return fPostPosition;               }
  inline virtual       G4int	             GetHitNumber()     const { return fHitNumber;                  }
  inline virtual       G4int                 GetPDGEncoding()   const { return fParticle->GetPDGEncoding(); }
  inline virtual const G4String&             GetParticleName()  const { return fParticle->GetParticleName();}
  
  static std::ofstream& GetOutputFileStream() { return *fOfs; } 
     
private:
  J4VComponent*         fComponent        ; // the Hit occured in 
  G4int                 fCloneID          ; // ReplicaNo for Replica or CopyNo for PVPlacement 
  G4int                 fTrackID          ; // TrackID
  G4int                 fMotherTrackID    ; // MotherTrackID
  G4ParticleDefinition* fParticle         ; // Name of perticle
  G4double              fTof              ; // TOF  
  G4double              fEnergyDeposit    ; // Energy Deposit 
  G4double              fTotalEnergy      ; // Total energy
  G4ThreeVector         fMomentum         ; // Momentum of perticle 
  G4ThreeVector         fPrePosition      ; // Pre-position of track 
  G4ThreeVector         fPostPosition     ; // Post-position of track
  G4int                 fHitNumber        ; // Hit Number per track
  
  static std::ofstream* fOfs;
  

};

//=====================================================================
//---------------------
// inline function for J4VHit
//---------------------

inline J4VHit::J4VHit(const J4VHit& right)
{

  fComponent     = right.fComponent    ;
  fCloneID       = right.fCloneID      ;
  fTrackID       = right.fTrackID      ;
  fMotherTrackID = right.fMotherTrackID;
  fParticle      = right.fParticle     ;
  fTof           = right.fTof          ;
  fEnergyDeposit = right.fEnergyDeposit;
  fTotalEnergy   = right.fTotalEnergy  ;
  fMomentum      = right.fMomentum     ;
  fPrePosition   = right.fPrePosition  ;
  fPostPosition  = right.fPostPosition ;
  fHitNumber     = right.fHitNumber    ;

}
inline const J4VHit&
        J4VHit::operator= (const J4VHit& right)
{

  fComponent     = right.fComponent   ;
  fCloneID       = right.fCloneID      ;
  fTrackID       = right.fTrackID      ;
  fMotherTrackID = right.fMotherTrackID;
  fParticle      = right.fParticle     ;
  fEnergyDeposit = right.fEnergyDeposit;
  fTotalEnergy   = right.fTotalEnergy  ;
  fMomentum      = right.fMomentum     ;
  fPrePosition   = right.fPrePosition  ;
  fPostPosition  = right.fPostPosition ;
  fHitNumber     = right.fHitNumber    ;

  return *this;
}

#endif

