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
};

#endif


