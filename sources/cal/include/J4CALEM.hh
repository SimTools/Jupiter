// $Id$
#ifndef __J4CALEM__
#define __J4CALEM__
//*************************************************************************
//* --------------------
//* J4CALEM
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"
#include "J4VCALBlock.hh"
#include "J4CALEMMiniCone.hh"
#include "G4Sphere.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALEMMiniCone;
class J4CALEM : public J4VCALBlock {

public:
  J4CALEM( J4VDetectorComponent *parent   = 0,
                          G4int  nclones   = 1,
                          G4int  nbrothers = 1, 
                          G4int  me        = 0,
                          G4int  copyno    = -1 );
  virtual ~J4CALEM();

  virtual G4String GetFirstName   () const { return fFirstName; }
  virtual G4int    GetNofMiniCones();
  virtual G4double GetInsideRadius();
  virtual G4double GetThickness   ();
  virtual G4String GetMaterial    ();
  virtual G4bool   GetVisAtt      ();
  virtual G4Color  GetColor       ();
  
protected:
  virtual J4VCALMiniCone *Create( J4VDetectorComponent *parent    = 0,
                                                 G4int  nclones   = 1,
				                 G4int  nbrothers = 1, 
                                                 G4int  me        = 0,
                                                 G4int  copyno    = -1 );

private:  
  static const G4String    fFirstName;
};

//=====================================================================               
//* Inline Implementation of Pure Virtuals of Base Class --------------               
 
inline G4int J4CALEM::GetNofMiniCones()
{
  return OpenParameterList()->GetEMMiniConeNClones();
}

inline G4double J4CALEM::GetInsideRadius()
{
  return static_cast<G4Sphere *>(GetMother()->GetSolid())->GetInsideRadius();
}

inline G4double J4CALEM::GetThickness()
{
  return OpenParameterList()->GetEMThickness();
}

inline G4String J4CALEM::GetMaterial()
{
  return OpenParameterList()->GetEMMaterial();
}

inline G4bool J4CALEM::GetVisAtt()
{
  return OpenParameterList()->GetEMVisAtt();
}

inline G4Color J4CALEM::GetColor()
{
  return OpenParameterList()->GetEMColor();
}

#endif
