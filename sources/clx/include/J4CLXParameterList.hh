// $Id$
#ifndef __J4CLXPARAMETERLIST__
#define __J4CLXPARAMETERLIST__
//********************************************************************
//* ---------------------------
//* J4CLXParameterList.hh
//* ---------------------------
//* (Description)
//* 	ParameterList class for CLX
//*     The instance must be singleton. Use "GetInstance()" function
//*     to create and get the instance.
//*     
//* (Update Record)
//*	2003/02/28  R.Kuboshima  Original version.
//********************************************************************

#include <iostream>
#include <cmath>
#include <iomanip> 
#include "globals.hh"
#include <vector>
#include <functional>
#include <algorithm>
#include "G4Material.hh"
#include "G4Color.hh"
#include "J4ParameterList.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4CLXParameterList : public J4VParameterList 
{

 protected: 

   J4CLXParameterList(const G4String &name);

 public:


   virtual ~J4CLXParameterList();

   static J4CLXParameterList *GetInstance();
   
   virtual void    PrintParameterList(){};


   //
   // Getters
   //

   //*CLX --------------------------------------------------------------
   inline G4double GetCLXOuterR()         const; 
   inline G4double GetCLXInnerR()         const;
   inline G4double GetCLXInnerHalfZ()     const;
   inline G4double GetCLXOuterHalfZ()     const;
   inline G4double GetCLXDeltaPhi()       const { return fCLXDeltaPhi;     }
   inline G4double GetCLXPhiOffset()      const { return fCLXPhiOffset;    }
   inline G4int GetNTraps()            const { return fNTraps;          }
    inline G4double GetTrapDeltaPhi()      const { return fTrapDeltaPhi; }

   //*Barrel ------------------------------------------------------------
   inline G4double GetBarrelOuterR()      const ;
   inline G4double GetBarrelInnerR()      const ;
   inline G4double GetBarrelHalfZ()       const { return fBarrelHalfZ;     }
   inline G4double GetBarrelDeltaPhi()    const { return fBarrelDeltaPhi;  }
   inline G4double GetBarrelPhiOffset()   const { return fBarrelPhiOffset; }

   //*Endcap ------------------------------------------------------------
   inline G4double GetEndcapOuterR()      const ;
   inline G4double GetEndcapInnerR()      const { return fEndcapInnerR;    } 
   inline G4double GetEndcapDeltaPhi()    const { return fEndcapDeltaPhi;  }
   inline G4double GetEndcapPhiOffset()   const { return fEndcapPhiOffset; }

   //*EM ----------------------------------------------------------------
   inline G4double GetEMThickness()       const;

   //*HD ---------------------------------------------------------
   inline G4double GetHDThickness()       const;

   //*Layer
   inline G4double GetEMLayerThickness()      const; 
   inline G4double GetHDLayerThickness()      const;
   inline G4int    GetEMNLayers()             const { return fEMNLayers; } 
   inline G4int    GetHDNLayers()             const { return fHDNLayers; } 

   //*AbsLayer
   inline G4double GetEMAbsLayerThickness() const { return fEMAbsLayerThickness; }  
   inline G4double GetHDAbsLayerThickness() const { return fHDAbsLayerThickness; }  

   //*ActiveLayer
   inline G4double GetEMActiveLayerThickness() const { return fEMActiveLayerThickness; }  
   inline G4double GetHDActiveLayerThickness() const { return fHDActiveLayerThickness; }  

    //*Cell
    inline G4double GetCellSize() const { return fCellSize;}

   //*Materials ---------------------------------------------------------
   inline G4String GetCLXMaterial()          const { return fCLXMaterial;    }
   inline G4String GetBarrelMaterial()       const { return fBarrelMaterial; }
   inline G4String GetEndcapMaterial()       const { return fEndcapMaterial; }
    inline G4String GetBlockMaterial()        const { return fBlockMaterial; }
   inline G4String GetEMMaterial()           const { return fEMMaterial;     }
   inline G4String GetHDMaterial()           const { return fHDMaterial;     }
   inline G4String GetLayerMaterial()        const { return fLayerMaterial; }
   inline G4String GetEMAbsLayerMaterial()   const { return fEMAbsLayerMaterial; }
   inline G4String GetHDAbsLayerMaterial()   const { return fHDAbsLayerMaterial; }
   inline G4String GetEMActiveLayerMaterial()const { return fEMActiveLayerMaterial; }
   inline G4String GetHDActiveLayerMaterial()const { return fHDActiveLayerMaterial; }
    inline G4String GetBoardMaterial()        const { return fBoardMaterial;}
    inline G4String GetLargeBoxCellMaterial() const { return fLargeBoxCellMaterial;}
    inline G4String GetEMCellMaterial()       const { return fEMCellMaterial;}
    inline G4String GetHDCellMaterial()       const { return fHDCellMaterial;}


   //*VisAtt ------------------------------------------------------------
   inline G4bool   GetCLXVisAtt()         const { return fCLXVisAtt;      }
   inline G4bool   GetBarrelVisAtt()      const { return fBarrelVisAtt;   }
   inline G4bool   GetEndcapVisAtt()      const { return fEndcapVisAtt;   }
    inline G4bool   GetBlockVisAtt()       const { return fBlockVisAtt; }
   inline G4bool   GetEMVisAtt()          const { return fEMVisAtt;       }
   inline G4bool   GetHDVisAtt()          const { return fHDVisAtt;       }
   inline G4bool   GetLayerVisAtt()       const { return fLayerVisAtt;    }
   inline G4bool   GetSubLayerVisAtt()    const { return fSubLayerVisAtt; }
    inline G4bool  GetBoardVisAtt()        const { return fBoardVisAtt; }
    inline G4bool  GetLargeBoxCellVisAtt() const { return fLargeBoxCellVisAtt;}
    inline G4bool  GetEMCellVisAtt()       const { return fEMCellVisAtt; }
    inline G4bool  GetHDCellVisAtt()       const { return fHDCellVisAtt; }

   //*Color  ------------------------------------------------------------
   inline G4Color  GetCLXColor()          const { return fCLXColor;       }
   inline G4Color  GetBarrelColor()       const { return fBarrelColor;    }
   inline G4Color  GetEndcapColor()       const { return fEndcapColor;    }
    inline G4Color GetBlockColor()        const {return fBlockColor; }
   inline G4Color  GetEMColor()           const { return fEMColor;        }
   inline G4Color  GetHDColor()           const { return fHDColor;        }
   inline G4Color  GetLayerColor()        const { return fLayerColor;   }
   inline G4Color  GetSubLayerColor()     const { return fSubLayerColor;   }
    inline G4Color  GetBoardColor()        const { return fBoardColor;}
    inline G4Color  GetLargeBoxCellColor() const { return fLargeBoxCellColor;}
    inline G4Color  GetEMCellColor()       const { return fEMCellColor;}
    inline G4Color  GetHDCellColor()       const { return fHDCellColor;}

   //
   // Setters
   //

   inline void SetCLXColor      (const G4Color &c) { fCLXColor        = c; }
   inline void SetBarrelColor   (const G4Color &c) { fBarrelColor     = c; }
   inline void SetEndcapColor   (const G4Color &c) { fEndcapColor     = c; }
    inline void SetBlockColor   (const G4Color &c) { fBlockColor       = c; }
   inline void SetEMColor       (const G4Color &c) { fEMColor         = c; }
   inline void SetHDColor       (const G4Color &c) { fHDColor         = c; }
   inline void SetLayerColor    (const G4Color &c) { fLayerColor        = c; }
   inline void SetSubLayerColor (const G4Color &c) { fSubLayerColor     = c; }
    inline void SetBoardColor   (const G4Color &c) { fBoardColor        = c; }
    inline void SetLargeBoxCellColor(const G4Color &c) { fLargeBoxCellColor = c;}
    inline void SetEMCellColor  (const G4Color &c) { fEMCellColor       = c; }
    inline void SetHDCellColor  (const G4Color &c) { fHDCellColor       = c; }

 private:

   virtual void      SetMaterials();
   virtual void      SetVisAttributes();
   virtual void      SetColors();
   virtual void      SetParameters();

 private:

   static J4CLXParameterList *fgInstance;

   // material
   G4String  fCLXMaterial;
   G4String  fBarrelMaterial;
   G4String  fEndcapMaterial;
    G4String fBlockMaterial;
   G4String  fEMMaterial;
   G4String  fHDMaterial;
   G4String  fLayerMaterial;
   G4String  fHDLayerMaterial;
   G4String  fEMAbsLayerMaterial;
   G4String  fHDAbsLayerMaterial;
   G4String  fEMActiveLayerMaterial;
   G4String  fHDActiveLayerMaterial;
    G4String fBoardMaterial;
    G4String fLargeBoxCellMaterial;
    G4String fEMCellMaterial;
    G4String fHDCellMaterial;

   // visatt 
   G4bool    fCLXVisAtt;
   G4bool    fBarrelVisAtt;
   G4bool    fEndcapVisAtt;
    G4bool fBlockVisAtt;
   G4bool    fEMVisAtt;
   G4bool    fHDVisAtt;
   G4bool    fLayerVisAtt;
   G4bool    fSubLayerVisAtt;
    G4bool fBoardVisAtt;
    G4bool fLargeBoxCellVisAtt;
    G4bool fEMCellVisAtt;
    G4bool fHDCellVisAtt;

   // color 
   G4Color   fCLXColor;
   G4Color   fBarrelColor;
   G4Color   fEndcapColor;
    G4Color   fBlockColor;
   G4Color   fEMColor;
   G4Color   fHDColor;
   G4Color   fLayerColor;
   G4Color   fSubLayerColor;
    G4Color fBoardColor;
    G4Color fLargeBoxCellColor;
    G4Color fEMCellColor;
    G4Color fHDCellColor;

   // CLX
   G4double  fCLXDeltaPhi;
   G4double  fCLXPhiOffset;
    G4int  fNTraps;
    G4double  fTrapDeltaPhi;

   // Barrel 
   G4double  fBarrelHalfZ;
   G4double  fBarrelDeltaPhi;
   G4double  fBarrelPhiOffset;
   G4double  fBarrelCoverageAngle;

   // Endcap 
   G4double  fEndcapInnerR;
   G4double  fEndcapDeltaPhi;
   G4double  fEndcapPhiOffset;

   // EM
   G4double  fEMThickness;

   // HD
   G4double  fHDThickness;

   // Layer
   G4double  fNLayers;
   G4int     fEMNLayers;
   G4int     fHDNLayers;

   // AbsLayer
   G4double   fEMAbsLayerThickness;
   G4double   fHDAbsLayerThickness;

   // ActiveLayer
   G4double   fEMActiveLayerThickness;
   G4double   fHDActiveLayerThickness;

    //Cell
    G4double fCellSize;

};

//=========================================================
//* inline functions

G4double J4CLXParameterList::GetCLXInnerR() const
{
   return J4ParameterList::GetInstance()->GetCALInnerR();
}

G4double J4CLXParameterList::GetCLXOuterR() const
{
   return J4ParameterList::GetInstance()->GetCALOuterR();
}

G4double J4CLXParameterList::GetCLXInnerHalfZ() const
{
   return J4ParameterList::GetInstance()->GetCALInnerHalfZ();
}

G4double J4CLXParameterList::GetCLXOuterHalfZ() const
{
   return J4ParameterList::GetInstance()->GetCALOuterHalfZ();
}

G4double J4CLXParameterList::GetBarrelOuterR() const
{
   return GetCLXOuterR();
}

G4double J4CLXParameterList::GetBarrelInnerR() const
{
   return GetCLXInnerR();
}

G4double J4CLXParameterList::GetEndcapOuterR() const
{
   return GetCLXOuterR();
}

G4double J4CLXParameterList::GetEMThickness() const 
{
    return ( GetEMAbsLayerThickness() + GetEMActiveLayerThickness() ) * (GetEMNLayers() + .5);
}
 
G4double J4CLXParameterList::GetHDThickness() const 
{
    return ( GetHDAbsLayerThickness() + GetHDActiveLayerThickness() ) * (GetHDNLayers() + .5);
}

G4double J4CLXParameterList::GetEMLayerThickness() const 
{
   return GetEMAbsLayerThickness() + GetEMActiveLayerThickness();
}
 
G4double J4CLXParameterList::GetHDLayerThickness() const 
{
   return GetHDAbsLayerThickness() + GetHDActiveLayerThickness(); 
}


#endif
