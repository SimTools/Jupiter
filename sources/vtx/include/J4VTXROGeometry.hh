// $Id$
#ifndef __J4VTXROGeometory__
#define __J4VTXROGeometory __

//*************************************************************************
//* --------------------------
//* J4VTXROGeometory.hh
//* --------------------------
//* (Description)
//* 	Class for describing his/her detector setup.
//*     Mother class : G4VUserVTXRO (abstruct class)
//*    
//* (Update Record)
//*	2001/01/18  K.Hoshina	Original version.
//*************************************************************************

#ifndef __HOSHINA__

#include "G4VReadOutGeometry.hh"
#include "G4ThreeVector.hh"
#include "J4VMaterialStore.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VTXROGeometry : public G4VReadOutGeometry {
	
public:
  J4VTXROGeometry(G4String);
  ~J4VTXROGeometry();
  virtual G4VPhysicalVolume* Build(); 

private:
#include "J4VTXParameter.hh"
  G4VPhysicalVolume* BuildAll();
  G4LogicalVolume* BuildMasterLV();
  G4LogicalVolume* BuildSensorLV();

};

#endif
#endif

