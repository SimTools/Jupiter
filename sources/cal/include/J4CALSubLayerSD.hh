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
//*	2003/03/18  K.Hoshina	      Original version.
//*	2004/08/30  Ono Hiroaki       Add GetCellID <ono@hep.sc.niigata-u.ac.jp>
//*     2004/10/12  Allister Sanchez  Removed GetCellID.
//*                                   Use std:multimap for monitoring hits.
//*************************************************************************
#include "J4VSD.hh"
#include "J4CALHit.hh"
#include "J4VComponent.hh"
#include "J4CALSubLayer.hh"
#include "TVAddress.hh"
#include "J4CALParameterList.hh"
#include <map>

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
    fConeID = -1; fTowerID = -1; fMiniConeID = -1; fMiniTowerID = -1; fLayerID = -1; fSubLayerID = -1; /* fIsBarrel = -1; fIsEM = -1; */
  }
  
  inline void SetCellID( TVAddress* address ) {
    fConeID      = address -> GetConeID();
    fTowerID     = address -> GetTowerID();
    fMiniConeID  = address -> GetMiniConeID();
    fMiniTowerID = address -> GetMiniTowerID();
    fLayerID     = address -> GetLayerID();
    fSubLayerID  = address -> GetSubLayerID();
//    fIsBarrel    = address -> IsBarrel();
//    fIsEM        = address -> IsEM();
  }

  inline void SetCellID(G4int cone, G4int tower,
			G4int mcone, G4int mtower,
			G4int layer, G4int sublyr) {
    fConeID      = cone;
    fTowerID     = tower;
    fMiniConeID  = mcone;
    fMiniTowerID = mtower;
    fLayerID     = layer;
    fSubLayerID  = sublyr;
  }

  inline static void SetHCID( G4int i ) { fgLastHCID = i; }
  
private:
  static G4int fgLastHCID;
  static G4int fgCurrentPreHitID;
  static std::multimap<G4int, J4CALHit*> fgCalHits; // multimap<cellid, map<prehitid, calhit*>>
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

#endif
