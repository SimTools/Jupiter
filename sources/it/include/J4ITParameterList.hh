// $Id$
#ifndef __J4ITPARAMETERLIST__
#define __J4ITPARAMETERLIST__
//********************************************************************
//* ---------------------
//* J4ITParameterList.hh
//* ---------------------
//* (Description)
//* 	ParameterList class for Intermediate Tracker.
//*     The instance must be singleton. Use "GetInstance()" function
//*     to create and get the instance.
//*     
//* (Update Record)
//*	2003/03/17  K.Hoshina	Original version.
//********************************************************************

#include "G4Material.hh"
#include "G4Color.hh"
#include "J4ParameterList.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4ITParameterList : public J4VParameterList 
{

 protected:  
   J4ITParameterList(const G4String &name);   

 public:
   virtual ~J4ITParameterList();  
   
   virtual void PrintParameterList(){}
  
   //
   // get parameters
   //

   static J4ITParameterList *GetInstance(); 

   
   //*IT ------------------------------------------------------------------
   inline G4double GetITInnerR()             const;
   inline G4double GetITOuterR()             const;
   inline G4double GetITHalfZ()              const;
   inline G4double GetITDeltaPhi()           const { return fITDeltaPhi;       }
   inline G4double GetITPhiOffset()          const { return fITPhiOffset;      }
   
   //*Layer -------------------------------------------------------------------
   inline G4int    GetNlayers()               const { return fNlayers;          }
   inline G4double GetLayerThick()            const { return fLayerThick;       }
   inline G4double GetLayerRspacing()         const { return fLayerRspacing;    }
   inline G4double GetLayerHalfZincrement()   const { return fLayerHalfZincrement;  }
   inline G4double GetLayerDeltaPhi()         const { return fLayerDeltaPhi;    }
   inline G4double GetLayerPhiOffset(G4int i) const { return fLayerPhiOffset[i];}
   inline G4double GetLayerInnerR(G4int i)    const; 
   inline G4double GetLayerOuterR(G4int i)    const; 
   inline G4double GetLayerHalfZ(G4int i)     const;
                 
   //*materials --------------------------------------------------------------
   inline G4String GetITMaterial()           const { return fITMaterial;       }
   inline G4String GetLayerMaterial()        const { return fLayerMaterial;    }

   //*VisAttributes ----------------------------------------------------------
   inline G4bool   GetITVisAtt()             const { return fITVisAtt;         }
   inline G4bool   GetLayerVisAtt()          const { return fLayerVisAtt;      }
   
   //*Color ------------------------------------------------------------------
   inline G4Color  GetITColor()              const { return fITColor;          }
   inline G4Color  GetLayerColor()           const { return fLayerColor;       }
  
   //
   // setters  
   //
   
   //*IT ------------------------------------------------------------------
   inline void SetITDeltaPhi(G4double x)              { fITDeltaPhi = x;      }
   inline void SetITPhiOffset(G4double x)             { fITPhiOffset = x;     }

   //*Layer -------------------------------------------------------------------
   inline void SetNlayers(G4int n)                    { fNlayers = n;          }
   inline void SetLayerThick(G4double x)              { fLayerThick = x;       }
   inline void SetLayerRspacing(G4double x)           { fLayerRspacing = x;    }
   inline void SetLayerHalfZincrement(G4double x)     { fLayerHalfZincrement = x;  }
   inline void SetLayerDeltaPhi(G4double x)           { fLayerDeltaPhi = x;    }
   inline void SetLayerPhiOffset(G4int i, G4double x) { fLayerPhiOffset[i] = x;}
    
   //*materials --------------------------------------------------------------
   inline void SetITMaterial(const G4String &name)    { fITMaterial = name;    }
   inline void SetLayerMaterial(const G4String &name) { fLayerMaterial = name; }

   //*VisAttributes ----------------------------------------------------------
   inline void SetITVisAtt(G4bool x)                  { fITVisAtt = x;         }
   inline void SetLayerVisAtt(G4bool x)               { fLayerVisAtt = x;      }
   
   //*Color ------------------------------------------------------------------
   inline void SetITColor(const G4Color &c)           { fITColor = c;          }
   inline void SetLayerColor(const G4Color &c)        { fLayerColor = c;       }

 private:
    virtual void  SetMaterials();
    virtual void  SetVisAttributes();
    virtual void  SetColors();
    virtual void  SetParameters();
 
 private:

   static J4ITParameterList *fgInstance;
   
   // material
   G4String  fITMaterial;
   G4String  fLayerMaterial;
  
   // VisAttributes
   G4bool    fITVisAtt;
   G4bool    fLayerVisAtt;
   
   // Color
   G4Color   fITColor;
   G4Color   fLayerColor;
   
   // IT
   G4double  fITDeltaPhi;
   G4double  fITPhiOffset;
  
   // Layer
   G4int     fNlayers;
   G4double  fLayerThick; 
   G4double  fLayerDeltaPhi; 
   G4double  fLayerRspacing; 
   G4double  fLayerHalfZincrement; 
   G4double  fFirstLayerInnerR; 
   G4double  fFirstLayerHalfZ; 
   G4double *fLayerPhiOffset;
   
};

//=========================================================
//* inline functions

G4double J4ITParameterList::GetITInnerR() const
{
   return J4ParameterList::GetInstance()->GetITInnerR();
}

G4double J4ITParameterList::GetITOuterR() const
{
   return J4ParameterList::GetInstance()->GetITOuterR();
}

G4double J4ITParameterList::GetITHalfZ() const
{
   return J4ParameterList::GetInstance()->GetITHalfZ();
}

G4double J4ITParameterList::GetLayerInnerR(G4int ilayer) const
{
   return fFirstLayerInnerR + ilayer * fLayerRspacing; 
} 

G4double J4ITParameterList::GetLayerOuterR(G4int ilayer) const
{
   return GetLayerInnerR(ilayer) + fLayerThick; 
} 

G4double J4ITParameterList::GetLayerHalfZ(G4int ilayer) const
{
   return fFirstLayerHalfZ + ilayer * fLayerHalfZincrement; 
}

#endif
