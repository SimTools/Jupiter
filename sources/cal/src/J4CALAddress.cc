// $Id$
//*************************************************************************
//* --------------------
//* TVAddress
//* --------------------
//* (Description)
//*   Address information descripter	
//*     
//* (Update Record)
//*	2004/08/03  ONO Hiroaki Original version.
//*************************************************************************
#include "G4Types.hh"
#include "TVAddress.hh"
#include "J4CALParameterList.hh"
#include "J4CALSubLayerParameterList.hh"

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------
J4CALAddress::J4CALAddress() 
: fConeID(0), fTowerID(0), fMiniConeID(0),fMiniTowerID(0),
  fLayerID(0), fSubLayerID(0)
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4CALAddress::~J4CALAddress() { }

//=====================================================================
//* static functions --------------------------------------------------
G4int J4CALAddress::GetCellID( G4int coneID, G4int towerID,
			    G4int miniConeID, G4int miniTowerID,
			    G4int layerID, G4int subLayerID,
			    G4bool isEM )
{
  G4int  cellID      = -1;
  
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  
  const G4int nCones        = ptrList -> GetNcones();
  const G4int nTowers       = ptrList -> GetConstNTowers(); // Set as constant value for tower
  const G4int nEMLayers     = ptrList -> GetEMNLayers();
  const G4int nHDLayers     = ptrList -> GetHDNLayers();
  const G4int nEMMiniCones  = ptrList -> GetEMMiniConeNClones();
  const G4int nHDMiniCones  = ptrList -> GetHDMiniConeNClones();
  const G4int nEMMiniTowers = ptrList -> GetEMMiniTowerNClones();
  const G4int nHDMiniTowers = ptrList -> GetHDMiniTowerNClones();
  
  if ( isEM ) 
    cellID = coneID + nCones*( towerID + nTowers*( miniConeID + nEMMiniCones*( miniTowerID + nEMMiniTowers*( layerID + nEMLayers*( subLayerID )))));
  else
    cellID = coneID + nCones*( towerID + nTowers*( miniConeID + nHDMiniCones*( miniTowerID + nHDMiniTowers*( layerID + nHDLayers*( subLayerID )))));

  return cellID;
}

G4int J4CALAddress::GetCellConeID( G4int cellID )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  G4int nCones = ptrList -> GetNcones();
  G4int coneID = cellID % nCones;
  return coneID;
}

G4int J4CALAddress::GetCellTowerID( G4int cellID )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  G4int nCones  = ptrList -> GetNcones();
  G4int nTowers = ptrList -> GetConstNTowers();
  G4int towerID = ( cellID / nCones ) % nTowers;
  return towerID;
}

G4int J4CALAddress::GetCellMiniConeID( G4int cellID, G4bool isEM )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  const G4int nCones       = ptrList -> GetNcones();
  const G4int nTowers      = ptrList -> GetConstNTowers();
  const G4int nEMMiniCones = ptrList -> GetEMMiniConeNClones();
  const G4int nHDMiniCones = ptrList -> GetHDMiniConeNClones();
  G4int miniConeID = -1;

  if ( isEM ) {
    miniConeID  = ( cellID / nCones / nTowers ) % nEMMiniCones;
  } else {
    miniConeID  = ( cellID / nCones / nTowers ) % nHDMiniCones;
  }
  return miniConeID;
}

G4int J4CALAddress::GetCellMiniTowerID( G4int cellID, G4bool isEM )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  const G4int nCones        = ptrList -> GetNcones();
  const G4int nTowers       = ptrList -> GetConstNTowers();
  const G4int nEMMiniCones  = ptrList -> GetEMMiniConeNClones();
  const G4int nHDMiniCones  = ptrList -> GetHDMiniConeNClones();
  const G4int nEMMiniTowers = ptrList -> GetEMMiniTowerNClones();
  const G4int nHDMiniTowers = ptrList -> GetHDMiniTowerNClones();
  G4int miniTowerID = -1;

  if ( isEM ) {
    miniTowerID  = ( cellID / nCones / nTowers / nEMMiniCones ) % nEMMiniTowers;
  } else {
    miniTowerID  = ( cellID / nCones / nTowers / nHDMiniCones ) % nHDMiniTowers;
  }
  return miniTowerID;
}

G4int J4CALAddress::GetCellLayerID( G4int cellID, G4bool isEM )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  const G4int nCones        = ptrList -> GetNcones();
  const G4int nTowers       = ptrList -> GetConstNTowers();
  const G4int nEMMiniCones  = ptrList -> GetEMMiniConeNClones();
  const G4int nHDMiniCones  = ptrList -> GetHDMiniConeNClones();
  const G4int nEMMiniTowers = ptrList -> GetEMMiniTowerNClones();
  const G4int nHDMiniTowers = ptrList -> GetHDMiniTowerNClones();
  const G4int nEMLayers     = ptrList -> GetEMNLayers();
  const G4int nHDLayers     = ptrList -> GetHDNLayers();
  G4int layerID = -1;

  if ( isEM ) {
    layerID  = ( cellID / nCones / nTowers / nEMMiniCones / nEMMiniTowers ) % nEMLayers;
  } else {
    layerID  = ( cellID / nCones / nTowers / nHDMiniCones / nHDMiniTowers ) % nHDLayers;
  }
  return layerID;
}

G4int J4CALAddress::GetCellSubLayerID( G4int cellID, G4bool isEM )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  J4CALSubLayerParameterList* ptrSubList = ptrList -> GetSubLayerParam();
  const G4int nCones        = ptrList -> GetNcones();
  const G4int nTowers       = ptrList -> GetConstNTowers();
  const G4int nEMMiniCones  = ptrList -> GetEMMiniConeNClones();
  const G4int nHDMiniCones  = ptrList -> GetHDMiniConeNClones();
  const G4int nEMMiniTowers = ptrList -> GetEMMiniTowerNClones();
  const G4int nHDMiniTowers = ptrList -> GetHDMiniTowerNClones();
  const G4int nEMLayers     = ptrList -> GetEMNLayers();
  const G4int nHDLayers     = ptrList -> GetHDNLayers();
  const G4int nEMSubLayers  = ptrSubList -> GetNLayers( "EM" );
  const G4int nHDSubLayers  = ptrSubList -> GetNLayers( "HD" );
  G4int subLayerID = -1;

  if ( isEM ) {
    subLayerID  = ( cellID / nCones / nTowers / nEMMiniCones / nEMMiniTowers / nEMLayers ) % nEMSubLayers;
  } else {
    subLayerID  = ( cellID / nCones / nTowers / nHDMiniCones / nHDMiniTowers / nHDLayers ) % nHDSubLayers; 
  }
  
  return subLayerID;
}
