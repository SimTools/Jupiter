// $Id$
#ifndef __J4CTPARAMETERLIST__
#define __J4CTPARAMETERLIST__
//********************************************************************
//* ---------------------
//* J4CTParameterList.hh
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
 
class J4CTParameterList : public J4VParameterList 
{

 protected:  
   J4CTParameterList(const G4String &name);   

 public:
   virtual ~J4CTParameterList();  
   
   virtual void PrintParameterList(){}
  
   //
   // get parameters
   //

   static J4CTParameterList *GetInstance(); 

   
   //*CT ------------------------------------------------------------------
   inline G4double GetCTInnerR()             const;
   inline G4double GetCTOuterR()             const;
   inline G4double GetCTHalfZ()              const;
   inline G4double GetCTDeltaPhi()           const { return fCTDeltaPhi;       }
   inline G4double GetCTPhiOffset()          const { return fCTPhiOffset;      }
   
  //*Endcap ----------------------------------------------------------------
   inline G4double GetEndcapHalfThick() const { return fEndcapHalfThick; }
  inline G4double GetEndcapFrontZ()    const { return GetCTHalfZ() - 2*GetEndcapHalfThick(); }
  inline G4double GetEndcapInnerR()    const { return GetCTInnerR(); }
  inline G4double GetEndcapOuterR()    const { return GetCTOuterR(); }
  //  inline G4double GetEndcapHalfZ()     const
  inline G4double GetEndcapPhiOffset() const { return GetCTPhiOffset(); }
   inline G4double GetEndcapDeltaPhi()  const { return fCTDeltaPhi;    }
                                                                                                                              
   //*SupportTub -------------------------------------------------------------
   inline G4double GetSupportTubHalfThick()   const { return fSupportTubHalfThick;}
   inline G4double GetSupportTubInnerR() const { return GetCTInnerR(); }
   inline G4double GetSupportTubOuterR() const 
  { return GetCTInnerR() + 2*GetSupportTubHalfThick(); }
   inline G4double GetSupportTubHalfZ() const { return GetEndcapFrontZ(); }
   inline G4double GetSupportTubPhiOffset()   const { return GetCTPhiOffset(); }
   inline G4double GetSupportTubDeltaPhi()     const { return fCTDeltaPhi;    }
   

   //*Outer Cylinder -------------------------------------------------------------
   inline G4double GetOuterCylinderHalfThick() const { return fOuterCylinderHalfThick;}
   inline G4double GetOuterCylinderInnerR()    const 
                              { return GetCTOuterR() - 2*GetOuterCylinderHalfThick(); }  
   inline G4double GetOuterCylinderOuterR()    const { return GetCTOuterR(); }
   inline G4double GetOuterCylinderHalfZ() const { return GetEndcapFrontZ(); }

   inline G4double GetOuterCylinderPhiOffset() const { return GetCTPhiOffset(); }
   inline G4double GetOuterCylinderDeltaPhi()     const { return fCTDeltaPhi;    }
                                                                                                                              

   //*Layer -------------------------------------------------------------------
   inline G4int    GetNlayers()               const { return fNlayers;          }
   inline G4double GetLayerRspacing()         const { return fLayerRspacing;    }
   inline G4double GetFirstLayerRadius()      const { return fFirstLayerRadius; }
   inline G4double GetLastLayerRadius()       const { return fLastLayerRadius; }
   inline G4double GetLayerDeltaPhi()         const { return GetCTDeltaPhi();  }
   inline G4double GetLayerPhiOffset(G4int i) const { return GetCTPhiOffset();}

   inline G4double GetLayerHalfZ(G4int ) const { return GetEndcapFrontZ(); }
   inline G4double GetLayerInnerR(G4int i)    const; 
   inline G4double GetLayerOuterR(G4int i)    const; 
                 
   //*materials --------------------------------------------------------------
   inline G4String GetCTMaterial()           const { return fCTMaterial;       }
   inline G4String GetLayerMaterial()        const { return fLayerMaterial;    }
   inline G4String GetSupportTubMaterial()   const { return fSupportTubMaterial;    }
   inline G4String GetOuterCylinderMaterial() const { return fOuterCylinderMaterial;    }
   inline G4String GetEndcapMaterial()       const { return fEndcapMaterial;    }

   //*VisAttributes ----------------------------------------------------------
   inline G4bool   GetCTVisAtt()             const { return fCTVisAtt;         }
   inline G4bool   GetLayerVisAtt()          const { return fLayerVisAtt;      }
   inline G4bool   GetSupportTubVisAtt()     const { return fSupportTubVisAtt;      }

   
   //*Color ------------------------------------------------------------------
   inline G4Color  GetCTColor()              const { return fCTColor;          }
   inline G4Color  GetLayerColor()           const { return fLayerColor;       }
   inline G4Color  GetSupportTubColor()      const { return fSupportTubColor;       }
  
   //
   // setters  
   //
   
   /*
   // CT ------------------------------------------------------------------
   inline void SetCTDeltaPhi(G4double x)              { fCTDeltaPhi = x;      }
   inline void SetCTPhiOffset(G4double x)             { fCTPhiOffset = x;     }

   // Layer -------------------------------------------------------------------
   inline void SetNlayers(G4int n)                    { fNlayers = n;          }
   inline void SetLayerRspacing(G4double x)           { fLayerRspacing = x;    }
   inline void SetLayerHalfZincrement(G4double x)     { fLayerHalfZincrement = x;  }
   inline void SetLayerDeltaPhi(G4double x)           { fLayerDeltaPhi = x;    }
   inline void SetLayerPhiOffset(G4int i, G4double x) { fLayerPhiOffset[i] = x;}
    
   // materials --------------------------------------------------------------
   inline void SetCTMaterial(const G4String &name)    { fCTMaterial = name;    }
   inline void SetLayerMaterial(const G4String &name) { fLayerMaterial = name; }
   */

   //* VisAttributes ----------------------------------------------------------
   inline void SetCTVisAtt(G4bool x)                  { fCTVisAtt = x;         }
   inline void SetLayerVisAtt(G4bool x)               { fLayerVisAtt = x;      }
   inline void SetSupportTubVisAtt(G4bool x)          { fSupportTubVisAtt = x;      }
   
   //*Color ------------------------------------------------------------------
   inline void SetCTColor(const G4Color &c)           { fCTColor = c;          }
   inline void SetLayerColor(const G4Color &c)        { fLayerColor = c;       }
   inline void SetSupportTubColor(const G4Color &c)   { fSupportTubColor = c;       }

 private:
    virtual void  SetMaterials();
    virtual void  SetVisAttributes();
    virtual void  SetColors();
    virtual void  SetParameters();
 
 private:

   static J4CTParameterList *fgInstance;
   
   // material
   G4String  fCTMaterial;
   G4String  fLayerMaterial;
   G4String  fEndcapMaterial;
   G4String  fSupportTubMaterial;
   G4String  fOuterCylinderMaterial;
  
   // VisAttributes
   G4bool    fCTVisAtt;
   G4bool    fLayerVisAtt;
   G4bool    fSupportTubVisAtt;
   
   // Color
   G4Color   fCTColor;
   G4Color   fLayerColor;
   G4Color   fSupportTubColor;
   
   // CT
   G4double  fCTDeltaPhi;
   G4double  fCTPhiOffset;
  
   // Layer
   G4int     fNlayers;
   G4double  fFirstLayerRadius;
   G4double  fLastLayerRadius;
   G4double  fLayerRspacing; 
  
   G4double *fLayerPhiOffset;

   G4double  fEndcapHalfThick; 
   G4double  fSupportTubHalfThick;
  G4double  fOuterCylinderHalfThick;
};

//=========================================================
//* inline functions

G4double J4CTParameterList::GetCTInnerR() const
{
  //   return J4ParameterList::GetInstance()->GetCTInnerR();
   return J4ParameterList::GetInstance()->GetCDCInnerR();
}

G4double J4CTParameterList::GetCTOuterR() const
{
  //   return J4ParameterList::GetInstance()->GetCTOuterR();
   return J4ParameterList::GetInstance()->GetCDCOuterR();
}

G4double J4CTParameterList::GetCTHalfZ() const
{
  //   return J4ParameterList::GetInstance()->GetCTHalfZ();
   return J4ParameterList::GetInstance()->GetCDCHalfZ();
}

G4double J4CTParameterList::GetLayerInnerR(G4int ilayer) const
{
   return fFirstLayerRadius + fLayerRspacing*ilayer;
} 

G4double J4CTParameterList::GetLayerOuterR(G4int ilayer) const
{
   return GetLayerInnerR(ilayer) + fLayerRspacing;
} 

#endif
