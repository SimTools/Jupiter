// $Id$
#ifndef __J4CLXADDRESS__
#define __J4CLXADDRESS__
//*************************************************************************
//* --------------------
//* J4CALAddress
//* --------------------
//* (Description)
//*     Cell addressor for converting cell address and position
//*     
//* (Update Record)
//*     2006/05/01  H.Ono Original version
//*************************************************************************

#include "G4Types.hh"
#include "G4ThreeVector.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4CLXAddress {

public:
  J4CLXAddress() ;

  J4CLXAddress( G4bool isEM, G4bool isBarrel,
		G4int blockID, G4int layerID,
		G4int stripID, G4int cellID );
  
  virtual ~J4CLXAddress();

  void SetGlobalCellID( G4bool isEM, G4bool isBarrel,
  			G4int blockID, G4int layerID,
  			G4int stripID, G4int cellID );
  
  //* Static accessor to be called without object.
  static G4int GetGlobalCellID( G4bool isEM,   G4bool isBarrel,
				G4int blockID, G4int layerID,
				G4int stripID, G4int cellID    );
				    
  static G4int GetIsBarrel    ( G4int cellID ) ;
  static G4int GetIsEndcap    ( G4int cellID ) ;
  static G4int GetBlockID     ( G4int cellID ) ;
  static G4int GetLayerID     ( G4int cellID, G4bool isEM ) ;
  static G4int GetStripID     ( G4int cellID, G4bool isEM ) ;
  static G4int GetCellID      ( G4int cellID, G4bool isEM ) ;

  static G4ThreeVector GetCellPosition( G4int globalID, G4bool isEM );
  
private:

  G4int fGlobalCellID;
  
};

#endif
