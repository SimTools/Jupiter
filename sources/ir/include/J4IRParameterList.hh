// $Id$
#ifndef __J4IRPARAMETERLIST__
#define __J4IRPARAMETERLIST__
//********************************************************************
//* ---------------------------
//* J4IRParameterList.hh
//* ---------------------------
//* (Description)
//* 	ParameterList class for IR
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
 
class J4IRParameterList : public J4VParameterList 
{
 public:
   J4IRParameterList();

   virtual ~J4IRParameterList() {}

   static J4IRParameterList *GetInstance() { return fInstance;    }
   
   // Getters
   inline G4String GetMaterial()         const { return fMaterial;      }
   inline G4bool   GetVisAtt  ()         const { return fVisAtt;        }
   inline G4Color *GetColor   ()         const { return fColor;         }
   inline G4double GetZMax    ()         const { return fZMax;          }
   inline G4double GetZMid    ()         const { return fZMid;          }
   inline G4double GetThetaMax()         const { return fThetaMax;      }
   inline G4double GetIRBoxHalfX()       const { return fIRBoxHalfX;    }
   inline G4double GetIRBoxHalfY()       const { return fIRBoxHalfY;    }
   inline G4double GetSupportTubInnerR() const { return fSuppTubInnerR ;}
   inline G4double GetBeampipeOuterR  () const { return fBeampipeOuterR;}

   // Setters
   inline void SetMaterial        (G4String s) { fMaterial       = s; }
   inline void SetVisAtt          (G4bool   b) { fVisAtt         = b; }
   inline void SetColor           (G4Color *c) { fColor          = c; }
   inline void SetZMax            (G4double x) { fZMax           = x; }
   inline void SetZMid            (G4double x) { fZMid           = x; }
   inline void SetThetaMax        (G4double x) { fThetaMax       = x; }
   inline void SetIRBoxHalfX      (G4double x) { fIRBoxHalfX     = x; }
   inline void SetIRBoxHalfY      (G4double x) { fIRBoxHalfY     = x; }
   inline void SetSupportTubInnerR(G4double x) { fSuppTubInnerR  = x; }
   inline void SetBeampipeOuterR  (G4double x) { fBeampipeOuterR = x; }
   
   virtual void    PrintParameterList(){};
    
 private:
   static J4IRParameterList *fInstance;

   G4String  fMaterial; 
   G4bool    fVisAtt;
   G4Color  *fColor;

   G4double  fZMax;
   G4double  fZMid;
   G4double  fThetaMax;
   G4double  fIRBoxHalfX;
   G4double  fIRBoxHalfY;
   G4double  fSuppTubInnerR;
   G4double  fBeampipeOuterR;

};

#endif
