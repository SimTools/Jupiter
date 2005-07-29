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
#include "J4ParameterList.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4SOLParameterList : public J4VParameterList 
{
 protected:
   J4SOLParameterList( G4double ri     = 375.*cm,
                       G4double ro     = 450.*cm,
                       G4double len    = 380.*cm );
 public: 

   static J4SOLParameterList  *GetInstance();

   virtual ~J4SOLParameterList();
   
   // Getters
   inline G4double GetSOLInnerR  () const ; 
   inline G4double GetSOLOuterR  () const ;
   inline G4double GetSOLHalfZ   () const ;
   inline G4String GetSOLMaterial() const { return fSOLMaterial; }
   inline G4bool   GetSOLVisAtt  () const { return fSOLVisAtt;   }
   inline G4Color  GetSOLColor   () const { return fSOLColor;    }
   inline G4double GetFieldR     () const { return fFieldR;      }
   inline G4double GetBField     () const { return fBField;      }

   // Get Coil parameters
   inline G4double GetSOLCoilInnerR  () const { return fSOLCoilInnerR;   }
   inline G4double GetSOLCoilOuterR  () const { return fSOLCoilOuterR;   }
   inline G4double GetSOLCoilHalfZ   () const { return fSOLCoilHalfZ;    }
   inline G4String GetSOLCoilMaterial() const { return fSOLCoilMaterial; }
   inline G4bool   GetSOLCoilVisAtt  () const { return fSOLCoilVisAtt;   }
   inline G4Color  GetSOLCoilColor   () const { return fSOLCoilColor;    }

   // Setters
   inline void     SetSOLMaterial    ( G4String s ) { fSOLMaterial = s; }
   inline void     SetSOLVisAtt      ( G4bool   b ) { fSOLVisAtt   = b; }
   inline void     SetSOlColor       ( G4Color  c ) { fSOLColor    = c; }
   inline void     SetFieldR         ( G4double x ) { fFieldR      = x; }
   inline void     SetBField         ( G4double x ) { fBField      = x; }
  
   // Set Coil parameters
   inline void     SetSOLCoilInnerR  ( G4double r ) { fSOLCoilInnerR   = r; }
   inline void     SetSOLCoilOuterR  ( G4double r ) { fSOLCoilOuterR   = r; }
   inline void     SetSOLCoilHalfZ   ( G4double z ) { fSOLCoilHalfZ    = z; }
   inline void     SetSOLCoilMaterial( G4String s ) { fSOLCoilMaterial = s; }
   inline void     SetSOLCoilVisAtt  ( G4bool   b ) { fSOLCoilVisAtt   = b; }
   inline void     SetSOlCoilColor   ( G4Color  c ) { fSOLCoilColor    = c; }

   virtual void    PrintParameterList(){};
    
 private:
 
   static J4SOLParameterList  *fgInstance;

   G4String  fSOLMaterial; 
   G4bool    fSOLVisAtt;
   G4Color   fSOLColor;
   G4double  fFieldR;
   G4double  fBField;

   //Coil
   G4double  fSOLCoilInnerR;
   G4double  fSOLCoilOuterR;
   G4double  fSOLCoilHalfZ;
   G4String  fSOLCoilMaterial; 
   G4bool    fSOLCoilVisAtt;
   G4Color   fSOLCoilColor;

};

//=========================================================
//* inline functions

G4double J4SOLParameterList::GetSOLInnerR() const
{
   return J4ParameterList::GetInstance()->GetSOLInnerR();
}

G4double J4SOLParameterList::GetSOLOuterR() const
{
   return J4ParameterList::GetInstance()->GetSOLOuterR();
}

G4double J4SOLParameterList::GetSOLHalfZ() const
{
   return J4ParameterList::GetInstance()->GetSOLHalfZ();
}

#endif
