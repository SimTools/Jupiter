#ifndef __J4CALPOSTHITKEEPER__ 
#define __J4CALPOSTHITKEEPER__
//*************************************************************************
//* --------------------
//* J4CALPostHitKeeper
//* --------------------
//* (Description)
//* 	Class to book keep post hits for CAL
//* (Update Record)
//*	2004/12/09  K.Fujii	Original version.
//*************************************************************************
#include "J4PHitKeeper.hh"

class J4CALPostHit;
class J4CALPostHitKeeper : public J4PHitKeeper {

private:
  J4CALPostHitKeeper();               // J4CALPostHitKeeper is a singleton

public:
  virtual ~J4CALPostHitKeeper();

  static J4CALPostHitKeeper *GetInstance();  // use this getter to create it
         G4int               GetCurPostHitID  () const;
         J4CALPostHit*       GetCurPostHitPtr () const;

private:
  static J4CALPostHitKeeper *fgInstance;
};

#endif
