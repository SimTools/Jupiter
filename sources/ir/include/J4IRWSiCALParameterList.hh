// J4IRWSiCALParameterList.hh
//
#ifndef __J4IRWSICALPARAMETERLIST__
#define __J4IRWSICALPARAMETERLIST__
//********************************************************************
//* ---------------------
//* J4IRWSiCALParameterList.hh
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

// ====================================================================
// ----------------
// class definition
// ----------------

class J4IRWSiCALParameterList : public J4VParameterList
{
private:
  static J4IRWSiCALParameterList *fgInstance;

public:
  J4IRWSiCALParameterList(const G4String& name);
  virtual ~J4IRWSiCALParameterList();
  virtual void PrintParameterList(){};
  static J4IRWSiCALParameterList *GetInstance();

public:
  //*
  //* Set/GetFunctions
  //*

  inline void SetWSiCALMaterial(G4String mat) {fWSiCALMaterial=mat;}
  inline G4String GetWSiCALMaterial() const { return fWSiCALMaterial;}

  // Color
  inline G4Color GetWSiCALColor() const { return *fWSiCALColor; }
  inline void SetWSiCALColor(G4Color *c) { fWSiCALColor =c; }

  // VisAtt  
  inline G4bool GetWSiCALVisAtt() const { return fWSiCALVisAtt; }
  inline void SetWSiCALVisAtt(G4bool b) { fWSiCALVisAtt=b; }

  inline G4int GetWSiCALNLayer() const { return fWSiCALNLayer;}
  inline void SetWSiCALNLayer(G4int n) { fWSiCALNLayer = n;}
  inline G4double GetWSiCAL2ZLength() const { return fWSiCAL2ZLength;}
  inline void SetWSiCAL2ZLength(G4double zl) {fWSiCAL2ZLength=zl;}

  inline G4double GetWSiCAL1Radius() const 
  { return fbpList->GetBPDrumRadius()+fbpList->GetBPDrumThick(); }
  inline G4double GetWSiCAL1Thick() const
  { return GetWSiCAL1Radius()/
    std::tan(50.*mrad)*std::tan(J4IRParameterList::GetInstance()->GetIRThetaMax())-GetWSiCAL1Radius();}
  inline G4double GetWSiCAL1ZLength() const
  { return J4IRParameterList::GetInstance()->GetIRSupportInnerRadius()/
    std::tan(J4IRParameterList::GetInstance()->GetIRThetaMax())
      -GetWSiCAL1Radius()/std::tan(50.*mrad); }
  inline G4double GetWSiCAL1ZPosition() const
  { return GetWSiCAL1Radius()/std::tan(50.*mrad); }

  inline G4double GetWSiCAL2Radius() const
  { return fbpList->GetBPDrumRadius()+fbpList->GetBPDrumThick(); }
  inline G4double GetWSiCAL2Thick() const
  { return J4IRParameterList::GetInstance()->GetIRSupportInnerRadius()-GetWSiCAL2Radius();}
  inline G4double GetWSiCAL2ZPosition() const
  { return fbpList->GetBPENDZPosition() - GetWSiCAL2ZLength(); }

private:
  virtual void SetMaterials();
  virtual void SetVisAttributes();
  virtual void SetColors();
  virtual void SetParameters();
  virtual void SetDefaults();
  virtual void BuildParameters();

private:
  // IRParameterList
  // J4IRParameterList* fList;
  J4IRBPParameterList* fbpList;

  // Materials
  G4String fWSiCALMaterial;

  // Visual Attributes
  G4bool fWSiCALVisAtt;

  // Visual Color
  G4Color* fWSiCALColor;
  //
  // Geomrtries             (example)
  //      1) Size      --   fDxyz , fDr
  //      2) Position  --   fxyz  , fr
  // 

  G4int fWSiCALNLayer;
  G4double fWSiCAL2ZLength;

};

#endif

