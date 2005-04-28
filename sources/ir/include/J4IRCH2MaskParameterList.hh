// J4IRCH2MaskParameterList.hh
//
#ifndef __J4IRCH2MASKPARAMETERLIST__
#define __J4IRCH2MASKPARAMETERLIST__
//********************************************************************
//* ---------------------
//* J4IRCH2MaskParameterList.hh
//* ---------------------
//* (Description)
//*     Parameter class for IR.
//*     Define Geomtrical parameters for IR here.
//*
//* (Update Record)
//*     2002/11/19  T.Aso   Original version.
//********************************************************************

#include "G4Material.hh"
#include "G4Color.hh"
#include "G4ThreeVector.hh"
#include "J4VParameterList.hh"
#include "J4IRParameterList.hh"
#include "J4IRBPParameterList.hh"
#include "J4IRQC1ParameterList.hh"


// ====================================================================
// ----------------
// class definition
// ----------------

class J4IRCH2MaskParameterList : public J4VParameterList
{
private:
  static J4IRCH2MaskParameterList *fgInstance;
public:
  J4IRCH2MaskParameterList(const G4String& name);
  virtual ~J4IRCH2MaskParameterList();
  virtual void PrintParameterList(){};
  static J4IRCH2MaskParameterList *GetInstance();

public:
  //*
  //* Set/GetFunctions
  //*
  inline void SetDrMargin(G4double m){ frMargin = m; }
  inline G4double GetDrMargin() const { return frMargin; }
  inline void SetDzMargin(G4double m){ fzMargin = m; }
  inline G4double GetDzMargin() const { return fzMargin; }

  // Color
  inline G4Color GetCH2MaskColor() const { return *fCH2MaskColor; }
  inline void SetCH2MaskColor(G4Color *c) { fCH2MaskColor =c; }
  // VisAtt  
  inline G4bool GetCH2MaskVisAtt() const { return fCH2MaskVisAtt; }
  inline void SetCH2MaskVisAtt(G4bool b) { fCH2MaskVisAtt=b; }

  inline G4double GetCH2MaskRadius() const
  { return fbpList->GetBPENDRadius()+fbpList->GetBPENDThick()+GetDrMargin(); }
  inline G4double GetCH2MaskThick() const
  { return fqc1List->GetQC1Radius()+fqc1List->GetQC1Thick()
      -GetCH2MaskRadius()+GetDrMargin();}
  inline G4double GetCH2MaskZLength() const { return fCH2MaskZLength; }
  inline void SetCH2MaskZLength(G4double zlen) { fCH2MaskZLength=zlen; }
  inline void SetCH2MaskMaterial(G4String mat) {fCH2MaskMaterial=mat;}
  inline G4String GetCH2MaskMaterial() const { return fCH2MaskMaterial;}
  inline G4double GetCH2MaskZPosition() const 
  { return fqc1List->GetQC1ZPosition()-GetCH2MaskZLength() -GetDzMargin();}

private:
  virtual void SetMaterials();
  virtual void SetVisAttributes();
  virtual void SetColors();
  virtual void SetParameters();
  virtual void SetDefaults();
  virtual void BuildParameters();

private:
  // IRParameterList
  //  J4IRParameterList*   fList;
  J4IRBPParameterList* fbpList;
  J4IRQC1ParameterList* fqc1List;

  // Materials
  G4String fCH2MaskMaterial;

  // Visual Attributes
  G4bool fCH2MaskVisAtt;

  // Visual Color
  G4Color* fCH2MaskColor;
  //
  // Geomrtries             (example)
  //      1) Size      --   fDxyz , fDr
  //      2) Position  --   fxyz  , fr
  // 
  G4double frMargin;
  G4double fzMargin;
  G4double fCH2MaskZLength;

};

#endif

