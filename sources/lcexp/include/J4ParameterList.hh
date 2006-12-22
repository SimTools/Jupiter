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
 protected:  
   
   J4ParameterList(const G4String &name);

 public:

   virtual ~J4ParameterList(); 
   
   // Getters

   static J4ParameterList *GetInstance();

   inline G4String GetEXPHallMaterial () const { return fEXPHallMaterial; }
   inline G4bool   GetEXPHallVisAtt   () const { return fEXPHallVisAtt;   }
   inline G4Color  GetEXPHallColor    () const { return fEXPHallColor;    }
   inline G4double GetEXPHallHalfX    () const { return fEXPHallHalfX;    }
   inline G4double GetEXPHallHalfY    () const { return fEXPHallHalfY;    }
   inline G4double GetEXPHallHalfZ    () const { return fEXPHallHalfZ;    }

   inline G4double GetBPOuterR        () const { return fBPOuterR;        }
   inline G4double GetBPMargin        () const { return fBPMargin;        }

   inline G4double GetIRThetaMax      () const { return fIRThetaMax;      }
   inline G4double GetIRBoxFrontZ     () const { return fIRBoxFrontZ;     }
   inline G4double GetIRBoxEndZ       () const { return fIRBoxEndZ;       }
   inline G4double GetIRBoxHalfX      () const { return GetEXPHallHalfX() - 1*cm;}
   inline G4double GetIRBoxHalfY      () const { return GetEXPHallHalfY() - 1*cm;}

   inline G4double GetSupportTubInnerR() const { return fSupportTubInnerR;}
   inline G4double GetSupportTubOuterR() const { return fSupportTubOuterR;}

   inline G4double GetVTXInnerR       () const { return GetBPOuterR();    }
   inline G4double GetVTXOuterR       () const { return fVTXOuterR;       }
   inline G4double GetVTXZcoverage    () const { return fVTXZcoverage;    }
   inline G4double GetVTXHalfZ        () const ;   

   inline G4double GetITInnerR        () const { return GetVTXOuterR();   }
   inline G4double GetITOuterR        () const { return GetSupportTubInnerR();}
   inline G4double GetITZcoverage     () const { return fITZcoverage;    }
   inline G4double GetITHalfZ         () const ;
   inline G4double GetITZMax          () const { return fITZMax; }

   inline G4double GetCDCInnerR       () const { return GetSupportTubOuterR();}
   inline G4double GetCDCOuterR       () const { return fCDCOuterR;       }
   inline G4double GetCDCHalfZ        () const { return fCDCHalfZ;        }

   inline G4double GetTPCInnerR       () const { return GetSupportTubOuterR();}
   inline G4double GetTPCOuterR       () const { return fTPCOuterR;       }
   inline G4double GetTPCHalfZ        () const { return fTPCHalfZ;        }

   inline G4double GetCALInnerR       () const { return fCALInnerR;       }
   inline G4double GetCALOuterR       () const { return fCALOuterR;       }
   inline G4double GetCALInnerHalfZ   () const { return fCALInnerHalfZ;   }
   inline G4double GetCALOuterHalfZ   () const { return fCALOuterHalfZ;   }
 
   inline G4double GetSOLInnerR       () const { return fSOLInnerR;       }
   inline G4double GetSOLOuterR       () const { return fSOLOuterR;       }
   inline G4double GetSOLHalfZ        () const { return fSOLHalfZ;        }

   inline G4int    GetIRNSolids       () const { return fIRNSolids;       }
   inline G4double GetIRREdges(int i)    const { return fIRREdges[i];     }
   inline G4double GetIRZEdges(int i)    const { return fIRZEdges[i];     }
   inline G4int    GetIRShapes(int i)    const { return fIRShapes[i];     }

   // Setters

   inline void     SetEXPHallMaterial(G4String s) { fEXPHallMaterial  = s; }
   inline void     SetEXPHallVisAtt  (G4bool   b) { fEXPHallVisAtt    = b; }
   inline void     SetEXPHallColor   (G4Color  c) { fEXPHallColor     = c; }
   inline void     SetEXPHallHalfX   (G4double x) { fEXPHallHalfX     = x; }
   inline void     SetEXPHallHalfY   (G4double x) { fEXPHallHalfY     = x; }
   inline void     SetEXPHallHalfZ   (G4double x) { fEXPHallHalfZ     = x; }

   inline void     SetBPOuterR       (G4double x) { fBPOuterR         = x; }
   inline void     SetBPMargin       (G4double x) { fBPMargin         = x; }

   inline void     SetIRThetaMax     (G4double x) { fIRThetaMax       = x; }
   inline void     SetIRBoxFrontZ    (G4double x) { fIRBoxFrontZ      = x; }
   inline void     SetIRBoxEndZ      (G4double x) { fIRBoxEndZ        = x; }
   inline void     SetIRBoxHalfX     (G4double x) { fIRBoxHalfX       = x; }
   inline void     SetIRBoxHalfY     (G4double x) { fIRBoxHalfY       = x; }

   inline void     SetSupportTubInnerR (G4double x) { fSupportTubInnerR = x; }
   inline void     SetSupportTubOuterR (G4double x) { fSupportTubOuterR = x; }

   inline void     SetVTXOuterR      (G4double x) { fVTXOuterR        = x; }
   inline void     SetVTXZcoverage   (G4double x) { fVTXZcoverage     = x; }

   inline void     SetITZcoverage    (G4double x) { fITZcoverage      = x; }

   inline void     SetCDCOuterR      (G4double x) { fCDCOuterR        = x; }
   inline void     SetCDCHalfZ       (G4double x) { fCDCHalfZ         = x; }

   inline void     SetTPCOuterR      (G4double x) { fTPCOuterR        = x; }
   inline void     SetTPCHalfZ       (G4double x) { fTPCHalfZ         = x; }

   inline void     SetCALInnerR      (G4double x) { fCALInnerR        = x; }
   inline void     SetCALOuterR      (G4double x) { fCALOuterR        = x; }
   inline void     SetCALInnerHalfZ  (G4double x) { fCALInnerHalfZ    = x; }
   inline void     SetCALOuterHalfZ  (G4double x) { fCALOuterHalfZ    = x; }
 
   inline void     SetSOLInnerR      (G4double x) { fSOLInnerR        = x; }
   inline void     SetSOLOuterR      (G4double x) { fSOLOuterR        = x; }
   inline void     SetSOLHalfZ       (G4double x) { fSOLHalfZ         = x; }

   
   virtual void    SetParameters();
   virtual void    PrintParameterList(){}
    

 private:

   static J4ParameterList *fgInstance;

   G4String  fEXPHallMaterial; 
   G4bool    fEXPHallVisAtt;
   G4Color   fEXPHallColor;
   G4double  fEXPHallHalfX;
   G4double  fEXPHallHalfY;
   G4double  fEXPHallHalfZ;

   G4double  fBPOuterR;         // OuterR of BeamPipe
   G4double  fBPMargin;         // Margin between beampipe and IR region
   G4double  fIRThetaMax;       // Theta Max of IR region
   G4double  fIRBoxFrontZ;      // Front-z of IR box     
   G4double  fIRBoxEndZ;        // End-z of IR box
   G4double  fIRBoxHalfX;       // half x-width of IR box
   G4double  fIRBoxHalfY;       // half y-width of IR box

   G4double  fSupportTubInnerR; // InnerR of Support Tub
   G4double  fSupportTubOuterR; // OuterR of Support Tub

   G4double  fVTXOuterR;        // OuterR of VTX 
   G4double  fVTXZcoverage;     // z coverage of VTX in cos_theta

   G4double  fITZMax;           // Zcordinate maximum of IT
   G4double  fITZcoverage;      // z coverage of IT in cos_theta 

   G4double  fCDCOuterR;        // OuterR of CDC 
   G4double  fCDCHalfZ;         // half z length of CDC 

   G4double  fTPCOuterR;        // OuterR of TPC
   G4double  fTPCHalfZ;         // half z length of TPC

   G4double  fCALInnerR;        // InnerR of CAL 
   G4double  fCALOuterR;        // OuterR of CAL 
   G4double  fCALInnerHalfZ;    // half z length of innerface of CAL 
   G4double  fCALOuterHalfZ;    // half z length of outersurface of CAL 

   G4double  fSOLInnerR;        // InnerR of CAL 
   G4double  fSOLOuterR;        // OuterR of CAL 
   G4double  fSOLHalfZ;         // half z length of CAL 

   G4int     fIRNSolids;        // Number of solids to define IR and VTX/IT boundary
   G4double  *fIRREdges;        // Radius of IR and VTX/IT boundary
   G4double  *fIRZEdges;        // Z poistion of IR and VTX/IT boundary corner position
   G4int     *fIRShapes;        // Shape of boundary (0=tubs, 1=cons)    

};

//=========================================================
//* inline functions

G4double J4ParameterList::GetVTXHalfZ() const   
{
   G4double costheta  = GetVTXZcoverage();
   G4double cottheta = costheta / std::sqrt((1 + costheta) * (1 - costheta)); 
   return GetVTXOuterR() * cottheta; 
}

G4double J4ParameterList::GetITHalfZ() const   
{
   G4double costheta  = GetITZcoverage();
   G4double cottheta = costheta / std::sqrt((1 + costheta) * (1 - costheta)); 
   return GetITOuterR() * cottheta; 
}

#endif
