// $Id$
#ifndef __J4BDPARAMETERLIST__
#define __J4BDPARAMETERLIST__
//********************************************************************
//* ---------------------------
//* J4BDParameterList.hh
//* ---------------------------
//* (Description)
//* 	ParameterList class for BD
//*     The instance must be singleton. Use "GetInstance()" function
//*     to create and get the instance.
//*     
//* (Update Record)
//*	2003/02/28  R.Kuboshima  Original version.
//********************************************************************

#include "globals.hh"
#include "G4Material.hh"
#include "G4Color.hh"
#include "J4VParameterList.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4BDParameterList : public J4VParameterList 
{

 protected: 
   J4BDParameterList(const G4String &name);

 public:
   virtual ~J4BDParameterList();

   static J4BDParameterList *GetInstance();
   
   // Getters
   inline G4String GetBDMaterial()       const { return fBDMaterial;    }
   inline G4bool   GetBDVisAtt  ()       const { return fBDVisAtt;      }
   inline G4Color  GetBDColor   ()       const { return fBDColor;       }
   inline G4double GetBDOuterHalfX()     const { return fBDOuterHalfX;  }
   inline G4double GetBDOuterHalfY()     const { return fBDOuterHalfY;  }
   inline G4double GetBDOuterHalfZ()     const { return fBDOuterHalfZ;  }
   inline G4double GetBDInnerHalfX()     const { return fBDInnerHalfX;  }
   inline G4double GetBDInnerHalfY()     const { return fBDInnerHalfY;  }
   inline G4double GetBDInnerHalfZ()     const { return fBDInnerHalfZ;  }

   // Setters
   inline void SetBDMaterial      (G4String s) { fBDMaterial     = s; }
   inline void SetBDVisAtt        (G4bool   b) { fBDVisAtt       = b; }
   inline void SetBDColor         (G4Color  c) { fBDColor        = c; }
   inline void SetBDOuterHalfX    (G4double x) { fBDOuterHalfX   = x; }
   inline void SetBDOuterHalfY    (G4double x) { fBDOuterHalfY   = x; }
   inline void SetBDOuterHalfZ    (G4double x) { fBDOuterHalfZ   = x; }
   inline void SetBDInnerHalfX    (G4double x) { fBDInnerHalfX   = x; }
   inline void SetBDInnerHalfY    (G4double x) { fBDInnerHalfY   = x; }
   inline void SetBDInnerHalfZ    (G4double x) { fBDInnerHalfZ   = x; }
   
   virtual void    PrintParameterList(){};
    
 private:
   static J4BDParameterList *fgInstance;

   G4String  fBDMaterial; 
   G4bool    fBDVisAtt;
   G4Color   fBDColor;

   G4double  fBDOuterHalfX;
   G4double  fBDOuterHalfY;
   G4double  fBDOuterHalfZ;
   G4double  fBDInnerHalfX;
   G4double  fBDInnerHalfY;
   G4double  fBDInnerHalfZ;

};

#endif
