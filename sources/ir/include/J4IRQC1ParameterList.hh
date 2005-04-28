// J4IRQC1ParameterList.hh
//
#ifndef __J4IRQC1PARAMETERLIST__
#define __J4IRQC1PARAMETERLIST__
//********************************************************************
//* ---------------------
//* J4IRQC1ParameterList.hh
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

// ====================================================================
// ----------------
// class definition
// ----------------

class J4IRQC1ParameterList : public J4VParameterList
{
private:
  static J4IRQC1ParameterList *fgInstance;
public:
  J4IRQC1ParameterList(const G4String& name);
  virtual ~J4IRQC1ParameterList();
  virtual void PrintParameterList(){};
  static J4IRQC1ParameterList *GetInstance();

public:
  //*
  //* Set/GetFunctions
  //*

  inline void SetQC1Material(G4String mat) {fQC1Material=mat;}
  inline void SetQC1SUSMaterial(G4String m){ fQC1SUSMaterial = m;}
  inline void SetQC1CollarMaterial(G4String m) {fQC1CollarMaterial=m;}
  inline void SetQC1CoilMaterial(G4String m) 
  {fQC1CoilMaterial=m;}
  inline void SetQC1CoolingMaterial(G4String m) { fQC1CoolingMaterial=m;}
  inline void SetQC1VacuumVesselMaterial(G4String m)
  {fQC1VacuumVesselMaterial=m;}
  inline void SetQC1ThermalMaterial(G4String m) {fQC1ThermalMaterial=m;}
  inline void SetQC1ThermalVesselMaterial(G4String m)
  {fQC1ThermalVesselMaterial=m;}
  inline void SetQC1HeMaterial(G4String m) {fQC1HeMaterial=m;}
  inline void SetQC1HeVesselMaterial(G4String m) {fQC1HeVesselMaterial=m;}

  inline G4String GetQC1Material() const { return fQC1Material;}
  inline G4String GetQC1SUSMaterial( )const{ return  fQC1SUSMaterial;}
  inline G4String GetQC1CollarMaterial( )const { return fQC1CollarMaterial;}
  inline G4String GetQC1CoilMaterial( ) const
  { return fQC1CoilMaterial;}
  inline G4String GetQC1CoolingMaterial( ) const { return fQC1CoolingMaterial;}
  inline G4String GetQC1VacuumVesselMaterial( ) const
  { return fQC1VacuumVesselMaterial;}
  inline G4String GetQC1ThermalMaterial( )const { return fQC1ThermalMaterial;}
  inline G4String GetQC1ThermalVesselMaterial( )const
  { return fQC1ThermalVesselMaterial;}
  inline G4String GetQC1HeMaterial( )const { return fQC1HeMaterial;}
  inline G4String GetQC1HeVesselMaterial() const{ return fQC1HeVesselMaterial;}

  // Color
  inline G4Color GetQC1Color() const { return *fQC1Color; }
  inline void SetQC1Color(G4Color *c) { fQC1Color =c; }
  // VisAtt  
  inline G4bool GetQC1VisAtt() const { return fQC1VisAtt; }
  inline void SetQC1VisAtt(G4bool b) { fQC1VisAtt=b; }

  inline G4double GetQC1Radius() const  { return fQC1Radius;}
  inline G4double GetQC1Thick() const   { return fQC1Thick;}
  inline G4double GetQC1ZLength() const { return fQC1ZLength; }
  inline void SetQC1Radius(G4double r)  { fQC1Radius = r ;}
  inline void SetQC1Thick(G4double t)   { fQC1Thick = t;}
  inline void SetQC1ZLength(G4double zlen) { fQC1ZLength=zlen; }
  inline G4double GetQC1ZPosition() const { 
    return J4IRParameterList::GetInstance()->GetLStar(); }


  inline G4double GetQC1SUSRadius() const {return fQC1SUSRadius; }
  inline void SetQC1SUSRadius(G4double r) { fQC1SUSRadius = r; }
  inline G4double GetQC1SUSThick() const {return fQC1SUSThick; }
  inline void SetQC1SUSThick(G4double t) { fQC1SUSThick = t; }

  inline G4int GetQC1NCollar() const { return fQC1NCollar;}
  inline void SetQC1NCollar(G4int n) { fQC1NCollar = n;}
  inline G4double GetQC1CollarRadius() const {return fQC1CollarRadius; }
  inline void SetQC1CollarRadius(G4double r) { fQC1CollarRadius = r; }
  inline G4double GetQC1CollarThick() const {return fQC1CollarThick; }
  inline void SetQC1CollarThick(G4double t) { fQC1CollarThick = t; }
  inline G4double GetQC1CollarPhi() const {return fQC1CollarPhi; }
  inline void SetQC1CollarPhi(G4double p) { fQC1CollarPhi = p; }
  inline G4double GetQC1CollarDPhi() const {return fQC1CollarDPhi; }
  inline void SetQC1CollarDPhi(G4double dp) { fQC1CollarDPhi = dp; }

  inline G4int GetQC1NCoil() const { return fQC1NCoil;}
  inline void SetQC1NCoil(G4int n) { fQC1NCoil = n;}
  inline G4double GetQC1CoilPhi() const {return fQC1CoilPhi; }
  inline void SetQC1CoilPhi(G4double p) { fQC1CoilPhi = p; }
  inline G4double GetQC1CoilDPhi() const {return fQC1CoilDPhi; }
  inline void SetQC1CoilDPhi(G4double dp) { fQC1CoilDPhi = dp; }
  inline G4double GetQC1CoilRadius() const { return GetQC1CollarRadius(); }
  inline G4double GetQC1CoilThick() const { return GetQC1CollarThick(); }

  inline G4double GetQC1CoolingRadius() const { return GetQC1Radius(); }
  inline G4double GetQC1CooilngThick() const 
  { return GetQC1CollarRadius() - GetQC1CoolingRadius();}

  inline G4double GetQC1ThermalThick() const { return fQC1ThermalThick;}
  inline void SetQC1ThermalThick(G4double t) {fQC1ThermalThick = t;}
  inline G4double GetQC1ThermalRadius()const 
  { return GetQC1VacuumVesselRadius()+GetQC1VacuumVesselThick(); }

  inline G4double GetQC1ThermalVesselThick() const 
  { return fQC1ThermalVesselThick;}
  inline void SetQC1ThermalVesselThick(G4double t)  
  {fQC1ThermalVesselThick = t;}
  inline G4double GetQC1ThermalVesselRadius() const
  { return GetQC1ThermalRadius()+GetQC1ThermalThick(); }

  inline G4double GetQC1VacuumVesselThick() const 
  { return fQC1VacuumVesselThick;}
  inline void SetQC1VacuumVesselThick(G4double t)  
  {fQC1VacuumVesselThick = t;}
  inline G4double GetQC1VacuumVesselRadius() const 
  { return GetQC1CoolingRadius();}

  inline G4double GetQC1HeThick() const { return fQC1HeThick;}
  inline void SetQC1HeThick(G4double t)  {fQC1HeThick = t;}
  inline G4double GetQC1HeRadius() const 
  { return GetQC1ThermalVesselRadius()+GetQC1ThermalVesselThick(); }

  inline G4double GetQC1HeVesselThick() const { return fQC1HeVesselThick;}
  inline void SetQC1HeVesselThick(G4double t) {fQC1HeVesselThick = t;}
  inline G4double GetQC1HeVesselRadius() const
  { return GetQC1HeRadius()+GetQC1HeThick(); }

private:
  virtual void SetMaterials();
  virtual void SetVisAttributes();
  virtual void SetColors();
  virtual void SetParameters();
  virtual void SetDefaults();
  virtual void BuildParameters();

  void SetCompact();

private:
  // IRParameterList
  //  J4IRParameterList* fList;

  // Materials
  G4String fQC1Material;
  G4String fQC1SUSMaterial;
  G4String fQC1CollarMaterial;
  G4String fQC1CoilMaterial;
  G4String fQC1CoolingMaterial;
  G4String fQC1VacuumVesselMaterial;
  G4String fQC1ThermalMaterial;
  G4String fQC1ThermalVesselMaterial;
  G4String fQC1HeMaterial;
  G4String fQC1HeVesselMaterial;

  // Visual Attributes
  G4bool fQC1VisAtt;

  // Visual Color
  G4Color* fQC1Color;
  //
  // Geomrtries             (example)
  //      1) Size      --   fDxyz , fDr
  //      2) Position  --   fxyz  , fr
  // 

  G4double fQC1Radius;
  G4double fQC1Thick;
  G4double fQC1ZLength;

  G4double fQC1SUSRadius;
  G4double fQC1SUSThick;

  G4int fQC1NCollar;  
  G4double fQC1CollarRadius;
  G4double fQC1CollarThick;

  G4double fQC1CollarPhi; 
  G4double fQC1CollarDPhi;

  G4int fQC1NCoil;
  G4double fQC1CoilPhi;
  G4double fQC1CoilDPhi;

  G4double fQC1ThermalThick;
  G4double fQC1ThermalVesselThick;
  G4double fQC1VacuumVesselThick;
  G4double fQC1HeThick;
  G4double fQC1HeVesselThick;

};

#endif

