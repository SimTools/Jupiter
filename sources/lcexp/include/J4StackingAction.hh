// $Id$
#ifndef __J4STACKINGACTION__ 
#define __J4STACKINGACTION__ 
//*************************************************************************
//* --------------------
//* J4StackingAction
//* --------------------
//* (Description)
//* 	Derived class for UserStackingAction.
//*     Mother class : G4UserStackingAction
//*    
//* (Update Record)
//*	2004/12/06  A.Yamaguchi	Original version.
//*************************************************************************
//


#include "G4UserStackingAction.hh"
#include "globals.hh"


class J4StackingAction : public G4UserStackingAction 
{

  public:
    J4StackingAction();
    virtual ~J4StackingAction();

    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track *aTrack);

    static G4int GetTopOfStackID() { return fgTopOfStackID; }

  private:
    static G4int fgTopOfStackID;
};

#endif


