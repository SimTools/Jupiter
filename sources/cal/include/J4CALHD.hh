// $Id$
#ifndef __J4CALHD__
#define __J4CALHD__
//*************************************************************************
//* --------------------
//* J4CALHD
//* --------------------
//* (Description)
//* 	Class to describe HD block of CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2004/11/14  K.Fujii     Most of its implementation now in is
//*				base class, J4CALBlock.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"
#include "J4CALBlock.hh"
#include "J4CALHit.hh"
#include "G4Sphere.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALHD : public J4CALBlock {
public:
  J4CALHD( J4VDetectorComponent *parent   = 0,
                         G4int  nclones   = 1,
                         G4int  nbrothers = 1, 
                         G4int  me        = 0,
                         G4int  copyno    = -1 );
  virtual ~J4CALHD();

  virtual G4String GetFirstName   () const { return fFirstName; }
  virtual G4int    GetNofMiniCones();
  virtual G4double GetInnerRadius ();
  virtual G4double GetThickness   ();
  virtual G4String GetMaterial    ();
  virtual G4bool   GetVisAtt      ();
  virtual G4Color  GetColor       ();

private:  
  static const G4String    fFirstName;
};

//=====================================================================
//* Inline Implementation of Pure Virtuals of Base Class --------------

inline G4int J4CALHD::GetNofMiniCones()
{
  return OpenParameterList()->GetHDMiniConeNClones();
}

inline G4double J4CALHD::GetInnerRadius()
{
  return static_cast<G4Sphere *>(GetMother()->GetSolid())->GetInsideRadius()
         + OpenParameterList()->GetEMThickness();
}

inline G4double J4CALHD::GetThickness()
{ 
  return OpenParameterList()->GetHDThickness();
}

inline G4String J4CALHD::GetMaterial()
{
  return OpenParameterList()->GetHDMaterial();
}

inline G4bool J4CALHD::GetVisAtt()
{
  return OpenParameterList()->GetHDVisAtt();
} 

inline G4Color J4CALHD::GetColor()
{
  return OpenParameterList()->GetHDColor();
} 

#endif
