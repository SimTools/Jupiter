// $Id$
#ifndef __J4VCALSUBLAYERSD__
#define __J4VCALSUBLAYERSD__
//*************************************************************************
//* --------------------
//* J4VCALSubLayerSD
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
#include "J4VCALSubLayer.hh"
#include "J4CALAddress.hh"
#include "J4CALParameterList.hh"
#include <map>

//=====================================================================
//---------------------
// class definition
//---------------------
class J4VCALSubLayerSD : public J4VSD<J4CALHit>{
  
public:
  J4VCALSubLayerSD( J4VDetectorComponent* ptrDetector );
  ~J4VCALSubLayerSD();

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
      G4cerr << "J4VCALSubLayerSD::OutputAll: No HitBuf! " << G4endl;
    }
  }
 
  using J4VSD<J4CALHit>::operator=;
#if 0
  inline virtual const J4VCALSubLayerSD& operator=( const J4VSD<J4CALHit> &right )
  {
    J4VSD<J4CALHit>::operator=( right );
    return *this;
  }
#endif

  inline static void SetHCID( G4int i ) { fgLastHCID = i; }

  virtual G4bool IsEM() = 0;

private:
  static G4int fgLastHCID;
  static std::multimap< G4int, J4CALHit* > fgCalHits; // multimap<cellid, map<prehitid, calhit*>>
  G4int         fNTowers;

  G4int         fCellID;
  G4int         fConeID;
  G4int         fTowerID;
  G4int         fMiniConeID;
  G4int         fMiniTowerID;
  G4int         fLayerID;
  G4int         fSubLayerID;
  G4bool        fIsBarrel;
};

#endif
