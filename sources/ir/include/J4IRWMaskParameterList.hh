// J4IRWMaskParameterList.hh
//
#ifndef __J4IRWMASKPARAMETERLIST__
#define __J4IRWMASKPARAMETERLIST__
//********************************************************************
//* ---------------------
//* J4IRWMaskParameterList.hh
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
#include "J4IRWSiCALParameterList.hh"
#include "J4IRCH2MaskParameterList.hh"

// ====================================================================
// ----------------
// class definition
// ----------------

class J4IRWMaskParameterList : public J4VParameterList
{
private:
  static J4IRWMaskParameterList *fgInstance;

public:
  J4IRWMaskParameterList(const G4String& name);
  virtual ~J4IRWMaskParameterList();
  virtual void PrintParameterList(){};
  static J4IRWMaskParameterList *GetInstance();

public:
  //*
  //* Set/GetFunctions
  //*

  inline void SetWMaskMaterial(G4String mat) {fWMaskMaterial=mat;}
  inline G4String GetWMaskMaterial() const { return fWMaskMaterial;}

  // Color
  inline G4Color GetWMaskColor() const { return *fWMaskColor; }
  inline void SetWMaskColor(G4Color *c) { fWMaskColor =c; }

  // VisAtt  
  inline G4bool GetWMaskVisAtt() const { return fWMaskVisAtt; }
  inline void SetWMaskVisAtt(G4bool b) { fWMaskVisAtt=b; }


  inline G4double GetMargin() const { return fMargin;}
  inline void SetMargin(G4double m) {fMargin=m;}

  inline G4double GetWMask1ZPosition() const 
  { return ( J4IRParameterList::GetInstance()->GetIRSupportInnerRadius()/
      std::tan(J4IRParameterList::GetInstance()->GetIRThetaMax())+GetMargin()); }
  inline G4double GetWMask2ZLength() const 
  { return fch2List->GetCH2MaskZPosition()-fbpList->GetBPENDZPosition(); }
  inline G4double GetWMask2ZPosition() const 
  { return fbpList->GetBPENDZPosition();}
  inline G4double GetWMask2Radius() const 
  { return fbpList->GetBPDrumRadius()+fbpList->GetBPDrumThick();}
  inline G4double GetWMask2Thick() const
  { return J4IRParameterList::GetInstance()->GetIRSupportInnerRadius()-GetWMask2Radius(); }
  inline G4double GetWMask1Thick() const { return fWMask1Thick; }
  inline void SetWMask1Thick(G4double t) { fWMask1Thick=t; }
  inline G4double GetWMask1Radius() const 
  { return J4IRParameterList::GetInstance()->GetIRSupportInnerRadius()-GetWMask1Thick();}
  inline G4double GetWMask1ZLengthA() const
  { return fwsiList->GetWSiCAL2ZPosition()-GetWMask1ZPosition();}
  inline G4double GetWMask1ZLengthB() const
  { return J4IRParameterList::GetInstance()->GetIRSupportInnerRadius()/
      std::tan(J4IRParameterList::GetInstance()->GetIRThetaMax()-50.*mrad)
      -GetWMask1ZPosition();}
  inline G4double GetWMask1ZLength() const
  { return ( GetWMask1ZLengthA() < GetWMask1ZLengthB() ?
	     GetWMask1ZLengthA() : GetWMask1ZLengthB() ) ; }
  inline G4bool IsWMask1Valid() const
  { return (GetWMask1ZLength() >0 ? TRUE : FALSE ); }
  inline G4bool IsWSiCAL2Valid() const
  { return IsWMask1Valid(); }

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
  J4IRWSiCALParameterList* fwsiList;
  J4IRCH2MaskParameterList* fch2List;

  // Materials
  G4String fWMaskMaterial;

  // Visual Attributes
  G4bool fWMaskVisAtt;

  // Visual Color
  G4Color* fWMaskColor;
  //
  // Geomrtries             (example)
  //      1) Size      --   fDxyz , fDr
  //      2) Position  --   fxyz  , fr
  // 

  G4double fMargin;
  G4double fWMask1Thick;

};

#endif

