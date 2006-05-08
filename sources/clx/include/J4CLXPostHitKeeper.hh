// $Id$
#ifndef __J4CLXPOSTHITKEEPER__ 
#define __J4CLXPOSTHITKEEPER__
//*************************************************************************
//* --------------------
//* J4CLXPostHitKeeper
//* --------------------
//* (Description)
//* 	Class to book keep post hits for CLX
//* (Update Record)
//*	2004/12/09  K.Fujii	Original version.
//*************************************************************************
#include "J4PHitKeeper.hh"

class J4CLXPostHit;
class J4CLXPostHitKeeper : public J4PHitKeeper {

private:
  J4CLXPostHitKeeper();               // J4CLXPostHitKeeper is a singleton

public:
  virtual ~J4CLXPostHitKeeper();

  static J4CLXPostHitKeeper *GetInstance();  // use this getter to create it
         G4int               GetCurPostHitID  () const;
         J4CLXPostHit*       GetCurPostHitPtr () const;

private:
  static J4CLXPostHitKeeper *fgInstance;
};

#endif
