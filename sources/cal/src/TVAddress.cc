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

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------
TVAddress::TVAddress() 
: fConeID(0), fTowerID(0), fMiniConeID(0),fMiniTowerID(0),
fLayerID(0), fSubLayerID(0), fIsBarrel(0), fIsEM(0)
{
}

//=====================================================================
//* constructor -------------------------------------------------------
TVAddress::TVAddress(  G4int coneID, 
                       G4int towerID, 
                       G4int miniConeID, 
                       G4int miniTowerID, 
                       G4int layerID, 
                       G4int subLayerID, 
                       G4bool isBarrel, 
                       G4bool isEM )
 : fConeID( coneID ), fTowerID( towerID ), fMiniConeID( miniConeID ), fMiniTowerID( miniTowerID ),
   fLayerID( layerID ), fSubLayerID( subLayerID ), fIsBarrel( isBarrel ), fIsEM( isEM )
{
}

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
  fIsBarrel    = right.fIsBarrel;
  fIsEM        = right.fIsEM;
}

//=====================================================================
//* destructor --------------------------------------------------------
TVAddress::~TVAddress() { }

//====================================================================
//* Initialize check    ----------------------------------------------
G4bool TVAddress::IsInitialize( TVAddress* address )
{
  if ( address == 0 ) return true;
  else return false;
}

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
	    << "isBarrel"  << fIsBarrel    << " "
	    << "isEM"      << fIsEM        << " "
	    << std::endl;
}
