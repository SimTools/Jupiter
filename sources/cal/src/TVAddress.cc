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
TVAddress::TVAddress() 
: fConeID(0), fTowerID(0), fMiniConeID(0),fMiniTowerID(0),
  fLayerID(0), fSubLayerID(0) /* , fIsBarrel(0), fIsEM(0) */
{ }

//=====================================================================
//* constructor -------------------------------------------------------
TVAddress::TVAddress(  G4int coneID, 
                       G4int towerID, 
                       G4int miniConeID, 
                       G4int miniTowerID, 
                       G4int layerID, 
                       G4int subLayerID /*, */
		       /* G4bool isBarrel, */
                       /* G4bool isEM */ )
 : fConeID( coneID ), fTowerID( towerID ), fMiniConeID( miniConeID ), fMiniTowerID( miniTowerID ),
   fLayerID( layerID ), fSubLayerID( subLayerID ) /* , fIsBarrel( isBarrel ), fIsEM( isEM ) */
{ }

//=====================================================================
//* copy constructor  -------------------------------------------------
TVAddress::TVAddress( const TVAddress& right )
{
  fConeID      = right.fConeID;
  fTowerID     = right.fTowerID;
  fMiniConeID  = right.fMiniConeID;
  fMiniTowerID = right.fMiniTowerID;
  fLayerID     = right.fLayerID;
  fSubLayerID  = right.fSubLayerID;
  //  fIsBarrel    = right.fIsBarrel;
  //  fIsEM        = right.fIsEM;
}

//=====================================================================
//* destructor --------------------------------------------------------
TVAddress::~TVAddress() { }

G4int TVAddress::GetCellConeID( G4int cellID )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  G4int nCones = ptrList -> GetNcones();
  G4int coneID = cellID % nCones;
  return coneID;
}

G4int TVAddress::GetCellTowerID( G4int cellID )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  G4int nCones  = ptrList -> GetNcones();
  G4int nTowers = ptrList -> GetConstNTowers();
  G4int towerID = ( cellID / nCones ) % nTowers;
  return towerID;
}

//G4bool TVAddress::GetCellIsEM( G4int cellID ) {
//  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
//  G4int nCones  = ptrList -> GetNcones();
//  G4int nTowers = ptrList -> GetConstNTowers();
//  G4int nIsEM   = ptrList -> GetNIsEM();
//  G4bool isEM = false;
//  
//  if ( ( cellID / nCones / nTowers % nIsEM ) == 1 )
//    isEM = true;
//  if ( ( cellID / nCones / nTowers % nIsEM ) != 1 )
//    isEM = false;
//  
//  return isEM;
//}

G4int TVAddress::GetCellMiniConeID( G4int cellID, G4bool isEM )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  const G4int nCones       = ptrList -> GetNcones();
  const G4int nTowers      = ptrList -> GetConstNTowers();
  //  const G4int nIsEM        = ptrList -> GetNIsEM();
  const G4int nEMMiniCones = ptrList -> GetEMMiniConeNClones();
  const G4int nHDMiniCones = ptrList -> GetHDMiniConeNClones();
  G4int miniConeID = -1;

  if ( isEM ) {
    miniConeID  = ( cellID / nCones / nTowers ) % nEMMiniCones;
  } else {
    miniConeID  = ( cellID / nCones / nTowers ) % nHDMiniCones;
  }
  
//  if ( ( cellID / nCones / nTowers % nIsEM ) == 1 ) {
//    miniConeID  = cellID / nCones / nTowers / nIsEM % nEMMiniCones;
//  } else {
//    miniConeID  = cellID / nCones / nTowers / nIsEM % nHDMiniCones;
//  }

  return miniConeID;
}

G4int TVAddress::GetCellMiniTowerID( G4int cellID, G4bool isEM )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  const G4int nCones        = ptrList -> GetNcones();
  const G4int nTowers       = ptrList -> GetConstNTowers();
  //  const G4int nIsEM         = ptrList -> GetNIsEM();
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
  
//  if ( ( cellID / nCones / nTowers % nIsEM ) == 1 ) {
//    miniTowerID  = cellID / nCones / nTowers / nIsEM / nEMMiniCones % nEMMiniTowers;
//  } else {
//    miniTowerID  = cellID / nCones / nTowers / nIsEM / nHDMiniCones % nHDMiniTowers;
//  }
  
  return miniTowerID;
}

G4int TVAddress::GetCellLayerID( G4int cellID, G4bool isEM )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  const G4int nCones        = ptrList -> GetNcones();
  const G4int nTowers       = ptrList -> GetConstNTowers();
  //  const G4int nIsEM         = ptrList -> GetNIsEM();
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
  
  //if ( ( cellID / nCones / nTowers % nIsEM ) == 1 ) {
  //  layerID  = cellID / nCones / nTowers / nIsEM / nEMMiniCones / nEMMiniTowers % nEMLayers;
  //} else {
  //  layerID  = cellID / nCones / nTowers / nIsEM / nHDMiniCones / nHDMiniTowers % nHDLayers;
  //}
  return layerID;
}

G4int TVAddress::GetCellSubLayerID( G4int cellID, G4bool isEM )
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  J4CALSubLayerParameterList* ptrSubList = ptrList -> GetSubLayerParam();
  const G4int nCones        = ptrList -> GetNcones();
  const G4int nTowers       = ptrList -> GetConstNTowers();
  //  const G4int nIsEM         = ptrList -> GetNIsEM();
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
  
 // if ( ( cellID / nCones / nTowers % nIsEM ) == 1 ) {
 //   subLayerID  = cellID / nCones / nTowers / nIsEM / nEMMiniCones / nEMMiniTowers / nEMLayers % nEMSubLayers;
 // } else {
 //   subLayerID  = cellID / nCones / nTowers / nIsEM / nHDMiniCones / nHDMiniTowers / nHDLayers % nHDSubLayers;
 // }
  
  return subLayerID;
}

//G4bool TVAddress::GetCellIsBarrel( G4int cellID, G4bool isBarrel ) {
//  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
//  J4CALSubLayerParameterList* ptrSubList = ptrList -> GetSubLayerParam();
//  const G4int nCones        = ptrList -> GetNcones();
//  const G4int nTowers       = ptrList -> GetConstNTowers();
//  //  const G4int nIsEM         = ptrList -> GetNIsEM();
//  const G4int nEMMiniCones  = ptrList -> GetEMMiniConeNClones();
//  const G4int nHDMiniCones  = ptrList -> GetHDMiniConeNClones();
//  const G4int nEMMiniTowers = ptrList -> GetEMMiniTowerNClones();
//  const G4int nHDMiniTowers = ptrList -> GetHDMiniTowerNClones();
//  const G4int nEMLayers     = ptrList -> GetEMNLayers();
//  const G4int nHDLayers     = ptrList -> GetHDNLayers();
//  const G4int nEMSubLayers  = ptrSubList -> GetNLayers( "EM" );
//  const G4int nHDSubLayers  = ptrSubList -> GetNLayers( "HD" );
//  //  const G4int nIsBarrel     = ptrList -> GetNIsBarrel();
//  //  G4bool isBarrel = false;
//  
//  if ( isEM ) {
//    if ( cellID / nCones / nTowers / nIsEM / nEMMiniCones / nEMMiniTowers / nEMLayers / nEMSubLayers % nIsBarrel )
//      isBarrel = true;
//    else
//      isBarrel = false;
//  } else {
//    
//    if ( cellID / nCones / nTowers / nIsEM / nHDMiniCones / nHDMiniTowers / nHDLayers / nHDSubLayers % nIsBarrel )
//      isBarrel = true;
//    else
//      isBarrel = false;
//  }
//  
//  return isBarrel;
//}


//* Draw  --------------------------------------------------------
void TVAddress::Draw() { }

//* Print  --------------------------------------------------------
void TVAddress::Print() const
{
  std::cout << "Cone"      << fConeID      << " "
	    << "Tower"     << fTowerID     << " "
	    << "MiniCone"  << fMiniConeID  << " "
	    << "MiniTower" << fMiniTowerID << " "
	    << "Layer"     << fLayerID     << " "
	    << "Sublayer"  << fSubLayerID  << " "
    //	    << "isBarrel"  << fIsBarrel    << " "
    //	    << "isEM"      << fIsEM        << " "
	    << std::endl;
}
