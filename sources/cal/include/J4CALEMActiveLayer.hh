// $Id$
#ifndef __J4CALEMACTIVELAYER__
#define __J4CALEMACTIVELAYER__
//*************************************************************************
//* --------------------
//* J4CALEMActiveLayer
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALEMLayer.hh"
#include "J4VCALSubLayer.hh"
#include "J4CALEMActiveLayerSD.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALEMActiveLayerSD;
class J4CALEMActiveLayer : public J4VCALSubLayer {

public:
  J4CALEMActiveLayer( J4VDetectorComponent  *parent    = 0,
                                      G4int  nclones   = 1,
                                      G4int  nbrothers = 1, 
                                      G4int  me        = 0,
                                      G4int  copyno    = -1 );
  virtual ~J4CALEMActiveLayer();

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
 
inline G4double J4CALEMActiveLayer::GetStartThickness()
{
  return OpenParameterList()->GetEMAbsLayerThickness();
}

inline G4double J4CALEMActiveLayer::GetEndThickness()
{
  return OpenParameterList()->GetEMActiveLayerThickness();
}

inline G4String J4CALEMActiveLayer::GetMaterial()
{
  return OpenParameterList()->GetEMActiveLayerMaterial();
}

inline G4bool J4CALEMActiveLayer::GetVisAtt()
{
  return OpenParameterList()->GetSubLayerVisAtt();
}

inline G4Color J4CALEMActiveLayer::GetColor()
{
  return OpenParameterList()->GetSubLayerColor();
}

#endif
