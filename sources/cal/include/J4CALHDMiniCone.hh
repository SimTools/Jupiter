// $Id$
#ifndef __J4CALHDMINICONE__
#define __J4CALHDMINICONE__
//*************************************************************************
//* --------------------
//* J4CALHDMiniCone
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"
#include "J4VCALMiniCone.hh"
#include "J4CALHDMiniTower.hh"
#include "G4Sphere.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALHDMiniTower;
class J4CALHDMiniCone : public J4VCALMiniCone {	

public:
  J4CALHDMiniCone(J4VDetectorComponent *parent    = 0,
                                 G4int  nclones   = 1,
                                 G4int  nbrothers = 1, 
                                 G4int  me        = 0,
                                 G4int  copyno    = -1 );
  virtual ~J4CALHDMiniCone();

  virtual G4String GetFirstName    () const { return fFirstName; }
  virtual G4int    GetNofMiniCones ();
  virtual G4int    GetNofMiniTowers();
  virtual G4String GetMaterial     ();
  virtual G4bool   GetVisAtt       ();
  virtual G4Color  GetColor        ();

protected:
  virtual J4VCALMiniTower *Create( J4VDetectorComponent *parent    = 0,
                                                  G4int  nclones   = 1,
				                  G4int  nbrothers = 1, 
                                                  G4int  me        = 0,
                                                  G4int  copyno    = -1 );

private:  
  static const G4String  fFirstName;
};

//=====================================================================               
//* Inline Implementation of Pure Virtuals of Base Class --------------               
 
inline G4int J4CALHDMiniCone::GetNofMiniCones()
{
  return OpenParameterList()->GetHDMiniConeNClones();
}

inline G4int J4CALHDMiniCone::GetNofMiniTowers()
{
  return OpenParameterList()->GetHDMiniTowerNClones();
}

inline G4String J4CALHDMiniCone::GetMaterial()
{
  return OpenParameterList()->GetMiniConeMaterial();
}

inline G4bool J4CALHDMiniCone::GetVisAtt()
{
  return OpenParameterList()->GetMiniConeVisAtt();
}

inline G4Color J4CALHDMiniCone::GetColor()
{
  return OpenParameterList()->GetMiniConeColor();
}

#endif
