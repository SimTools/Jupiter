#ifndef __J4CALPREHITKEEPER__ 
#define __J4CALPREHITKEEPER__
//*************************************************************************
//* --------------------
//* J4CALPreHitKeeper
//* --------------------
//* (Description)
//* 	Class to book keep pre hits for CAL
//* (Update Record)
//*	2004/12/09  K.Fujii	Original version.
//*************************************************************************
//

#include "J4PHitKeeper.hh"

class J4CALPreHit;

class J4CALPreHitKeeper : public J4PHitKeeper {
private:
  J4CALPreHitKeeper();                       // J4CALPreHitKeeper is a singleton

public:
  static  J4CALPreHitKeeper *GetInstance();  // use this getter to create it
  virtual ~J4CALPreHitKeeper();
   
  inline J4CALPreHit *GetCurrentPreHitPtr() const { return fCurrentPreHitPtr; }
  inline G4int        GetCurrentPreHitID () const { return fCurrentPreHitID;  }

  inline void SetCurrentPreHitPtr(J4CALPreHit* p) { fCurrentPreHitPtr = p;    }
  inline void SetCurrentPreHitID (G4int n)        { fCurrentPreHitID  = n;    }
  inline void IncrementCurrentPreHitID()          { fCurrentPreHitID++;       }

private:
         J4CALPreHit       *fCurrentPreHitPtr;
         G4int              fCurrentPreHitID;
  static J4CALPreHitKeeper *fgInstance;
};

#endif
