// $Id$
#ifndef __J4SOLPARAMETERLIST__
#define __J4SOLPARAMETERLIST__
//********************************************************************
//* ---------------------------
//* J4SOLParameterList.hh
//* ---------------------------
//* (Description)
//* 	ParameterList class for Detector Solenoid
//*     
//* (Update Record)
//*	2002/10/28  R.Kuboshima  Original version.
//********************************************************************

#include "globals.hh"
#include "G4Material.hh"
#include "G4Color.hh"
#include "J4VParameterList.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4SOLParameterList : public J4VParameterList 
{
 public:
   J4SOLParameterList(G4double ri   = 375.*cm,
                      G4double ro   = 450.*cm,
                      G4double len    = 340.*cm,
                      G4double bfield = 3.*tesla,
                    // G4double magrad =  160.*cm)
                      G4double magrad =  400.*cm)
           : fMaterial("Air"),
	     fMagInnerRadius(ri),
             fMagOuterRadius(ro),
             fMagLength(len),
             fMagRad(magrad),
             fBField(bfield),
	     fVisAtt(TRUE),
	     fColor(0.,0.,0.5) {}
   virtual ~J4SOLParameterList() {}
   
   // Getters
   inline G4String GetMaterial() const { return fMaterial;        }
   inline G4double GetIR      () const { return fMagInnerRadius;  }
   inline G4double GetOR      () const { return fMagOuterRadius;  }
   inline G4double GetLength  () const { return fMagLength;       }
   inline G4double GetMagRad  () const { return fMagRad;          }
   inline G4double GetBField  () const { return fBField;          }
   inline G4bool   GetVisAtt  () const { return fVisAtt;          }
   inline G4Color  GetColor   () const { return fColor;           }

   // Setters
   inline void     SetMaterial(G4String s) { fMaterial       = s; }
   inline void     SetIR      (G4double x) { fMagInnerRadius = x; }
   inline void     SetOR      (G4double x) { fMagOuterRadius = x; }
   inline void     SetLength  (G4double x) { fMagLength      = x; }
   inline void     SetMagRad  (G4double x) { fMagRad         = x; }
   inline void     SetBField  (G4double x) { fBField         = x; }
   inline void     SetVisAtt  (G4bool   b) { fVisAtt         = b; }
   inline void     SetColor   (G4Color  c) { fColor          = c; }
   
   virtual void PrintParameterList(){};
    
 private:
   G4String  fMaterial; 

   G4double  fMagInnerRadius;
   G4double  fMagOuterRadius;
   G4double  fMagLength;
   G4double  fMagRad;

   G4double  fBField;

   G4bool    fVisAtt;
   G4Color   fColor;
};

#endif
