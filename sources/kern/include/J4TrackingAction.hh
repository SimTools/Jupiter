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

#ifdef __THEBE__
#include <fstream>
#endif

#include "G4UserTrackingAction.hh"


class J4TrackingAction : public G4UserTrackingAction {

  public:
    J4TrackingAction(){};
    virtual ~J4TrackingAction(){};
   
    virtual void PreUserTrackingAction(const G4Track* aTrack);
    virtual void PostUserTrackingAction(const G4Track* aTrack);
    inline virtual G4TrackingManager* GetTrackingManager() const
                   { return fpTrackingManager; }

  private:
#ifdef __THEBE__
    G4std::ofstream  fErrorOfs;
#endif

};

#endif


