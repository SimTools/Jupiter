// $Id$
#ifndef __J4TRACKINGACTION__ 
#define __J4TRACKINGACTION__ 
//*************************************************************************
//* --------------------
//* J4TrackingAction
//* --------------------
//* (Description)
//* 	Derivation class for UserTrackingAction.
//*     Mother class : G4UserTrackingAction
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
//


#include "G4UserTrackingAction.hh"


class J4TrackingAction : public G4UserTrackingAction {

  public:
    J4TrackingAction(){};
    virtual ~J4TrackingAction(){};
   
    virtual void PreUserTrackingAction(const G4Track*);

};

#endif


