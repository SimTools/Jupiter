// $Id$
#ifndef __J4CDCPARAMETERLIST__
#define __J4CDCPARAMETERLIST__
//********************************************************************
//* ---------------------
//* J4CDCParameterList.hh
//* ---------------------
//* (Description)
//* 	Material Store class for CDC.
//*     Define Materials for CDC here.
//*     
//* (Update Record)
//*	2002/10/??  K.Hoshina	Original version.
//********************************************************************

#include "G4Material.hh"
#include "G4Color.hh"
#include "J4VParameterList.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4CDCParameterList : public J4VParameterList 
{
 
 public:
   J4CDCParameterList();   
   J4CDCParameterList(const G4String &name);   
   virtual ~J4CDCParameterList();  
   
   virtual void PrintParameterList(){};
  
   //
   // get parameters
   //
   
   //*cdc ------------------------------------------------------------------
   inline G4double GetCDCIR()    const { return fCDCInnerRadius; }
   inline G4double GetCDCOR()    const { return fCDCOuterRadius; }
   inline G4double GetCDCHalfZ() const { return fCDCHalfZLength; }
   inline G4double GetCDCDPhi()  const { return fCDCDeltaPhi;    }
   inline G4double GetCDCSPhi()  const { return fCDCPhiOffset;   }
   
   //*Endcap ----------------------------------------------------------------
   inline G4double GetEndcapThick()  const { return fEndcapHalfThickness; }
   inline G4double GetEndcapFrontZ() const;
   inline G4double GetEndcapIR()     const;
   inline G4double GetEndcapOR()     const;
   inline G4double GetEndcapHalfZ()  const;
   inline G4double GetEndcapSPhi()   const;
   inline G4double GetEndcapDPhi()   const { return fCDCDeltaPhi;    }
   
   //*SupportTub -------------------------------------------------------------
   inline G4double GetSupportTubThick()   const { return fSupportTubThickness;}
   inline G4double GetOuterSupportTubIR() const;
   inline G4double GetOuterSupportTubOR() const;
   inline G4double GetInnerSupportTubIR() const;
   inline G4double GetInnerSupportTubOR() const;
   inline G4double GetSupportTubHalfZ()   const;
   inline G4double GetSupportTubSPhi()    const;
   inline G4double GetSupportTubDPhi()    const { return fCDCDeltaPhi;    }
 
   //*SuperLayer --------------------------------------------------------------
   inline G4bool   IsOddSuperLyrOutermost()      const { return fIsOddSuperLyrOutermost;    }
   inline G4int    GetNsuperLayers()       const { return fNsuperLayers;        }
   inline G4int    GetNlayersPerSuperLayer(G4int ilayer) const;
   inline G4int    GetNcellsPerLayer(G4int ilayer) const
                                              { return fNcellsParLayer[ilayer]; }
                                              
   inline G4double GetSuperLayerInnerGap() const { return fSuperLayerInnerGap;  }
   inline G4double GetSuperLayerOuterGap() const { return fSuperLayerOuterGap;  }
   inline G4double GetAxialToStereoGap()   const { return fAxialToStereoGap;    }
   inline G4double GetStereoToStereoGap()  const { return fStereoToStereoGap;   }
   inline G4double GetStereoToAxialGap()   const { return fStereoToAxialGap;    }
   inline G4double GetSuperLayerHalfZ()    const;
   inline G4double GetSuperLayerThick(G4int ilayer) const;
   inline G4double GetSuperLayerIR   (G4int ilayer) const;
   inline G4double GetSuperLayerOR   (G4int ilayer) const;
   inline G4double GetSuperLayerSPhi (G4int ilayer) const 
                                        { return fSuperLayerPhiOffset[ilayer]; }
   
   //*Layer -------------------------------------------------------------------
   inline G4bool   IsAxialOnly()             const { return fIsAxialOnly; }
   inline G4int    GetNlayers()              const { return fNlayers;          }
   inline G4double GetUniformShieldLayerThick()const;
   
   // generation function of global No. through the chamber
   G4int  GetLayerNumber(G4int superlayerid, G4int myid) const; 
   
   // following functions requires global layer number.
   inline G4double GetLayerSPhi(G4int gi)    const { return fLayerPhiOffset[gi];}
   inline G4double GetLayerPhiTwist(G4int gi)const { return fTwistedAngle[gi];  }
                 
   //*Cell -------------------------------------------------------------------
   inline G4double GetCellThick()        const { return fCellThickness;   }
  
   //*DriftRegion ------------------------------------------------------------
   inline G4int    GetNdriftRegions()    const { return fNdriftRegions;        }
   inline G4double GetDriftRegionThick() const { return fDriftRegionThickness; }
  
   //*DummyDriftRegion -------------------------------------------------------
   inline G4double GetDummyDriftRegionThick() const 
                   { return fDummyDriftRegionThickness; }
                        
   //*SenseWire --------------------------------------------------------------
   inline G4double GetSenseWireRadius()     const { return fSenseWireRadius; }
    
   //*materials --------------------------------------------------------------
   inline G4String GetCDCMaterial()         const { return fCDCMaterial;        }
   inline G4String GetSupportTubMaterial()  const { return fSupportTubMaterial; }
   inline G4String GetEndcapMaterial()      const { return fEndcapMaterial;     }
   inline G4String GetLayerMaterial()       const { return fLayerMaterial;      }
   inline G4String GetCellMaterial()        const { return fCellMaterial;       }
   inline G4String GetDriftRegionMaterial() const { return fDriftRegionMaterial;}
   inline G4String GetSenseWireMaterial()   const { return fSenseWireMaterial;  }
   inline G4String GetDummyDriftRegionMaterial() const 
                   { return fDriftRegionMaterial; }

   //*VisAttributes ----------------------------------------------------------
   inline G4bool GetCDCVisAtt()         const { return fCDCVisAtt;         }
   inline G4bool GetEndcapVisAtt()      const { return fEndcapVisAtt;      }
   inline G4bool GetSupportTubVisAtt()  const { return fSupportTubVisAtt;  }
   inline G4bool GetSuperLayerVisAtt()  const { return fSuperLayerVisAtt;  }
   inline G4bool GetLayerVisAtt()       const { return fLayerVisAtt;       }
   inline G4bool GetCellVisAtt()        const { return fCellVisAtt;        }
   inline G4bool GetDriftRegionVisAtt() const { return fDriftRegionVisAtt; }
   inline G4bool GetSenseWireVisAtt()   const { return fSenseWireVisAtt;   }
   inline G4bool GetStereoCellVisAtt()  const { return fStereoCellVisAtt;        }
   inline G4bool GetStereoDriftRegionVisAtt() const 
                 { return fStereoDriftRegionVisAtt; }
   inline G4bool GetDummyDriftRegionVisAtt() const 
                 { return fDummyDriftRegionVisAtt; }
   
   //*Color ------------------------------------------------------------------
   inline G4Color GetCDCColor()         const { return *fCDCColor;         }
   inline G4Color GetEndcapColor()      const { return *fEndcapColor;      }
   inline G4Color GetSupportTubColor()  const { return *fSupportTubColor;  }
   inline G4Color GetSuperLayerColor()  const { return *fSuperLayerColor;  }
   inline G4Color GetLayerColor()       const { return *fLayerColor;       }
   inline G4Color GetCellColor()        const { return *fCellColor;        }
   inline G4Color GetDriftRegionColor() const { return *fDriftRegionColor; }
   inline G4Color GetSenseWireColor()   const { return *fSenseWireColor; }
   inline G4Color GetStereoCellColor()  const { return *fStereoCellColor;        }
   inline G4Color GetStereoDriftRegionColor() const 
                  { return *fStereoDriftRegionColor; }
   inline G4Color GetDummyDriftRegionColor() const 
                  { return *fDummyDriftRegionColor; }
  
 private:
 
    virtual void  SetMaterials();
    virtual void  SetVisAttributes();
    virtual void  SetColors();
    virtual void  SetParameters();
    
 private:
   
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
   G4Color  *fCDCColor;
   G4Color  *fEndcapColor;
   G4Color  *fSupportTubColor;
   G4Color  *fSuperLayerColor;
   G4Color  *fLayerColor;
   G4Color  *fCellColor;
   G4Color  *fDriftRegionColor;
   G4Color  *fStereoCellColor;
   G4Color  *fStereoDriftRegionColor;
   G4Color  *fDummyDriftRegionColor;
   G4Color  *fSenseWireColor;
   
   // CDC
   G4double  fCDCInnerRadius;
   G4double  fCDCOuterRadius;
   G4double  fCDCHalfZLength;
   G4double  fCDCDeltaPhi;
   G4double  fCDCPhiOffset;
  
   // Endcap
   G4double  fEndcapHalfThickness;
   
   // SupportTub
   G4double  fSupportTubThickness;
   
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
   G4double  fSuperLayerInnerGap;   // gap between InnerSupportTubOR and superlayer
   G4double  fSuperLayerOuterGap;   // gap between superlayer and OuterSupportTubIR
   G4double  fAxialToStereoGap;     // gap between axial layer and stereo layer
   G4double  fStereoToStereoGap;    // gap between stereo layer and stereo layer
   G4double  fStereoToAxialGap;     // gap between stereo layer and axial layer
   G4double *fSuperLayerPhiOffset;
   G4int    *fNcellsParLayer;
  
   // Cell
   G4double  fCellThickness;
  
   // DriftRegion
   G4int     fNdriftRegions;        // per cell
   G4double  fDriftRegionThickness;
  
   // DummyDriftRegion
   G4double  fDummyDriftRegionThickness;
  
   // SenseWire
   G4double  fSenseWireRadius;
  
};

//=========================================================
//* inline functions

G4double J4CDCParameterList::GetEndcapFrontZ() const 
{
   return fCDCHalfZLength - 2 * fEndcapHalfThickness;
}

G4double J4CDCParameterList::GetEndcapIR() const
{
   return fCDCInnerRadius;
}

G4double J4CDCParameterList::GetEndcapOR() const
{
   return fCDCOuterRadius;
}

G4double J4CDCParameterList::GetEndcapHalfZ() const
{
   return fEndcapHalfThickness;
}

G4double J4CDCParameterList::GetEndcapSPhi() const
{
   return fCDCPhiOffset;
}

G4double J4CDCParameterList::GetOuterSupportTubIR() const
{
   return fCDCOuterRadius - fSupportTubThickness;
}

G4double J4CDCParameterList::GetOuterSupportTubOR() const
{
   return fCDCOuterRadius;
}

G4double J4CDCParameterList::GetInnerSupportTubIR() const
{
   return fCDCInnerRadius;
}

G4double J4CDCParameterList::GetInnerSupportTubOR() const
{
   return fCDCInnerRadius + fSupportTubThickness;
}

G4double J4CDCParameterList::GetSupportTubHalfZ() const
{
   return GetEndcapFrontZ();
}

G4double J4CDCParameterList::GetSupportTubSPhi() const
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
      return fCellThickness;
   } else {
      return (3 * fCellThickness + fAxialToStereoGap +
              fStereoToStereoGap + fStereoToAxialGap);
   }
}

G4double J4CDCParameterList::GetSuperLayerIR(G4int ilayer) const
{
   if (fIsOddSuperLyrOutermost || (!fIsOddSuperLyrOutermost && ilayer == 0)) {
      return (GetInnerSupportTubOR() + fSuperLayerInnerGap 
              + ilayer * GetSuperLayerThick(1));
   } else {
      return (GetInnerSupportTubOR() + fSuperLayerInnerGap 
              + fCellThickness // innermost small superlayer
              + (ilayer - 1) * GetSuperLayerThick(1));
   }
}

G4double J4CDCParameterList::GetSuperLayerOR(G4int ilayer) const
{
   return GetSuperLayerIR(ilayer) + GetSuperLayerThick(ilayer);
}

G4double J4CDCParameterList::GetUniformShieldLayerThick() const
{
   return (fCDCOuterRadius - fCDCInnerRadius 
           - 2 * fSupportTubThickness
           - fNlayers * fCellThickness) / fNlayers;
}



#endif
