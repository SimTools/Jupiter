// $Id$
#ifndef __J4CALHDACTIVELAYER__
#define __J4CALHDACTIVELAYER__
//*************************************************************************
//* --------------------
//* J4CALHDActiveLayer
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALHDLayer.hh"
#include "J4VCALSubLayer.hh"
#include "J4CALHDActiveLayerSD.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALHDActiveLayerSD;
class J4CALHDActiveLayer : public J4VCALSubLayer {

public:
  J4CALHDActiveLayer( J4VDetectorComponent  *parent   = 0,
                                      G4int  nclones   = 1,
                                      G4int  nbrothers = 1, 
                                      G4int  me        = 0,
                                      G4int  copyno    = -1 );
  virtual ~J4CALHDActiveLayer();

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
 
inline G4double J4CALHDActiveLayer::GetStartThickness()
{
  return OpenParameterList()->GetHDAbsLayerThickness();
}

inline G4double J4CALHDActiveLayer::GetEndThickness()
{
  return OpenParameterList()->GetHDActiveLayerThickness();
}

inline G4String J4CALHDActiveLayer::GetMaterial()
{
  return OpenParameterList()->GetHDActiveLayerMaterial();
}

inline G4bool J4CALHDActiveLayer::GetVisAtt()
{
  return OpenParameterList()->GetSubLayerVisAtt();
}

inline G4Color J4CALHDActiveLayer::GetColor()
{
  return OpenParameterList()->GetSubLayerColor();
}

#endif
