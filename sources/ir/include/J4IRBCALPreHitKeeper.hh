#ifndef __J4IRBCALPREHITKEEPER__ 
#define __J4IRBCALPREHITKEEPER__
//*************************************************************************
//* --------------------
//* J4IRBCALPreHitKeeper
//* --------------------
//* (Description)
//* 	Class to book keep pre hits for CAL
//* (Update Record)
//*	2004/12/09  K.Fujii	Original version.
//*************************************************************************
//

#include "J4PHitKeeper.hh"

class J4IRBCALPreHit;

class J4IRBCALPreHitKeeper : public J4PHitKeeper {
private:
  J4IRBCALPreHitKeeper();                       // J4IRBCALPreHitKeeper is a singleton

public:
  static  J4IRBCALPreHitKeeper *GetInstance();  // use this getter to create it
  virtual ~J4IRBCALPreHitKeeper();
   
  inline J4IRBCALPreHit *GetCurrentPreHitPtr() const { return fCurrentPreHitPtr; }
  inline G4int        GetCurrentPreHitID () const { return fCurrentPreHitID;  }

  inline void SetCurrentPreHitPtr(J4IRBCALPreHit* p) { fCurrentPreHitPtr = p;    }
  inline void SetCurrentPreHitID (G4int n)        { fCurrentPreHitID  = n;    }
  inline void IncrementCurrentPreHitID()          { fCurrentPreHitID++;       }

private:
         J4IRBCALPreHit       *fCurrentPreHitPtr;
         G4int              fCurrentPreHitID;
  static J4IRBCALPreHitKeeper *fgInstance;
};

#endif
