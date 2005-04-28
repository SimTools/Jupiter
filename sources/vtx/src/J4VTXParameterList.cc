// J4vtxparameterlist.cc
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
#include "J4ParameterTable.hh"
#include <vector>

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
  fVTXMaterial       = J4ParameterTable::GetValue("J4VTX.Material","Air");
  fLayerMaterial     = J4ParameterTable::GetValue("J4VTX.Material.Layer","Silicon");
  //fLayerMaterial     = "Air";
  fLadderMaterial    = J4ParameterTable::GetValue("J4VTX.Material.Ladder","Air");
  fSensorMaterial    = J4ParameterTable::GetValue("J4VTX.Material.Sensor","Silicon");
  fSubstrateMaterial = J4ParameterTable::GetValue("J4VTX.Material.Substrate","Silicon");
  fEpitaxialMaterial = J4ParameterTable::GetValue("J4VTX.Material.Epitaxial","Silicon");
  fPixelAreaMaterial = J4ParameterTable::GetValue("J4VTX.Material.PixelArea","Silicon");

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
  /*
  SetLayerSD(TRUE);    // if TRUE, Layer specific configuration.
  SetLadderSD(FALSE);
  SetSensorSD(FALSE);
  SetPixelAreaSD(FALSE);
  SetPixelSD(FALSE);
  */
  SetLayerSD(J4ParameterTable::GetValue("J4VTX.Activate.LayerSD",TRUE));
  SetLadderSD(J4ParameterTable::GetValue("J4VTX.Activate.LadderSD",FALSE));
  SetSensorSD(J4ParameterTable::GetValue("J4VTX.Activate.SensorSD",FALSE));
  SetPixelAreaSD(J4ParameterTable::GetValue("J4VTX.Activate.PixelAreaSD",FALSE));
  SetPixelSD(J4ParameterTable::GetValue("J4VTX.Activate.PixelSD",FALSE));

  if( !IsLayerSD() && !IsLadderSD() && !IsSensorSD() && !IsPixelAreaSD() && !IsPixelSD() ) {
    std::cerr << "!! Error in J4VTXParameterList;;SetSensitiveDetetor" << std::endl;
    std::cerr << "All Sensitive detector in VTX are off. ";
    std::cerr << "At least one SD has to be activated." << std::endl;
    exit(-1);
  }

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

  //  G4double  sensorDZ = 330*micrometer;
  //  G4double  epitaxDZ = 30*micrometer;

  G4double sensorWidth = J4ParameterTable::GetValue("J4VTX.Sensor.Width",1.25)*cm;
  G4double sensorLength = J4ParameterTable::GetValue("J4VTX.Sensor.Length",5.0)*cm;
  G4double sensorDZ = J4ParameterTable::GetValue("J4VTX.Sensor.Thickness",0.0330)*cm;
  G4double epitaxDZ = J4ParameterTable::GetValue("J4VTX.Epitax.Thickness",0.0030)*cm;


  // Sensor Size 
  //  SetSensorSize(G4ThreeVector(1.25*cm,sensorDZ,5.0*cm));
  SetSensorSize(G4ThreeVector(sensorWidth,sensorDZ,sensorLength));
  // Substrate Size
  SetDySubstrate(sensorDZ-epitaxDZ);
  // Epitaxial
  SetDyEpitaxial(epitaxDZ);

  // Number of Pixels
  //  SetNzPixels(2000);
  //  SetNxPixels(500);
  SetNzPixels(J4ParameterTable::GetValue("J4VTX.NzPixels",2000));
  SetNxPixels(J4ParameterTable::GetValue("J4VTX.NxPixels",500));

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
  //  SetNLayers(4);
  // Number of sensors in a ladder in a layer
  //  G4int nsensors[] = {  2,  3,  4,  5 };
  // Number of ladders in a layer
  //  G4int nladders[] = { 16, 24, 32, 40 };
  // Radius of the layer
  //  G4double layerradius[] = { 2.4*cm, 3.6*cm, 4.8*cm, 6.0*cm };
#endif
#if __VTX5LYRCONF__
  SetNLayers(5);
  G4int nsensors[] = {  2,  3,  4,  5 ,6};
  G4int nladders[] = { 8, 16, 24, 32 ,40};
  G4double layerradius[] = { 1.5*cm, 2.7*cm, 3.9*cm, 5.1*cm ,6.3*cm};
#endif
  int nlayers=J4ParameterTable::GetValue("J4VTX.NLayers",4);
  SetNLayers(nlayers);
  // Number of sensors in a ladder in a layer
  //  G4int nsensors[] = {  2,  3,  4,  5 };
  std::vector<int> nsensors=J4ParameterTable::GetIValue("J4VTX.NSensors","2 3 4 5",nlayers);
  // Number of ladders in a layer
  //  G4int nladders[] = { 16, 24, 32, 40 };
  std::vector<int> nladders=J4ParameterTable::GetIValue("J4VTX.NLadders","16 24 32 40",nlayers);
  // Radius of the layer
  //  G4double layerradius[] = { 2.4*cm, 3.6*cm, 4.8*cm, 6.0*cm };
  std::vector<double> layerradius=J4ParameterTable::GetDValue("J4VTX.Layer.Radius","2.4 3.6 4.8 6.0",nlayers);
  for(int iii=0;iii<nlayers;iii++){ layerradius[iii]*=cm; }

  // Cover angle of VTX Mother Volume  ( not Used.)
  SetVTXAngle(205.*milliradian);

  // Tilt of ladders
  //  SetTilt(10*deg);
  SetTilt(J4ParameterTable::GetValue("J4VTX.TiltAngle",10.0*deg));

  // Set parameters 
  for ( G4int ilayer = 0; ilayer < GetNLayers() ; ilayer++ ){
    SetNLadders(ilayer,nladders[ilayer]);
    SetNSensors(ilayer,nsensors[ilayer]);
    SetRLayer(ilayer,layerradius[ilayer]);
  }

  // MaxAllowedStep
  //SetMaxAllowedStep(0.001*mm);
  //  SetMaxAllowedStep(0.01*mm);
  SetMaxAllowedStep(J4ParameterTable::GetValue("J4VTX.MaxAllowedStep",0.001)*cm);

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
             frLayer[ilayer]*std::cos(iladder*theta),
             frLayer[ilayer]*std::sin(iladder*theta),
             0.*mm);
      fangleLadder[ilayer][iladder] = -halfpi-theta*iladder+ftiltLadder;
    }

    if ( !IsLayerSD() ){
      frInnerLayer[ilayer] = 
	frLayer[ilayer]-fDxyzLadder[ilayer]->x()/2.*std::sin(ftiltLadder);
      frOuterLayer[ilayer] = 
	frLayer[ilayer]
	+(fDxyzLadder[ilayer]->x()+2.*fDxyzLadder[ilayer]->y())*std::sin(ftiltLadder);
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

  fVTXVisAtt = J4ParameterTable::GetValue("J4VTX.VisAtt",false);
  fLayerVisAtt     = J4ParameterTable::GetValue("J4VTX.VisAtt.Layer",true);
  fLadderVisAtt    = J4ParameterTable::GetValue("J4VTX.VisAtt.Ladder",false);
  fSensorVisAtt    = J4ParameterTable::GetValue("J4VTX.VisAtt.Sensor",false); 
  fSubstrateVisAtt = J4ParameterTable::GetValue("J4VTX.VisAtt.Subtrate",false); 
  fEpitaxialVisAtt = J4ParameterTable::GetValue("J4VTX.VisAtt.Epitaxial",false); 
  fPixelAreaVisAtt = J4ParameterTable::GetValue("J4VTX.VisAtt.PixelArea",false); 
  fPixelVisAtt = J4ParameterTable::GetValue("J4VTX.VisAtt.Pixel",false); 

}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4VTXParameterList::SetColors()
{
  std::vector<double> col;
  col=J4ParameterTable::GetDValue("J4VTX.Color","0.5 0.5 0.5 1.0",4); // gray
  fVTXColor       = new G4Color(col[0], col[1], col[2], col[3]);  
  col=J4ParameterTable::GetDValue("J4VTX.Color.Layer","0.5 0.5 0.5 1.0",4); //gray
  fLayerColor     = new G4Color(col[0], col[1], col[2], col[3]);  
  col=J4ParameterTable::GetDValue("J4VTX.Color.Ladder","1.0 1.0 0.0 1.0",4);// yellow
  fLadderColor    = new G4Color(col[0], col[1], col[2], col[3]);  
  col=J4ParameterTable::GetDValue("J4VTX.Color.Sensor","1.0 1.0 0.0 1.0",4);//blue
  fSensorColor    = new G4Color(col[0], col[1], col[2], col[3]);  
  col=J4ParameterTable::GetDValue("J4VTX.Color.Subtrate","0.0 1.0 1.0 1.0",4);//cyan
  fSubstrateColor = new G4Color(col[0], col[1], col[2], col[3]);
  col=J4ParameterTable::GetDValue("J4VTX.Color.Epitaxial","0.0 1.0 0.0 1.0",4);//green
  fEpitaxialColor = new G4Color(col[0], col[1], col[2], col[3]);  // green
  col=J4ParameterTable::GetDValue("J4VTX.Color.PixelArea","1.0 0.0 1.0 1.0",4);//magenta
  fPixelAreaColor = new G4Color(col[0], col[1], col[2], col[3]);  // magenta
}


