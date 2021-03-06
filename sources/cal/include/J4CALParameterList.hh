// $Id$
#ifndef __J4CALPARAMETERLIST__
#define __J4CALPARAMETERLIST__
//********************************************************************
//* ---------------------------
//* J4CALParameterList.hh
//* ---------------------------
//* (Description)
//* 	ParameterList class for CAL
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
 
class J4CALParameterList : public J4VParameterList 
{

 protected: 

   J4CALParameterList(const G4String &name);

 public:


   virtual ~J4CALParameterList();

   static J4CALParameterList *GetInstance();
   
   virtual void    PrintParameterList(){};

   virtual void    ShowTowerParameters();

   virtual void    DrawTowerParameters();

   //
   // Getters
   //

   //*CAL --------------------------------------------------------------
   inline G4double GetCALOuterR()         const; 
   inline G4double GetCALInnerR()         const;
   inline G4double GetCALInnerHalfZ()     const;
   inline G4double GetCALOuterHalfZ()     const;
   inline G4double GetCALDeltaPhi()       const { return fCALDeltaPhi;     }
   inline G4double GetCALPhiOffset()      const { return fCALPhiOffset;    }

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

   //*Cone --------------------------------------------------------------
   inline G4int    GetNcones()            const; 
   inline G4int    GetNbarrelCones()      const; 
   inline G4int    GetNendcapCones()      const; 

   //*Tower -------------------------------------------------------------
   inline G4double GetBarrelTowerFrontRho() const { return fBarrelTowerFrontRho; }
   inline G4double GetEndcapTowerFrontZ()   const { return fEndcapTowerFrontZ;   }
   inline G4int    GetConstNTowers()        const { return fConstNTowers;        }

   //*EM ----------------------------------------------------------------
   inline G4double GetEMThickness()       const;

   //*HD ---------------------------------------------------------
   inline G4double GetHDThickness()       const;

   //*IsBarrel
   inline G4int   GetNIsBarrel()          const { return fNIsBarrel; }
  
   //*IsEM
   inline G4int   GetNIsEM()              const { return fNIsEM; }

   //*MiniCone --------------------------------------------------
   //inline G4int    GetNMiniCones()            const; 

  //*MiniCone and MiniTower (# of clones) ---------------------------------
   inline G4int GetEMMiniConeNClones()  const { return fEMMiniConeNClones; }
   inline G4int GetEMMiniTowerNClones() const { return fEMMiniTowerNClones; }
   inline G4int GetHDMiniConeNClones()  const { return fHDMiniConeNClones; }
   inline G4int GetHDMiniTowerNClones() const { return fHDMiniTowerNClones; }

   //*Layer
   inline G4double GetEMLayerThickness()      const; 
   inline G4double GetHDLayerThickness()      const;
   inline G4int    GetEMNLayers()             const { return fEMNLayers; } 
   inline G4int    GetHDNLayers()             const { return fHDNLayers; } 

   //*SubLayer
   inline G4int    GetNSubLayers()          const { return fNSubLayers; } 
   
   //*AbsLayer
   inline G4double GetEMAbsLayerThickness() const { return fEMAbsLayerThickness; }  
   inline G4double GetHDAbsLayerThickness() const { return fHDAbsLayerThickness; }  

   //*ActiveLayer
   inline G4double GetEMActiveLayerThickness() const { return fEMActiveLayerThickness; }  
   inline G4double GetHDActiveLayerThickness() const { return fHDActiveLayerThickness; }  

   //*Materials ---------------------------------------------------------
   inline G4String GetCALMaterial()          const { return fCALMaterial;    }
   inline G4String GetBarrelMaterial()       const { return fBarrelMaterial; }
   inline G4String GetEndcapMaterial()       const { return fEndcapMaterial; }
   inline G4String GetConeMaterial()         const { return fConeMaterial;   }
   inline G4String GetTowerMaterial()        const { return fTowerMaterial;  }
   inline G4String GetEMMaterial()           const { return fEMMaterial;     }
   inline G4String GetHDMaterial()           const { return fHDMaterial;     }
   inline G4String GetMiniConeMaterial()     const { return fMiniConeMaterial; }
   inline G4String GetMiniTowerMaterial()    const { return fMiniTowerMaterial; }
   inline G4String GetLayerMaterial()        const { return fLayerMaterial; }
   inline G4String GetEMAbsLayerMaterial()   const { return fEMAbsLayerMaterial; }
   inline G4String GetHDAbsLayerMaterial()   const { return fHDAbsLayerMaterial; }
   inline G4String GetEMActiveLayerMaterial()const { return fEMActiveLayerMaterial; }
   inline G4String GetHDActiveLayerMaterial()const { return fHDActiveLayerMaterial; }


   //*VisAtt ------------------------------------------------------------
   inline G4bool   GetCALVisAtt()         const { return fCALVisAtt;      }
   inline G4bool   GetBarrelVisAtt()      const { return fBarrelVisAtt;   }
   inline G4bool   GetEndcapVisAtt()      const { return fEndcapVisAtt;   }
   inline G4bool   GetConeVisAtt()        const { return fConeVisAtt;     }
   inline G4bool   GetTowerVisAtt()       const { return fTowerVisAtt;    }
   inline G4bool   GetEMVisAtt()          const { return fEMVisAtt;       }
   inline G4bool   GetHDVisAtt()          const { return fHDVisAtt;       }
   inline G4bool   GetMiniConeVisAtt()    const { return fMiniConeVisAtt; }
   inline G4bool   GetMiniTowerVisAtt()   const { return fMiniTowerVisAtt;}
   inline G4bool   GetLayerVisAtt()       const { return fLayerVisAtt;    }
   inline G4bool   GetSubLayerVisAtt()    const { return fSubLayerVisAtt; }

   //*Color  ------------------------------------------------------------
   inline G4Color  GetCALColor()          const { return fCALColor;       }
   inline G4Color  GetBarrelColor()       const { return fBarrelColor;    }
   inline G4Color  GetEndcapColor()       const { return fEndcapColor;    }
   inline G4Color  GetConeColor()         const { return fConeColor;      }
   inline G4Color  GetTowerColor()        const { return fTowerColor;     }
   inline G4Color  GetEMColor()           const { return fEMColor;        }
   inline G4Color  GetHDColor()           const { return fHDColor;        }
   inline G4Color  GetMiniConeColor()     const { return fMiniConeColor;  }
   inline G4Color  GetMiniTowerColor()    const { return fMiniTowerColor; }
   inline G4Color  GetLayerColor()        const { return fLayerColor;   }
   inline G4Color  GetSubLayerColor()     const { return fSubLayerColor;   }

   //
   // Setters
   //

   inline void SetCALColor      (const G4Color &c) { fCALColor        = c; }
   inline void SetBarrelColor   (const G4Color &c) { fBarrelColor     = c; }
   inline void SetEndcapColor   (const G4Color &c) { fEndcapColor     = c; }
   inline void SetConeColor     (const G4Color &c) { fConeColor       = c; }
   inline void SetTowerColor    (const G4Color &c) { fTowerColor      = c; }
   inline void SetEMColor       (const G4Color &c) { fEMColor         = c; }
   inline void SetHDColor       (const G4Color &c) { fHDColor         = c; }
   inline void SetMiniConeColor (const G4Color &c) { fMiniConeColor  = c; }
   inline void SetMiniTowerColor(const G4Color &c) { fMiniTowerColor = c; }
   inline void SetLayerColor    (const G4Color &c) { fLayerColor        = c; }
   inline void SetSubLayerColor (const G4Color &c) { fSubLayerColor     = c; }

 private:

   virtual void      SetMaterials();
   virtual void      SetVisAttributes();
   virtual void      SetColors();
   virtual void      SetParameters();

   static  G4int     EstimateNtowers(G4double length, 
                                     G4double width, 
                                     G4double lambdamin, 
                                     G4double lambdamax); 

   static  G4double  CalcNextTowerEdgeAngle(G4double length,
                                            G4double width,
                                            G4double lastlambda); 

  virtual void      SetTowerParameters( G4double startlambda,
                                        G4double endlambda,
                                        G4double length,
                                        G4double width,
                                        G4bool   isbarrel);

 public:

   class J4CALTowerParam {

     public: 

        J4CALTowerParam (G4double r, 
                         G4double centerlambda, 
                         G4double dlambda, 
                         G4double nominalsizeinphi,
                         G4double isbarrel) 
                         : fR(r), fCenterLambda(centerlambda), 
                          fDlambda(dlambda), fIsBarrel(isbarrel)
        {
           G4double radius;
           if (fIsBarrel) {
              radius   = J4CALParameterList::GetInstance()->GetBarrelTowerFrontRho(); 
           } else {
              G4double absangle = 0.5 * M_PI - std::fabs(centerlambda);  
              radius   = fR * std::sin(absangle);
           }

           G4double circumference = 2 * M_PI * radius; 
           fNphi = (G4int) (std::fabs(circumference) / nominalsizeinphi);
           fDphi = 2 * M_PI / fNphi;
        }
       
        ~J4CALTowerParam(){}  

        void ShowData() 
             {
                std::cerr << std::setprecision(5) 
                          << std::setw(10) << fIsBarrel
                          << std::setw(10) << fR
                          << std::setw(10) << fCenterLambda
                          << std::setw(10) << fDlambda
                          << std::setw(10) << 2 * fR * std::sin(0.5 * fDlambda)
                          << std::setw(10) << fNphi
                          << std::setw(10) << fDphi 
                          << std::setw(10) << 2 * fR * std::sin(0.5 * fDphi)
                          << std::endl;
              }

        inline G4bool     IsBarrel()   const { return fIsBarrel;     }
        inline G4double   GetR()       const { return fR;            }
        inline G4double   GetLambda()  const { return fCenterLambda; }
        inline G4int      GetNphi()    const { return fNphi;         }
        inline G4double   GetDphi()    const { return fDphi;         }
        inline G4double   GetDlambda() const { return fDlambda;      }
        inline G4double   GetDtheta()  const { return GetDlambda();  }
        inline G4double   GetTheta()   const { return 0.5 * M_PI - fCenterLambda; }
 

     private:

        G4double   fR;            //  Radius of front face 
        G4double   fCenterLambda; //  Azimutial angle of the center of tower from X-Y plane
        G4double   fDlambda;      //  Azimutial width  
        G4int      fNphi;         //  Number of segments in phi  
        G4double   fDphi;         //  Phi width  
        G4bool     fIsBarrel;     //  TRUE/FALSE = BarrelCAL/EndcapCAL 
   };

   typedef std::pair<G4double, J4CALTowerParam * > J4CALTowerParamPair; 
   typedef std::vector<J4CALTowerParamPair>        J4CALTowerParamVector; 

   J4CALTowerParamVector  GetTowerParamVector()  const { return fTowerParamVector; }
   J4CALTowerParam       *GetTowerParam(G4int i) const { return fTowerParamVector[i].second; }

 private:

   static J4CALParameterList *fgInstance;
   J4CALTowerParamVector      fTowerParamVector;

   // material
   G4String  fCALMaterial; 
   G4String  fBarrelMaterial; 
   G4String  fEndcapMaterial; 
   G4String  fConeMaterial; 
   G4String  fTowerMaterial; 
   G4String  fEMMaterial; 
   G4String  fHDMaterial; 
   G4String  fMiniConeMaterial;
   G4String  fMiniTowerMaterial;
   G4String  fLayerMaterial;
   G4String  fHDLayerMaterial;
   G4String  fEMAbsLayerMaterial;
   G4String  fHDAbsLayerMaterial;
   G4String  fEMActiveLayerMaterial;
   G4String  fHDActiveLayerMaterial;

   // visatt 
   G4bool    fCALVisAtt;
   G4bool    fBarrelVisAtt;
   G4bool    fEndcapVisAtt;
   G4bool    fConeVisAtt;
   G4bool    fTowerVisAtt;
   G4bool    fEMVisAtt;
   G4bool    fHDVisAtt;
   G4bool    fMiniConeVisAtt;
   G4bool    fMiniTowerVisAtt;
   G4bool    fLayerVisAtt;
   G4bool    fSubLayerVisAtt;

   // color 
   G4Color   fCALColor;
   G4Color   fBarrelColor;
   G4Color   fEndcapColor;
   G4Color   fConeColor;
   G4Color   fTowerColor;
   G4Color   fEMColor;
   G4Color   fHDColor;
   G4Color   fMiniConeColor;
   G4Color   fMiniTowerColor;
   G4Color   fLayerColor;
   G4Color   fSubLayerColor;

   // CAL
   G4double  fCALDeltaPhi;
   G4double  fCALPhiOffset;

   // Barrel 
   G4double  fBarrelHalfZ;
   G4double  fBarrelDeltaPhi;
   G4double  fBarrelPhiOffset;
   G4double  fBarrelCoverageAngle;

   // Endcap 
   G4double  fEndcapInnerR;
   G4double  fEndcapDeltaPhi;
   G4double  fEndcapPhiOffset;

   // Tower 
   G4double  fNominalBarrelTowerFrontSize;
   G4double  fNominalEndcapTowerFrontSize;
   G4double  fBarrelTowerFrontRho;
   G4double  fEndcapTowerFrontZ;
   G4int     fConstNTowers;

   // EM
   G4double  fEMThickness;

   // HD
   G4double  fHDThickness;

   // Barrel, endcap types for isBarrel
   G4int     fNIsBarrel;
  
   // EM HD types for isEM
   G4int     fNIsEM;

   // MiniCone
   G4int     fEMMiniConeNClones;
   G4int     fHDMiniConeNClones;
   
   // MiniTower
   G4int     fEMMiniTowerNClones;
   G4int     fHDMiniTowerNClones;

   // Layer
   G4double  fNLayers;
   G4int     fEMNLayers;
   G4int     fHDNLayers;
   
   // SubLayer
   G4int     fNSubLayers;
   // AbsLayer
   G4double   fEMAbsLayerThickness;
   G4double   fHDAbsLayerThickness;

   // ActiveLayer
   G4double   fEMActiveLayerThickness;
   G4double   fHDActiveLayerThickness;

};

//=========================================================
//* inline functions

G4double J4CALParameterList::GetCALInnerR() const
{
   return J4ParameterList::GetInstance()->GetCALInnerR();
}

G4double J4CALParameterList::GetCALOuterR() const
{
   return J4ParameterList::GetInstance()->GetCALOuterR();
}

G4double J4CALParameterList::GetCALInnerHalfZ() const
{
   return J4ParameterList::GetInstance()->GetCALInnerHalfZ();
}

G4double J4CALParameterList::GetCALOuterHalfZ() const
{
   return J4ParameterList::GetInstance()->GetCALOuterHalfZ();
}

G4double J4CALParameterList::GetBarrelOuterR() const
{
   return GetCALOuterR();
}

G4double J4CALParameterList::GetBarrelInnerR() const
{
   return GetCALInnerR();
}

G4double J4CALParameterList::GetEndcapOuterR() const
{
   return GetCALOuterR();
}

G4int J4CALParameterList::GetNcones() const 
{
   return (G4int)fTowerParamVector.size();
}

G4int J4CALParameterList::GetNbarrelCones() const 
{
   G4int count = 0;
   for (G4int i=0; i < GetNcones(); i++) {
      if (GetTowerParam(i)->IsBarrel()) count++;
   }
   return count;
}

G4int J4CALParameterList::GetNendcapCones() const 
{
   return GetNcones() - GetNbarrelCones(); 
}

G4double J4CALParameterList::GetEMThickness() const 
{
   return ( GetEMAbsLayerThickness() + GetEMActiveLayerThickness() ) * GetEMNLayers();
}
 
G4double J4CALParameterList::GetHDThickness() const 
{
   return ( GetHDAbsLayerThickness() + GetHDActiveLayerThickness() ) * GetHDNLayers();
}

G4double J4CALParameterList::GetEMLayerThickness() const 
{
   return GetEMAbsLayerThickness() + GetEMActiveLayerThickness();
}
 
G4double J4CALParameterList::GetHDLayerThickness() const 
{
   return GetHDAbsLayerThickness() + GetHDActiveLayerThickness(); 
}


#endif
