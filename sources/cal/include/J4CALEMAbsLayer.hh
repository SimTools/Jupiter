// $Id$
#ifndef __J4CALEMABSLAYER__
#define __J4CALEMABSLAYER__
//*************************************************************************
//* --------------------
//* J4CALEMAbsLayer
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

class J4CALEMAbsLayer : public J4VCALSubLayer {

public:
  J4CALEMAbsLayer( J4VDetectorComponent  *parent    = 0,
                                   G4int  nclones   = 1,
                                   G4int  nbrothers = 1, 
                                   G4int  me        = 0,
                                   G4int  copyno    = -1 );
  virtual ~J4CALEMAbsLayer();

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
 
inline G4double J4CALEMAbsLayer::GetStartThickness()
{
  return 0.;
}

inline G4double J4CALEMAbsLayer::GetEndThickness()
{
  return OpenParameterList()->GetEMAbsLayerThickness();
}

inline G4String J4CALEMAbsLayer::GetMaterial()
{
  return OpenParameterList()->GetEMAbsLayerMaterial();
}

inline G4bool J4CALEMAbsLayer::GetVisAtt()
{
  return OpenParameterList()->GetSubLayerVisAtt();
}

inline G4Color J4CALEMAbsLayer::GetColor()
{
  return OpenParameterList()->GetSubLayerColor();
}

#endif
