// J4VTXParameterList.cc
//*************************************************************************
//* --------------------
//* J4VTXParameterList
//* --------------------
//* (Description)
//*     Class for describing his/her detector compornents.
//*
//* (Update Record)
//*     2002/11/19  T.Aso   Original version.
//*************************************************************************

#include "J4VTXParameterList.hh"

#define __VTXACFAREPCONF__  0
#define __VTXSTDCONF__      1
#define __VTX5LYRCONF__     0

//=====================================================================
//* constructor -------------------------------------------------------

J4VTXParameterList::J4VTXParameterList()
{
  SetSensitiveDetector();  // SensitiveDetector must be called at first.
  SetParameters();
  SetMaterials();
  SetVisAttributes();
  SetColors();
}
//=====================================================================
//* destructor -------------------------------------------------------

J4VTXParameterList::~J4VTXParameterList()
{

  delete fNLadders;  
  delete fNSensors;
  delete frLayer;
  delete frInnerLayer;
  delete frOuterLayer;
  delete fDxyzLadder;
  delete fDrLayer;

  delete  fVTXColor;
  delete  fLayerColor;
  delete  fLadderColor;
  delete  fSensorColor;
  delete  fSubstrateColor;
  delete  fEpitaxialColor;
  delete  fPixelAreaColor;

}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4VTXParameterList::SetMaterials()
{
#if 1
  fVTXMaterial       = "Air";
  fLayerMaterial     = "Silicon";
  //fLayerMaterial     = "Air";
  fLadderMaterial    = "Air";
  fSensorMaterial    = "Silicon";
  fSubstrateMaterial = "Silicon";
  fEpitaxialMaterial = "Silicon";
  fPixelAreaMaterial = "Silicon";
#else
  fVTXMaterial       = "vacuum";
  fLayerMaterial     = "vacuum";
  fLadderMaterial    = "vacuum";
  fSensorMaterial    = "vacuum";
  fSubstrateMaterial = "vacuum";
  fEpitaxialMaterial = "vacuum";
  fPixelAreaMaterial = "vacuum";
#endif

}

//=====================================================================
//* SetSensitiveDetector-----------------------------------------------
void J4VTXParameterList::SetSensitiveDetector()
{
  SetLayerSD(TRUE);    // if TRUE, Layer specific configuration.
  SetLadderSD(FALSE);
  SetSensorSD(FALSE);
  SetPixelAreaSD(FALSE);
  SetPixelSD(FALSE);
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4VTXParameterList::SetParameters()
{
  SetDefaults();
  BuildParameters();
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4VTXParameterList::SetDefaults()
{

  // Margin for avoiding volume intersection.
  SetDxyzMarginSize(G4ThreeVector(0.01*mm,0.01*mm,0.01*mm));
  SetDrMarginSize(0.5*mm);

  G4double  sensorDZ = 330*micrometer;
  G4double  epitaxDZ = 30*micrometer;

  // Sensor Size 
  SetSensorSize(G4ThreeVector(1.25*cm,sensorDZ,5.0*cm));
  // Substrate Size
  SetDySubstrate(sensorDZ-epitaxDZ);
  // Epitaxial
  SetDyEpitaxial(epitaxDZ);

  // Number of Pixels
  SetNzPixels(2000);
  SetNxPixels(500);

#if __VTXACFAREPCONF__
  // Number of laysers
  SetNLayers(3);
  // Number of sensors in a ladder in a layer
  G4int nsensors[] = {  3,  6,  9 };
  // Number of ladders in a layer
  G4int nladders[] = { 16, 24, 32 };
  // Radius of the layer
  G4double layerradius[] = { 2.5*cm, 5.0*cm, 7.5*cm };
#endif
#if __VTXSTDCONF__  
  // Number of laysers
  SetNLayers(4);
  // Number of sensors in a ladder in a layer
  G4int nsensors[] = {  2,  3,  4,  5 };
  // Number of ladders in a layer
  G4int nladders[] = { 16, 24, 32, 40 };
  // Radius of the layer
  G4double layerradius[] = { 2.4*cm, 3.6*cm, 4.8*cm, 6.0*cm };
#endif
#if __VTX5LYRCONF__
  SetNLayers(5);
  G4int nsensors[] = {  2,  3,  4,  5 ,6};
  G4int nladders[] = { 8, 16, 24, 32 ,40};
  G4double layerradius[] = { 1.5*cm, 2.7*cm, 3.9*cm, 5.1*cm ,6.3*cm};
#endif

  // Cover angle of VTX Mother Volume  ( not Used.)
  SetVTXAngle(205.*milliradian);

  // Tilt of ladders
  SetTilt(10*deg);

  // Set parameters 
  for ( G4int ilayer = 0; ilayer < GetNLayers() ; ilayer++ ){
    SetNLadders(ilayer,nladders[ilayer]);
    SetNSensors(ilayer,nsensors[ilayer]);
    SetRLayer(ilayer,layerradius[ilayer]);
  }

  // MaxAllowedStep
  //SetMaxAllowedStep(0.001*mm);
  SetMaxAllowedStep(0.01*mm);
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4VTXParameterList::BuildParameters()
{
  //  PixelArea
  fDxyzPixelArea = 
     G4ThreeVector(fDxyzEpitaxial.x(),fDxyzEpitaxial.y(),fDxyzEpitaxial.z());

  fxyzSubstrate = G4ThreeVector(0.*mm,-fDxyzEpitaxial.y()/2.0,0.*mm);
  fxyzEpitaxial = G4ThreeVector(0.*mm,+fDxyzSubstrate.y()/2.0,0.*mm);

  // For Computing the size of ladders and layers to match the sensor size
  fDxyzLadder = new G4ThreeVector*[fNLayers];
  fDrLayer = new G4double[fNLayers];
  frInnerLayer = new G4double[fNLayers];
  frOuterLayer = new G4double[fNLayers];
  
  for ( G4int ilayer = 0; ilayer < fNLayers; ilayer++){
    for ( G4int isensor = 0; isensor < fNSensors[ilayer] ; isensor++){
      fxyzSensor[ilayer][isensor] = G4ThreeVector(
          0.*mm,
	  -0.5*(fDxyzSensor.y()/2.-fDxyzEpitaxial.y()/2),
	fDxyzSensor.z()
   	 * ((G4double)(isensor+1) - (G4double)( fNSensors[ilayer]+1 )/2.));
    }

    fDxyzLadder[ilayer] = new G4ThreeVector(
             fDxyzSensor.x()+2.*fDxyzMargin.x(),
             fDxyzSensor.y()+2.*fDxyzMargin.y(),
	     fDxyzSensor.z()*fNSensors[ilayer]+2.*fDxyzMargin.z() );

    G4double theta = twopi/fNLadders[ilayer];
    for ( G4int iladder = 0; iladder < fNLadders[ilayer]; iladder++){
      fxyzLadder[ilayer][iladder].set(
             frLayer[ilayer]*cos(iladder*theta),
             frLayer[ilayer]*sin(iladder*theta),
             0.*mm);
      fangleLadder[ilayer][iladder] = -halfpi-theta*iladder+ftiltLadder;
    }

    if ( !IsLayerSD() ){
      frInnerLayer[ilayer] = 
	frLayer[ilayer]-fDxyzLadder[ilayer]->x()/2.*sin(ftiltLadder);
      frOuterLayer[ilayer] = 
	frLayer[ilayer]
	+(fDxyzLadder[ilayer]->x()+2.*fDxyzLadder[ilayer]->y())*sin(ftiltLadder);
    }else{
      frInnerLayer[ilayer] = frLayer[ilayer];
      frOuterLayer[ilayer] = frLayer[ilayer]+fDxyzSensor.y();
    }

  }

  frVTXInner = frInnerLayer[0]-fDrMargin;
  frVTXOuter = frOuterLayer[fNLayers-1]+fDrMargin;
  fzVTX      = fDxyzLadder[fNLayers-1]->z()+2.*fDxyzMargin.z();
}

//=====================================================================
//* SetVtsAttributes ------------------------------------------------------
void J4VTXParameterList::SetVisAttributes()
{
  fVTXVisAtt       = FALSE;
  fLayerVisAtt     = TRUE;
  fLadderVisAtt    = FALSE;
  fSensorVisAtt    = FALSE;
  fSubstrateVisAtt = FALSE;
  fEpitaxialVisAtt = FALSE;
  fPixelAreaVisAtt = FALSE;
  fPixelVisAtt = FALSE;
}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4VTXParameterList::SetColors()
{
    fVTXColor       = new G4Color(0.5,0.5,0.5);  // gray
    fLayerColor     = new G4Color(0.5,0.5,0.5);  // gray
    fLadderColor    = new G4Color(1.0,1.0,0.0);  // yellow
    fSensorColor    = new G4Color(0.0,0.0,1.0);  // blue
    fSubstrateColor = new G4Color( 0.0,1.0,1.0); // cyan
    fEpitaxialColor = new G4Color(0.0,1.0,0.0);  // green
    fPixelAreaColor = new G4Color(1.0,0.0,1.0);  // magenta
}


