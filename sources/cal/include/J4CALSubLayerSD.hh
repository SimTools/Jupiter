// $Id$
#ifndef __J4CALSUBLAYERSD__
#define __J4CALSUBLAYERSD__
//*************************************************************************
//* --------------------
//* J4CALSubLayerSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4CALSubLayer
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*	2004/08/30  Ono Hiroaki Add GetCellID <ono@hep.sc.niigata-u.ac.jp>
//*************************************************************************
 
#include "J4VSD.hh"
#include "J4CALHit.hh"
#include "J4VComponent.hh"
#include "J4CALSubLayer.hh"
#include "TVAddress.hh"
#include "J4CALParameterList.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4CALSubLayerSD : public J4VSD<J4CALHit>{
  
public:

  J4CALSubLayerSD( J4VDetectorComponent* ptrDetector );
  ~J4CALSubLayerSD();

  virtual G4bool ProcessHits( G4Step* aStep, G4TouchableHistory* ROhist );
  virtual void   Initialize ( G4HCofThisEvent* HCTE );
  virtual void   EndOfEvent ( G4HCofThisEvent* HCTE );

  virtual void   DrawAll();
  virtual void   PrintAll();
 
  virtual void   OutputAll( G4HCofThisEvent* HCTE )
  {
    if( GetHitBuf() ) {
      J4VSD<J4CALHit>::OutputAll( HCTE );
    } else {
      G4cerr << "J4CALSubLayerSD::OutputAll: No HitBuf! " << G4endl;
    }
  }
 
  inline virtual const J4CALSubLayerSD& operator=( const J4VSD<J4CALHit> &right )
  {
    J4VSD<J4CALHit>::operator=( right );
    return *this;
  }

  inline void InitCellID() {
    fConeID = -1; fTowerID = -1; fMiniConeID = -1; fMiniTowerID = -1; fLayerID = -1; fSubLayerID = -1; fIsBarrel = -1; fIsEM = -1;
  }
  
  inline void SetCellID( TVAddress* address ) {
    fConeID      = address -> GetConeID();
    fTowerID     = address -> GetTowerID();
    fMiniConeID  = address -> GetMiniConeID();
    fMiniTowerID = address -> GetMiniTowerID();
    fLayerID     = address -> GetLayerID();
    fSubLayerID  = address -> GetSubLayerID();
    fIsBarrel    = address -> IsBarrel();
    fIsEM        = address -> IsEM();
  }

  inline G4int GetCellID( TVAddress* address ) ;
  inline static void SetHCID( G4int i ) { fgLastHCID = i; }
  
//  inline G4bool IsAddress( TVAddress** address ) {
//    
//    for ( G4int i = 0; i < address.size(); i++ ) {
//      if ( fConeID         == address[i] -> GetConeID() 
//	   && fTowerID     == address[i] -> GetTowerID()
//	   && fMiniConeID  == address[i] -> GetMiniConeID()
//	   && fMiniTowerID == address[i] -> GetMiniTowerID()
//	   && fLayerID     == address[i] -> GetLayerID()
//	   && fSubLayerID  == address[i] -> GetSubLayerID()
//	   && fIsBarrel    == address[i] -> IsBarrel()
//	   && fIsEM        == address[i] -> IsEM() ) 
//	} 	
//
//      else
//	return FALSE;
//    }
//  }
//
//  inline G4bool CheckCellID( TVAddress* address ) {
//    if ( fConeID      == address -> GetConeID() 
//	 && fTowerID     == address -> GetTowerID()
//	 && fMiniConeID  == address -> GetMiniConeID()
//	 && fMiniTowerID == address -> GetMiniTowerID()
//	 && fLayerID     == address -> GetLayerID()
//	 && fSubLayerID  == address -> GetSubLayerID()
//	 && fIsBarrel    == address -> IsBarrel()
//	 && fIsEM        == address -> IsEM() )
//      return TRUE;
//    else
//      return FALSE;
//  }
  
private:
  static G4int fgLastHCID;
  static G4int currentPreHitID;
  std::vector<TVAddress*> fAddress;
  //J4CALHit    **fCalHits;
  //  static std::vector<J4CALHit*> fgCalHits;
  static std::vector<J4CALHit*> fgCalHits;
  G4int         fNTowers;

  G4int         fCellID;
  G4int         fConeID;
  G4int         fTowerID;
  G4int         fMiniConeID;
  G4int         fMiniTowerID;
  G4int         fLayerID;
  G4int         fSubLayerID;
  G4bool        fIsBarrel;
  G4bool        fIsEM;
};

////////////////////////////////////////////////////////////
// inline function
G4int J4CALSubLayerSD::GetCellID( TVAddress* address )
{
  G4int cellid = -1;
  G4int  coneID      = address -> GetConeID();
  G4int  towerID     = address -> GetTowerID();
  G4int  miniConeID  = address -> GetMiniConeID();
  G4int  miniTowerID = address -> GetMiniTowerID();
  G4int  layerID     = address -> GetLayerID();
  //  G4int  subLayerID  = address -> GetSubLayerID();
  //G4bool isBarrel    = address -> IsBarrel();
  G4bool isEM        = address -> IsEM();

  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  //  G4int  nCones        = ptrList -> GetNcones();
  const G4int nEMLayers     = ptrList -> GetEMNLayers();
  const G4int nHDLayers     = ptrList -> GetHDNLayers();
  const G4int nEMMiniCones  = ptrList -> GetEMMiniConeNClones();
  const G4int nHDMiniCones  = ptrList -> GetHDMiniConeNClones();
  const G4int nEMMiniTowers = ptrList -> GetEMMiniTowerNClones();
  const G4int nHDMiniTowers = ptrList -> GetHDMiniTowerNClones();
  const G4int nEMs = nEMMiniCones * nEMMiniTowers * nEMLayers;
  const G4int nHDs = nHDMiniCones * nHDMiniTowers * nHDLayers;
  G4int  nTowers       = fNTowers;

#if 0
  G4cerr << "coneID:"      << coneID      << " "
	 << "towerID:"     << towerID     << " "
	 << "miniConeID:"  << miniConeID  << " "
	 << "miniTowerID:" << miniTowerID << " "
	 << "layerID:"     << layerID     << " "
	 <<  G4endl;
#endif
#if 0
  G4cerr //<< __FILE__ << " " << __LINE__ << " : "
         //<< "nCones = "        << nCones << " "
         << "nTowers = "       << nTowers << " "
         << "nEMMiniCones = "  << nEMMiniCones << " "
         << "nHDMiniCones = "  << nHDMiniCones << " "
         << "nEMMiniTowers = " << nEMMiniTowers << " "
         << "nHDMiniTowers = " << nHDMiniTowers << " "
	 << "nEMLayers = "     << nEMLayers << " "
         << "nHDLayers = "     << nHDLayers << " "
         << G4endl;
#endif
  
  G4int EMHDID      = -1;
  //  G4int  nSubLayers  = -1;

  if ( isEM ) {
    EMHDID = miniConeID + nEMMiniCones*( miniTowerID + nEMMiniTowers * layerID );
  } else {
    EMHDID = miniConeID + nHDMiniCones*( miniTowerID + nHDMiniTowers * layerID ) + nEMs;
  }
  
  cellid = towerID + nTowers*( coneID*( nEMs + nHDs ) + EMHDID );
  //cellid = coneID*( nEMs + nHDs ) + EMHDID;

  fCellID = cellid;
  return fCellID;
}

#endif
