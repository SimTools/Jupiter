// $Id$
//*************************************************************************
//* --------------------
//* TVAddress
//* --------------------
//* (Description)
//*     Cell addressor for converting cell address and position
//*     
//* (Update Record)
//*     Preriminal version
//*     2004/08/01  ONO Hiroaki  <ono@hep.sc.niigata-u.ac.jp>
//*************************************************************************
#ifndef __TVADDRESS__
#define __TVADDRESS__

#include "J4CALParameterList.hh"
#include "J4CALSubLayerParameterList.hh"

//=========================================================================
//---------------------
// class definition
//---------------------

class TVAddress {

public:
  TVAddress();

  TVAddress( G4int  coneID, 
             G4int  towerID, 
             G4int  miniConeID, 
             G4int  miniTowerID, 
             G4int  layerID, 
             G4int  subLayerID /*, */
	     /* G4bool isBarrel,*/ 
             /* G4bool isEM */ );

  TVAddress( const TVAddress& rhs );

  TVAddress& operator=( const TVAddress& rhs )
  {
    fConeID      = rhs.fConeID;
    fTowerID     = rhs.fTowerID;
    fMiniConeID  = rhs.fMiniConeID;
    fMiniTowerID = rhs.fMiniTowerID;
    fLayerID     = rhs.fLayerID;
    fSubLayerID  = rhs.fSubLayerID;
    /*    fIsBarrel    = rhs.fIsBarrel;*/
    /*   fIsEM        = rhs.fIsEM; */
    return *this;
  }

  G4bool operator==( const TVAddress& rhs )
  {
    if ( fConeID         == rhs.fConeID
	 && fTowerID     == rhs.fTowerID
	 && fMiniConeID  == rhs.fMiniConeID
	 && fMiniTowerID == rhs.fMiniTowerID
	 && fLayerID     == rhs.fLayerID
	 && fSubLayerID  == rhs.fSubLayerID
	 /* && fIsBarrel    == rhs.fIsBarrel */
	 /* && fIsEM        == rhs.fIsEM */ )
      return TRUE;
    else
      return FALSE;
  }
  
public:
  ~TVAddress();
  void Draw() ;
  void Print() const ;

  // getter/setter
public:
  
  inline G4int  GetConeID()       const { return fConeID;      }
  inline G4int  GetTowerID()      const { return fTowerID;     }
  inline G4int  GetMiniConeID()   const { return fMiniConeID;  }
  inline G4int  GetMiniTowerID()  const { return fMiniTowerID; }
  inline G4int  GetLayerID()      const { return fLayerID;     }
  inline G4int  GetSubLayerID()   const { return fSubLayerID;  }
  //  inline G4bool IsBarrel()        const { return fIsBarrel;    }
  //  inline G4bool IsEM()            const { return fIsEM;        }

  inline void SetConeID( G4int n )      { fConeID       = n; }
  inline void SetTowerID( G4int n )     { fTowerID      = n; }
  inline void SetMiniConeID( G4int n )  { fMiniConeID   = n; }
  inline void SetMiniTowerID( G4int n ) { fMiniTowerID  = n; }
  inline void SetLayerID( G4int n )     { fLayerID      = n; }
  inline void SetSubLayerID( G4int n )  { fSubLayerID   = n; }
  //  inline void SetIsBarrel( G4bool b )   { fIsBarrel     = b; }
  //  inline void SetIsEM( G4bool b )       { fIsEM         = b; }

  static G4int GetCellConeID( G4int cellID );
  static G4int GetCellTowerID( G4int cellID );
  static G4int GetCellMiniConeID( G4int cellID, G4bool isEM );
  static G4int GetCellMiniTowerID( G4int cellID, G4bool isEM );
  static G4int GetCellLayerID( G4int cellID, G4bool isEM );
  static G4int GetCellSubLayerID( G4int cellID,G4bool isEM );
  //  static G4bool GetCellIsBarrel( G4int cellID );
  //  static G4bool GetCellIsEM( G4int cellID );
  
  inline TVAddress* GetAddress()  const { return fAddress;    }
  inline void SetAddress( TVAddress* address ) { fAddress = address; }
  
  inline G4int GetCellID( G4bool isEM
                          /* G4int coneID, G4int towerID, */
			  /* G4int miniConeID, G4int miniTowerID, */
			  /* G4int layerID, G4int subLayerID, */
			  /* G4bool isBarrel, G4bool isEM */ );
  
  inline TVAddress* GetCellAddress( G4int cellID, G4bool isEM );
  //static TVAddress* GetCellAddress( G4int cellID );
  
private:
  G4int   fConeID; 
  G4int   fTowerID; 
  G4int   fMiniConeID; 
  G4int   fMiniTowerID; 
  G4int   fLayerID; 
  G4int   fSubLayerID; 
  //  G4bool  fIsBarrel;
  //  G4bool  fIsEM;
  G4int   fCellID;
  TVAddress* fAddress;

};

inline G4int TVAddress::GetCellID( G4bool isEM
				   /* G4int coneID, G4int towerID,*/
				   /* G4int miniConeID, G4int miniTowerID,*/
				   /* G4int layerID, G4int subLayerID, */
				  /* G4bool isBarrel, G4bool isEM */ )
{
  G4int  cellID      = -1;
  
  G4int  coneID      = fConeID;
  G4int  towerID     = fTowerID;
  G4int  miniConeID  = fMiniConeID;
  G4int  miniTowerID = fMiniTowerID;
  G4int  layerID     = fLayerID;
  G4int  subLayerID  = fSubLayerID;

#if 0  
  G4cerr << "coneID:" << coneID << " "
	 << "towerID:" << towerID << " "
	 << "miniConeID:" << miniConeID << " "
	 << "miniTowerID:" << miniTowerID << " "
	 << "layerID:" << layerID << " "
	 << "subLayerID:" << subLayerID << " "
    	 << "isBarrel:" << isBarrel << " "
    	 << "isEM:" << isEM << " "
	 << G4endl;
#endif  
    
#if 1
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  //  J4CALSubLayerParameterList* ptrSubList = ptrList -> GetSubLayerParam();
  
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
#endif
  fCellID = cellID;
  
  return fCellID;
}

inline TVAddress* TVAddress::GetCellAddress( G4int cellID, G4bool isEM )
{
#if 1
  G4int  coneID      = -1;
  G4int  towerID     = -1;
  G4int  miniConeID  = -1;
  G4int  miniTowerID = -1;
  G4int  layerID     = -1;
  G4int  subLayerID  = -1;
  //  G4bool isBarrel    = -1;
  //  G4bool isEM        = -1;
#endif
  
#if 0  
  G4int  coneID      = fConeID;
  G4int  towerID     = fTowerID;
  G4int  miniConeID  = fMiniConeID;
  G4int  miniTowerID = fMiniTowerID;
  G4int  layerID     = fLayerID;
  G4int  subLayerID  = fSubLayerID;
  //  G4bool isBarrel    = fIsBarrel;
  //  G4bool isEM        = fIsEM;
#endif
  
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  J4CALSubLayerParameterList* ptrSubList = ptrList -> GetSubLayerParam();

  const G4int nCones        = ptrList -> GetNcones();
  const G4int nTowers       = ptrList -> GetConstNTowers(); // Set as constant value for tower
  const G4int nIsEM         = ptrList -> GetNIsEM();
  const G4int nEMMiniCones  = ptrList -> GetEMMiniConeNClones();
  const G4int nHDMiniCones  = ptrList -> GetHDMiniConeNClones();
  const G4int nEMMiniTowers = ptrList -> GetEMMiniTowerNClones();
  const G4int nHDMiniTowers = ptrList -> GetHDMiniTowerNClones();
  const G4int nEMLayers     = ptrList -> GetEMNLayers();
  const G4int nHDLayers     = ptrList -> GetHDNLayers();
  //  const G4int nIsBarrel     = ptrList -> GetNIsBarrel();
  const G4int nEMSubLayers = ptrSubList -> GetNLayers( "EM" );
  const G4int nHDSubLayers = ptrSubList -> GetNLayers( "HD" );
  
  coneID  = cellID % nCones;
  towerID = cellID / nCones % nTowers;

//  if ( ( cellID / nCones / nTowers % nIsEM ) == 1 )
//    isEM = true;
//  if ( ( cellID / nCones / nTowers % nIsEM ) != 1 )
//    isEM = false;

//  nEMSubLayers  = ptrSubList -> GetNLayers( "EM" );
//  nHDSubLayers  = ptrSubList -> GetNLayers( "HD" );

  //  const G4int nEMs = nEMMiniCones * nEMMiniTowers * nEMLayers * nEMSubLayers * nIsBarrel;
  //  const G4int nEMs = nEMMiniCones * nEMMiniTowers * nEMLayers * nEMSubLayers;
  
  if ( isEM ) {
    miniConeID  = cellID / nCones / nTowers / nIsEM % nEMMiniCones;
    miniTowerID = cellID / nCones / nTowers / nIsEM / nEMMiniCones % nEMMiniTowers;
    layerID     = cellID / nCones / nTowers / nIsEM / nEMMiniCones / nEMMiniTowers % nEMLayers;
    subLayerID  = cellID / nCones / nTowers / nIsEM / nEMMiniCones / nEMMiniTowers / nEMLayers % nEMSubLayers;
    //    isBarrel    = cellID / nCones / nTowers / nIsEM / nEMMiniCones / nEMMiniTowers / nEMLayers / nEMSubLayers % nIsBarrel;
  } else {
    miniConeID  = cellID / nCones / nTowers / nIsEM % nHDMiniCones;
    miniTowerID = cellID / nCones / nTowers / nIsEM / nHDMiniCones % nHDMiniTowers;
    layerID     = cellID / nCones / nTowers / nIsEM / nHDMiniCones / nHDMiniTowers % nHDLayers;
    subLayerID  = cellID / nCones / nTowers / nIsEM / nHDMiniCones / nHDMiniTowers / nHDLayers % nHDSubLayers;
    //    isBarrel    = cellID / nCones / nTowers / nIsEM / nHDMiniCones / nHDMiniTowers / nHDLayers / nHDSubLayers % nIsBarrel;
  }

  TVAddress* address = new TVAddress( coneID, towerID, miniConeID, miniTowerID, layerID, subLayerID /* , isBarrel, isEM */ );
  
  fConeID      = coneID;
  fTowerID     = towerID;
  fMiniConeID  = miniConeID;
  fMiniTowerID = miniTowerID;
  fLayerID     = layerID;
  fSubLayerID  = subLayerID;
  //  fIsBarrel    = isBarrel;
  //  fIsEM        = isEM;

  fAddress = address;
  
  delete address;
  
  return fAddress;
}

#endif
