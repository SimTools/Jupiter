// $Id$
#ifndef J4PRIMARYGENERATORACTION
#define J4PRIMARYGENERATORACTION
//*************************************************************************
//* ------------------------
//* J4PrimaryGeneratorAction
//* ------------------------
//*     
//* (Update Record)
//*     2002/05/30  K.Hoshina   Original version.
//*************************************************************************

//_________________________________________________________________________
//
// Class description 
//
// This class defines PrimaryGeneratorAction as singleton. 
// It loads 3type of PrimaryGenerators,
// (1) HEPEvtInterface(default), (2)CAINEvtInterface, and (3)G4ParticleGun.
// In order to switch those generators, use /jupiter/generator command
// (see online-help or J4VPrimaryGeneratorMessenger).
//------------------------------------------------------------------------


#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "J4TypeDef.hh"

class G4VPrimaryGenerator;
class G4Event;
class G4ParticleGun;
class J4PrimaryGeneratorMessenger;
class J4HEPEvtInterface;
class J4CAINEvtInterface;
class J4ParticleBeam;

class J4PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

public:

   J4PrimaryGeneratorAction();
   ~J4PrimaryGeneratorAction();


   void          GeneratePrimaries(G4Event* anEvent);

   inline void   SetPrimaryGenerator(EPrimaryGeneratorType t=kHEPEvt) 
                                                 { fEprimarygentype = t;    }

   inline EPrimaryGeneratorType GetPrimaryGeneratorType() const 
                                                 { return fEprimarygentype; }

   inline G4bool IsInitialized() const           { return fIsInitialized;   }
   inline void   SetIsInitialized(G4bool f=false){ fIsInitialized = f;      } 
   inline G4bool AbortRun() const { return fAbortRun; }
   inline void   SetAbortRun(G4bool f=false) { fAbortRun=f; }

   static J4PrimaryGeneratorAction *GetPrimaryGeneratorAction() 
                                         { return fPrimaryGeneratorAction; }
  inline G4int   GetInitialSeed(){ return fInitialSeed; }
  void    SetInitialSeed(G4int i);


private:
   void Initialize();

private:
   J4HEPEvtInterface           *fHEPEvt;
   J4CAINEvtInterface          *fCAINEvt;
   G4ParticleGun               *fParticleGun;
   J4ParticleBeam              *fParticleBeam;
   J4PrimaryGeneratorMessenger *fMessenger;
   G4String                     fHEPEvtFileName;
   EPrimaryGeneratorType        fEprimarygentype;
   G4bool                       fIsInitialized; 
   G4bool                       fAbortRun;
   G4long                       fInitialSeed;

   // this class is singleton.
   static J4PrimaryGeneratorAction *fPrimaryGeneratorAction;

};

#endif

