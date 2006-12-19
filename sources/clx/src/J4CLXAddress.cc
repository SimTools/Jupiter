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
//*     2006/12/13  H.Ono BlockID change to be separated Barrel/Endcap+/-Z
//*************************************************************************//
#include "J4CLXAddress.hh"
#include "J4CLXParameterList.hh"
#include "J4ParameterTable.hh"

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXAddress::J4CLXAddress()
{}

J4CLXAddress::J4CLXAddress( G4bool isEM,
			    G4int  blockID,
			    G4int  layerID,
			    G4int  trapStripID,
			    G4int  stripID,
			    G4int  cellID )
{
  SetGlobalCellID( isEM, blockID, layerID, trapStripID, stripID, cellID );
}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXAddress::~J4CLXAddress()
{}

//=====================================================================
//* SetGlobalCellID ---------------------------------------------------
void J4CLXAddress::SetGlobalCellID( G4bool isEM, G4int blockID,
				    G4int layerID, G4int trapStripID,
				    G4int stripID, G4int cellID )
{
  fGlobalCellID = GetGlobalCellID( isEM, blockID, layerID, trapStripID, stripID, cellID );
}

//=====================================================================
//* static functions --------------------------------------------------

//=====================================================================
//* GetGlobalCelLID ---------------------------------------------------
G4int J4CLXAddress::GetGlobalCellID( G4bool isEM, G4int blockID,
				     G4int layerID, G4int trapStripID,
				     G4int stripID, G4int cellID )
{
  G4int globalID = -1;

  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();
  
  G4int nEMCells      = ptrList->GetEMNCells();
  G4int nEMStrips     = ptrList->GetEMNStrips();
  G4int nHDStrips     = ptrList->GetHDNStrips();
  G4int nEMTrapStrips = ptrList->GetEMNTrapStrips();
  G4int nHDTrapStrips = ptrList->GetHDNTrapStrips();
  G4int nEMLayers     = ptrList->GetEMNLayers();
  G4int nHDLayers     = ptrList->GetHDNLayers();
  G4int nBlocks       = 3*ptrList->GetNTraps(); // 3 for Barrel and Endcap+/-Z 
  
  G4int nEMTotal      = nEMCells*nEMStrips*nEMTrapStrips*nEMLayers;
  
#if 0
  G4int nHDCells      = ptrList->GetHDNCells();
  G4int nHDTotal      = nHDCells*nHDStrips*nHDTrapStrips*nHDLayers;
  std::cout << "nEMTotal=" << nEMTotal << " " 
	    << "nHDTotal=" << nHDTotal << " "
	    << "nTotal=" << (nEMTotal+nHDTotal)*nBlocks << " "
	    << "INT_MAX=" << INT_MAX << " "
	    << std::endl;
#endif

  globalID = ( isEM )
    ? ((( cellID*nEMStrips+stripID)*nEMTrapStrips+trapStripID)*nEMLayers+layerID)*nBlocks+blockID
    : ( nEMTotal+((cellID*nHDStrips+stripID)*nHDTrapStrips+trapStripID)*nHDLayers+layerID)*nBlocks+blockID;

  if ( globalID > INT_MAX ) {
   std::cerr << "**** Error! CAL globalID over to INT_MAX! " << globalID
	     << " over " << INT_MAX << std::endl;
  }

  if ( globalID < 0 ) {
   std::cerr << "**** Error! CAL globalID is negative! " << globalID << std::endl;
  }

  return globalID;
}

//=====================================================================
//* GetBlockID --------------------------------------------------------
G4int J4CLXAddress::GetBlockID( G4int cellID )
{
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();
  G4int nBlocks = 3*ptrList->GetNTraps(); // 3 for Barrel and Endcap +/-Z position

  return cellID%nBlocks;
}

//=====================================================================
//* GetLayerID --------------------------------------------------------
G4int J4CLXAddress::GetLayerID( G4int cellID, G4bool isEM )
{
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();
  G4int nBlocks   = 3*ptrList->GetNTraps(); // 3 for Barrel and Endcap+/-Z 

  G4int nEMLayers = ptrList->GetEMNLayers();
  G4int nHDLayers = ptrList->GetHDNLayers();
  G4int nEMCells  = ptrList->GetEMNCells();
  G4int nEMStrips = ptrList->GetEMNStrips();
  G4int nEMTrapStrips = ptrList->GetEMNTrapStrips();  
  G4int nEMTotal  = nEMCells*nEMStrips*nEMTrapStrips*nEMLayers;
  G4int blockID   = cellID/nBlocks;
  
  return ( isEM ) ? blockID % nEMLayers
                  : (blockID-nEMTotal) % nHDLayers;
}

//=====================================================================
//* GetStripID --------------------------------------------------------
G4int J4CLXAddress::GetTrapStripID( G4int cellID, G4bool isEM )
{
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();

  G4int nBlocks   = 3*ptrList->GetNTraps(); // 3 for Barrel and Endcap+/-Z
  G4int nEMLayers = ptrList->GetEMNLayers();
  G4int nHDLayers = ptrList->GetHDNLayers();
  G4int nEMTrapStrips = ptrList->GetEMNTrapStrips();
  G4int nHDTrapStrips = ptrList->GetHDNTrapStrips();
  G4int nEMStrips = ptrList->GetEMNStrips();
  G4int nEMCells  = ptrList->GetEMNCells();
  G4int nEMTotal  = nEMCells*nEMStrips*nEMTrapStrips*nEMLayers;
  
  G4int blockID   = cellID/nBlocks;
  return ( isEM ) ? (blockID/nEMLayers)%nEMTrapStrips
                  : ((blockID-nEMTotal)/nHDLayers)%nHDTrapStrips;
}

//=====================================================================
//* GetStripID --------------------------------------------------------
G4int J4CLXAddress::GetStripID( G4int cellID, G4bool isEM )
{
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();

  G4int nBlocks   = 3*ptrList->GetNTraps(); // 3 for Barrel/Endcap+/-Z
  G4int nEMLayers = ptrList->GetEMNLayers();
  G4int nHDLayers = ptrList->GetHDNLayers();
  G4int nEMTrapStrips = ptrList->GetEMNTrapStrips();
  G4int nHDTrapStrips = ptrList->GetHDNTrapStrips();    
  G4int nEMStrips = ptrList->GetEMNStrips();
  G4int nHDStrips = ptrList->GetHDNStrips();
  G4int nEMCells  = ptrList->GetEMNCells();
  G4int nEMTotal  = nEMCells*nEMStrips*nEMTrapStrips*nEMLayers;
  
  G4int blockID   = cellID/nBlocks;
  return ( isEM ) ? (blockID/nEMLayers/nEMTrapStrips)%nEMStrips
                  : ((blockID-nEMTotal)/nHDLayers/nHDTrapStrips)%nHDStrips ;
}

//=====================================================================
//* GetCellID ---------------------------------------------------------
G4int J4CLXAddress::GetCellID( G4int cellID, G4bool isEM )
{
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();

  G4int nBlocks   = 3*ptrList->GetNTraps();  // 3 for Barrel/Endcap+/-Z
  G4int nEMLayers = ptrList->GetEMNLayers();
  G4int nHDLayers = ptrList->GetHDNLayers();
  G4int nEMTrapStrips = ptrList->GetEMNTrapStrips();
  G4int nHDTrapStrips = ptrList->GetHDNTrapStrips();  
  G4int nEMStrips = ptrList->GetEMNStrips();
  G4int nHDStrips = ptrList->GetHDNStrips();
  G4int nEMCells  = ptrList->GetEMNCells();
  G4int nEMTotal  = nEMCells*nEMStrips*nEMTrapStrips*nEMLayers;

  G4int blockID   = cellID/nBlocks;
  return ( isEM ) ? blockID/nEMLayers/nEMTrapStrips/nEMStrips
                  : (blockID-nEMTotal)/nHDLayers/nHDTrapStrips/nHDStrips;
}

//=====================================================================
//* IsBoundary --------------------------------------------------------
G4bool J4CLXAddress::IsBoundary( G4int globalID, G4bool isEM )
{
  G4int stripID = GetStripID( globalID, isEM );
  return ( stripID == 1 ) ? false : true;
}


//=====================================================================
//* IsXNegative -------------------------------------------------------
G4bool J4CLXAddress::IsXNegative( G4int globalID, G4bool isEM )
{
  G4int stripID     = GetStripID( globalID, isEM );
  return ( IsBoundary( globalID, isEM ) && stripID == 0 ) ? true : false;
}

//=====================================================================
//* GetIsBarrel -------------------------------------------------------
G4bool J4CLXAddress::IsBarrel( G4int cellID )
{
  return ( IsEndcap( cellID ) ) ? false : true;
}

//=====================================================================
//* GetIsEndcap -------------------------------------------------------
G4int J4CLXAddress::IsEndcap( G4int cellID, G4bool /*isBarrel*/ )
{
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();
  G4int nTraps  = ptrList->GetNTraps();
  G4int blockID = GetBlockID( cellID );
  
  G4int isEndcap = 0;

  if ( blockID < nTraps )                          isEndcap =  0; // Barrel
  if ( blockID >=   nTraps && blockID < 2*nTraps ) isEndcap =  1; // Endcap+Z
  if ( blockID >= 2*nTraps && blockID < 3*nTraps ) isEndcap = -1; // Endcap-Z

  return isEndcap;
}

//=====================================================================
//* GetNTrapStrips ----------------------------------------------------
G4int J4CLXAddress::GetNTrapStrips( G4bool isEM, G4bool isBarrel )
{
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();

  G4double fgCLXBarrelInnerR  = ptrList->GetBarrelInnerR();
  G4double fgCLXEndcapInnerR  = ptrList->GetEndcapInnerR();
  G4double fgCLXBarrelHalfZ   = ptrList->GetBarrelHalfZ();
  G4double fgCLXGap           = ptrList->GetBarrelEndcapGap();
  G4int    fgCLXEMNLayers     = ptrList->GetEMNLayers();
  G4int    fgCLXHDNLayers     = ptrList->GetHDNLayers();
  G4double fgCLXEMActiveThick = ptrList->GetEMActiveLayerThickness();
  G4double fgCLXHDActiveThick = ptrList->GetHDActiveLayerThickness();
  G4double fgCLXEMAbsThick    = ptrList->GetEMAbsLayerThickness();
  G4double fgCLXHDAbsThick    = ptrList->GetHDAbsLayerThickness();
  G4double fgCLXEMFlexThick   = ptrList->GetEMFlexLayerThickness();
  G4double fgCLXHDFlexThick   = ptrList->GetHDFlexLayerThickness();
  G4double fgCLXCellSize      = ptrList->GetCellSize();
  
  G4double layerThick = (isEM) ? fgCLXEMAbsThick+fgCLXEMActiveThick+fgCLXEMFlexThick
                               : fgCLXHDAbsThick+fgCLXHDActiveThick+fgCLXHDFlexThick;
  G4double EMThick  = layerThick*fgCLXEMNLayers;
  G4double HDThick  = layerThick*fgCLXHDNLayers;
  G4double HDYMax   = fgCLXBarrelInnerR+EMThick+HDThick;
  //G4double halfZ    = (isEM) ? fgCLXBarrelHalfZ-fgCLXGap : fgCLXBarrelHalfZ+EMThick-fgCLXGap;
  G4double halfZ    = (isEM) ? fgCLXBarrelHalfZ-fgCLXGap : fgCLXBarrelHalfZ-fgCLXGap;
  //G4double height   = (isEM) ? ymax-fgCLXEndcapInnerR-fgCLXGap : ymax-fgCLXEndcapInnerR;
  G4double height   = HDYMax-fgCLXEndcapInnerR;

  return (isBarrel) ? (G4int)(2*halfZ/fgCLXCellSize) : (G4int)(height/fgCLXCellSize);
}

//=====================================================================
//* GetNCells ---------------------------------------------------------
G4int J4CLXAddress::GetNCells( G4bool isEM, G4bool isBarrel, G4int id )
{
  J4CLXParameterList *ptrList = J4CLXParameterList::GetInstance();
  
  G4int    fgCLXNTraps        = ptrList->GetNTraps();
  G4double fgCLXBarrelInnerR  = ptrList->GetBarrelInnerR();
  G4double fgCLXEndcapInnerR  = ptrList->GetEndcapInnerR();
  G4int    fgCLXEMNLayers     = ptrList->GetEMNLayers();
  G4double fgCLXEMActiveThick = ptrList->GetEMActiveLayerThickness();
  G4double fgCLXHDActiveThick = ptrList->GetHDActiveLayerThickness();
  G4double fgCLXEMAbsThick    = ptrList->GetEMAbsLayerThickness();
  G4double fgCLXHDAbsThick    = ptrList->GetHDAbsLayerThickness();
  G4double fgCLXEMFlexThick   = ptrList->GetEMFlexLayerThickness();
  G4double fgCLXHDFlexThick   = ptrList->GetHDFlexLayerThickness();
  G4double fgCLXCellSize      = ptrList->GetCellSize();
  
  G4double layerThick = (isEM) ? fgCLXEMAbsThick+fgCLXEMActiveThick+fgCLXEMFlexThick
                               : fgCLXHDAbsThick+fgCLXHDActiveThick+fgCLXHDFlexThick;

  G4double EMThick      = layerThick*fgCLXEMNLayers;

  //* Position of activeLayer front surface
  G4double barrelR = (isEM) ? fgCLXBarrelInnerR+id*layerThick+fgCLXEMAbsThick
                            : fgCLXBarrelInnerR+EMThick+id*layerThick+fgCLXHDAbsThick;
  G4double endcapR = fgCLXEndcapInnerR+id*fgCLXCellSize;
  G4double halfX   = (isBarrel) ? barrelR*std::tan( M_PI/fgCLXNTraps )
                                : endcapR*std::tan( M_PI/fgCLXNTraps );
  G4int    nCells  = 2*(G4int)(halfX/fgCLXCellSize);

  return nCells;
}

//=====================================================================
//* GetCellPosition ---------------------------------------------------
//  Return front surface of cell center position
G4ThreeVector J4CLXAddress::GetCellPosition( G4int globalID, G4bool isEM, G4bool /*isBarrel*/ )
{
  J4CLXParameterList *ptrList = J4CLXParameterList::GetInstance();
  
  G4int    fgCLXNTraps        = ptrList->GetNTraps();
  G4double fgCLXBarrelInnerR  = ptrList->GetBarrelInnerR();
  G4double fgCLXEndcapInnerR  = ptrList->GetEndcapInnerR();
  G4double fgCLXBarrelHalfZ   = ptrList->GetBarrelHalfZ();
  G4double fgCLXGap           = ptrList->GetBarrelEndcapGap();
  G4int    fgCLXEMNLayers     = ptrList->GetEMNLayers();
  //G4int    fgCLXHDNLayers     = ptrList->GetHDNLayers();
  G4double fgCLXEMActiveThick = ptrList->GetEMActiveLayerThickness();
  G4double fgCLXHDActiveThick = ptrList->GetHDActiveLayerThickness();
  G4double fgCLXEMAbsThick    = ptrList->GetEMAbsLayerThickness();
  G4double fgCLXHDAbsThick    = ptrList->GetHDAbsLayerThickness();
  G4double fgCLXEMFlexThick   = ptrList->GetEMFlexLayerThickness();
  G4double fgCLXHDFlexThick   = ptrList->GetHDFlexLayerThickness();
  G4double fgCLXCellSize      = ptrList->GetCellSize();

  G4int cellID       = GetCellID( globalID, isEM );
  //G4int stripID      = GetStripID( globalID, isEM );
  G4int trapStripID  = GetTrapStripID( globalID, isEM );  
  G4int layerID      = GetLayerID( globalID, isEM );
  G4int blockID      = GetBlockID( globalID );

  G4bool isBarrel    = IsBarrel( globalID );
  G4bool isBoundary  = IsBoundary( globalID, isEM );
  G4bool isXNegative = IsXNegative( globalID, isEM );
  //G4int  isEndcap    = IsEndcap( globalID, isBarrel );
  G4int  isEndcap    = IsEndcap( globalID );

  G4double EMLayerThick = fgCLXEMAbsThick+fgCLXEMActiveThick+fgCLXEMFlexThick;
  G4double HDLayerThick = fgCLXHDAbsThick+fgCLXHDActiveThick+fgCLXHDFlexThick;

  G4double layerThick  = (isEM) ? EMLayerThick       : HDLayerThick;
  G4double activeThick = (isEM) ? fgCLXEMActiveThick : fgCLXHDActiveThick;
  G4double absThick    = (isEM) ? fgCLXEMAbsThick    : fgCLXHDAbsThick;  
  G4double EMThick     = EMLayerThick*fgCLXEMNLayers;
  //G4double HDThick     = HDLayerThick*fgCLXHDNLayers;

  //* HalfLength of barrel/endcap and fixed length with cell size
  //G4double barrelHalfL = (isEM) ? fgCLXBarrelHalfZ-fgCLXGap : fgCLXBarrelHalfZ+EMThick-fgCLXGap;
  G4double barrelHalfL = (isEM) ? fgCLXBarrelHalfZ-fgCLXGap : fgCLXBarrelHalfZ-fgCLXGap;
  G4double endcapHalfL = (isEM) ? fgCLXBarrelHalfZ : fgCLXBarrelHalfZ+EMThick;
  G4double barrelFixedHalfL = fgCLXCellSize*(G4int)( barrelHalfL/fgCLXCellSize );
  
  //* Position of activeLayer front surface at barrel/endcap
  G4double barrelR = (isEM) ? fgCLXBarrelInnerR+layerID*EMLayerThick+fgCLXEMAbsThick
                            : fgCLXBarrelInnerR+EMThick+layerID*HDLayerThick+fgCLXHDAbsThick;
  G4double endcapR = fgCLXEndcapInnerR+trapStripID*fgCLXCellSize;

  //* Half length of X/Z
  G4double halfX   = (isBarrel) ? barrelR*std::tan( M_PI/fgCLXNTraps )
                                : endcapR*std::tan( M_PI/fgCLXNTraps );
  
  G4double halfZ   = (isBarrel) ? -barrelFixedHalfL+(trapStripID+0.5)*fgCLXCellSize
                                : endcapHalfL+layerID*layerThick+absThick+0.5*activeThick;
  
  //* Half number of cells and boundary cell half length
  G4int    nCellsHalf = (G4int)( halfX/fgCLXCellSize );
  G4double boundHalfX = 0.5*(halfX-fgCLXCellSize*nCellsHalf); // Boundary cells halfX

  G4double px      = (isBoundary) ? fgCLXCellSize*nCellsHalf+boundHalfX
                                  : -fgCLXCellSize*nCellsHalf+(cellID+0.5)*fgCLXCellSize;
  G4double py      = (isBarrel) ? barrelR+0.5*activeThick
                                : endcapR+0.5*fgCLXCellSize;
  G4double pz      = (isBarrel) ? halfZ
                                : halfZ*isEndcap;
  
  //*  Endcap is negative case, x direction was rotated.
  if ( isEndcap == -1 ) px *= -1;
  if ( isBoundary && isXNegative ) px *= -1.;

  //* Position rotated to -i*dphi direction
  G4ThreeVector position( px, py, pz );
  position.rotateZ( -blockID*2.*M_PI/fgCLXNTraps );

  return position;
}
