// J4VTXParameterList.hh
//
#ifndef __J4VTXPARAMETERLIST__
#define __J4VTXPARAMETERLIST__
//********************************************************************
//* ---------------------
//* J4VTXParameterList.hh
//* ---------------------
//* (Description)
//*     Parameter class for VTX.
//*     Define Geomtrical parameters for VTX here.
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

class J4VTXParameterList : public J4VParameterList
{

public:
  J4VTXParameterList();
  virtual ~J4VTXParameterList();
  virtual void PrintParameterList(){};

public:
  //*
  //* SetFunctions
  //*
  // Sensitive Detector
  inline void SetLayerSD(G4bool log) {fLayerSD = log; }
  inline void SetLadderSD(G4bool log) {fLadderSD = log; }
  inline void SetSensorSD(G4bool log) {fSensorSD = log; }
  inline void SetPixelAreaSD(G4bool log) { fPixelAreaSD = log; }
  inline void SetPixelSD(G4bool log) { fPixelSD = log; }

  inline void SetMaxAllowedStep(G4double step){ fStepSize = step; }

  inline G4double GetMaxAllowedStep(){ return fStepSize; }

  // Materials
  inline void SetVTXMaterial(G4String mat) {fVTXMaterial=mat;}
  inline void SetLayerMaterial(G4String mat){ fLayerMaterial=mat;}
  inline void SetLadderMaterial(G4String mat){fLadderMaterial=mat;}
  inline void SetSensorMaterial(G4String mat){ fSensorMaterial=mat;}
  inline void SetSubstrateMaterial(G4String mat){fSubstrateMaterial=mat;}
  inline void SetEpitaxialMaterial(G4String mat){fEpitaxialMaterial=mat;}
  inline void SetPixelAreaMaterial(G4String mat){fPixelAreaMaterial=mat;}

  // Margin for avoiding volume intersection.
  inline void SetDxyzMarginSize(G4ThreeVector size){fDxyzMargin=size;}
  inline void SetDrMarginSize(G4double size){fDrMargin=size;}
  // Sensor Size => Will be filled in fDxyzSensor
  inline void SetSensorSize(G4ThreeVector size){fDxyzSensor=size; }
  inline void SetDySubstrate(G4double size);
  inline void SetDyEpitaxial(G4double size);
  // Number of Pixels
  inline void SetNzPixels(G4int n){ fNzPixels=n; }
  inline void SetNxPixels(G4int n){ fNxPixels=n; }
  // Number of laysers
  inline void SetNLayers(G4int n);
  // Number of ladders in a layer
  inline void SetNLadders(G4int layer,G4int n){fNLadders[layer]=n; }
  // Number of sensors in a ladder in a layer
  inline void SetNSensors(G4int layer,G4int n){fNSensors[layer]=n; }
  // Radius of the layers
  inline void SetRLayer(G4int layer,G4double r){frLayer[layer]=r; }
  // Tilt of ladders
  inline void SetTilt(G4double t){ftiltLadder=t; }
  // Cover angle of VTX Master (not used)
  inline void SetVTXAngle(G4double a){ fVTXAngle=a;}

  //*
  //* Get Functions
  //*

  inline G4ThreeVector GetDxyzMarginSize() const { return fDxyzMargin;}

  // Sensitive Detector
  inline G4bool IsLayerSD() const { return fLayerSD; }
  inline G4bool IsLadderSD() const { return fLadderSD; }
  inline G4bool IsSensorSD() const { return fSensorSD; }
  inline G4bool IsPixelAreaSD() const { return fPixelAreaSD; }
  inline G4bool IsPixelSD() const { return fPixelSD; }

  // Parameters
  inline G4int GetNLayers() const { return fNLayers; }
  inline G4int GetNLadders(G4int layer) const { return fNLadders[layer];}
  inline G4int GetNSensors(G4int layer) const { return fNSensors[layer];}
  inline G4int GetNxPixels() const { return fNxPixels; }
  inline G4int GetNzPixels() const { return fNzPixels; }

  // Geometorical parameters
  // Master
  inline G4double GetVTXInnerRadius() const { return frVTXInner; }
  inline G4double GetVTXOuterRadius() const { return frVTXOuter; }
  inline G4double GetVTXZLength() const { return fzVTX; }
  inline G4double GetVTXAngle() const { return fVTXAngle; }
  // Layer
  inline G4double GetLayerInnerRadius(G4int layer) 
    const  { return frInnerLayer[layer];};
  inline G4double GetLayerOuterRadius(G4int layer) 
    const  { return frOuterLayer[layer];};
  inline G4double GetLayerZLength(G4int layer)
  const { return (G4double)GetNSensors(layer)*GetSensorSize().z()+4.*GetDxyzMarginSize().z(); }
  //Ladder
  inline G4ThreeVector* GetLadderSize(G4int layer)
    const { return fDxyzLadder[layer]; };
  inline G4ThreeVector GetLadderPosition(G4int layer,G4int ladder)
    const { return fxyzLadder[layer][ladder]; };
  inline G4double GetLadderAngle(G4int layer,G4int ladder)
    const { return fangleLadder[layer][ladder]; };
  //  Sensor
  inline G4ThreeVector GetSensorSize() const { return fDxyzSensor;}
  inline G4ThreeVector GetSensorPosition(G4int layer,G4int sensor) 
    const { return fxyzSensor[layer][sensor];};
  // Substrate
  inline G4ThreeVector GetSubstrateSize() const { return fDxyzSubstrate;}  
  inline G4ThreeVector GetSubstratePosition() 
    const { return fxyzSubstrate;}  
  // Epitaxial
  inline G4ThreeVector GetEpitaxialSize() const { return fDxyzEpitaxial;}  
  inline G4ThreeVector GetEpitaxialPosition() 
    const { return fxyzEpitaxial;}  
  // PixelArea
  inline G4ThreeVector GetPixelAreaSize() const { return fDxyzPixelArea;}  
  inline G4ThreeVector GetPixelAreaPosition() 
    const { return fxyzPixelArea;}  
  // PixelArray
  inline G4ThreeVector GetPixelArraySize()
    const { return G4ThreeVector(fDxyzPixelArea.x(),
				 fDxyzPixelArea.y(),
				 fDxyzPixelArea.z()/(G4double)fNzPixels); };
  // Pixel
  inline G4ThreeVector GetPixelSize()  const { return G4ThreeVector(
			   fDxyzPixelArea.x()/(G4double)fNxPixels,
 			   fDxyzPixelArea.y(),
			   fDxyzPixelArea.z()/(G4double)fNzPixels); };

  // Material
  inline G4String GetVTXMaterial() const { return fVTXMaterial;}
  inline G4String GetLayerMaterial() const { return fLayerMaterial;}
  inline G4String GetLadderMaterial() const { return fLadderMaterial;}
  inline G4String GetSensorMaterial() const { return fSensorMaterial;}
  inline G4String GetSubstrateMaterial() const { return fSubstrateMaterial;}
  inline G4String GetEpitaxialMaterial() const { return fEpitaxialMaterial;}
  inline G4String GetPixelAreaMaterial() const { return fPixelAreaMaterial;}

  // Color
  inline G4Color GetVTXColor() const { return *fVTXColor; }
  inline G4Color GetLayerColor() const { return *fLayerColor; }
  inline G4Color GetLadderColor() const { return *fLadderColor; }
  inline G4Color GetSensorColor() const { return *fSensorColor; }
  inline G4Color GetSubstrateColor() const { return *fSubstrateColor; }
  inline G4Color GetEpitaxialColor() const { return *fEpitaxialColor; }
  inline G4Color GetPixelAreaColor() const { return *fPixelAreaColor; }

  // VisAtt  
  inline G4bool GetVTXVisAtt() const { return fVTXVisAtt; }
  inline G4bool GetLayerVisAtt() const { return fLayerVisAtt; }
  inline G4bool GetLadderVisAtt() const { return fLadderVisAtt; }
  inline G4bool GetSensorVisAtt() const { return fSensorVisAtt; }
  inline G4bool GetSubstrateVisAtt() const { return fSubstrateVisAtt; }
  inline G4bool GetEpitaxialVisAtt() const { return fEpitaxialVisAtt; }
  inline G4bool GetPixelAreaVisAtt() const { return fPixelAreaVisAtt; }
  inline G4bool GetPixelVisAtt() const { return fPixelVisAtt; }

private:
  virtual void SetMaterials();
  virtual void SetVisAttributes();
  virtual void SetColors();
  virtual void SetParameters();
  virtual void SetDefaults();
  virtual void BuildParameters();
  virtual void SetSensitiveDetector();

private:

  // Sensitive Detector
  G4bool fLayerSD;
  G4bool fLadderSD;
  G4bool fSensorSD;
  G4bool fPixelAreaSD;
  G4bool fPixelSD;
  
  // Materials
  G4String fVTXMaterial;
  G4String fLayerMaterial;
  G4String fLadderMaterial;
  G4String fSensorMaterial;
  G4String fSubstrateMaterial;
  G4String fEpitaxialMaterial;
  G4String fPixelAreaMaterial;

  // Visual Attributes
  G4bool fVTXVisAtt;
  G4bool fLayerVisAtt;
  G4bool fLadderVisAtt;
  G4bool fSensorVisAtt;
  G4bool fSubstrateVisAtt;
  G4bool fEpitaxialVisAtt;
  G4bool fPixelAreaVisAtt;
  G4bool fPixelVisAtt;

  // Visual Color
  G4Color* fVTXColor;
  G4Color* fLayerColor;
  G4Color* fLadderColor;
  G4Color* fSensorColor;
  G4Color* fSubstrateColor;
  G4Color* fEpitaxialColor;
  G4Color* fPixelAreaColor;

  //
  // Geomrtries             (example)
  //      1) Size      --   fDxyz , fDr
  //      2) Position  --   fxyz  , fr
  // 

  G4ThreeVector fDxyzMargin;
  G4double      fDrMargin;

  //   Substrate
  G4ThreeVector fDxyzSubstrate;
  G4ThreeVector fxyzSubstrate;
  //   Epitaxial
  G4ThreeVector fDxyzEpitaxial;
  G4ThreeVector fxyzEpitaxial;
  //   PixelArea
  G4ThreeVector fDxyzPixelArea;
  G4ThreeVector fxyzPixelArea;
  //   Sensor 
  G4ThreeVector fDxyzSensor;

  // Number of Layer
  G4int fNLayers;

  // Number of Ladders in a Layer
  G4int* fNLadders;
  // Number of Sensors in a Ladder
  G4int* fNSensors;

  // Position of Sensors in the Layer / in the Ladder
  //  G4ThreeVector fxyzSensor[10][10];
  G4ThreeVector fxyzSensor[10][200];

  // Tile of ladder;
  G4double ftiltLadder;

  // Radius of a layer
  G4double* frLayer;
  G4double* frInnerLayer;
  G4double* frOuterLayer;

  //  Size and Position of Ladders;
  //  G4ThreeVector fxyzLadder[10][50];
  //  G4double fangleLadder[10][50];
  G4ThreeVector fxyzLadder[10][200];
  G4double fangleLadder[10][200];
  G4ThreeVector** fDxyzLadder;

  //  dr of layer
  G4double* fDrLayer;

  //  Master volume
  G4double frVTXInner;
  G4double frVTXOuter;
  G4double fzVTX;
  G4double fVTXAngle;

  // Number of pixels;
  G4int fNzPixels;
  G4int fNxPixels;

  // Pixel Size
  G4double fDzPixel;
  G4double fDxPixel;

  // Limit Step Size
  G4double fStepSize;
};

//
inline void J4VTXParameterList::SetDySubstrate(G4double size)
{
  fDxyzSubstrate.setX(fDxyzSensor.x());
  fDxyzSubstrate.setY(size);
  fDxyzSubstrate.setZ(fDxyzSensor.z());
}
inline void J4VTXParameterList::SetDyEpitaxial(G4double size)
{
  fDxyzEpitaxial.setX(fDxyzSensor.x());
  fDxyzEpitaxial.setY(size);
  fDxyzEpitaxial.setZ(fDxyzSensor.z());
}
inline void J4VTXParameterList::SetNLayers(G4int n)
{ 
  fNLayers=n; 
  delete fNLadders;
  delete fNSensors;
  delete frLayer;
  fNLadders = new G4int[fNLayers];
  fNSensors = new G4int[fNLayers];
  frLayer = new G4double[fNLayers];
}
#endif

