// $Id$
#ifndef __J4CDCPARAMETERLIST__
#define __J4CDCPARAMETERLIST__
//********************************************************************
//* ---------------------
//* J4CDCParameterList.hh
//* ---------------------
//* (Description)
//*     ParameterList class for CDC.
//*     The instance must be singleton. Use "GetInstance()" function
//*     to create and get the instance.
//*     
//* (Update Record)
//*	2002/10/??  K.Hoshina	Original version.
//********************************************************************

#include "G4Material.hh"
#include "G4Color.hh"
#include "J4ParameterList.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4CDCParameterList : public J4VParameterList 
{

 protected: 

   J4CDCParameterList(const G4String &name);   

 public:
   virtual ~J4CDCParameterList();  
   
   virtual void PrintParameterList(){};
 
   static J4CDCParameterList* GetInstance();
  
   //
   // get parameters
   //
   
   //*cdc ------------------------------------------------------------------
   inline G4double GetCDCInnerR()    const; 
   inline G4double GetCDCOuterR()    const; 
   inline G4double GetCDCHalfZ()     const;
   inline G4double GetCDCDeltaPhi()  const { return fCDCDeltaPhi;  }
   inline G4double GetCDCPhiOffset() const { return fCDCPhiOffset; }
   
   //*Endcap ----------------------------------------------------------------
   inline G4double GetEndcapHalfThick() const { return fEndcapHalfThick; }
   inline G4double GetEndcapFrontZ()    const;
   inline G4double GetEndcapInnerR()    const;
   inline G4double GetEndcapOuterR()    const;
   inline G4double GetEndcapHalfZ()     const;
   inline G4double GetEndcapPhiOffset() const;
   inline G4double GetEndcapDeltaPhi()  const { return fCDCDeltaPhi;    }
   
   //*SupportTub -------------------------------------------------------------
   inline G4double GetSupportTubHalfThick()   const { return fSupportTubHalfThick;}
   inline G4double GetOuterSupportTubInnerR() const;
   inline G4double GetOuterSupportTubOuterR() const;
   inline G4double GetInnerSupportTubInnerR() const;
   inline G4double GetInnerSupportTubOuterR() const;
   inline G4double GetSupportTubHalfZ()       const;
   inline G4double GetSupportTubPhiOffset()   const;
   inline G4double GetSupportTubDeltaPhi()    const { return fCDCDeltaPhi;    }
 
   //*SuperLayer --------------------------------------------------------------
   inline G4bool   IsOddSuperLyrOutermost()         const { return fIsOddSuperLyrOutermost; }
   inline G4int    GetNsuperLayers()                const { return fNsuperLayers;           }
   inline G4int    GetNcellsPerLayer(G4int i)       const { return fNcellsParLayer[i];      }
   inline G4int    GetNlayersPerSuperLayer(G4int i) const;
                                              
   inline G4double GetSuperLayerInnerGap()          const { return fSuperLayerInnerGap; }
   inline G4double GetSuperLayerOuterGap()          const { return fSuperLayerOuterGap; }
   inline G4double GetAxialToStereoGap()            const { return fAxialToStereoGap;   }
   inline G4double GetStereoToStereoGap()           const { return fStereoToStereoGap;  }
   inline G4double GetStereoToAxialGap()            const { return fStereoToAxialGap;   }
   inline G4double GetSuperLayerHalfZ()             const;
   inline G4double GetSuperLayerThick(G4int i)      const;
   inline G4double GetSuperLayerInnerR(G4int i)     const;
   inline G4double GetSuperLayerOuterR(G4int i)     const;
   inline G4double GetSuperLayerPhiOffset(G4int i)  const { return fSuperLayerPhiOffset[i]; }
   
   //*Layer -------------------------------------------------------------------
   inline G4bool   IsAxialOnly()                    const { return fIsAxialOnly; }
   inline G4int    GetNlayers()                     const { return fNlayers;     }
   inline G4double GetUniformShieldLayerThick()     const;
   
   // argument "gi" must be a global layer number.
   inline G4double GetLayerPhiOffset(G4int gi)      const { return fLayerPhiOffset[gi];}
   inline G4double GetLayerPhiTwist(G4int gi)       const { return fTwistedAngle[gi];  }

   // generate global No. through the chamber
   G4int  GetLayerNumber(G4int superlayerid, G4int myid) const; 
                 
   //*Cell -------------------------------------------------------------------
   inline G4double GetCellThick()              const { return fCellThick;   }
  
   //*DriftRegion ------------------------------------------------------------
   inline G4double GetMeasPlaneHalfThick()     const { return fMeasPlaneHalfThick;    }
   inline G4int    GetNdriftRegions()          const { return fNdriftRegions;         }
   inline G4double GetDriftRegionThick()       const { return fDriftRegionThick;      }
   inline G4double GetDummyDriftRegionThick()  const { return fDummyDriftRegionThick; }
                        
   //*SenseWire --------------------------------------------------------------
   inline G4double GetSenseWireR()             const { return fSenseWireR;  }

    
   //*materials --------------------------------------------------------------
   inline G4String GetCDCMaterial()              const { return fCDCMaterial;        }
   inline G4String GetSupportTubMaterial()       const { return fSupportTubMaterial; }
   inline G4String GetEndcapMaterial()           const { return fEndcapMaterial;     }
   inline G4String GetLayerMaterial()            const { return fLayerMaterial;      }
   inline G4String GetCellMaterial()             const { return fCellMaterial;       }
   inline G4String GetDriftRegionMaterial()      const { return fDriftRegionMaterial;}
   inline G4String GetSenseWireMaterial()        const { return fSenseWireMaterial;  }
   inline G4String GetDummyDriftRegionMaterial() const { return fDriftRegionMaterial; }

   //*VisAttributes ----------------------------------------------------------
   inline G4bool GetCDCVisAtt()               const { return fCDCVisAtt;         }
   inline G4bool GetEndcapVisAtt()            const { return fEndcapVisAtt;      }
   inline G4bool GetSupportTubVisAtt()        const { return fSupportTubVisAtt;  }
   inline G4bool GetSuperLayerVisAtt()        const { return fSuperLayerVisAtt;  }
   inline G4bool GetLayerVisAtt()             const { return fLayerVisAtt;       }
   inline G4bool GetCellVisAtt()              const { return fCellVisAtt;        }
   inline G4bool GetDriftRegionVisAtt()       const { return fDriftRegionVisAtt; }
   inline G4bool GetSenseWireVisAtt()         const { return fSenseWireVisAtt;   }
   inline G4bool GetStereoCellVisAtt()        const { return fStereoCellVisAtt;  }
   inline G4bool GetStereoDriftRegionVisAtt() const { return fStereoDriftRegionVisAtt; }
   inline G4bool GetDummyDriftRegionVisAtt()  const { return fDummyDriftRegionVisAtt; }
   
   //*Color ------------------------------------------------------------------
   inline G4Color GetCDCColor()               const { return fCDCColor;         }
   inline G4Color GetEndcapColor()            const { return fEndcapColor;      }
   inline G4Color GetSupportTubColor()        const { return fSupportTubColor;  }
   inline G4Color GetSuperLayerColor()        const { return fSuperLayerColor;  }
   inline G4Color GetLayerColor()             const { return fLayerColor;       }
   inline G4Color GetCellColor()              const { return fCellColor;        }
   inline G4Color GetDriftRegionColor()       const { return fDriftRegionColor; }
   inline G4Color GetSenseWireColor()         const { return fSenseWireColor;   }
   inline G4Color GetStereoCellColor()        const { return fStereoCellColor;  }
   inline G4Color GetStereoDriftRegionColor() const { return fStereoDriftRegionColor; }
   inline G4Color GetDummyDriftRegionColor()  const { return fDummyDriftRegionColor;  }


   //
   // set parameters
   //

   //*Color ------------------------------------------------------------------
   inline void SetCDCColor(const G4Color &c)        { fCDCColor = c;         }
   inline void SetEndcapColor(const G4Color &c)     { fEndcapColor = c;      }
   inline void SetSupportTubColor(const G4Color &c) { fSupportTubColor = c;  }
   inline void SetSuperLayerColor(const G4Color &c) { fSuperLayerColor = c;  }
   inline void SetLayerColor(const G4Color &c)      { fLayerColor = c;       }
   inline void SetCellColor(const G4Color &c)       { fCellColor = c;        }
   inline void SetDriftRegionColor(const G4Color &c){ fDriftRegionColor = c; }
   inline void SetSenseWireColor(const G4Color &c)  { fSenseWireColor = c;   }
   inline void SetStereoCellColor(const G4Color &c) { fStereoCellColor = c;  }
   inline void SetStereoDriftRegionColor(const G4Color &c) { fStereoDriftRegionColor = c; }
   inline void SetDummyDriftRegionColor(const G4Color &c)  { fDummyDriftRegionColor = c;  }
  
 private:
 
    virtual void  SetMaterials();
    virtual void  SetVisAttributes();
    virtual void  SetColors();
    virtual void  SetParameters();
    
 private:
   
   static J4CDCParameterList* fgInstance;

   // material
   G4String  fCDCMaterial;
   G4String  fSupportTubMaterial;
   G4String  fEndcapMaterial;
   G4String  fLayerMaterial;
   G4String  fCellMaterial;
   G4String  fDriftRegionMaterial;
   G4String  fSenseWireMaterial;
  
   // VisAttributes
   G4bool    fCDCVisAtt;
   G4bool    fEndcapVisAtt;
   G4bool    fSupportTubVisAtt;
   G4bool    fSuperLayerVisAtt;
   G4bool    fLayerVisAtt;
   G4bool    fCellVisAtt;
   G4bool    fDriftRegionVisAtt;
   G4bool    fStereoCellVisAtt;
   G4bool    fStereoDriftRegionVisAtt;
   G4bool    fDummyDriftRegionVisAtt;
   G4bool    fSenseWireVisAtt;
   
   // Color
   G4Color   fCDCColor;
   G4Color   fEndcapColor;
   G4Color   fSupportTubColor;
   G4Color   fSuperLayerColor;
   G4Color   fLayerColor;
   G4Color   fCellColor;
   G4Color   fDriftRegionColor;
   G4Color   fStereoCellColor;
   G4Color   fStereoDriftRegionColor;
   G4Color   fDummyDriftRegionColor;
   G4Color   fSenseWireColor;
   
   // CDC
   G4double  fCDCDeltaPhi;
   G4double  fCDCPhiOffset;
  
   // Endcap
   G4double  fEndcapHalfThick;
   
   // SupportTub
   G4double  fSupportTubHalfThick;
   
   // Layer
   G4int     fNlayers;
   G4double *fTwistedAngle;
   G4double *fLayerPhiOffset;
   G4bool    fIsAxialOnly;
   
   // SuperLayer
   G4bool    fIsOddSuperLyrOutermost;
             // Is axial layer innermost in a superlayer?
             // YES : 3 big superlayer + 1 small (outermost) superlayer
             // NO  : 1 small (innermost) superlayer + 3 big superlayer
             
   G4int     fNsuperLayers;         // number of superlayers
   G4int     fNlayersPerSuperLayer; // number of layers in a super layer
   G4double  fSuperLayerInnerGap;   // gap between InnerSupportTubOuterR and superlayer
   G4double  fSuperLayerOuterGap;   // gap between superlayer and OuterSupportTubInnerR
   G4double  fAxialToStereoGap;     // gap between axial layer and stereo layer
   G4double  fStereoToStereoGap;    // gap between stereo layer and stereo layer
   G4double  fStereoToAxialGap;     // gap between stereo layer and axial layer
   G4double *fSuperLayerPhiOffset;
   G4int    *fNcellsParLayer;
  
   // Cell
   G4double  fCellThick;
  
   // DriftRegion
   G4double  fMeasPlaneHalfThick;   // thickness of hypothetical measurement plane 
   G4int     fNdriftRegions;        // per cell
   G4double  fDriftRegionThick;     // thickness of driftregion per wire
  
   // DummyDriftRegion
   G4double  fDummyDriftRegionThick;
  
   // SenseWire
   G4double  fSenseWireR;
  
};

//=========================================================
//* inline functions

G4double J4CDCParameterList::GetCDCInnerR() const 
{ 
   return J4ParameterList::GetInstance()->GetCDCInnerR();
}

G4double J4CDCParameterList::GetCDCOuterR() const 
{
   return J4ParameterList::GetInstance()->GetCDCOuterR();
}

G4double J4CDCParameterList::GetCDCHalfZ() const
{
   return J4ParameterList::GetInstance()->GetCDCHalfZ();     
}

G4double J4CDCParameterList::GetEndcapFrontZ() const 
{
   return GetCDCHalfZ() - 2 * fEndcapHalfThick;
}

G4double J4CDCParameterList::GetEndcapInnerR() const
{
   return GetCDCInnerR();
}

G4double J4CDCParameterList::GetEndcapOuterR() const
{
   return GetCDCOuterR();
}

G4double J4CDCParameterList::GetEndcapHalfZ() const
{
   return fEndcapHalfThick;
}

G4double J4CDCParameterList::GetEndcapPhiOffset() const
{
   return fCDCPhiOffset;
}

G4double J4CDCParameterList::GetOuterSupportTubInnerR() const
{
   return GetCDCOuterR() - 2 * fSupportTubHalfThick;
}

G4double J4CDCParameterList::GetOuterSupportTubOuterR() const
{
   return GetCDCOuterR();
}

G4double J4CDCParameterList::GetInnerSupportTubInnerR() const
{
   return GetCDCInnerR();
}

G4double J4CDCParameterList::GetInnerSupportTubOuterR() const
{
   return GetCDCInnerR() + 2 * fSupportTubHalfThick;
}

G4double J4CDCParameterList::GetSupportTubHalfZ() const
{
   return GetEndcapFrontZ();
}

G4double J4CDCParameterList::GetSupportTubPhiOffset() const
{
   return fCDCPhiOffset;
}

G4int J4CDCParameterList::GetNlayersPerSuperLayer(G4int ilayer) const
{ 
   if (fIsOddSuperLyrOutermost) {
      if (ilayer < fNsuperLayers) {
         return fNlayersPerSuperLayer;
      } else {
         return 1;
      }
   } else {
      if (ilayer == 0) {
         return 1;
      } else {
         return fNlayersPerSuperLayer;
      }
   }
}

G4double J4CDCParameterList::GetSuperLayerHalfZ() const
{
   return GetEndcapFrontZ();
}

G4double J4CDCParameterList::GetSuperLayerThick(G4int ilayer) const
{
   if ((fIsOddSuperLyrOutermost && (ilayer == fNsuperLayers - 1)) ||
                   ((!fIsOddSuperLyrOutermost) && ilayer == 0)) {
      // small super layer! (A)
      return fCellThick;
   } else {
      // large super layer (A,U,V)
      return (3 * fCellThick + fAxialToStereoGap +
              fStereoToStereoGap + fStereoToAxialGap);
   }
}

G4double J4CDCParameterList::GetSuperLayerInnerR(G4int ilayer) const
{
   if (fIsOddSuperLyrOutermost || (!fIsOddSuperLyrOutermost && ilayer == 0)) {
      return (GetInnerSupportTubOuterR() + fSuperLayerInnerGap 
              + ilayer * GetSuperLayerThick(1));
   } else {
      return (GetInnerSupportTubOuterR() + fSuperLayerInnerGap 
              + fCellThick // innermost small superlayer
              + (ilayer - 1) * GetSuperLayerThick(1));
   }
}

G4double J4CDCParameterList::GetSuperLayerOuterR(G4int ilayer) const
{
   return GetSuperLayerInnerR(ilayer) + GetSuperLayerThick(ilayer);
}

G4double J4CDCParameterList::GetUniformShieldLayerThick() const
{
   return (GetCDCOuterR() - GetCDCInnerR() 
           - 4 * fSupportTubHalfThick
           - fNlayers * fCellThick) / fNlayers;
}



#endif
