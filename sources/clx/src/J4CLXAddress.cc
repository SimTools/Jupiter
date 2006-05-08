// $Id$
//*************************************************************************
//* --------------------
//* J4CLXAddress
//* --------------------
//* (Description)
//*   Address information descripter	
//*     
//* (Update Record)
//*	2006/05/01  H.Ono Original version.
//*************************************************************************//
#include "J4CLXAddress.hh"
#include "J4CLXParameterList.hh"

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXAddress::J4CLXAddress()
{}

J4CLXAddress::J4CLXAddress( G4bool isEM,
			    G4bool isBarrel,
			    G4int  blockID,
			    G4int  layerID,
			    G4int  stripID,
			    G4int  cellID )
{
  SetGlobalCellID( isEM, isBarrel, blockID, layerID, stripID, cellID );
}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXAddress::~J4CLXAddress()
{}

//=====================================================================
//* SetGlobalCellID ---------------------------------------------------
void J4CLXAddress::SetGlobalCellID( G4bool isEM, G4bool isBarrel,
				    G4int blockID, G4int layerID,
				    G4int stripID, G4int cellID )
{
  fGlobalCellID = GetGlobalCellID( isEM,
				   isBarrel,
				   blockID,
				   layerID,
				   stripID,
				   cellID   );
}

//=====================================================================
//* static functions --------------------------------------------------

//* GetGlobalCelLID
G4int J4CLXAddress::GetGlobalCellID( G4bool isEM,   G4bool isBarrel,
				     G4int blockID, G4int layerID,
				     G4int stripID, G4int cellID    )
{
  G4int globalID = -1;

  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();
  
  G4int nEMCells  = ptrList->GetEMNCells();
  //  G4int nHDCells  = ptrList->GetHDNCells();
  G4int nEMStrips = ptrList->GetEMNStrips();
  G4int nHDStrips = ptrList->GetHDNStrips();
  G4int nEMLayers = ptrList->GetEMNLayers();
  G4int nHDLayers = ptrList->GetHDNLayers();  
  G4int nBlocks   = 2*ptrList->GetNTraps();
  G4int nIsBarrel = ptrList->GetNIsBarrel();
  G4int nEMTotal  = nEMCells*nEMStrips*nEMLayers;

  globalID = ( isEM )
    ? ((( cellID*nEMStrips+stripID)*nEMLayers+layerID)*nBlocks+blockID)*nIsBarrel+isBarrel
    : (( nEMTotal+(cellID*nHDStrips+stripID)*nHDLayers+layerID)*nBlocks+blockID)*nIsBarrel+isBarrel;

  if ( globalID > INT_MAX ) {
   std::cerr << "**** Error! CAL globalID over to INT_MAX! " << globalID
	     << " over " << INT_MAX << std::endl;
  }

  if ( globalID < 0 ) {
   std::cerr << "**** Error! CAL globalID is negative! " << globalID << std::endl;
  }

  return globalID;
}

//* GetIsBarrel
G4int J4CLXAddress::GetIsBarrel( G4int cellID )
{
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();
  G4int nIsBarrel  = ptrList->GetNIsBarrel();
  return cellID%nIsBarrel;
}

//* GetBlockID
G4int J4CLXAddress::GetBlockID( G4int cellID )
{
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();
  G4int nBlocks   = 2*ptrList->GetNTraps();
  G4int nIsBarrel = ptrList->GetNIsBarrel();

  return (cellID/nIsBarrel)%nBlocks;
}

//* GetIsEndcap
G4int J4CLXAddress::GetIsEndcap( G4int cellID )
{
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();
  G4int nTraps     = ptrList->GetNTraps();
  G4int nBlocks    = 2*nTraps;
  G4int nIsBarrel  = ptrList->GetNIsBarrel();
  G4int blockID    = (cellID/nIsBarrel)%nBlocks;
  G4int isBarrel   = cellID%nIsBarrel;
  
  return ( blockID < nTraps ) ? isBarrel : -isBarrel;
}

//* GetLayerID
G4int J4CLXAddress::GetLayerID( G4int cellID, G4bool isEM )
{
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();
  G4int nBlocks   = 2*ptrList->GetNTraps();
  G4int nIsBarrel = ptrList->GetNIsBarrel();
  G4int nEMLayers = ptrList->GetEMNLayers();
  G4int nHDLayers = ptrList->GetHDNLayers();
  G4int nEMCells  = ptrList->GetEMNCells();
  G4int nEMStrips = ptrList->GetEMNStrips();
  G4int nEMTotal  = nEMCells*nEMStrips*nEMLayers;
  G4int blockID   = cellID/nIsBarrel/nBlocks;
  
  return ( isEM ) ? blockID % nEMLayers
                  : (blockID-nEMTotal) % nHDLayers;
}

//* GetStripID
G4int J4CLXAddress::GetStripID( G4int cellID, G4bool isEM )
{
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();

  G4int nBlocks   = 2*ptrList->GetNTraps();
  G4int nIsBarrel = ptrList->GetNIsBarrel();
  G4int nEMLayers = ptrList->GetEMNLayers();
  G4int nHDLayers = ptrList->GetHDNLayers();
  G4int nEMStrips = ptrList->GetEMNStrips();
  G4int nHDStrips = ptrList->GetHDNStrips();
  G4int nEMCells  = ptrList->GetEMNCells();
  G4int nEMTotal  = nEMCells*nEMStrips*nEMLayers;
  
  G4int blockID   = cellID/nIsBarrel/nBlocks;
  return ( isEM ) ? (blockID/nEMLayers)%nEMStrips
                  : ((blockID-nEMTotal)/nHDLayers)%nHDStrips ;
}

//* GetCellID
G4int J4CLXAddress::GetCellID( G4int cellID, G4bool isEM )
{
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();
  G4int nBlocks   = 2*ptrList->GetNTraps();
  G4int nIsBarrel = ptrList->GetNIsBarrel();
  G4int nEMLayers = ptrList->GetEMNLayers();
  G4int nHDLayers = ptrList->GetHDNLayers();
  G4int nEMStrips = ptrList->GetEMNStrips();
  G4int nHDStrips = ptrList->GetHDNStrips();
  G4int nEMCells  = ptrList->GetEMNCells();
  //  G4int nHDCells  = ptrList->GetHDNCells();
  G4int nEMTotal  = nEMCells*nEMStrips*nEMLayers;

  G4int blockID   = cellID/nIsBarrel/nBlocks;
  return ( isEM ) ? blockID/nEMLayers/nEMStrips
                  : (blockID-nEMTotal)/nHDLayers/nHDStrips ;
}

G4ThreeVector J4CLXAddress::GetCellPosition( G4int globalID, G4bool isEM )
{
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();

  G4int cellID   = GetCellID( globalID, isEM );
  G4int stripID  = GetStripID( globalID, isEM );
  G4int layerID  = GetLayerID( globalID, isEM );
  G4int blockID  = GetBlockID( globalID );
  //  G4int isEndcap = GetIsEndcap( globalID );
  G4int isBarrel = GetIsBarrel( globalID );

  G4double layerThick  = (isEM) ? ptrList->GetEMLayerThickness()
                                : ptrList->GetHDLayerThickness();
  G4double activeThick = (isEM) ? ptrList->GetEMActiveLayerThickness()
                                : ptrList->GetHDActiveLayerThickness();
  G4double absThick    = (isEM) ? ptrList->GetEMAbsLayerThickness()
                                : ptrList->GetHDAbsLayerThickness();
  G4double halfl       = (isEM) ? ptrList->GetEMHalfZ()
                                : ptrList->GetHDHalfZ();

  G4double cellSize = ptrList->GetCellSize();
  //  G4double EMYmax   = ptrList->GetEMYmax();
  //  G4double HDYmax   = ptrList->GetHDYmax();
  
  G4double innerR   = (isBarrel) ? ptrList->GetCLXInnerR()
                                 : ptrList->GetEndcapInnerR();
  G4double ymin     = (isBarrel) ? (innerR+layerID*layerThick+absThick)
                                 : (innerR+stripID*cellSize);
  
  G4double dphi     = ptrList->GetTrapDeltaPhi();
  G4double halfx    = ymin*std::tan( 0.5*dphi );
  G4double halfz    = (isBarrel)? -halfl+(stripID+0.5)*cellSize
                                :  halfl+layerID*layerThick+absThick ;
  G4int    nCells   = (G4int)(2*halfx/cellSize);

  G4double px       = -0.5*cellSize*nCells+(cellID+0.5)*cellSize;
  G4double py       = ( isBarrel ) ? ymin + 0.5*activeThick
                                   : ymin + 0.5*cellSize;
  G4double pz       = ( isBarrel ) ? halfz
                                   : halfz*GetIsEndcap( cellID );

  G4ThreeVector position( px, py, pz );
  position.rotateZ( blockID*dphi );
  
  return position;
}
