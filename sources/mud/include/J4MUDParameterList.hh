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
  inline G4double GetMUDInnerR()    const { return fBarrelInnerR; }
  inline G4double GetMUDOuterR()    const { return fBarrelOuterR; }
  inline G4double GetMUDHalfZ()     const { return fBarrelHalfZ;  }
  inline G4double GetMUDDeltaPhi()  const { return fDeltaPhi;     }

  //*Barrel -------------------------------------------------------------------
  inline G4int    GetNBarrelLayers()  const { return fNBarrelLayers;}
  inline G4double GetBarrelLayer()    const { return fBarrelLayer;  }
  inline G4double GetBarrelDeltaPhi() const { return fDeltaPhi;     }
  inline G4double GetBarrelHalfZ()    const { return fEndcapFrontZ; }
  inline G4double GetBarrelInnerR( G4int i ) const; 
  inline G4double GetBarrelOuterR( G4int i ) const; 
  
  //*Endcap ----------------------------------------------------------------
  inline G4int    GetNEndcapLayers()   const { return fNEndcapLayers;}
  inline G4double GetEndcapInnerR()    const { return fEndcapInnerR; }
  inline G4double GetEndcapOuterR()    const { return fBarrelOuterR; }
  inline G4double GetEndcapFrontZ()    const { return fEndcapFrontZ; }
  inline G4double GetEndcapDeltaPhi()  const { return fDeltaPhi;     }
  inline G4double GetEndcapThickness() const { return fEndcapThickness; }
  inline G4double GetEndcapLayer()     const { return fEndcapLayer; }
  inline G4double GetEndcapZ( G4int i ) const;// { return fEndcapFrontZ + 0.5*fEndcapThickness; }

  //*materials --------------------------------------------------------------
  inline G4String GetMUDMaterial()           const { return fMUDMaterial;       }
  inline G4String GetBarrelMaterial()        const { return fBarrelMaterial;     }
  inline G4String GetEndcapMaterial()        const { return fEndcapMaterial;    }
  
  //*VisAttributes ----------------------------------------------------------
  inline G4bool   GetMUDVisAtt()            const { return fMUDVisAtt;        }
  inline G4bool   GetBarrelVisAtt()         const { return fBarrelVisAtt;     }
  inline G4bool   GetEndcapVisAtt()         const { return fEndcapVisAtt;     }
  
  //*Color ------------------------------------------------------------------
  inline G4Color  GetMUDColor()             const { return fMUDColor;         }
  inline G4Color  GetBarrelColor()          const { return fBarrelColor;      }
  inline G4Color  GetEndcapColor()          const { return fEndcapColor;      }
  
   //* VisAttributes ----------------------------------------------------------
   inline void SetMUDVisAtt(G4bool x)                 { fMUDVisAtt = x;        }
   inline void SetBarrelVisAtt(G4bool x)              { fBarrelVisAtt = x;    }
   inline void SetEndcapVisAtt(G4bool x)              { fEndcapVisAtt = x;     }
   
   //*Color ------------------------------------------------------------------
   inline void SetMUDColor(const G4Color &c)          { fMUDColor = c;         }
   inline void SetBarrelColor(const G4Color &c)       { fBarrelColor = c;      }
   inline void SetEndcapColor(const G4Color &c)       { fEndcapColor = c;      }

 private:
    virtual void  SetMaterials();
    virtual void  SetVisAttributes();
    virtual void  SetColors();
    virtual void  SetParameters();
 
 private:
  static J4MUDParameterList* fgInstance;
   
  // material
  G4String fMUDMaterial;
  G4String fBarrelMaterial;
  G4String fEndcapMaterial;
  
  // VisAttributes
  G4bool    fMUDVisAtt;
  G4bool    fBarrelVisAtt;
  G4bool    fEndcapVisAtt;
   
  // Color
  G4Color   fMUDColor;
  G4Color   fBarrelColor;
  G4Color   fEndcapColor;

  // Barrel
  G4double  fBarrelInnerR;
  G4double  fBarrelOuterR;
  G4double  fBarrelHalfZ;
  G4int     fNBarrelLayers;
  G4double  fBarrelLayer;

  // Endcap
  G4double  fDeltaPhi;
  G4double  fEndcapInnerR;
  G4double  fEndcapFrontZ;
  G4double  fEndcapThickness;
  G4int     fNEndcapLayers;
  G4double  fEndcapLayer;

};

//=========================================================
//* inline functions
G4double J4MUDParameterList::GetEndcapZ( G4int layerID ) const
{
  if ( layerID < fNEndcapLayers ) 
    return fEndcapFrontZ + 0.5*fEndcapLayer*(2*layerID+1);
  else 
    return fEndcapFrontZ + 0.5*fEndcapLayer*(2*(layerID-fNEndcapLayers)+1);
}

G4double J4MUDParameterList::GetBarrelInnerR( G4int layerID ) const
{
  return fBarrelInnerR + fBarrelLayer*layerID;
} 

G4double J4MUDParameterList::GetBarrelOuterR( G4int layerID ) const
{
  return GetBarrelInnerR( layerID ) + fBarrelLayer;
} 

#endif
