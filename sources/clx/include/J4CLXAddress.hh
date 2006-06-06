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

  J4CLXAddress( G4bool isEM, G4int blockID,
                G4int layerID, G4int trapStripID,
                G4int stripID, G4int cellID );
  
  virtual ~J4CLXAddress();

  void SetGlobalCellID( G4bool isEM, G4int blockID,
                        G4int layerID, G4int trapStripID,
                        G4int stripID, G4int cellID );
  
  //* Static accessor to be called without object.
  static G4int GetGlobalCellID( G4bool isEM, G4int blockID,
                                G4int layerID, G4int trapStripID,
                                G4int stripID, G4int cellID );
				    
  //  static G4int GetIsBarrel    ( G4int cellID ) ;
  static G4int  GetBlockID     ( G4int cellID ) ;
  static G4int  GetLayerID     ( G4int cellID, G4bool isEM ) ;
  static G4int  GetTrapStripID ( G4int cellID, G4bool isEM ) ;
  static G4int  GetStripID     ( G4int cellID, G4bool isEM ) ;
  static G4int  GetCellID      ( G4int cellID, G4bool isEM ) ;

  //* Boolean checker
  static G4bool IsBoundary     ( G4int cellID, G4bool isEM ) ;
  static G4bool IsXNegative    ( G4int cellID, G4bool isEM ) ;  
  static G4int  IsEndcap       ( G4int cellID, G4bool isBarrel ) ;

  //* Gettter for any informations
  static G4int  GetNTrapStrips ( G4bool isEM, G4bool isBarrel );
  static G4int  GetNCells      ( G4bool isEM, G4bool isBarrel, G4int id );
  
  static G4ThreeVector GetCellPosition( G4int globalID, G4bool isEM, G4bool isBarrel );
  
private:

#if 0
  static G4int    fgCLXNTraps;
  static G4double fgCLXBarrelInnerR;
  static G4double fgCLXEndcapInnerR;
  static G4double fgCLXBarrelHalfZ;
  static G4double fgCLXGap;
  static G4int    fgCLXEMNLayers;	   
  static G4int    fgCLXHDNLayers;	   
  static G4double fgCLXEMActiveThick; 
  static G4double fgCLXHDActiveThick; 
  static G4double fgCLXEMAbsThick;
  static G4double fgCLXHDAbsThick;	   
  static G4double fgCLXEMFlexThick;   
  static G4double fgCLXHDFlexThick;
  static G4double fgCLXCellSize;
#endif
  
  G4int fGlobalCellID;
  
};

#endif
