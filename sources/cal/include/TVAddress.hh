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
             G4int  subLayerID, 
             G4bool isBarrel, 
             G4bool isEM,
	     G4ThreeVector position );

  TVAddress( const TVAddress& rhs );

  TVAddress& operator=( const TVAddress& rhs )
  {
    fConeID      = rhs.fConeID;
    fTowerID     = rhs.fTowerID;
    fMiniConeID  = rhs.fMiniConeID;
    fMiniTowerID = rhs.fMiniTowerID;
    fLayerID     = rhs.fLayerID;
    fSubLayerID  = rhs.fSubLayerID;
    fIsBarrel    = rhs.fIsBarrel;
    fIsEM        = rhs.fIsEM;
    fPosition    = rhs.fPosition;
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
	 && fIsBarrel    == rhs.fIsBarrel
	 && fIsEM        == rhs.fIsEM )
      return TRUE;
    else
      return FALSE;
  }
  
public:
  ~TVAddress();
  void Draw() ;
  void Print() const ;
  G4bool IsInitialize( TVAddress* address ) ;

  // getter/setter
public:
  
  inline G4int  GetConeID()       const { return fConeID;      }
  inline G4int  GetTowerID()      const { return fTowerID;     }
  inline G4int  GetMiniConeID()   const { return fMiniConeID;  }
  inline G4int  GetMiniTowerID()  const { return fMiniTowerID; }
  inline G4int  GetLayerID()      const { return fLayerID;     }
  inline G4int  GetSubLayerID()   const { return fSubLayerID;  }
  inline G4bool IsBarrel()        const { return fIsBarrel;    }
  inline G4bool IsEM()            const { return fIsEM;        }
  inline G4ThreeVector GetPosition() const { return fPosition; }
  //inline G4int  GetCellID()       const { return fgCellID;     }

  inline void SetConeID( G4int n )      { fConeID       = n; }
  inline void SetTowerID( G4int n )     { fTowerID      = n; }
  inline void SetMiniConeID( G4int n )  { fMiniConeID   = n; }
  inline void SetMiniTowerID( G4int n ) { fMiniTowerID  = n; }
  inline void SetLayerID( G4int n )     { fLayerID      = n; }
  inline void SetSubLayerID( G4int n )  { fSubLayerID   = n; }
  inline void SetIsBarrel( G4bool b )   { fIsBarrel     = b; }
  inline void SetIsEM( G4bool b )       { fIsEM         = b; }
  inline void SetPosition(G4ThreeVector v) { fPosition  = v; }
  //inline void SetCellID( G4int n )      { fgCellID       = n; }

private:
  G4int   fConeID; 
  G4int   fTowerID; 
  G4int   fMiniConeID; 
  G4int   fMiniTowerID; 
  G4int   fLayerID; 
  G4int   fSubLayerID; 
  G4bool  fIsBarrel;
  G4bool  fIsEM;
 // static  G4int   fgCellID;
  G4ThreeVector fPosition;

};

#endif
