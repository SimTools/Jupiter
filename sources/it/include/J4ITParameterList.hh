// $Id$
#ifndef __J4ITPARAMETERLIST__
#define __J4ITPARAMETERLIST__
//********************************************************************
//* ---------------------
//* J4ITParameterList.hh
//* ---------------------
//* (Description)
//* 	Material Store class for IT.
//*     Define Materials for IT here.
//*     
//* (Update Record)
//*	2003/03/17  K.Hoshina	Original version.
//********************************************************************

#include "G4Material.hh"
#include "G4Color.hh"
#include "J4VParameterList.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4ITParameterList : public J4VParameterList 
{
 
 public:
   J4ITParameterList();   
   J4ITParameterList(const G4String &name);   
   virtual ~J4ITParameterList();  
   
   virtual void PrintParameterList(){}
  
   //
   // get parameters
   //

   static J4ITParameterList *GetInstance() { return fInstance;    }

   
   //*IT ------------------------------------------------------------------
   inline G4double GetITInnerR()         const { return fITInnerRadius;    }
   inline G4double GetITOuterR()         const { return fITOuterRadius;    }
   inline G4double GetITHalfZ()          const { return fITHalfZLength;    }
   inline G4double GetITDeltaPhi()       const { return fITDeltaPhi;       }
   inline G4double GetITPhiOffset()      const { return fITPhiOffset;      }
   
   //*Layer -------------------------------------------------------------------
   inline G4int    GetNlayers()              const { return fNlayers;          }
   inline G4double GetLayerThick()           const { return fLayerThick;       }
   inline G4double GetLayerSpacingR()        const { return fLayerSpacingR;    }
   inline G4double GetLayerZincrement()      const { return fLayerZincrement;  }
   inline G4double GetLayerDeltaPhi()        const { return fLayerDeltaPhi;    }
   inline G4double GetLayerPhiOffset(G4int i)const { return fLayerPhiOffset[i];}
   inline G4double GetLayerR(G4int ilayer)   const; 
   inline G4double GetLayerZ(G4int ilayer)   const;
                 
   //*materials --------------------------------------------------------------
   inline G4String GetITMaterial()       const { return fITMaterial;       }
   inline G4String GetLayerMaterial()    const { return fLayerMaterial;    }

   //*VisAttributes ----------------------------------------------------------
   inline G4bool   GetITVisAtt()         const { return fITVisAtt;         }
   inline G4bool   GetLayerVisAtt()      const { return fITVisAtt;         }
   
   //*Color ------------------------------------------------------------------
   inline G4Color  GetITColor()          const { return *fITColor;         }
   inline G4Color  GetLayerColor()       const { return *fLayerColor;     }
  
   //
   // setters  
   //
   
   //*IT ------------------------------------------------------------------
   inline void SetITInnerR(G4double x)   { fITInnerRadius = x;    }
   inline void SetITOuterR(G4double x)   { fITOuterRadius = x;    }
   inline void SetITHalfZ(G4double x)    { fITHalfZLength = x;    }
   inline void SetITDeltaPhi(G4double x) { fITDeltaPhi = x;       }
   inline void SetITPhiOffset(G4double x){ fITPhiOffset = x;      }
    
 private:
    virtual void  SetMaterials();
    virtual void  SetVisAttributes();
    virtual void  SetColors();
    virtual void  SetParameters();
 
 private:

   static J4ITParameterList *fInstance;
   
   // material
   G4String  fITMaterial;
   G4String  fLayerMaterial;
  
   // VisAttributes
   G4bool    fITVisAtt;
   G4bool    fLayerVisAtt;
   
   // Color
   G4Color  *fITColor;
   G4Color  *fLayerColor;
   
   // IT
   G4double  fITInnerRadius;
   G4double  fITOuterRadius;
   G4double  fITHalfZLength;
   G4double  fITDeltaPhi;
   G4double  fITPhiOffset;
  
   // Layer
   G4int     fNlayers;
   G4double  fLayerThick; 
   G4double  fLayerDeltaPhi; 
   G4double  fLayerSpacingR; 
   G4double  fLayerZincrement; 
   G4double  fFirstLayerR; 
   G4double  fFirstLayerZ; 
   G4double *fLayerPhiOffset;
   
};

//=========================================================
//* inline functions

G4double J4ITParameterList::GetLayerR(G4int ilayer) const
{
   return fFirstLayerR + ilayer * fLayerSpacingR; 
} 

G4double J4ITParameterList::GetLayerZ(G4int ilayer) const
{
   return fFirstLayerZ + ilayer * fLayerZincrement; 
}

#endif
