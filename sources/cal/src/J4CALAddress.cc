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
: fConeID(0), fTowerID(0), fMiniConeID(0), fMiniTowerID(0), fLayerID(0)
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4CALAddress::~J4CALAddress() { }

//=====================================================================
//* static functions --------------------------------------------------
G4int J4CALAddress::GetCellID( G4int coneID, G4int towerID,
			       G4int miniConeID, G4int miniTowerID,
			       G4int layerID, G4bool isEM )
{
  G4int  cellID      = -1;
  
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  
  //const G4int nCones        = ptrList -> GetNcones();
  const G4int nTowers       = ptrList -> GetConstNTowers(); // Set as constant value for tower
  const G4int nEMLayers     = ptrList -> GetEMNLayers();
  const G4int nHDLayers     = ptrList -> GetHDNLayers();
  const G4int nEMMiniCones  = ptrList -> GetEMMiniConeNClones();
  const G4int nHDMiniCones  = ptrList -> GetHDMiniConeNClones();
  const G4int nEMMiniTowers = ptrList -> GetEMMiniTowerNClones();
  const G4int nHDMiniTowers = ptrList -> GetHDMiniTowerNClones();
  const G4int nIsEM         = ptrList -> GetNIsEM();

  if ( isEM ) 
    cellID = ((((coneID*nTowers + towerID)*nIsEM + 0)*nEMMiniCones + miniConeID)*nEMMiniTowers + miniTowerID)*nEMLayers + layerID;
  else
    cellID = ((((coneID*nTowers + towerID)*nIsEM + 1)*nHDMiniCones + miniConeID)*nHDMiniTowers + miniTowerID)*nHDLayers + layerID;

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
  const G4int nIsEM        = ptrList -> GetNIsEM();
  G4int miniConeID = -1;

  if ( isEM ) {
    miniConeID  = ( cellID / nCones / nTowers / nIsEM ) % nEMMiniCones;
  } else {
    miniConeID  = ( cellID / nCones / nTowers / nIsEM ) % nHDMiniCones;
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
  const G4int nIsEM         = ptrList -> GetNIsEM();
  G4int miniTowerID = -1;

  if ( isEM ) {
    miniTowerID  = ( cellID / nCones / nTowers / nIsEM / nEMMiniCones / nIsEM ) % nEMMiniTowers;
  } else {
    miniTowerID  = ( cellID / nCones / nTowers / nIsEM / nHDMiniCones / nIsEM ) % nHDMiniTowers;
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
  const G4int nIsEM         = ptrList -> GetNIsEM();
  G4int layerID = -1;

  if ( isEM ) {
    layerID  = ( cellID / nCones / nTowers / nIsEM / nEMMiniCones / nEMMiniTowers ) % nEMLayers;
  } else {
    layerID  = ( cellID / nCones / nTowers / nIsEM / nHDMiniCones / nHDMiniTowers ) % nHDLayers;
  }
  return layerID;
}

