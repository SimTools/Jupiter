#ifndef __J4IRFCALPREHITKEEPER__ 
#define __J4IRFCALPREHITKEEPER__
//*************************************************************************
//* --------------------
//* J4IRFCALPreHitKeeper
//* --------------------
//* (Description)
//* 	Class to book keep pre hits for CAL
//* (Update Record)
//*	2004/12/09  K.Fujii	Original version.
//*************************************************************************
//

#include "J4PHitKeeper.hh"

class J4IRFCALPreHit;

class J4IRFCALPreHitKeeper : public J4PHitKeeper {
private:
  J4IRFCALPreHitKeeper();                       // J4IRFCALPreHitKeeper is a singleton

public:
  static  J4IRFCALPreHitKeeper *GetInstance();  // use this getter to create it
  virtual ~J4IRFCALPreHitKeeper();
   
  inline J4IRFCALPreHit *GetCurrentPreHitPtr() const { return fCurrentPreHitPtr; }
  inline G4int        GetCurrentPreHitID () const { return fCurrentPreHitID;  }

  inline void SetCurrentPreHitPtr(J4IRFCALPreHit* p) { fCurrentPreHitPtr = p;    }
  inline void SetCurrentPreHitID (G4int n)        { fCurrentPreHitID  = n;    }
  inline void IncrementCurrentPreHitID()          { fCurrentPreHitID++;       }

private:
         J4IRFCALPreHit       *fCurrentPreHitPtr;
         G4int              fCurrentPreHitID;
  static J4IRFCALPreHitKeeper *fgInstance;
};

#endif
