// $Id$
#ifndef __J4CALADDRESS__
#define __J4CALADDRESS__
//*************************************************************************
//* --------------------
//* J4CALAddress
//* --------------------
//* (Description)
//*     Cell addressor for converting cell address and position
//*     
//* (Update Record)
//*     Preriminal version
//*     2004/08/01  ONO Hiroaki  <ono@hep.sc.niigata-u.ac.jp>
//*************************************************************************

#include "J4CALParameterList.hh"

//=========================================================================
//---------------------
// class definition
//---------------------

class J4CALAddress {

public:

  J4CALAddress();
  ~J4CALAddress();

  // getter/setter
public:
  
  static G4int GetCellConeID( G4int cellID );
  static G4int GetCellTowerID( G4int cellID );
  static G4int GetCellMiniConeID( G4int cellID, G4bool isEM );
  static G4int GetCellMiniTowerID( G4int cellID, G4bool isEM );
  static G4int GetCellLayerID( G4int cellID, G4bool isEM );

  static G4int GetCellID(  G4int coneID, G4int towerID,
			   G4int miniConeID, G4int miniTowerID,
			   G4int layerID, G4bool isEM );
  
private:
  G4int   fConeID; 
  G4int   fTowerID; 
  G4int   fMiniConeID; 
  G4int   fMiniTowerID; 
  G4int   fLayerID; 
  G4int   fCellID;
  
};

#endif
