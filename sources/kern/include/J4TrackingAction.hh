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

#include "G4Types.hh"
#include "G4ios.hh"

#ifdef __THEBE__
#include <fstream>
#endif

#include "G4UserTrackingAction.hh"

class J4TrackingActionMessenger;

class J4TrackingAction : public G4UserTrackingAction 
{

  public:
    J4TrackingAction();
    virtual ~J4TrackingAction();
   
    virtual void    PreUserTrackingAction(const G4Track* aTrack);
    virtual void    PostUserTrackingAction(const G4Track* aTrack);
    inline  virtual G4TrackingManager* GetTrackingManager() const
                    { return fpTrackingManager; }
    inline  G4int   GetCurrentTrackID() const { return fCurrentTrackID; }

    inline void     SetStoredTrajectoryID(G4int id);
    inline G4int    GetStoredTrajectoryID() const { return fStoredTrajectoryID; }

#ifdef __THEBE__
    inline void     SetStoredDebugPrintID(G4int id);
    inline G4int    GetStoredDebugPrintID() const { return fStoredDebugPrintID; }
#endif

  private:

    G4int            fCurrentTrackID;        // 1 : charged particle only 
    G4int            fStoredTrajectoryID;    // 1 : charged particle only 
                                             // 2 : all particles
#ifdef __THEBE__
    G4std::ofstream  fErrorOfs;              // for debugprint 
    G4int            fStoredDebugPrintID;    // -2 : no output
                                             // -1 : output last track
                                             // N  : output Nth track 
#endif

    J4TrackingActionMessenger * fMessenger;

};

//=====================================================
// * Inline Functions
//=====================================================

void J4TrackingAction::SetStoredTrajectoryID(G4int id) 
{ 
   fStoredTrajectoryID = id;
   G4cerr << " J4TrackingAction::StoredTracjectoryID is " 
          << fStoredTrajectoryID << G4endl;
}

#ifdef __THEBE__
void J4TrackingAction::SetStoredDebugPrintID(G4int id) 
{  
   fStoredDebugPrintID = id;
   G4cerr << " J4TrackingAction::StoredDebugPrintID is " 
          << fStoredDebugPrintID << G4endl;
}
#endif

#endif


