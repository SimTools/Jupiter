// $Id$
#ifndef __J4PARAMETERLIST__
#define __J4PARAMETERLIST__
//********************************************************************
//* ---------------------------
//* J4ParameterList.hh
//* ---------------------------
//* (Description)
//* 	ParameterList class for All Detectors
//*     
//* (Update Record)
//*	2002/10/28  R.Kuboshima  Original version.
//********************************************************************

#include "G4Material.hh"
#include "G4Color.hh"
#include "J4VParameterList.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4ParameterList : public J4VParameterList 
{

 public:
   
   //* --------------------------------------------------------- 
   //* !!! ATTENTION !!!
   //* J4ParameterList must be singleton. 
   //* Call the constructor at the begining of the main program.  
   //* --------------------------------------------------------- 

   J4ParameterList();

   virtual ~J4ParameterList(); 
   
   // Getters

   static J4ParameterList *GetInstance()      { return fgParameterList ; }

   inline G4String GetEXPHallMaterial() const { return fEXPHallMaterial;   }
   inline G4bool   GetEXPHallVisAtt  () const { return fEXPHallVisAtt;     }
   inline G4Color* GetEXPHallColor   () const { return fEXPHallColor;      }
   inline G4double GetEXPHallHalfX   () const { return fEXPHallHalfX;      }
   inline G4double GetEXPHallHalfY   () const { return fEXPHallHalfY;      }
   inline G4double GetEXPHallHalfZ   () const { return fEXPHallHalfZ;      }

   inline G4double GetBPOuterRadius  () const { return fBPOuterRadius;     }
   inline G4double GetBPMargin       () const { return fBPMargin;          }

   inline G4double GetIRThetaMax     () const { return fIRThetaMax;        }
   inline G4double GetIRBoxFrontZ    () const { return fIRBoxFrontZ;       }
   inline G4double GetIRBoxEndZ      () const { return fIRBoxEndZ;         }
   inline G4double GetIRBoxHalfX     () const { return fIRBoxHalfX;        }
   inline G4double GetIRBoxHalfY     () const { return fIRBoxHalfY;        }

   inline G4double GetSupportTubInnerRadius () const { return fSupportTubInnerRadius; }
   inline G4double GetSupportTubOuterRadius () const { return fSupportTubOuterRadius; }

   inline G4double GetVTXOuterRadius () const { return fVTXOuterRadius; }
   inline G4double GetVTXAngle       () const { return fVTXAngle;          }

   inline G4double GetCDCOuterRadius () const { return fCDCOuterRadius; }
   inline G4double GetCDCHalfZ       () const { return fCDCHalfZ;          }

   inline G4double GetCALInnerRadius () const { return fCALInnerRadius; }
   inline G4double GetCALOuterRadius () const { return fCALOuterRadius; }
   inline G4double GetCALHalfZ       () const { return fCALHalfZ;          }
 
   inline G4double GetSOLInnerRadius () const { return fSOLInnerRadius; }
   inline G4double GetSOLOuterRadius () const { return fSOLOuterRadius; }
   inline G4double GetSOLHalfZ       () const { return fSOLHalfZ;          }
  
   // Setters

   inline void     SetEXPHallMaterial(G4String s) { fEXPHallMaterial  = s; }
   inline void     SetEXPHallVisAtt  (G4bool   b) { fEXPHallVisAtt    = b; }
   inline void     SetEXPHallColor   (G4Color* c) { fEXPHallColor     = c; }
   inline void     SetEXPHallHalfX   (G4double x) { fEXPHallHalfX     = x; }
   inline void     SetEXPHallHalfY   (G4double x) { fEXPHallHalfY     = x; }
   inline void     SetEXPHallHalfZ   (G4double x) { fEXPHallHalfZ     = x; }

   inline void     SetBPOuterRadius  (G4double x) { fBPOuterRadius    = x; }
   inline void     SetBPMargin       (G4double x) { fBPMargin         = x; }

   inline void     SetIRThetaMax     (G4double x) { fIRThetaMax       = x; }
   inline void     SetIRBoxFrontZ    (G4double x) { fIRBoxFrontZ      = x; }
   inline void     SetIRBoxEndZ      (G4double x) { fIRBoxEndZ        = x; }
   inline void     SetIRBoxHalfX     (G4double x) { fIRBoxHalfX       = x; }
   inline void     SetIRBoxHalfY     (G4double x) { fIRBoxHalfY       = x; }

   inline void     SetSupportTubInnerRadius (G4double x) { fSupportTubInnerRadius = x; }
   inline void     SetSupportTubOuterRadius (G4double x) { fSupportTubOuterRadius = x; }

   inline void     SetVTXOuterRadius (G4double x) { fVTXOuterRadius    = x; }
   inline void     SetVTXAngle       (G4double x) { fVTXAngle          = x; }

   inline void     SetCDCOuterRadius (G4double x) { fCDCOuterRadius = x; }
   inline void     SetCDCHalfZ       (G4double x) { fCDCHalfZ          = x; }

   inline void     SetCALInnerRadius (G4double x) { fCALInnerRadius = x; }
   inline void     SetCALOuterRadius (G4double x) { fCALOuterRadius = x; }
   inline void     SetCALHalfZ       (G4double x) { fCALHalfZ          = x; }
 
   inline void     SetSOLInnerRadius (G4double x) { fSOLInnerRadius = x; }
   inline void     SetSOLOuterRadius (G4double x) { fSOLOuterRadius = x; }
   inline void     SetSOLHalfZ       (G4double x) { fSOLHalfZ          = x; }
   
   virtual void    SetParameters();
   virtual void    PrintParameterList(){}
    

 private:

   static J4ParameterList *fgParameterList;

   G4String  fEXPHallMaterial; 
   G4bool    fEXPHallVisAtt;
   G4Color  *fEXPHallColor;
   G4double  fEXPHallHalfX;
   G4double  fEXPHallHalfY;
   G4double  fEXPHallHalfZ;

   G4double  fBPOuterRadius;         // OuterRadius of BeamPipe
   G4double  fBPMargin;              // Margin between beampipe and IR region
   G4double  fIRThetaMax;            // Theta Max of IR region
   G4double  fIRBoxFrontZ;           // Front-z of IR box     
   G4double  fIRBoxEndZ;             // End-z of IR box
   G4double  fIRBoxHalfX;            // half x-width of IR box
   G4double  fIRBoxHalfY;            // half y-width of IR box

   G4double  fSupportTubInnerRadius; // InnerRadius of Support Tub
   G4double  fSupportTubOuterRadius; // OuterRadius of Support Tub

   G4double  fVTXOuterRadius;        // OuterRadius of VTX 
   G4double  fVTXAngle;              // half z length of VTX 

   G4double  fCDCOuterRadius;        // OuterRadius of CDC 
   G4double  fCDCHalfZ;              // half z length of CDC 

   G4double  fCALInnerRadius;        // InnerRadius of CAL 
   G4double  fCALOuterRadius;        // OuterRadius of CAL 
   G4double  fCALHalfZ;              // half z length of CAL 

   G4double  fSOLInnerRadius;        // InnerRadius of CAL 
   G4double  fSOLOuterRadius;        // OuterRadius of CAL 
   G4double  fSOLHalfZ;              // half z length of CAL 

};

#endif
