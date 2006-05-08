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
  inline G4double GetCLXOuterR()         const ; 
  inline G4double GetCLXInnerR()         const ;
  inline G4double GetCLXInnerHalfZ()     const ;
  inline G4double GetCLXOuterHalfZ()     const ;
  inline G4double GetCLXDeltaPhi()       const { return fCLXDeltaPhi     ; }
  inline G4double GetCLXPhiOffset()      const { return fCLXPhiOffset    ; }
  inline G4int    GetNTraps()            const { return fNTraps          ; }
  inline G4double GetTrapDeltaPhi()      const { return fTrapDeltaPhi    ; }
  inline G4double GetLayerTolerance()    const { return fLayerTolerance  ; }
  inline G4double GetPhiTolerance()      const { return fPhiTolerance    ; }
  inline G4double GetBarrelEndcapGap()   const { return fBarrelEndcapGap ; }
  
  //*Barrel ------------------------------------------------------------
  inline G4double GetBarrelOuterR()      const ;
  inline G4double GetBarrelInnerR()      const ;
  inline G4double GetBarrelThickness()   const ;
  inline G4double GetBarrelHalfZ()       const { return fBarrelHalfZ     ; }
  inline G4double GetBarrelDeltaPhi()    const { return fBarrelDeltaPhi  ; }
  inline G4double GetBarrelPhiOffset()   const { return fBarrelPhiOffset ; }

  //*Endcap ------------------------------------------------------------
  inline G4double GetEndcapFrontZ()      const { return fEndcapFrontZ    ; }
  inline G4double GetEndcapOuterR()      const ;
  inline G4double GetEndcapInnerR()      const { return fEndcapInnerR    ; } 
  inline G4double GetEndcapDeltaPhi()    const { return fEndcapDeltaPhi  ; }
  inline G4double GetEndcapPhiOffset()   const { return fEndcapPhiOffset ; }
  inline G4double GetEndcapThickness()   const ;
  
  //*EM ----------------------------------------------------------------
  inline G4int    GetEMNSubLayers()      const { return fEMNSubLayers    ; }  
  inline G4int    GetEMNLayers()         const { return fEMNLayers       ; }
  inline G4double GetEMYmax()            const ;
  inline G4double GetEMThickness()       const ;
  inline G4double GetEMLayerThickness()  const ;
  inline G4double GetEMHalfZ()           const ;
  inline G4double GetEMEndcapFrontZ()    const ;
  inline G4double GetEMEndcapYmax()      const ;
  inline G4double GetEMAbsLayerThickness()    const { return fEMAbsLayerThickness    ; }
  inline G4double GetEMActiveLayerThickness() const { return fEMActiveLayerThickness ; }  
  inline G4double GetEMFlexLayerThickness()   const { return fEMFlexLayerThickness   ; }
  
  //*HD ---------------------------------------------------------------
  inline G4int    GetHDNSubLayers()      const { return fHDNSubLayers    ; }  
  inline G4int    GetHDNLayers()         const { return fHDNLayers       ; }
  inline G4double GetHDYmax()            const ;
  inline G4double GetHDThickness()       const ;
  inline G4double GetHDLayerThickness()  const ;
  inline G4double GetHDHalfZ()           const ;
  inline G4double GetHDEndcapFrontZ()    const ;
  inline G4double GetHDAbsLayerThickness()    const { return fHDAbsLayerThickness    ; }
  inline G4double GetHDActiveLayerThickness() const { return fHDActiveLayerThickness ; }  
  inline G4double GetHDFlexLayerThickness()   const { return fHDFlexLayerThickness   ; }
  
  //*Cell --------------------------------------------------------------
  inline G4double GetCellSize()          const { return fCellSize        ; }

  //*Maximum number of cells, strips ----------------------------------
  inline G4int    GetEMNCells()          const { return fEMNCells        ; }
  inline G4int    GetHDNCells()          const { return fHDNCells        ; }
  inline G4int    GetEMNStrips()         const { return fEMNStrips       ; }
  inline G4int    GetHDNStrips()         const { return fHDNStrips       ; }
  inline G4int    GetMaxNStrips()        const { return fMaxNStrips      ; }
  inline G4int    GetMaxNCells()         const { return fMaxNCells       ; }

  //* Nubmer of types of EM/HD, Barrel/Endcap
  inline G4int    GetNIsEM()             const { return fNIsEM           ; }  
  inline G4int    GetNIsBarrel()         const { return fNIsBarrel       ; }
  
  //*Materials ---------------------------------------------------------
  inline G4String GetCLXMaterial()          const { return fCLXMaterial           ; }
  inline G4String GetBlockMaterial()        const { return fBlockMaterial         ; }
  inline G4String GetLayerMaterial()        const { return fLayerMaterial         ; }
  inline G4String GetEMAbsLayerMaterial()   const { return fEMAbsLayerMaterial    ; }
  inline G4String GetHDAbsLayerMaterial()   const { return fHDAbsLayerMaterial    ; }
  inline G4String GetEMActiveLayerMaterial()const { return fEMActiveLayerMaterial ; }
  inline G4String GetHDActiveLayerMaterial()const { return fHDActiveLayerMaterial ; }
  inline G4String GetEMFlexLayerMaterial()  const { return fEMFlexLayerMaterial   ; }
  inline G4String GetHDFlexLayerMaterial()  const { return fHDFlexLayerMaterial   ; }
  inline G4String GetTrapStripMaterial()    const { return fTrapStripMaterial     ; }
  inline G4String GetStripMaterial()        const { return fStripMaterial         ; }  
  inline G4String GetEMCellMaterial()       const { return fEMCellMaterial        ; }
  inline G4String GetHDCellMaterial()       const { return fHDCellMaterial        ; }
  
  //*VisAtt ------------------------------------------------------------
  inline G4bool   GetCLXVisAtt()          const { return fCLXVisAtt          ; }
  inline G4bool   GetEMVisAtt()           const { return fEMVisAtt           ; }
  inline G4bool   GetHDVisAtt()           const { return fHDVisAtt           ; }
  inline G4bool   GetLayerVisAtt()        const { return fLayerVisAtt        ; }
  inline G4bool   GetSubLayerVisAtt()     const { return fSubLayerVisAtt     ; }
  inline G4bool   GetTrapStripVisAtt()    const { return fTrapStripVisAtt    ; }
  inline G4bool   GetStripVisAtt()        const { return fStripVisAtt        ; }  
  inline G4bool   GetCellVisAtt()         const { return fCellVisAtt         ; }

  //*Color  ------------------------------------------------------------
  inline G4Color  GetCLXColor()           const { return fCLXColor           ; }
  inline G4Color  GetEMColor()            const { return fEMColor            ; }
  inline G4Color  GetHDColor()            const { return fHDColor            ; }
  inline G4Color  GetLayerColor()         const { return fLayerColor         ; }
  inline G4Color  GetSubLayerColor()      const { return fSubLayerColor      ; }
  inline G4Color  GetTrapStripColor()     const { return fTrapStripColor     ; }
  inline G4Color  GetStripColor()         const { return fStripColor         ; }
  inline G4Color  GetCellColor()          const { return fCellColor          ; }
  
  //
  //* Setters
  //
  //*Color ------------------------------------------------------------
  inline void SetCLXColor         ( const G4Color &c ) { fCLXColor          = c ; }
  inline void SetEMColor          ( const G4Color &c ) { fEMColor           = c ; }
  inline void SetHDColor          ( const G4Color &c ) { fHDColor           = c ; }
  inline void SetLayerColor       ( const G4Color &c ) { fLayerColor        = c ; }
  inline void SetSubLayerColor    ( const G4Color &c ) { fSubLayerColor     = c ; }
  inline void SetTrapStripColor   ( const G4Color &c ) { fTrapStripColor    = c ; }
  inline void SetStripColor       ( const G4Color &c ) { fStripColor        = c ; }  
  inline void SetCellColor        ( const G4Color &c ) { fCellColor         = c ; }
  
private:

  virtual void      SetMaterials();
  virtual void      SetVisAttributes();
  virtual void      SetColors();
  virtual void      SetParameters();
  
private:
  
  static J4CLXParameterList *fgInstance;

  //* CLX
  G4double fCLXDeltaPhi;
  G4double fCLXPhiOffset;
  G4int    fNTraps;
  G4double fTrapDeltaPhi;
  G4double fLayerTolerance;
  G4double fPhiTolerance;
  G4double fBarrelEndcapGap;
  
  //* Barrel
  G4double fBarrelHalfZ;
  G4double fBarrelDeltaPhi;
  G4double fBarrelPhiOffset;
  
  //* Endcap
  G4double fEndcapFrontZ;
  G4double fEndcapInnerR;
  G4double fEndcapDeltaPhi;
  G4double fEndcapPhiOffset;
  
  //* EM
  G4double fEMThickness;
  G4int    fEMNLayers;
  G4int    fEMNSubLayers;
  G4double fEMAbsLayerThickness;
  G4double fEMActiveLayerThickness;
  G4double fEMFlexLayerThickness;
  
  //* HD
  G4double fHDThickness;
  G4int    fHDNLayers;
  G4int    fHDNSubLayers;
  G4double fHDAbsLayerThickness;
  G4double fHDActiveLayerThickness;
  G4double fHDFlexLayerThickness;
  
  //* Cell
  G4double fCellSize;

  //* Maximum nubmer of cells, strips
  G4int    fEMNCells;
  G4int    fHDNCells;
  G4int    fEMNStrips;
  G4int    fHDNStrips;
  G4int    fMaxNCells;
  G4int    fMaxNStrips;

  //* Number of types for EM/HD, Barerl/Endap
  G4int    fNIsEM;
  G4int    fNIsBarrel;
  
  //* Material
  G4String fCLXMaterial;
  G4String fBlockMaterial;
  G4String fLayerMaterial;
  G4String fEMAbsLayerMaterial;
  G4String fHDAbsLayerMaterial;
  G4String fEMActiveLayerMaterial;
  G4String fHDActiveLayerMaterial;
  G4String fEMFlexLayerMaterial;
  G4String fHDFlexLayerMaterial;
  G4String fTrapStripMaterial;
  G4String fStripMaterial;
  G4String fEMCellMaterial;
  G4String fHDCellMaterial;
  
  //* visatt
  G4bool   fCLXVisAtt;
  G4bool   fEMVisAtt;
  G4bool   fHDVisAtt;
  G4bool   fLayerVisAtt;
  G4bool   fSubLayerVisAtt;
  G4bool   fTrapStripVisAtt;
  G4bool   fStripVisAtt;
  G4bool   fCellVisAtt;
  
  //* color 
  G4Color  fCLXColor;
  G4Color  fEMColor;
  G4Color  fHDColor;
  G4Color  fLayerColor;
  G4Color  fSubLayerColor;
  G4Color  fTrapStripColor;
  G4Color  fStripColor;
  G4Color  fCellColor;
  
};

//=========================================================
//* inline functions

inline G4double J4CLXParameterList::GetCLXInnerR() const
{
  return J4ParameterList::GetInstance()->GetCALInnerR();
}

inline G4double J4CLXParameterList::GetCLXOuterR() const
{
  return J4ParameterList::GetInstance()->GetCALOuterR();
}

inline G4double J4CLXParameterList::GetCLXInnerHalfZ() const
{
  return J4ParameterList::GetInstance()->GetCALInnerHalfZ();
}

inline G4double J4CLXParameterList::GetCLXOuterHalfZ() const
{
  return J4ParameterList::GetInstance()->GetCALOuterHalfZ();
}

inline G4double J4CLXParameterList::GetBarrelInnerR() const
{
  return GetCLXInnerR();
}

inline G4double J4CLXParameterList::GetBarrelOuterR() const
{
  return GetCLXOuterR();
}

inline G4double J4CLXParameterList::GetEndcapOuterR() const
{
  return GetCLXOuterR();
}

inline G4double J4CLXParameterList::GetBarrelThickness() const
{
  return GetEMThickness() + GetHDThickness();
}

inline G4double J4CLXParameterList::GetEndcapThickness() const
{
  return GetEMThickness() + GetHDThickness();
}

inline G4double J4CLXParameterList::GetEMThickness() const 
{
  return GetEMLayerThickness() * GetEMNLayers();
}

inline G4double J4CLXParameterList::GetHDThickness() const 
{
  return GetHDLayerThickness() * GetHDNLayers();
}

inline G4double J4CLXParameterList::GetEMHalfZ() const
{
  return GetBarrelHalfZ();
}

inline G4double J4CLXParameterList::GetHDHalfZ() const
{
  return GetBarrelHalfZ() + GetEMThickness();
}

inline G4double J4CLXParameterList::GetEMEndcapFrontZ() const
{
  return GetEndcapFrontZ();
}

inline G4double J4CLXParameterList::GetHDEndcapFrontZ() const
{
  return GetEndcapFrontZ() + GetEMThickness();
}

inline G4double J4CLXParameterList::GetEMYmax() const 
{
  return GetCLXInnerR() + GetEMThickness();
}

inline G4double J4CLXParameterList::GetEMEndcapYmax() const 
{
  return GetCLXInnerR() + GetEMThickness() - GetBarrelEndcapGap();
}

inline G4double J4CLXParameterList::GetHDYmax() const 
{
  return GetEMYmax() + GetHDThickness();
}

inline G4double J4CLXParameterList::GetEMLayerThickness() const 
{
#if 0
  return GetEMAbsLayerThickness() + GetEMActiveLayerThickness();
#else
  return GetEMAbsLayerThickness() + GetEMActiveLayerThickness() + GetEMFlexLayerThickness();
#endif
}

inline G4double J4CLXParameterList::GetHDLayerThickness() const 
{
#if 0
  return GetHDAbsLayerThickness() + GetHDActiveLayerThickness(); 
#else
  return GetHDAbsLayerThickness() + GetHDActiveLayerThickness() + GetHDFlexLayerThickness(); 
#endif
}

#endif
