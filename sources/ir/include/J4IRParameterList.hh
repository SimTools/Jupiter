// J4IRParameterList.hh
//
#ifndef __J4IRPARAMETERLIST__
#define __J4IRPARAMETERLIST__
//********************************************************************
//* ---------------------
//* J4IRParameterList.hh
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


// ====================================================================
// ----------------
// class definition
// ----------------

class J4IRParameterList : public J4VParameterList
{

protected :

  J4IRParameterList(const G4String &name);

public:
  virtual ~J4IRParameterList();
  virtual void PrintParameterList(){};

public:
  //*
  //* Set/GetFunctions
  //*

  inline G4bool IsCompact() 
  { // G4cout << "ASOASO " << GetCrossAngle()/mrad << G4endl;  
    return ( abs(GetCrossAngle()) > 9.*mrad ? TRUE : FALSE);}
  inline G4bool IsPairMonitorSD()
  { return fPairMonSD; }
  inline void SetPairMonitorSD(G4bool log){ fPairMonSD = log; }

  // Materials
  inline void SetIRMaterial(G4String mat) {fIRMaterial=mat;}
  inline G4String GetIRMaterial() const { return fIRMaterial;}

  // Margin for avoiding volume intersection.
  inline void SetDxyzMarginSize(G4ThreeVector size){fDxyzMargin=size;}
  inline void SetDrMarginSize(G4double size){fDrMargin=size;}
  inline G4ThreeVector GetDxyzMarginSize()const { return fDxyzMargin;}
  inline G4double SetDrMarginSize()const{return fDrMargin;}

  // Color
  inline G4Color GetIRColor() const { return *fIRColor; }
  // VisAtt  
  inline G4bool GetIRVisAtt() const { return fIRVisAtt; }

  //   Crossing Angle
  inline G4double GetCrossAngle() const { return fCrossAngle;} 
  inline void SetCrossAngle(G4double angle) { fCrossAngle=angle;} 
  //   L* position of QC1
  inline G4double GetLStar() const { return fLStar;} 
  inline void SetLStar(G4double z) { fLStar=z;} 
  //   Be Beam pipe 
  inline G4double GetBeamPipeRadius()const { return fBPRadiusSmall;}
  inline void    SetBeamPipeRadius(G4double r){fBPRadiusSmall = r;}
  inline G4double GetBeamPipeThick()const { return fBPBeThick;}
  inline void    SetBeamPipeThick(G4double t){fBPBeThick = t;}
  //   Max Z Length of IR region
  inline G4double GetIRZMax() const { return fIRZMax;}
  inline void SetIRZMax(G4double zmax) {fIRZMax=zmax;}
  //   Z Length of Middle part of IR region
  inline G4double GetIRZMid()const{return fIRZMid;}
  inline void SetIRZMid(G4double zmid ){fIRZMid=zmid;}
  //   Inner radius os Support tube
  inline G4double GetIRSupportInnerRadius()const{return fIRSupportTubeInnerR;}
  inline void SetIRSupportInnerRadius(G4double r){fIRSupportTubeInnerR=r;}
  //   Minimum inner radius of IR
  inline G4double GetIRMinimumRadius()const{return fIRMinimumRadius;}
  inline void SetIRMinimumRadius(G4double r){fIRMinimumRadius=r;}
  //   Maximum theta angle
  inline G4double GetIRThetaMax()const{return fIRThetaMax;}
  inline void SetIRThetaMax(G4double thetamax){fIRThetaMax=thetamax;}
  //   IR Box Size
  inline G4ThreeVector GetDxyzIRBox()const{ return fDxyzIRBox; }
  inline void SetDxyzIRBox(G4ThreeVector size){fDxyzIRBox = size;}

  // Caluculated Values
  inline G4double GetIRBeamPipeZLength()const{ 
    return 2.*(tan(M_PI/2.-GetIRThetaMax())*GetIRMinimumRadius());}
  inline G4double GetIRDrumFaceZPosition()const{
    return tan(M_PI/2.-GetIRThetaMax())*GetIRSupportInnerRadius();}
  inline G4double GetIRConeZLength()const{
    return GetIRDrumFaceZPosition()-GetIRBeamPipeZLength()/2.;}
  inline G4double GetIRDrumZLength()const{
    return GetIRZMid()-GetIRDrumFaceZPosition();}
  inline G4double GetIRConeZPosition()const{
    return GetIRBeamPipeZLength()/2+GetIRConeZLength()/2;}
  inline G4double GetIRDrumZPosition() const{
    return GetIRConeZPosition()+GetIRConeZLength()/2.+GetIRDrumZLength()/2.;}
  inline G4double GetIRBoxZPosition()const{
        return GetIRZMid()+GetDxyzIRBox().z();}
    //    return GetIRDrumZPosition()+GetIRDrumZLength()/2.+GetDxyzIRBox().z()/2.;}


  static J4IRParameterList * GetInstance();

private:
  virtual void SetMaterials();
  virtual void SetVisAttributes();
  virtual void SetColors();
  virtual void SetSensitiveDetector();
  virtual void SetParameters();
  virtual void SetDefaults();
  virtual void BuildParameters();

private:

  static J4IRParameterList *fgInstance;

  // Materials
  G4String fIRMaterial;

  // Visual Attributes
  G4bool fIRVisAtt;

  // Visual Color
  G4Color* fIRColor;
  //
  // Geomrtries             (example)
  //      1) Size      --   fDxyz , fDr
  //      2) Position  --   fxyz  , fr
  // 

  G4ThreeVector fDxyzMargin;
  G4double      fDrMargin;

  // PairMonitorSD
  G4bool   fPairMonSD;

  //   Crossing Angle
  G4double fCrossAngle; 
  //   L*  ( Position of QC1 )
  G4double fLStar;
  //   Be Beam Pipe
  G4double fBPRadiusSmall;  
  G4double fBPBeThick;
  //   Max Z Length of IR region
  G4double fIRZMax;
  //   Z Length of Middle part of IR region
  G4double fIRZMid;
  //   Inner radius of Support tube
  G4double fIRSupportTubeInnerR;
  //   Minimum inner radius ( equal to outer radius of beam pipe at IP.)
  G4double fIRMinimumRadius;
  //   Maximum theta angle
  G4double fIRThetaMax;
  //   IR Box Size
  G4ThreeVector fDxyzIRBox;
};

#endif

