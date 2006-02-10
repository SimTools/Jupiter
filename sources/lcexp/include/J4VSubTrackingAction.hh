#ifndef __J4VSUBTRACKINGACTION__ 
#define __J4VSUBTRACKINGACTION__ 
//*************************************************************************
//* --------------------
//* J4VSubTrackingAction
//* --------------------
//* (Description)
//* 	Base class to define TrackingAction by a detector component.
//*     J4TrackingAction invokes
//*       PreTrackDoIt
//*       PostTrackDoIt
//*     at the beginning and the end of each track's life time. 
//* (Update Record)
//*	2004/12/09  K.Fujii	Original version.
//*************************************************************************
//

#include "G4Types.hh"
#include "G4Track.hh"

class J4VSubTrackingAction {
public:
  J4VSubTrackingAction();
  virtual ~J4VSubTrackingAction();
   
  virtual void    PreTrackDoIt(const G4Track* aTrack = 0) = 0;
  virtual void    Clear() {}
};

#endif


