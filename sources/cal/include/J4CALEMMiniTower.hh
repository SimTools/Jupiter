// $Id$
#ifndef __J4CALEMMINITOWER__
#define __J4CALEMMINITOWER__
//*************************************************************************
//* --------------------
//* J4CALEMMiniTower
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALMiniTower.hh"
#include "J4CALEMLayer.hh"
#include "G4Sphere.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALEMLayer;
class J4CALEMMiniTower : public J4VCALMiniTower {	

public:
  J4CALEMMiniTower(J4VDetectorComponent *parent    = 0,
                                  G4int  nclones   = 1,
                                  G4int  nbrothers = 1, 
                                  G4int  me        = 0,
                                  G4int  copyno    = -1 );
  virtual ~J4CALEMMiniTower();

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
 
inline G4int J4CALEMMiniTower::GetNofMiniTowers()
{
  return OpenParameterList()->GetEMMiniTowerNClones();
}

inline G4int J4CALEMMiniTower::GetNofLayers()
{
  return OpenParameterList()->GetEMNLayers();
}

inline G4String J4CALEMMiniTower::GetMaterial()
{
  return OpenParameterList()->GetMiniTowerMaterial();
}

inline G4bool J4CALEMMiniTower::GetVisAtt()
{
  return OpenParameterList()->GetMiniTowerVisAtt();
}

inline G4Color J4CALEMMiniTower::GetColor()
{
  return OpenParameterList()->GetMiniTowerColor();
}

#endif
