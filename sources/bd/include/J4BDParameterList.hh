// $Id$
#ifndef __J4BDPARAMETERLIST__
#define __J4BDPARAMETERLIST__
//********************************************************************
//* ---------------------------
//* J4BDParameterList.hh
//* ---------------------------
//* (Description)
//* 	ParameterList class for BD
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
 public:
   J4BDParameterList();

   virtual ~J4BDParameterList() {}

   static J4BDParameterList *GetInstance() { return fInstance;    }
   
   // Getters
   inline G4String GetMaterial()         const { return fMaterial;      }
   inline G4bool   GetVisAtt  ()         const { return fVisAtt;        }
   inline G4Color *GetColor   ()         const { return fColor;         }
   inline G4double GetOuterHalfX()       const { return fOuterHalfX;    }
   inline G4double GetOuterHalfY()       const { return fOuterHalfY;    }
   inline G4double GetOuterHalfZ()       const { return fOuterHalfZ;    }
   inline G4double GetInnerHalfX()       const { return fInnerHalfX;    }
   inline G4double GetInnerHalfY()       const { return fInnerHalfY;    }
   inline G4double GetInnerHalfZ()       const { return fInnerHalfZ;    }

   // Setters
   inline void SetMaterial        (G4String s) { fMaterial       = s; }
   inline void SetVisAtt          (G4bool   b) { fVisAtt         = b; }
   inline void SetColor           (G4Color *c) { fColor          = c; }
   inline void SetOuterHalfX      (G4double x) { fOuterHalfX     = x; }
   inline void SetOuterHalfY      (G4double x) { fOuterHalfY     = x; }
   inline void SetOuterHalfZ      (G4double x) { fOuterHalfZ     = x; }
   inline void SetInnerHalfX      (G4double x) { fInnerHalfX     = x; }
   inline void SetInnerHalfY      (G4double x) { fInnerHalfY     = x; }
   inline void SetInnerHalfZ      (G4double x) { fInnerHalfZ     = x; }
   
   virtual void    PrintParameterList(){};
    
 private:
   static J4BDParameterList *fInstance;

   G4String  fMaterial; 
   G4bool    fVisAtt;
   G4Color  *fColor;

   G4double  fOuterHalfX;
   G4double  fOuterHalfY;
   G4double  fOuterHalfZ;
   G4double  fInnerHalfX;
   G4double  fInnerHalfY;
   G4double  fInnerHalfZ;

};

#endif
