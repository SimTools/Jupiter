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

  //=== get parameters===========================================
  static J4MUDParameterList* GetInstance(); 
   
  //*MUD ------------------------------------------------------------------
  inline G4double GetMUDHeight()           const { return fMUDHeight;           }
  inline G4double GetMUDInnerR()           const { return fBarrelInnerR;        }
  inline G4double GetMUDOuterR()           const { return fMUDOuterR;           }
  inline G4double GetMUDHalfL()            const { return fMUDHalfL;            }
  inline G4double GetMUDDeltaPhi()         const { return fDeltaPhi;            }
  inline G4double GetTrapDeltaPhi()        const { return fTrapDeltaPhi;        }
  inline G4int    GetNTraps()              const { return fNTraps;              }
  
  //*Barrel -------------------------------------------------------------------
  inline G4int    GetBarrelNSuperLayers()  const { return fBarrelNSuperLayers;  }
  inline G4int    GetBarrelNActiveLayers() const { return fBarrelNActiveLayers; }
  inline G4int    GetBarrelNAbsLayers()    const { return fBarrelNAbsLayers;    }
  inline G4double GetBarrelThick()         const { return fBarrelThick;         }
  inline G4double GetBarrelAbsThick()      const { return fBarrelAbsThick;      }
  inline G4double GetBarrelActiveThick()   const { return fBarrelActiveThick;   }
  inline G4double GetBarrelDeltaPhi()      const { return fDeltaPhi;            }
  inline G4double GetBarrelFrontHalfL()    const { return fBarrelFrontHalfL;    }
  inline G4double GetBarrelFront()         const { return fBarrelInnerR;        }
  inline G4double GetBarrelAbsFront( G4int i )         const;
  inline G4double GetBarrelActiveFront( G4int i )      const;
  inline G4double GetBarrelAbsHalfL( G4int i )         const;
  inline G4double GetBarrelActiveHalfL( G4int i )      const;

  //*Endcap ----------------------------------------------------------------
  inline G4int    GetEndcapNSuperLayers()  const { return fEndcapNSuperLayers;  }
  inline G4int    GetEndcapNActiveLayers() const { return fEndcapNActiveLayers; }
  inline G4int    GetEndcapNAbsLayers()    const { return fEndcapNAbsLayers;    }
  inline G4double GetEndcapThick()         const { return fEndcapThick;         }
  inline G4double GetEndcapAbsThick()      const { return fEndcapAbsThick;      }
  inline G4double GetEndcapActiveThick()   const { return fEndcapActiveThick;   }
  inline G4double GetEndcapInnerR()        const { return fEndcapInnerR;        }
  inline G4double GetEndcapOuterR()        const { return fMUDOuterR;           }
  inline G4double GetEndcapFrontZ()        const { return fEndcapFrontZ;        }
  inline G4double GetEndcapDeltaPhi()      const { return fDeltaPhi;            }
  inline G4double GetEndcapAbsHeight( G4int i )    const;
  inline G4double GetEndcapActiveHeight( G4int i ) const;
  inline G4double GetEndcapAbsFront( G4int i )     const;
  inline G4double GetEndcapActiveFront( G4int i )  const;
  inline G4double GetEndcapAbsZ( G4int i )         const;
  inline G4double GetEndcapActiveZ( G4int i )      const;

  //*FrontEndcap ------------------------------------------------------------
  inline G4int    GetFrontEndcapNSuperLayers()  const { return fFrontEndcapNSuperLayers;  }
  inline G4int    GetFrontEndcapNActiveLayers() const { return fFrontEndcapNActiveLayers; }
  inline G4int    GetFrontEndcapNAbsLayers()    const { return fFrontEndcapNAbsLayers;    }
  inline G4double GetFrontEndcapThick()         const { return fFrontEndcapThick;         }
  inline G4double GetFrontEndcapAbsThick()      const { return fFrontEndcapAbsThick;      }
  inline G4double GetFrontEndcapActiveThick()   const { return fFrontEndcapActiveThick;   }
  inline G4double GetFrontEndcapInnerR()        const { return fEndcapInnerR;             }
  inline G4double GetFrontEndcapOuterR()        const { return fFrontEndcapOuterR;        }
  inline G4double GetFrontEndcapFrontZ()        const { return fFrontEndcapFrontZ;        }
  inline G4double GetFrontEndcapDeltaPhi()      const { return fDeltaPhi;                 }
  inline G4double GetFrontEndcapAbsHeight( G4int i )    const;
  inline G4double GetFrontEndcapActiveHeight( G4int i ) const;
  inline G4double GetFrontEndcapAbsFront( G4int i )     const;
  inline G4double GetFrontEndcapActiveFront( G4int i )  const;
  inline G4double GetFrontEndcapAbsZ( G4int i )         const;
  inline G4double GetFrontEndcapActiveZ( G4int i )      const;


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
  inline G4bool   GetMUDVisAtt()             const { return fMUDVisAtt;          }
  inline G4bool   GetBlockVisAtt()           const { return fBlockVisAtt;        }
  inline G4bool   GetBarrelAbsVisAtt()       const { return fBarrelAbsVisAtt;    }
  inline G4bool   GetBarrelActiveVisAtt()    const { return fBarrelActiveVisAtt; }
  inline G4bool   GetEndcapAbsVisAtt()       const { return fEndcapAbsVisAtt;    }
  inline G4bool   GetEndcapActiveVisAtt()    const { return fEndcapActiveVisAtt; }
  inline G4bool   GetFrontEndcapAbsVisAtt()    const { return fFrontEndcapAbsVisAtt;    }
  inline G4bool   GetFrontEndcapActiveVisAtt() const { return fFrontEndcapActiveVisAtt; }
  
  //*Color ------------------------------------------------------------------
  inline G4Color  GetMUDColor()              const { return fMUDColor;           }
  inline G4Color  GetBlockColor()            const { return fBlockColor;         }
  inline G4Color  GetBarrelAbsColor()        const { return fBarrelAbsColor;     }
  inline G4Color  GetBarrelActiveColor()     const { return fBarrelActiveColor;  }
  inline G4Color  GetEndcapAbsColor()        const { return fEndcapAbsColor;     }
  inline G4Color  GetEndcapActiveColor()     const { return fEndcapActiveColor;  }
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
  static J4MUDParameterList* fgInstance;
   
  // material
  G4String fMUDMaterial;
  G4String fBlockMaterial;
  G4String fBarrelAbsMaterial;
  G4String fBarrelActiveMaterial;
  G4String fEndcapAbsMaterial;
  G4String fEndcapActiveMaterial;
  G4String fFrontEndcapAbsMaterial;
  G4String fFrontEndcapActiveMaterial;

  // VisAttributes
  G4bool    fMUDVisAtt;
  G4bool    fBlockVisAtt;
  G4bool    fBarrelAbsVisAtt;
  G4bool    fBarrelActiveVisAtt;
  G4bool    fEndcapAbsVisAtt;
  G4bool    fEndcapActiveVisAtt;
  G4bool    fFrontEndcapAbsVisAtt;
  G4bool    fFrontEndcapActiveVisAtt;

  // Color
  G4Color   fMUDColor;
  G4Color   fBlockColor;
  G4Color   fBarrelAbsColor;
  G4Color   fBarrelActiveColor;
  G4Color   fEndcapAbsColor;
  G4Color   fEndcapActiveColor;
  G4Color   fFrontEndcapAbsColor;
  G4Color   fFrontEndcapActiveColor;

  // MUD
  G4double  fMUDHeight;
  G4double  fMUDHalfL;
  G4double  fTrapDeltaPhi;
  G4double  fMUDOuterR;
  G4double  fDeltaPhi;
  G4int     fNTraps;
  
  // Barrel
  G4double  fBarrelInnerR;
  //G4double  fBarrelOuterR;
  G4double  fBarrelHalfL;
  G4double  fBarrelFrontHalfL;
  G4double  fBarrelThick;
  G4double  fBarrelAbsThick;
  G4double  fBarrelActiveThick;
  G4int     fBarrelNSuperLayers;
  G4int     fBarrelNAbsLayers;
  G4int     fBarrelNActiveLayers;

  // Endcap
  G4double  fEndcapInnerR;
  G4double  fEndcapFrontZ;
  G4double  fEndcapThick;
  G4double  fEndcapAbsThick;
  G4double  fEndcapActiveThick;
  G4int     fEndcapNSuperLayers;
  G4int     fEndcapNAbsLayers;
  G4int     fEndcapNActiveLayers;

  // FrontEndcap
  G4double  fFrontEndcapFrontZ;
  G4double  fFrontEndcapOuterR;
  G4double  fFrontEndcapThick;
  G4double  fFrontEndcapActiveThick;
  G4double  fFrontEndcapAbsThick;
  G4int     fFrontEndcapNSuperLayers;
  G4int     fFrontEndcapNAbsLayers;
  G4int     fFrontEndcapNActiveLayers;

};

//=========================================================
//* inline functions
G4double J4MUDParameterList::GetBarrelAbsFront( G4int layerID ) const
{
  return fBarrelInnerR + layerID*(fBarrelAbsThick+fBarrelActiveThick);
}

G4double J4MUDParameterList::GetEndcapAbsFront( G4int layerID ) const
{
  return fEndcapFrontZ + layerID*(fEndcapAbsThick+fEndcapActiveThick) ; 
}

G4double J4MUDParameterList::GetBarrelActiveFront( G4int layerID ) const
{
  return GetBarrelAbsFront( layerID ) + fBarrelAbsThick;
}

G4double J4MUDParameterList::GetEndcapActiveFront( G4int layerID ) const
{
  return GetEndcapAbsFront( layerID ) + fEndcapAbsThick;
}

G4double J4MUDParameterList::GetEndcapAbsZ( G4int layerID ) const
{
  return GetEndcapAbsFront(layerID) + 0.5*fEndcapAbsThick;
}

G4double J4MUDParameterList::GetEndcapActiveZ( G4int layerID ) const
{
  return GetEndcapActiveFront(layerID) + 0.5*fEndcapActiveThick;
}

G4double J4MUDParameterList::GetBarrelAbsHalfL( G4int layerID ) const
{
  return fEndcapFrontZ+(layerID+2)*fEndcapAbsThick+(layerID+1)*fEndcapActiveThick;
}

G4double J4MUDParameterList::GetBarrelActiveHalfL( G4int layerID ) const
{
  return GetBarrelAbsHalfL( layerID ) + fEndcapActiveThick;
}

G4double J4MUDParameterList::GetEndcapAbsHeight( G4int layerID ) const
{
  if ( layerID < 2 )
    return GetBarrelAbsFront( 0 );
  else
    return GetBarrelAbsFront( layerID -1 );
}

G4double J4MUDParameterList::GetEndcapActiveHeight( G4int layerID ) const
{
  if ( layerID == 0 )
    return GetBarrelAbsFront( 0 );
  else
    return GetBarrelAbsFront( layerID-1 )+fBarrelAbsThick;
}

G4double J4MUDParameterList::GetFrontEndcapAbsHeight( G4int /*layerID*/ ) const
{
  return GetFrontEndcapOuterR() * cos( 0.5*GetTrapDeltaPhi() );
}

G4double J4MUDParameterList::GetFrontEndcapActiveHeight( G4int /*layerID*/ ) const
{
  return GetFrontEndcapOuterR() * cos( 0.5*GetTrapDeltaPhi() );
}

G4double J4MUDParameterList::GetFrontEndcapAbsFront( G4int layerID ) const
{
  return GetFrontEndcapFrontZ() + layerID*(GetFrontEndcapAbsThick()+GetFrontEndcapActiveThick());
}

G4double J4MUDParameterList::GetFrontEndcapActiveFront( G4int layerID ) const
{
  return GetFrontEndcapAbsFront( layerID ) + GetFrontEndcapAbsThick();
}

G4double J4MUDParameterList::GetFrontEndcapAbsZ( G4int layerID )  const
{
  return GetFrontEndcapAbsFront( layerID ) + 0.5*GetFrontEndcapAbsThick();
}

G4double J4MUDParameterList::GetFrontEndcapActiveZ( G4int layerID ) const
{
  return GetFrontEndcapActiveFront( layerID ) + 0.5*GetFrontEndcapActiveThick();
}

#endif
