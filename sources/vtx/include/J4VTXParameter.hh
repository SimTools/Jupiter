// $Id$
//=============================================
// Parameter of VTX
//
//
//=============================================

#define _VTXVISATT_	TRUE
#define _VTXLAYERVISATT_	FALSE
#define _VTXLADDERVISATT_	FALSE	
#define _VTXSENSORVISATT_ 	FALSE	
#define _SUBSTRATEVISATT_       FALSE 
#define _EPITAXIALVISATT_       FALSE 
#define _PIXELAREAVISATT_       FALSE 

#define _MASTERMATERIAL_ "Air"
#define _LAYERMATERIAL_ "Air"
#define _LADDERMATERIAL_ "Air"
#define _SENSORMATERIAL_ "Air"
#define _SUBSTRATEMATERIAL_ "Silicon"
#define _EPITAXIALMATERIAL_ "Silicon"
#define _PIXELAREAMATERIAL_ "Silicon"

  G4ThreeVector DXYZ_MARGIN;
  G4double R_MARGIN;


  G4ThreeVector DXYZ_SUBSTRATE;
  G4ThreeVector XYZ_SUBSTRATE;

  G4ThreeVector DXYZ_EPITAXIAL;
  G4ThreeVector XYZ_EPITAXIAL;

  G4ThreeVector DXYZ_PIXELAREA;
  G4ThreeVector XYZ_PIXELAREA;

  G4ThreeVector DXYZ_SENSOR;
  G4ThreeVector DXYZ_SENSOR_GAP;
  G4int NLAYER;

  G4int* NLADDER;
  G4int* NSENSOR;

  G4ThreeVector XYZ_SENSOR[10][10];

  G4double* TILT_LADDER;
  G4double* R_LAYER;
  G4double* RINNER_LAYER;
  G4double* ROUTER_LAYER;

  G4ThreeVector XYZ_LAYER;

  G4ThreeVector** DXYZ_LADDER;
  G4ThreeVector XYZ_LADDER[10][50];
  G4double ANGLE_LADDER[10][50];

  G4double* DR_LAYER;

  G4double VTXMASTER_INNER_R;
  G4double VTXMASTER_OUTER_R;
  G4double VTXMASTER_Z;
  G4double VTXMASTER_PHI;

G4int NZPIXEL;
G4int NXPIXEL;

G4double ZPIXELSIZE;
G4double XPIXELSIZE;
