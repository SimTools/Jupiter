// $Id$
#ifndef __J4CALHDABSLAYER__
#define __J4CALHDABSLAYER__
//*************************************************************************
//* --------------------
//* J4CALHDAbsLayer
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALSubLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALHDAbsLayer : public J4VCALSubLayer {

public:
  J4CALHDAbsLayer( J4VDetectorComponent  *parent   = 0,
                                   G4int  nclones   = 1,
                                   G4int  nbrothers = 1, 
                                   G4int  me        = 0,
                                   G4int  copyno    = -1 );
  virtual ~J4CALHDAbsLayer();

  virtual G4String GetFirstName      () const { return fFirstName; }
  virtual G4double GetStartThickness ();
  virtual G4double GetEndThickness   ();
  virtual G4String GetMaterial       ();
  virtual G4bool   GetVisAtt         ();
  virtual G4Color  GetColor          ();

private:
  void  Cabling ();

private:  
  static const G4String fFirstName;

};

//=====================================================================               
//* Inline Implementation of Pure Virtuals of Base Class --------------               
 
inline G4double J4CALHDAbsLayer::GetStartThickness()
{
  return 0.;
}

inline G4double J4CALHDAbsLayer::GetEndThickness()
{
  return OpenParameterList()->GetHDAbsLayerThickness();
}

inline G4String J4CALHDAbsLayer::GetMaterial()
{
  return OpenParameterList()->GetHDAbsLayerMaterial();
}

inline G4bool J4CALHDAbsLayer::GetVisAtt()
{
  return OpenParameterList()->GetSubLayerVisAtt();
}

inline G4Color J4CALHDAbsLayer::GetColor()
{
  return OpenParameterList()->GetSubLayerColor();
}

#endif
