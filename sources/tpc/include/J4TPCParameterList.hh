#ifndef __J4TPCPARAMETERLIST__
#define __J4TPCPARAMETERLIST__
//********************************************************************
//* ---------------------
//* J4TPCParameterList.hh
//* ---------------------
//* (Description)
//* 	ParameterList class for TPC.
//*     The instance must be singleton. Use "GetInstance()" function
//*     to create and get the instance.
//*     
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//********************************************************************

#include "G4Material.hh"
#include "G4Color.hh"
#include "J4ParameterList.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4TPCParameterList : public J4VParameterList 
{

 protected:  
   J4TPCParameterList(const G4String &name);   

 public:
   virtual ~J4TPCParameterList();  
   
   virtual void PrintParameterList(){}
  
   //
   // get parameters
   //

   static J4TPCParameterList *GetInstance(); 

   
   //*TPC ------------------------------------------------------------------
   inline G4double GetTPCInnerR()             const;
   inline G4double GetTPCOuterR()             const;
   inline G4double GetTPCHalfZ()              const;
   inline G4double GetTPCDeltaPhi()           const { return fTPCDeltaPhi;     }
   inline G4double GetTPCPhiOffset()          const { return fTPCPhiOffset;    }
   
   //*Endcap ----------------------------------------------------------------
   inline G4double GetEndcapHalfThick()       const { return fEndcapHalfThick; }
   inline G4double GetEndcapFrontZ()          const;
   inline G4double GetEndcapInnerR()          const;
   inline G4double GetEndcapOuterR()          const;
   inline G4double GetEndcapPhiOffset()       const { return fTPCPhiOffset;    }
   inline G4double GetEndcapDeltaPhi()        const { return fTPCDeltaPhi;     }
                                                                                
   //*SupportTub -------------------------------------------------------------
   inline G4double GetInnerSupportTubHalfThick()   const { return fInnerSupportTubHalfThick;}
   inline G4double GetOuterSupportTubHalfThick()   const { return fOuterSupportTubHalfThick;}
   inline G4double GetOuterSupportTubInnerR() const;
   inline G4double GetOuterSupportTubOuterR() const;
   inline G4double GetInnerSupportTubInnerR() const;
   inline G4double GetInnerSupportTubOuterR() const;
   inline G4double GetSupportTubHalfZ()       const;
   inline G4double GetSupportTubPhiOffset()   const { return fTPCPhiOffset;    }
   inline G4double GetSupportTubDeltaPhi()    const { return fTPCDeltaPhi;     }

   //*CentralMembrane --------------------------------------------------------
   inline G4double GetCentralMembraneHalfThick() const { return fCentralMembraneHalfThick; }
   inline G4double GetCentralMembraneInnerR()    const;
   inline G4double GetCentralMembraneOuterR()    const;
   inline G4double GetCentralMembranePhiOffset() const { return fTPCPhiOffset; }
   inline G4double GetCentralMembraneDeltaPhi()  const { return fTPCDeltaPhi;  }

   //*PadPlane ----------------------------------------------------------------
   inline G4double GetPadPlaneHalfThick()    const { return fPadPlaneHalfThick;}
   inline G4double GetPadPlaneFrontZ()       const;
   inline G4double GetPadPlaneInnerR()       const;
   inline G4double GetPadPlaneOuterR()       const;
   inline G4double GetPadPlanePhiOffset()    const { return fTPCPhiOffset;     }
   inline G4double GetPadPlaneDeltaPhi()     const { return fTPCDeltaPhi;      }

   //*PadRow -----------------------------------------------------------------
   inline G4int    GetNpadRows()            const { return fNpadRows;        }
   inline G4double GetPadRowHalfZ()         const { return fPadPlaneHalfThick;}
   inline G4double GetPadRowDeltaPhi()      const { return fTPCDeltaPhi;      }
   inline G4double GetPadRowPhiOffset()     const { return fTPCPhiOffset;     }
   inline G4double GetPadRowInnerR(G4int i) const; 
   inline G4double GetPadRowOuterR(G4int i) const; 
   inline G4double GetPadRowThick()         const;

   //*Pad -----------------------------------------------------------------
   inline G4int    GetNpads(G4int i)         const;
   inline G4double GetPadHalfZ()             const { return fPadPlaneHalfThick;}
   inline G4double GetPadDeltaPhi()          const { return fTPCDeltaPhi;      }
   inline G4double GetPadPhiOffset()         const { return fTPCPhiOffset;     }
   inline G4double GetPadInnerR(G4int i)     const; 
   inline G4double GetPadOuterR(G4int i)     const; 
   inline G4double GetPadThick()             const;
   inline G4double GetNfirstPads()           const { return fNfirstPads;       }

   //*Layer -------------------------------------------------------------------
   inline G4int    GetNlayers()              const { return fNlayers;         }
   inline G4double GetLayerDeltaPhi()        const { return fTPCDeltaPhi;     }
   inline G4double GetLayerPhiOffset()       const { return fTPCPhiOffset;    }
   inline G4double GetLayerInnerR(G4int i)   const; 
   inline G4double GetLayerOuterR(G4int i)   const; 
   inline G4double GetLayerThick()           const { return fLayerThick;      }
   inline G4double GetLayerRspacing()        const;
   inline G4double GetFirstLayerInnerR()     const { return fFirstLayerInnerR;}
   inline G4double GetT0detInnerR()          const;
   inline G4double GetT0detOuterR()          const;
                 
   //*DriftRegion -----------------------------------------------------------
   inline G4double GetDriftRegionDeltaPhi()  const { return fTPCDeltaPhi;     }
   inline G4double GetDriftRegionHalfZ()     const;

   //*materials --------------------------------------------------------------
   inline G4String GetTPCMaterial()           const { return fTPCMaterial;     }
   inline G4String GetInnerSupportTubMaterial() const { return fInnerSupportTubMaterial; }
   inline G4String GetOuterSupportTubMaterial() const { return fOuterSupportTubMaterial; }
   inline G4String GetEndcapMaterial()        const { return fEndcapMaterial;  }
   inline G4String GetLayerMaterial()         const { return fLayerMaterial;   }
   inline G4String GetT0detMaterial()         const { return fT0detMaterial;   }
   inline
       G4String GetCentralMembraneMaterial()  const { return fCentralMembraneMaterial;}
   inline G4String GetPadPlaneMaterial()      const { return fPadPlaneMaterial;}
   inline G4String GetPadRowMaterial()        const { return fPadRowMaterial; }
   inline G4String GetPadMaterial()           const { return fPadMaterial;     }
   inline G4String GetDriftRegionMaterial()   const { return fDriftRegionMaterial;     }

   //*VisAttributes ----------------------------------------------------------
   inline G4bool GetTPCVisAtt()               const { return fTPCVisAtt;       }
   inline G4bool GetEndcapVisAtt()            const { return fEndcapVisAtt;    }
   inline G4bool GetSupportTubVisAtt()        const { return fSupportTubVisAtt;}
   inline G4bool GetLayerVisAtt()             const { return fLayerVisAtt;     }
   inline G4bool GetCentralMembraneVisAtt()   const { return fCentralMembraneVisAtt;}
   inline G4bool GetPadPlaneVisAtt()          const { return fPadPlaneVisAtt;  }
   inline G4bool GetPadRowVisAtt()            const { return fPadRowVisAtt;   }
   inline G4bool GetPadVisAtt()               const { return fPadVisAtt;       }
   inline G4bool GetDriftRegionVisAtt()       const { return fPadVisAtt;       }

   //*Color ------------------------------------------------------------------
   inline G4Color GetTPCColor()               const { return fTPCColor;        }
   inline G4Color GetEndcapColor()            const { return fEndcapColor;     }
   inline G4Color GetSupportTubColor()        const { return fSupportTubColor; }
   inline G4Color GetLayerColor()             const { return fLayerColor;      }
   inline G4Color GetCentralMembraneColor()   const { return fCentralMembraneColor;}
   inline G4Color GetPadPlaneColor()          const { return fPadPlaneColor;   }
   inline G4Color GetPadRowColor()            const { return fPadRowColor;    }
   inline G4Color GetPadColor()               const { return fPadColor;        }
   inline G4Color GetDriftRegionColor()       const { return fPadColor;        }
  
   //
   // setters  
   //
   
   //*TPC ------------------------------------------------------------------
   inline void SetTPCDeltaPhi(G4double x)             { fTPCDeltaPhi = x;      }
   inline void SetTPCPhiOffset(G4double x)            { fTPCPhiOffset = x;     }

   //*Layer -------------------------------------------------------------------
   inline void SetNlayers(G4int n)                    { fNlayers = n;          }
   inline void SetLayerThick(G4double x)              { fLayerThick = x;       }
   inline void SetFirstLayerInnerR(G4double x)        { fFirstLayerInnerR = x; } 
   //*Endcap -----------------------------------------------------------------
   inline void SetEndcapHalfThick(G4double x)         { fEndcapHalfThick = x;  }
                                                                                
   //*SupportTub -------------------------------------------------------------
   inline void SetOuterSupportTubHalfThick(G4double x)     { fOuterSupportTubHalfThick = x; }
   inline void SetInnerSupportTubHalfThick(G4double x)     { fInnerSupportTubHalfThick = x; }
    
   //*CentralMembrane --------------------------------------------------------
   inline void SetCentralMembraneHalfThick(G4double x){ fCentralMembraneHalfThick = x;  }

   //*PadPlane ---------------------------------------------------------------
   inline void SetPadPlaneHalfThick(G4double x)       { fPadPlaneHalfThick = x;}

   //*PadRow ----------------------------------------------------------------
   inline void SetNpadRows(G4int n)                  { fNpadRows = n;        }

   //*Pad ---------------------------------------------------------------------
   inline void SetNfirstPads(G4int n)                 { fNfirstPads = n;      }

   //*Materials --------------------------------------------------------------
   inline void SetTPCMaterial(const G4String &name)   { fTPCMaterial = name;   }
   inline void SetLayerMaterial(const G4String &name) { fLayerMaterial = name; }
   inline void SetInnerSupportTubMaterial(const G4String &name) { fInnerSupportTubMaterial = name; }
   inline void SetOuterSupportTubMaterial(const G4String &name) { fOuterSupportTubMaterial = name; }
   inline void SetEndcapMaterial(const G4String &name){ fEndcapMaterial = name;}
   inline void SetCentralMembraneMaterial(const G4String &name) { fCentralMembraneMaterial = name; }
   inline void SetPadPlaneMaterial(const G4String &name) { fPadPlaneMaterial = name; }
   inline void SetPadRowMaterial(const G4String &name)  { fPadRowMaterial = name; }
   inline void SetPadMaterial(const G4String &name)   { fPadMaterial = name;   }
   inline void SetDriftRegionMaterial(const G4String &name)   { fDriftRegionMaterial = name;   }

   //*VisAttributes ----------------------------------------------------------
   inline void SetTPCVisAtt(G4bool x)                 { fTPCVisAtt = x;        }
   inline void SetTPCHalfVisAtt(G4bool x)             { fTPCHalfVisAtt = x;    }
   inline void SetLayerVisAtt(G4bool x)               { fLayerVisAtt = x;      }
   inline void SetEndcapVisAtt(G4bool x)              { fEndcapVisAtt = x;     }
   inline void SetSupportTubVisAtt(G4bool x)          { fSupportTubVisAtt = x; }
   inline void SetCentralMembraneVisAtt(G4bool x)     { fCentralMembraneVisAtt = x; }
   inline void SetPadPlaneVisAtt(G4bool x)            { fPadPlaneVisAtt = x;   }
   inline void SetPadRowVisAtt(G4bool x)             { fPadRowVisAtt = x;    }
   inline void SetPadVisAtt(G4bool x)                 { fPadVisAtt = x;        }
   inline void SetDriftRegionVisAtt(G4bool x)         { fPadVisAtt = x;        }
   
   //*Color ------------------------------------------------------------------
   inline void SetTPCColor(const G4Color &c)          { fTPCColor = c;         }
   inline void SetTPCHalfColor(const G4Color &c)      { fTPCHalfColor = c;     }
   inline void SetLayerColor(const G4Color &c)        { fLayerColor = c;       }
   inline void SetEndcapColor(const G4Color &c)       { fEndcapColor = c;      }
   inline void SetSupportTubColor(const G4Color &c)   { fSupportTubColor = c;  }
   inline void SetCentralMembraneColor(const G4Color &c) { fCentralMembraneColor = c;}
   inline void SetPadPlaneColor(const G4Color &c)     { fPadPlaneColor = c;    }
   inline void SetPadRowColor(const G4Color &c)      { fPadRowColor = c;     }
   inline void SetPadColor(const G4Color &c)          { fPadColor = c;         }
   inline void SetDriftRegionColor(const G4Color &c)  { fPadColor = c;         }


 private:
    virtual void  SetMaterials();
    virtual void  SetVisAttributes();
    virtual void  SetColors();
    virtual void  SetParameters();
 
 private:

   static J4TPCParameterList *fgInstance;
   
   // material
   G4String  fTPCMaterial;
   G4String  fLayerMaterial;
   G4String  fT0detMaterial;
   G4String  fInnerSupportTubMaterial;
   G4String  fOuterSupportTubMaterial;
   G4String  fEndcapMaterial;
   G4String  fCentralMembraneMaterial;
   G4String  fPadPlaneMaterial;
   G4String  fPadRowMaterial;
   G4String  fPadMaterial;
   G4String  fDriftRegionMaterial;
  
   // VisAttributes
   G4bool    fTPCVisAtt;
   G4bool    fTPCHalfVisAtt;
   G4bool    fEndcapVisAtt;
   G4bool    fSupportTubVisAtt;
   G4bool    fLayerVisAtt;
   G4bool    fCentralMembraneVisAtt;
   G4bool    fPadPlaneVisAtt;
   G4bool    fPadRowVisAtt;
   G4bool    fPadVisAtt;
   G4bool    fDriftRegionVisAtt;
   
   // Color
   G4Color   fTPCColor;
   G4Color   fTPCHalfColor;
   G4Color   fEndcapColor;
   G4Color   fSupportTubColor;
   G4Color   fLayerColor;
   G4Color   fCentralMembraneColor;
   G4Color   fPadPlaneColor;
   G4Color   fPadRowColor;
   G4Color   fPadColor;
   G4Color   fDriftRegionColor;
   
   // TPC
   G4double  fTPCDeltaPhi;
   G4double  fTPCPhiOffset;
  
   // Endcap
   G4double  fEndcapHalfThick;
                                                                                
   // SupportTub
   G4double  fInnerSupportTubHalfThick;
   G4double  fOuterSupportTubHalfThick;

   // CentralMembrane
   G4double  fCentralMembraneHalfThick;

   // PadPlane
   G4double fPadPlaneHalfThick;

   // PadRow
   G4int    fNpadRows;

   // Pad
   G4int    fNfirstPads;

   // Layer
   G4int     fNlayers;
   G4double  fLayerThick;
   G4double  fFirstLayerInnerR;
   G4double  fT0detThick;
   
};

//=========================================================
//* inline functions

G4double J4TPCParameterList::GetTPCInnerR() const
{
   return J4ParameterList::GetInstance()->GetTPCInnerR();
}

G4double J4TPCParameterList::GetTPCOuterR() const
{
   return J4ParameterList::GetInstance()->GetTPCOuterR();
}

G4double J4TPCParameterList::GetTPCHalfZ() const
{
   return J4ParameterList::GetInstance()->GetTPCHalfZ();
}

G4double J4TPCParameterList::GetEndcapFrontZ() const
{
   return GetTPCHalfZ() / 2 - 2 * fEndcapHalfThick;
}
                                                                                
G4double J4TPCParameterList::GetEndcapInnerR() const
{
   return GetTPCInnerR();
}
                                                                                
G4double J4TPCParameterList::GetEndcapOuterR() const
{
   return GetTPCOuterR();
}
                                                                                
G4double J4TPCParameterList::GetOuterSupportTubInnerR() const
{
   return GetTPCOuterR() - 2 * fOuterSupportTubHalfThick;
}
                                                                                
G4double J4TPCParameterList::GetOuterSupportTubOuterR() const
{
   return GetTPCOuterR();
}
                                                                                
G4double J4TPCParameterList::GetInnerSupportTubInnerR() const
{
   return GetT0detOuterR();
}
                                                                                
G4double J4TPCParameterList::GetInnerSupportTubOuterR() const
{
   return GetInnerSupportTubInnerR() + 2 * fInnerSupportTubHalfThick;
}

G4double J4TPCParameterList::GetSupportTubHalfZ() const
{
   return (GetTPCHalfZ() - 2 * fEndcapHalfThick) / 2;
}
                                                                                
G4double J4TPCParameterList::GetCentralMembraneInnerR() const
{
   return GetInnerSupportTubOuterR();
}
                                                                                
G4double J4TPCParameterList::GetCentralMembraneOuterR() const
{
   return GetOuterSupportTubInnerR();
}
                                                                                
G4double J4TPCParameterList::GetLayerRspacing() const
{
   return (GetOuterSupportTubInnerR() - GetInnerSupportTubOuterR() 
           - fFirstLayerInnerR) / fNlayers;
}

G4double J4TPCParameterList::GetLayerInnerR(G4int ilayer) const
{
   return GetInnerSupportTubOuterR() +
          ilayer * GetLayerRspacing() + fFirstLayerInnerR;
} 

G4double J4TPCParameterList::GetLayerOuterR(G4int ilayer) const
{
   return GetLayerInnerR(ilayer) + fLayerThick;
} 

G4double J4TPCParameterList::GetDriftRegionHalfZ() const
{
   return (GetTPCHalfZ() - fCentralMembraneHalfThick - 
           2 * (fEndcapHalfThick + fPadPlaneHalfThick)) / 2;
}

G4double J4TPCParameterList::GetT0detInnerR() const
{
   return GetTPCInnerR();
}

G4double J4TPCParameterList::GetT0detOuterR() const
{
   return GetT0detInnerR() + fT0detThick;
}

G4double J4TPCParameterList::GetPadPlaneFrontZ() const
{
   return GetEndcapFrontZ() - fPadPlaneHalfThick * 2;
}

G4double J4TPCParameterList::GetPadPlaneInnerR() const
{
   return GetInnerSupportTubOuterR();
}

G4double J4TPCParameterList::GetPadPlaneOuterR() const
{
   return GetOuterSupportTubInnerR();
}

G4double J4TPCParameterList::GetPadRowInnerR(G4int ipadRow) const
{
   return GetPadPlaneInnerR() + ipadRow * GetPadRowThick();
}

G4double J4TPCParameterList::GetPadRowOuterR(G4int ipadRow) const
{
   return GetPadRowInnerR(ipadRow + 1);
}

G4double J4TPCParameterList::GetPadRowThick() const
{
   return (GetPadPlaneOuterR() - GetPadPlaneInnerR()) / fNpadRows;
}

G4int J4TPCParameterList::GetNpads(G4int ipadRow) const
{
   return  (G4int)((GetPadPlaneInnerR() + (ipadRow + 0.5) * GetPadThick()) /
                   (GetPadPlaneInnerR() + 0.5 * GetPadThick()) * fNfirstPads);
}

G4double J4TPCParameterList::GetPadInnerR(G4int ipadRow) const
{
   return GetPadRowInnerR(ipadRow);
} 

G4double J4TPCParameterList::GetPadOuterR(G4int ipadRow) const
{
   return GetPadRowOuterR(ipadRow);
} 

G4double J4TPCParameterList::GetPadThick() const
{
   return GetPadRowThick();
}

#endif
