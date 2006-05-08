//$Id$
#ifndef __J4CLXPREHITKEEPER__ 
#define __J4CLXPREHITKEEPER__
//*************************************************************************
//* --------------------
//* J4CLXPreHitKeeper
//* --------------------
//* (Description)
//* 	Class to book keep pre hits for CLX
//* (Update Record)
//*	2004/12/09  K.Fujii	Original version.
//*************************************************************************
//

#include "J4PHitKeeper.hh"

class J4CLXPreHit;

class J4CLXPreHitKeeper : public J4PHitKeeper {
private:
  J4CLXPreHitKeeper();                       // J4CLXPreHitKeeper is a singleton

public:
  static  J4CLXPreHitKeeper *GetInstance();  // use this getter to create it
  virtual ~J4CLXPreHitKeeper();
   
  inline J4CLXPreHit *GetCurrentPreHitPtr() const { return fCurrentPreHitPtr; }
  inline G4int        GetCurrentPreHitID () const { return fCurrentPreHitID;  }

  inline void SetCurrentPreHitPtr(J4CLXPreHit* p) { fCurrentPreHitPtr = p;    }
  inline void SetCurrentPreHitID (G4int n)        { fCurrentPreHitID  = n;    }
  inline void IncrementCurrentPreHitID()          { fCurrentPreHitID++;       }

private:
         J4CLXPreHit       *fCurrentPreHitPtr;
         G4int              fCurrentPreHitID;
  static J4CLXPreHitKeeper *fgInstance;
};

#endif
