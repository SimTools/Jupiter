// $Id$
#ifndef __J4CALEMMINICONE__
#define __J4CALEMMINICONE__
//*************************************************************************
//* --------------------
//* J4CALEMMiniCone
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALMiniCone.hh"
#include "J4CALEMMiniTower.hh"
#include "G4Sphere.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALEMMiniTower;
class J4CALEMMiniCone : public J4VCALMiniCone {	

public:
  J4CALEMMiniCone(J4VDetectorComponent *parent    = 0,
                                 G4int  nclones   = 1,
                                 G4int  nbrothers = 1, 
                                 G4int  me        = 0,
                                 G4int  copyno    = -1 );
  virtual ~J4CALEMMiniCone();

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
 
inline G4int J4CALEMMiniCone::GetNofMiniCones()
{
  return OpenParameterList()->GetEMMiniConeNClones();
}

inline G4int J4CALEMMiniCone::GetNofMiniTowers()
{
  return OpenParameterList()->GetEMMiniTowerNClones();
}

inline G4String J4CALEMMiniCone::GetMaterial()
{
  return OpenParameterList()->GetMiniConeMaterial();
}

inline G4bool J4CALEMMiniCone::GetVisAtt()
{
  return OpenParameterList()->GetMiniConeVisAtt();
}

inline G4Color J4CALEMMiniCone::GetColor()
{
  return OpenParameterList()->GetMiniConeColor();
}

#endif
