// $Id$
//*************************************************************************
//* --------------------------
//* J4VTXROGeometry.cc
//* --------------------------
//* (Description)
//* 	
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#ifndef __HOSHINA__

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "J4Parameter.hh"
#include "J4VTXROGeometry.hh"
#include "J4ExpHall.hh"
#include "J4VTXDummySD.hh"

//#include "J4VTXDummySD.hh"


//************************************************************************
//---------------------
// Class Description
//---------------------
 
//=====================================================================
//* constructor -------------------------------------------------------

J4VTXROGeometry::J4VTXROGeometry(G4String name )
  : G4VReadOutGeometry(name)
{
#include "J4VTXParameter.icc"
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXROGeometry::~J4VTXROGeometry()
{
}

//=====================================================================
//* Construct   -------------------------------------------------------

G4VPhysicalVolume* J4VTXROGeometry::Build()
{
  return BuildAll();
}

G4VPhysicalVolume* J4VTXROGeometry::BuildAll()
{

 G4Material* dummyMat= new G4Material(name="dummyMat",
				 1.,1.*g/mole,1.*g/cm3);

 G4Box *ROWorldBox = new G4Box("ROWorldBox", _EXPHALLHALFX_,_EXPHALLHALFY_,_EXPHALLHALFZ_);
 G4LogicalVolume *ROWorldLog = new G4LogicalVolume(ROWorldBox, dummyMat,
                                                    "ROWorldLogical", 0, 0, 0);
 G4PVPlacement *ROWorldPhys = new G4PVPlacement(0,G4ThreeVector(),
						"ROWorldPhysical",
						ROWorldLog,
						0,false,0);

    G4LogicalVolume* masterLV = BuildMasterLV();
    G4LogicalVolume* sensorLV = BuildSensorLV();

    //VTX Layer
    // Install Layer       //
    for (G4int  layer = 0; layer < NLAYER ; layer++) {
      G4double rmin = RINNER_LAYER[layer];
      G4double rmax = ROUTER_LAYER[layer];
      G4double len  = VTXMASTER_Z/2.;
      G4Tubs* layerS=new G4Tubs("VTX_layer",rmin,rmax,len,0.*deg,360*deg );
      G4LogicalVolume* layerLV = new 
          G4LogicalVolume(layerS, dummyMat, "VTX_Layer"); 
      G4VPhysicalVolume* layerPhys = new G4PVPlacement(0,G4ThreeVector(),
                                                 layerLV,
                                                 "VTX_layer",
				       masterLV,false,layer);
      // Ladder
      G4int numOfLadders = NLADDER[layer];
      G4Box* ladderS =  new G4Box( "VTX_Ladder",DXYZ_LADDER[layer]->x()/2.,
				   DXYZ_LADDER[layer]->y()/2.,
				   DXYZ_LADDER[layer]->z()/2.);
      G4LogicalVolume* ladderLV=
	   new G4LogicalVolume(ladderS,dummyMat,"VTX_Ladder");


      // Sensor
      G4int numOfSensors = NSENSOR[layer];
	for( G4int sensor = 0; sensor<numOfSensors; sensor++){
	  G4VPhysicalVolume* asensorPhys = 
	    new G4PVPlacement(0,XYZ_SENSOR[layer][sensor],
			      sensorLV,
			      "VTX_Sensor",
			      ladderLV,false,sensor);
	}

      for ( G4int ladder = 0; ladder < numOfLadders ; ladder++) {
        G4RotationMatrix* rotM = new G4RotationMatrix;
	rotM->rotateZ(ANGLE_LADDER[layer][ladder]);
	G4VPhysicalVolume* ladderPhys = new G4PVPlacement(rotM,
					   XYZ_LADDER[layer][ladder],
					   ladderLV,
					   "VTX_Ladder",
					   layerLV,
					  false,ladder);
      }  //Ladder
    } //Layer


    // Master
    G4ThreeVector xyz_master(0.*mm,0.*mm,0.*mm);
    G4PVPlacement* vtxmaster = new G4PVPlacement(0,xyz_master,
						 "VTXDET",
						 masterLV,
						 ROWorldPhys,
						 false,0);
 


    return ROWorldPhys;
}

G4LogicalVolume* J4VTXROGeometry::BuildMasterLV(){

 G4Material* dummyMat= new G4Material(name="dummyMat",
				 1.,1.*g/mole,1.*g/cm3);


 // VTX Laster Volume
  G4double rmin = VTXMASTER_INNER_R;
  G4double rmax = VTXMASTER_OUTER_R;
  G4double len  = VTXMASTER_Z/2.;
  G4double dphi = VTXMASTER_PHI;
  G4Tubs* masterS  = new 
    G4Tubs( "VTX_master", rmin, rmax, len, 0.*deg, 360*deg );	   
  G4LogicalVolume* masterLV = new 
      G4LogicalVolume(masterS, dummyMat, "VTX_Master");     

  return masterLV;
}


G4LogicalVolume* J4VTXROGeometry::BuildSensorLV()
{

 G4Material* dummyMat= new G4Material(name="dummyMat",
				 1.,1.*g/mole,1.*g/cm3);


  G4Box* sensorS =  new G4Box( "VTX_Sensor",DXYZ_SENSOR.x()/2.,
			       DXYZ_SENSOR.y()/2.,
			       DXYZ_SENSOR.z()/2.);
  G4LogicalVolume* sensorLV=new G4LogicalVolume(sensorS,dummyMat,"VTX_Sensor");

  G4Box* epitaxialS =  new G4Box( "VTX_Epi",DXYZ_EPITAXIAL.x()/2.,
			       DXYZ_EPITAXIAL.y()/2.,
			       DXYZ_EPITAXIAL.z()/2.);
  G4LogicalVolume* epitaxialLV=new G4LogicalVolume(epitaxialS,
						dummyMat,"VTX_Epi");
  G4Box* substrateS =  new G4Box( "VTX_Sub",DXYZ_SUBSTRATE.x()/2.,
			       DXYZ_SUBSTRATE.y()/2.,
			       DXYZ_SUBSTRATE.z()/2.);
  G4LogicalVolume* substrateLV=new G4LogicalVolume(substrateS,
						dummyMat,"VTX_Sub");
  G4Box* pixelAreaS =  new G4Box( "VTX_PixArea",DXYZ_PIXELAREA.x()/2.,
			       DXYZ_PIXELAREA.y()/2.,
			       DXYZ_PIXELAREA.z()/2.);
  G4LogicalVolume* pixelAreaLV=new G4LogicalVolume(pixelAreaS,
						dummyMat,"VTX_PixArea1");

  // Make Sensor Unit

  		G4VPhysicalVolume* epitaxialPhys =
		  new G4PVPlacement(0,XYZ_EPITAXIAL,
				          epitaxialLV,
					 "VTX_Epi",
					  sensorLV,false,0);

		G4VPhysicalVolume* substratePhys =
		  new G4PVPlacement(0,XYZ_SUBSTRATE,
				          substrateLV,
					 "VTX_Epi",
					  sensorLV,false,0);

		G4VPhysicalVolume* pixelAreaPhys =
		  new G4PVPlacement(0,XYZ_PIXELAREA,
				          pixelAreaLV,
					 "VTX_PIXAREA",
					  epitaxialLV,false,0);
  
  //---------------------------------
// G4cout << "DXYZ PIXEL AREA "<< DXYZ_PIXELAREA << G4endl;
//G4cout << "Z PIXELSIZE     " << ZPIXELSIZE << "N ZPIX "<< NZPIXEL<< G4endl;
//  G4cout << "X PIXELSIZE     " << XPIXELSIZE << "N XPIX "<< NXPIXEL<< G4endl;

   G4Box*  zpixelS = new G4Box("ZPixel",DXYZ_PIXELAREA.x()/2.,
    			     DXYZ_PIXELAREA.y()/2.,
    			     ZPIXELSIZE/2.);
    G4LogicalVolume*  zpixelLV = new G4LogicalVolume(zpixelS,
  		     dummyMat,
		     "ZPixel");
//    G4cout << " Make Z Replica "<<G4endl;
    G4VPhysicalVolume*  zpixelPhys = new G4PVReplica("ZPixel",
  				  zpixelLV,
  				  pixelAreaPhys,
  				  kZAxis,
  				  NZPIXEL,
				  ZPIXELSIZE);
//    G4cout << " Finish Z Replica "<<G4endl;  

    G4Box* xpixelS = new G4Box("XPixel",XPIXELSIZE/2.,
  			     DXYZ_PIXELAREA.y()/2.,
			     ZPIXELSIZE/2.);
    G4LogicalVolume* xpixelLV = new G4LogicalVolume(xpixelS,
						      dummyMat,
						      "XPixel");
    //    G4cout << " Make X Replica "<<G4endl;
    G4VPhysicalVolume* xpixelPV = new G4PVReplica("XPixel",
  				  xpixelLV,
  				  zpixelPhys,
  				  kXAxis,
  				  NXPIXEL,
  				  XPIXELSIZE);
    //    G4cout << " Finish X Replica "<<G4endl;
//--------------------------------

	J4VTXDummySD* dummySD = new J4VTXDummySD;
    	xpixelLV->SetSensitiveDetector(dummySD);

  return sensorLV;
}


#endif

