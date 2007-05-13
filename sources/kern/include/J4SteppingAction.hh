// $Id$
#ifndef __J4STEPPINGACTION__ 
#define __J4STEPPINGACTION__ 
//*************************************************************************
//* --------------------
//* J4SteppingAction
//* --------------------
//* (Description)
//* 	Derivation class for UserSteppingAction.
//*     Mother class : G4UserTrackingAction
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
//
#include "G4UserSteppingAction.hh"

class J4SteppingAction : public G4UserSteppingAction
{
  public:
    J4SteppingAction();
   ~J4SteppingAction();

    void UserSteppingAction(const G4Step*);

private:
  static G4int fLoop;
  static G4int fLastTID;
  static G4double fEcutSum;

public:
  static void ResetECutSum(){ fEcutSum=0;}
  static G4double GetECutSum(){ return fEcutSum; }

};

#endif


