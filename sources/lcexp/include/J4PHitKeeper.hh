#ifndef __J4PHITKEEPER__ 
#define __J4PHITKEEPER__
//*************************************************************************
//* --------------------
//* J4PHitKeeper
//* --------------------
//* (Description)
//* 	Base class to book keep pre or post hists.
//* (Update Record)
//*	2004/12/09  K.Fujii	Original version.
//*************************************************************************
//

#include "J4VSubTrackingAction.hh"
#include "globals.hh"

class J4PHitKeeper : public J4VSubTrackingAction {
public:
  J4PHitKeeper();
  virtual ~J4PHitKeeper();
   
  virtual void    PreTrackDoIt(const G4Track*);
          G4bool  IsNext();
          void    Reset (G4int n = INT_MAX);
  inline  G4int   GetCurTrackID() { return fInTrackID; }
  inline  G4bool  IsPHitCreated() { return fIsPHitCreated; }

private:
  G4int       fInTrackID;    // incident track ID
  G4int       fTopTrackID;   // top of strack track ID 
  G4bool      fIsPHitCreated;// whether PHit created or not
};

#endif
