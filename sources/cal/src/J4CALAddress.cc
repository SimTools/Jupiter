// $Id$
//*************************************************************************
//* --------------------
//* J4CALAddress
//* --------------------
//* (Description)
//*   Address information descripter	
//*     
//* (Update Record)
//*	2004/08/03  ONO Hiroaki Original version.
//*************************************************************************

#include "G4Types.hh"
#include "J4CALAddress.hh"
#include "J4CALParameterList.hh"

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------
J4CALAddress::J4CALAddress() 
: fConeID(0), fTowerID(0), fMiniConeID(0), fMiniTowerID(0), fLayerID(0),fSubLayerID(0)
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4CALAddress::~J4CALAddress() { }

//=====================================================================
//* static functions --------------------------------------------------
G4int J4CALAddress::GetCellID( G4int coneID, G4int towerID,
			       G4int miniConeID, G4int miniTowerID,
			       G4int layerID, G4int subLayerID, G4bool isEM )
{
  G4int  cellID    = -1;
  G4int  blockID   = -1;
  
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  
  //const G4int nCones        = ptrList -> GetNcones();
  const G4int nTowers       = ptrList -> GetConstNTowers(); // Set as constant value for tower
  const G4int nEMLayers     = ptrList -> GetEMNLayers();
  const G4int nHDLayers     = ptrList -> GetHDNLayers();
  const G4int nEMMiniCones  = ptrList -> GetEMMiniConeNClones();
  const G4int nEMMiniTowers = ptrList -> GetEMMiniTowerNClones();
  const G4int nHDMiniTowers = ptrList -> GetHDMiniTowerNClones();
  const G4int nHDMiniCones  = ptrList -> GetHDMiniConeNClones();
  const G4int nSubLayers    = ptrList -> GetNSubLayers();
  const G4int nEMCells      = nEMLayers*nEMMiniCones*nEMMiniTowers*nSubLayers;
  const G4int nHDCells      = nHDLayers*nHDMiniCones*nHDMiniTowers*nSubLayers;
  const G4int nBlocks       = nEMCells + nHDCells;


  if ( isEM ) {
    blockID   = ((((( subLayerID*nEMLayers + layerID )*nEMMiniTowers + miniTowerID )*nEMMiniCones + miniConeID)));
  } else {
    blockID   = nEMCells + ((((( subLayerID*nHDLayers + layerID )*nHDMiniTowers + miniTowerID )*nHDMiniCones + miniConeID)));
  }
  cellID = (coneID*nTowers + towerID)*nBlocks + blockID;
  return cellID;
}

G4int J4CALAddress::GetCellConeID( G4int cellID )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  const G4int nTowers       = ptrList -> GetConstNTowers();
  const G4int nEMLayers     = ptrList -> GetEMNLayers();
  const G4int nHDLayers     = ptrList -> GetHDNLayers();
  const G4int nEMMiniCones  = ptrList -> GetEMMiniConeNClones();
  const G4int nEMMiniTowers = ptrList -> GetEMMiniTowerNClones();
  const G4int nHDMiniTowers = ptrList -> GetHDMiniTowerNClones();
  const G4int nHDMiniCones  = ptrList -> GetHDMiniConeNClones();
  const G4int nSubLayers    = ptrList -> GetNSubLayers();
  const G4int nEMCells      = nEMLayers*nEMMiniCones*nEMMiniTowers*nSubLayers;
  const G4int nHDCells      = nHDLayers*nHDMiniCones*nHDMiniTowers*nSubLayers;
  const G4int nBlocks       = nEMCells + nHDCells;

  G4int coneID        = ( cellID / nBlocks / nTowers ) ;
  return coneID;
}

G4int J4CALAddress::GetCellTowerID( G4int cellID )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  const G4int nTowers       = ptrList -> GetConstNTowers();
  const G4int nEMLayers     = ptrList -> GetEMNLayers();
  const G4int nHDLayers     = ptrList -> GetHDNLayers();
  const G4int nEMMiniCones  = ptrList -> GetEMMiniConeNClones();
  const G4int nEMMiniTowers = ptrList -> GetEMMiniTowerNClones();
  const G4int nHDMiniTowers = ptrList -> GetHDMiniTowerNClones();
  const G4int nHDMiniCones  = ptrList -> GetHDMiniConeNClones();
  const G4int nSubLayers    = ptrList -> GetNSubLayers();
  const G4int nEMCells      = nEMLayers*nEMMiniCones*nEMMiniTowers*nSubLayers;
  const G4int nHDCells      = nHDLayers*nHDMiniCones*nHDMiniTowers*nSubLayers;
  const G4int nBlocks       = nEMCells + nHDCells;
  const G4int towerID       = ( cellID / nBlocks ) % nTowers;
  return towerID;
}

G4int J4CALAddress::GetCellMiniConeID( G4int cellID, G4bool isEM )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  const G4int nEMLayers     = ptrList -> GetEMNLayers();
  const G4int nHDLayers     = ptrList -> GetHDNLayers();
  const G4int nEMMiniCones  = ptrList -> GetEMMiniConeNClones();
  const G4int nEMMiniTowers = ptrList -> GetEMMiniTowerNClones();
  const G4int nHDMiniTowers = ptrList -> GetHDMiniTowerNClones();
  const G4int nHDMiniCones  = ptrList -> GetHDMiniConeNClones();
  const G4int nSubLayers    = ptrList -> GetNSubLayers();
  const G4int nEMCells      = nEMLayers*nEMMiniCones*nEMMiniTowers*nSubLayers;
  const G4int nHDCells      = nHDLayers*nHDMiniCones*nHDMiniTowers*nSubLayers;
  const G4int nBlocks       = nEMCells + nHDCells;
  const G4int blockID       = cellID % nBlocks;
  G4int miniConeID = -1;

  if ( isEM ) {
    miniConeID  = blockID % nEMMiniCones;
  } else {
    miniConeID  = ( blockID - nEMCells ) % nHDMiniCones;
  }
  return miniConeID;
}

G4int J4CALAddress::GetCellMiniTowerID( G4int cellID, G4bool isEM )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  const G4int nEMLayers     = ptrList -> GetEMNLayers();
  const G4int nHDLayers     = ptrList -> GetHDNLayers();
  const G4int nEMMiniCones  = ptrList -> GetEMMiniConeNClones();
  const G4int nEMMiniTowers = ptrList -> GetEMMiniTowerNClones();
  const G4int nHDMiniTowers = ptrList -> GetHDMiniTowerNClones();
  const G4int nHDMiniCones  = ptrList -> GetHDMiniConeNClones();
  const G4int nSubLayers    = ptrList -> GetNSubLayers();
  const G4int nEMCells      = nEMLayers*nEMMiniCones*nEMMiniTowers*nSubLayers;
  const G4int nHDCells      = nHDLayers*nHDMiniCones*nHDMiniTowers*nSubLayers;
  const G4int nBlocks       = nEMCells + nHDCells;
  const G4int blockID       = cellID % nBlocks;
  G4int miniTowerID = -1;

  if ( isEM ) {
    miniTowerID  = ( blockID / nEMMiniCones ) % nEMMiniTowers;
  } else {
    miniTowerID  = (( blockID - nEMCells) / nHDMiniCones ) % nHDMiniTowers;
  }
  return miniTowerID;
}

G4int J4CALAddress::GetCellLayerID( G4int cellID, G4bool isEM )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  const G4int nEMLayers     = ptrList -> GetEMNLayers();
  const G4int nHDLayers     = ptrList -> GetHDNLayers();
  const G4int nEMMiniCones  = ptrList -> GetEMMiniConeNClones();
  const G4int nEMMiniTowers = ptrList -> GetEMMiniTowerNClones();
  const G4int nHDMiniTowers = ptrList -> GetHDMiniTowerNClones();
  const G4int nHDMiniCones  = ptrList -> GetHDMiniConeNClones();
  const G4int nSubLayers    = ptrList -> GetNSubLayers();
  const G4int nEMCells      = nEMLayers*nEMMiniCones*nEMMiniTowers*nSubLayers;
  const G4int nHDCells      = nHDLayers*nHDMiniCones*nHDMiniTowers*nSubLayers;
  const G4int nBlocks       = nEMCells + nHDCells;
  const G4int blockID       = cellID % nBlocks;
  G4int layerID = -1;

  if ( isEM ) {
    layerID  = ( blockID / nEMMiniCones / nEMMiniTowers ) % nEMLayers;
  } else {
    layerID  = (( blockID - nEMCells ) / nHDMiniCones / nHDMiniTowers ) % nHDLayers;
  }
  return layerID;
}

G4int J4CALAddress::GetCellSubLayerID( G4int cellID, G4bool isEM )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  const G4int nEMLayers     = ptrList -> GetEMNLayers();
  const G4int nHDLayers     = ptrList -> GetHDNLayers();
  const G4int nEMMiniCones  = ptrList -> GetEMMiniConeNClones();
  const G4int nEMMiniTowers = ptrList -> GetEMMiniTowerNClones();
  const G4int nHDMiniTowers = ptrList -> GetHDMiniTowerNClones();
  const G4int nHDMiniCones  = ptrList -> GetHDMiniConeNClones();
  const G4int nSubLayers    = ptrList -> GetNSubLayers();
  const G4int nEMCells      = nEMLayers*nEMMiniCones*nEMMiniTowers*nSubLayers;
  const G4int nHDCells      = nHDLayers*nHDMiniCones*nHDMiniTowers*nSubLayers;
  const G4int nBlocks       = nEMCells + nHDCells;
  const G4int blockID       = cellID % nBlocks;
  G4int subLayerID = -1;

  if ( isEM ) {
    subLayerID  = ( blockID / nEMMiniCones / nEMMiniTowers / nEMLayers ) % nSubLayers;
  } else {
    subLayerID  = (( blockID - nEMCells ) / nHDMiniCones / nHDMiniTowers / nHDLayers ) % nSubLayers; 
  }
  return subLayerID;
}

