#ifndef __J4TPCPOSTHITKEEPER__ 
#define __J4TPCPOSTHITKEEPER__
//*************************************************************************
//* --------------------
//* J4TPCPostHitKeeper
//* --------------------
//* (Description)
//* 	Class to book keep post hits for TPC
//* (Update Record)
//*	2004/12/09  K.Fujii	Original version.
//*************************************************************************
//

#include "J4PHitKeeper.hh"

class J4TPCPostHit;

class J4TPCPostHitKeeper : public J4PHitKeeper {
private:
  J4TPCPostHitKeeper();               // J4TPCPostHitKeeper is a singleton

public:
  virtual ~J4TPCPostHitKeeper();

  static J4TPCPostHitKeeper *GetInstance();  // use this getter to create it
         G4int               GetCurPostHitID () const;

private:
  static J4TPCPostHitKeeper *fgInstance;
};

#endif
