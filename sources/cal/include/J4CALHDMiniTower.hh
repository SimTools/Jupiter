// $Id$
#ifndef __J4CALHDMINITOWER__
#define __J4CALHDMINITOWER__
//*************************************************************************
//* --------------------
//* J4CALHDMiniTower
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALMiniTower.hh"
#include "J4CALHDLayer.hh"
#include "G4Sphere.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALHDLayer;
class J4CALHDMiniTower : public J4VCALMiniTower {	

public:
  J4CALHDMiniTower(J4VDetectorComponent *parent    = 0,
                                  G4int  nclones   = 1,
                                  G4int  nbrothers = 1, 
                                  G4int  me        = 0,
                                  G4int  copyno    = -1 );
  virtual ~J4CALHDMiniTower();

  virtual G4String GetFirstName    () const { return fFirstName; }
  virtual G4int    GetNofMiniTowers();
  virtual G4int    GetNofLayers    ();
  virtual G4String GetMaterial     ();
  virtual G4bool   GetVisAtt       ();
  virtual G4Color  GetColor        ();

protected:
  virtual J4VCALLayer *Create( J4VDetectorComponent *parent    = 0,
                                              G4int  nclones   = 1,
                                              G4int  nbrothers = 1, 
                                              G4int  me        = 0,
                                              G4int  copyno    = -1 );

private:  
  static const G4String   fFirstName;

};

//=====================================================================               
//* Inline Implementation of Pure Virtuals of Base Class --------------               
 
inline G4int J4CALHDMiniTower::GetNofMiniTowers()
{
  return OpenParameterList()->GetHDMiniTowerNClones();
}

inline G4int J4CALHDMiniTower::GetNofLayers()
{
  return OpenParameterList()->GetHDNLayers();
}

inline G4String J4CALHDMiniTower::GetMaterial()
{
  return OpenParameterList()->GetMiniTowerMaterial();
}

inline G4bool J4CALHDMiniTower::GetVisAtt()
{
  return OpenParameterList()->GetMiniTowerVisAtt();
}

inline G4Color J4CALHDMiniTower::GetColor()
{
  return OpenParameterList()->GetMiniTowerColor();
}



#endif
