#ifndef __J4MUDPREHITKEEPER__ 
#define __J4MUDPREHITKEEPER__
//*************************************************************************
//* --------------------
//* J4MUDPreHitKeeper
//* --------------------
//* (Description)
//* 	Class to book keep pre hits for MUD 
//* (Update Record)
//*	2004/12/09  K.Fujii	Original version.
//*************************************************************************
#include "J4PHitKeeper.hh"

class J4MUDPreHit;
class J4MUDPreHitKeeper : public J4PHitKeeper {
private:
  J4MUDPreHitKeeper();                       // J4MUDPreHitKeeper is a singleton

public:
  static  J4MUDPreHitKeeper *GetInstance();  // use this getter to create it
  virtual ~J4MUDPreHitKeeper();
   
  inline J4MUDPreHit *GetCurrentPreHitPtr() const { return fCurrentPreHitPtr; }
  inline G4int        GetCurrentPreHitID () const { return fCurrentPreHitID;  }

  inline void SetCurrentPreHitPtr(J4MUDPreHit* p) { fCurrentPreHitPtr = p;    }
  inline void SetCurrentPreHitID (G4int n)        { fCurrentPreHitID  = n;    }
  inline void IncrementCurrentPreHitID()          { fCurrentPreHitID++;       }

private:
         J4MUDPreHit       *fCurrentPreHitPtr;
         G4int              fCurrentPreHitID;
  static J4MUDPreHitKeeper *fgInstance;
};

#endif
