// $Id$
#ifndef __J4MUDPARAMETERLIST__
#define __J4MUDPARAMETERLIST__
//********************************************************************
//* ---------------------
//* J4MUDParameterList.hh
//* ---------------------
//* (Description)
//* 	ParameterList class for Intermediate Tracker.
//*     The instance must be singleton. Use "GetInstance()" function
//*     to create and get the instance.
//*     
//* (Update Record)
//*	2003/03/17  K.Hoshina	Original version.
//*	2005/05/26  H.Ono       Edit from CAL
//********************************************************************
#include "G4Material.hh"
#include "G4Color.hh"
#include "J4ParameterList.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
class J4MUDParameterList : public J4VParameterList 
{
protected:  
  J4MUDParameterList( const G4String &name );   
  
public:
  virtual ~J4MUDParameterList();  
  
  virtual void PrintParameterList() { }

  //____Getter and Setters_________________________________________________
  static J4MUDParameterList* GetInstance();

  //*MUD Magnetic field
  inline G4double GetBarrelBField             () const { return fBarrelBField            ; }
  inline G4double GetCornerBField             () const { return fCornerBField            ; }
  inline G4double GetEndcapBField             () const { return fEndcapBField            ; }
  inline G4double GetReturnBField             () const { return fReturnBField            ; }
  
  //*MUD ------------------------------------------------------------------
  inline G4double GetMUDHeight                () const { return fMUDHeight               ; }
  inline G4double GetMUDDeltaPhi              () const { return fDeltaPhi                ; }
  inline G4int    GetNTraps                   () const { return fNTraps                  ; }
  inline G4int    GetNLayers                  () const { return fNLayers                 ; }
  inline G4double GetTrapDeltaPhi             () const { return fTrapDeltaPhi            ; }
  inline G4double GetPhiTolerance             () const { return fPhiTolerance            ; }
  inline G4double GetAbsThick( G4int i )         const { return fAbsThick[i]             ; }
  inline G4double GetActiveThick              () const { return fActiveThick             ; }
  G4double GetTotalAbsThick( G4int i )           const ;
  
  //*MUD and Block ----------------------------------------------------------
  inline G4double GetMUDInnerR                () const { return fMUDInnerR               ; }
  inline G4double GetMUDOuterR                () const { return fMUDOuterR               ; }
  inline G4double GetMUDEndcapFrontZ          () const { return fMUDEndcapFrontZ         ; }
  inline G4double GetMUDEndcapInnerR          () const { return fMUDEndcapInnerR         ; }
  inline G4double GetMUDEndcapThick           () const { return fMUDEndcapThick          ; }
  inline G4double GetMUDFrontEndcapThick      () const { return fMUDFrontEndcapThick     ; }
  inline G4double GetMUDFrontEndcapOuterR     () const { return fMUDFrontEndcapOuterR    ; }
  inline G4double GetMUDFrontEndcapFrontZ     () const { return fMUDFrontEndcapFrontZ    ; }
  inline G4double GetMUDHalfL                 () const { return fMUDHalfL                ; }
  inline G4double GetBlockInnerR              () const { return fBlockInnerR             ; }
  inline G4double GetBlockOuterR              () const { return fBlockOuterR             ; }
  inline G4double GetBlockEndcapFrontZ        () const { return fBlockEndcapFrontZ       ; }
  inline G4double GetBlockEndcapInnerR        () const { return fBlockEndcapInnerR       ; }
  inline G4double GetBlockEndcapThick         () const { return fBlockEndcapThick        ; }
  inline G4double GetBlockFrontEndcapThick    () const { return fBlockFrontEndcapThick   ; }  
  inline G4double GetBlockFrontEndcapFrontZ   () const { return fBlockFrontEndcapFrontZ  ; }
  inline G4double GetBlockFrontEndcapOuterR   () const { return fBlockFrontEndcapOuterR  ; }
  inline G4double GetBlockHalfL               () const { return fBlockHalfL              ; }
  
  //*Barrel -------------------------------------------------------------------
  inline G4int    GetBarrelNSuperLayers       () const { return fBarrelNSuperLayers      ; }
  inline G4int    GetBarrelNActiveLayers      () const { return fBarrelNActiveLayers     ; }
  inline G4int    GetBarrelNAbsLayers         () const { return fBarrelNAbsLayers        ; }
  inline G4double GetBarrelThick              () const { return fBarrelThick             ; }
  inline G4double GetBarrelActiveThick        () const { return fBarrelActiveThick       ; }
  inline G4double GetBarrelAbsThick( G4int i )   const { return fAbsThick[i]             ; }
  inline G4double GetBarrelDeltaPhi           () const { return fDeltaPhi                ; }
  inline G4double GetBarrelFrontHalfL         () const { return fBarrelFrontHalfL        ; }
  inline G4double GetBarrelInnerR             () const { return fBarrelInnerR            ; }

  G4double GetBarrelAbsFront( G4int i )         const;
  G4double GetBarrelActiveFront( G4int i )      const;
  G4double GetBarrelAbsHalfL( G4int i )         const;
  G4double GetBarrelActiveHalfL( G4int i )      const;
  
  //*Endcap ----------------------------------------------------------------
  inline G4int    GetEndcapNSuperLayers       () const { return fEndcapNSuperLayers      ; }
  inline G4int    GetEndcapNActiveLayers      () const { return fEndcapNActiveLayers     ; }
  inline G4int    GetEndcapNAbsLayers         () const { return fEndcapNAbsLayers        ; }
  inline G4double GetEndcapThick              () const { return fEndcapThick             ; }
  inline G4double GetEndcapActiveThick        () const { return fEndcapActiveThick       ; }
  inline G4double GetEndcapAbsThick( G4int i )   const { return fAbsThick[i]             ; }
  inline G4double GetEndcapInnerR             () const { return fEndcapInnerR            ; }
  inline G4double GetEndcapOuterR             () const { return fBlockOuterR             ; }
  inline G4double GetEndcapFrontZ             () const { return fEndcapFrontZ            ; }
  inline G4double GetEndcapDeltaPhi           () const { return fDeltaPhi                ; }

  G4double GetEndcapAbsHeight( G4int i )    const;
  G4double GetEndcapActiveHeight( G4int i ) const;
  G4double GetEndcapAbsFront( G4int i )     const;
  G4double GetEndcapActiveFront( G4int i )  const;
  G4double GetEndcapAbsZ( G4int i )         const;
  G4double GetEndcapActiveZ( G4int i )      const;

  //*FrontEndcap ------------------------------------------------------------
  inline G4int    GetFrontEndcapNSuperLayers()  const { return fFrontEndcapNSuperLayers  ; }
  inline G4int    GetFrontEndcapNActiveLayers() const { return fFrontEndcapNActiveLayers ; }
  inline G4int    GetFrontEndcapNAbsLayers()    const { return fFrontEndcapNAbsLayers    ; }
  inline G4double GetFrontEndcapThick()         const { return fFrontEndcapThick         ; }
  inline G4double GetFrontEndcapActiveThick()   const { return fFrontEndcapActiveThick   ; }
  inline G4double GetFrontEndcapAbsThick()      const { return fFrontEndcapAbsThick      ; }
  inline G4double GetFrontEndcapInnerR()        const { return fEndcapInnerR             ; }
  inline G4double GetFrontEndcapOuterR()        const { return fFrontEndcapOuterR        ; }
  inline G4double GetFrontEndcapFrontZ()        const { return fFrontEndcapFrontZ        ; }
  inline G4double GetFrontEndcapDeltaPhi()      const { return fDeltaPhi                 ; }

  G4double GetFrontEndcapAbsHeight( G4int i )    const;
  G4double GetFrontEndcapActiveHeight( G4int i ) const;
  G4double GetFrontEndcapAbsFront( G4int i )     const;
  G4double GetFrontEndcapActiveFront( G4int i )  const;
  G4double GetFrontEndcapAbsZ( G4int i )         const;
  G4double GetFrontEndcapActiveZ( G4int i )      const;
  
  //*materials --------------------------------------------------------------
  inline G4String GetMUDMaterial()           const { return fMUDMaterial;          }
  inline G4String GetBlockMaterial()         const { return fBlockMaterial;        }
  inline G4String GetBarrelAbsMaterial()     const { return fBarrelAbsMaterial;    }
  inline G4String GetBarrelActiveMaterial()  const { return fBarrelActiveMaterial; }
  inline G4String GetEndcapAbsMaterial()     const { return fEndcapAbsMaterial;    }
  inline G4String GetEndcapActiveMaterial()  const { return fEndcapActiveMaterial; }
  inline G4String GetFrontEndcapAbsMaterial()    const { return fFrontEndcapAbsMaterial;    }
  inline G4String GetFrontEndcapActiveMaterial()  const { return fFrontEndcapActiveMaterial; }
  
  //*VisAttributes ----------------------------------------------------------
  inline G4bool   GetMUDVisAtt()               const { return fMUDVisAtt;               }
  inline G4bool   GetBlockVisAtt()             const { return fBlockVisAtt;             }
  inline G4bool   GetBarrelAbsVisAtt()         const { return fBarrelAbsVisAtt;         }
  inline G4bool   GetBarrelActiveVisAtt()      const { return fBarrelActiveVisAtt;      }
  inline G4bool   GetEndcapAbsVisAtt()         const { return fEndcapAbsVisAtt;         }
  inline G4bool   GetEndcapActiveVisAtt()      const { return fEndcapActiveVisAtt;      }
  inline G4bool   GetFrontEndcapAbsVisAtt()    const { return fFrontEndcapAbsVisAtt;    }
  inline G4bool   GetFrontEndcapActiveVisAtt() const { return fFrontEndcapActiveVisAtt; }
  
  //*Color ------------------------------------------------------------------
  inline G4Color  GetMUDColor()               const { return fMUDColor;                }
  inline G4Color  GetBlockColor()             const { return fBlockColor;              }
  inline G4Color  GetBarrelAbsColor()         const { return fBarrelAbsColor;          }
  inline G4Color  GetBarrelActiveColor()      const { return fBarrelActiveColor;       }
  inline G4Color  GetEndcapAbsColor()         const { return fEndcapAbsColor;          }
  inline G4Color  GetEndcapActiveColor()      const { return fEndcapActiveColor;       }
  inline G4Color  GetFrontEndcapAbsColor()    const { return fFrontEndcapAbsColor;     }
  inline G4Color  GetFrontEndcapActiveColor() const { return fFrontEndcapActiveColor;  }
  
   //* VisAttributes ----------------------------------------------------------
  inline void SetMUDVisAtt(G4bool x)                 { fMUDVisAtt = x;           }
  inline void SetBlockVisAtt(G4bool x)               { fBlockVisAtt = x;         }
  inline void SetBarrelAbsVisAtt(G4bool x)           { fBarrelAbsVisAtt = x;     }
  inline void SetBarrelActiveVisAtt(G4bool x)        { fBarrelActiveVisAtt = x;  }
  inline void SetEndcapAbsVisAtt(G4bool x)           { fEndcapAbsVisAtt = x;     }
  inline void SetEndcapActiveVisAtt(G4bool x)        { fEndcapActiveVisAtt = x;  }  
  inline void SetFrontEndcapAbsVisAtt(G4bool x)      { fFrontEndcapAbsVisAtt = x;     }
  inline void SetFrontEndcapActiveVisAtt(G4bool x)   { fFrontEndcapActiveVisAtt = x;  }  
  
  //*Color ------------------------------------------------------------------
  inline void SetMUDColor(const G4Color &c)          { fMUDColor = c;            }
  inline void SetBlockColor(const G4Color &c)        { fBlockColor = c;          }
  inline void SetBarrelAbsColor(const G4Color &c)    { fBarrelAbsColor = c;      }
  inline void SetBarrelActiveColor(const G4Color &c) { fBarrelActiveColor = c;   }
  inline void SetEndcapAbsColor(const G4Color &c)    { fEndcapAbsColor = c;      }  
  inline void SetEndcapActiveColor(const G4Color &c) { fEndcapActiveColor = c;   }
  inline void SetFrontEndcapAbsColor(const G4Color &c)    { fFrontEndcapAbsColor = c;      }  
  inline void SetFrontEndcapActiveColor(const G4Color &c) { fFrontEndcapActiveColor = c;   }

 private:
  virtual void  SetMaterials();
  virtual void  SetVisAttributes();
  virtual void  SetColors();
  virtual void  SetParameters();

 private:
  //____Data members_________________________________________________________
  static J4MUDParameterList* fgInstance;
  
  //____Switch Front Layer to active_________________________________________
  G4bool   fIsFrontActive;
  
  //____MUD Magnetic filed___________________________________________________
  G4double  fBarrelBField;
  G4double  fCornerBField;
  G4double  fEndcapBField;
  G4double  fReturnBField;
  
  //____MUD_________________________________________________________________
  G4int     fNLayers;
  G4int     fNTraps;
  G4double  fMUDHeight;
  G4double  fTrapDeltaPhi;
  G4double  fDeltaPhi;
  G4double  fTolerance;
  G4double  fPhiTolerance;
  G4double  fActiveThick;
  G4double* fAbsThick;
  G4double  fFrontActiveThick;

  //____MUD and Block________________________________________________________
  G4double fMUDHalfL;
  G4double fMUDInnerR;
  G4double fMUDOuterR;
  G4double fMUDEndcapFrontZ;
  G4double fMUDEndcapInnerR;
  G4double fMUDEndcapThick;
  G4double fMUDFrontEndcapThick;
  G4double fMUDFrontEndcapFrontZ;
  G4double fMUDFrontEndcapOuterR;

  G4double fBlockHalfL;
  G4double fBlockInnerR;     
  G4double fBlockOuterR;
  G4double fBlockEndcapFrontZ;
  G4double fBlockEndcapInnerR;
  G4double fBlockEndcapThick;
  G4double fBlockFrontEndcapThick;
  G4double fBlockFrontEndcapFrontZ;
  G4double fBlockFrontEndcapOuterR;
  
  //____Barrel_______________________________________________________________
  G4double  fBarrelInnerR;
  G4double  fBarrelHalfL;
  G4double  fBarrelFrontHalfL;
  G4double  fBarrelThick;
  G4double  fBarrelAbsThick;
  G4double  fBarrelActiveThick;
  G4int     fBarrelNSuperLayers;
  G4int     fBarrelNAbsLayers;
  G4int     fBarrelNActiveLayers;

  //____Endcap_______________________________________________________________
  G4double  fEndcapInnerR;
  G4double  fEndcapFrontZ;
  G4double  fEndcapThick;
  G4double  fEndcapAbsThick;
  G4double  fEndcapActiveThick;
  G4int     fEndcapNSuperLayers;
  G4int     fEndcapNAbsLayers;
  G4int     fEndcapNActiveLayers;

  //____FrontEndcap__________________________________________________________
  G4double  fFrontEndcapFrontZ;
  G4double  fFrontEndcapOuterR;
  G4double  fFrontEndcapThick;
  G4double  fFrontEndcapActiveThick;
  G4double  fFrontEndcapAbsThick;
  G4int     fFrontEndcapNSuperLayers;
  G4int     fFrontEndcapNAbsLayers;
  G4int     fFrontEndcapNActiveLayers;

  //____material_____________________________________________________________
  G4String fMUDMaterial;
  G4String fBlockMaterial;
  G4String fBarrelAbsMaterial;
  G4String fBarrelActiveMaterial;
  G4String fEndcapAbsMaterial;
  G4String fEndcapActiveMaterial;
  G4String fFrontEndcapAbsMaterial;
  G4String fFrontEndcapActiveMaterial;

  //____VisAttributes_________________________________________________________
  G4bool    fMUDVisAtt;
  G4bool    fBlockVisAtt;
  G4bool    fBarrelAbsVisAtt;
  G4bool    fBarrelActiveVisAtt;
  G4bool    fEndcapAbsVisAtt;
  G4bool    fEndcapActiveVisAtt;
  G4bool    fFrontEndcapAbsVisAtt;
  G4bool    fFrontEndcapActiveVisAtt;

  //____Color_________________________________________________________________
  G4Color   fMUDColor;
  G4Color   fBlockColor;
  G4Color   fBarrelAbsColor;
  G4Color   fBarrelActiveColor;
  G4Color   fEndcapAbsColor;
  G4Color   fEndcapActiveColor;
  G4Color   fFrontEndcapAbsColor;
  G4Color   fFrontEndcapActiveColor;
  
};

#endif
