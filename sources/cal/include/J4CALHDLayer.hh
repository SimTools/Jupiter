// $Id$
#ifndef __J4CALHDLAYER__
#define __J4CALHDLAYER__
//*************************************************************************
//* --------------------
//* J4CALHDLayer
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALLayer.hh"
#include "J4CALHDAbsLayer.hh"
#include "J4CALHDActiveLayer.hh"
#include "G4Sphere.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALHDAbsLayer;
class J4CALHDActiveLayer;
class J4CALHDLayer : public J4VCALLayer {	

public:
  J4CALHDLayer(J4VDetectorComponent  *parent    = 0,
                               G4int  nclones   = 1,
                               G4int  nbrothers = 1, 
                               G4int  me        = 0,
                               G4int  copyno    = -1 );
  virtual ~J4CALHDLayer();

  virtual G4String GetFirstName     () const { return fFirstName; }
  virtual G4double GetLayerThickness();
  virtual G4String GetMaterial      ();
  virtual G4bool   GetVisAtt        ();
  virtual G4Color  GetColor         ();

protected:
  virtual J4VCALSubLayer *CreateAbs( J4VDetectorComponent *parent    = 0,
                                                    G4int  nclones   = 1,
                                                    G4int  nbrothers = 1, 
                                                    G4int  me        = 0,
                                                    G4int  copyno    = -1 );

  virtual J4VCALSubLayer *CreateActive( J4VDetectorComponent *parent    = 0,
                                                       G4int  nclones   = 1,
                                                       G4int  nbrothers = 1, 
                                                       G4int  me        = 0,
                                                       G4int  copyno    = -1 );

private:  
  static const G4String   fFirstName;

};

//=====================================================================               
//* Inline Implementation of Pure Virtuals of Base Class --------------               
 
inline G4double J4CALHDLayer::GetLayerThickness()
{
  return OpenParameterList()->GetHDLayerThickness();
}

inline G4String J4CALHDLayer::GetMaterial()
{
  return OpenParameterList()->GetLayerMaterial();
}

inline G4bool J4CALHDLayer::GetVisAtt()
{
  return OpenParameterList()->GetLayerVisAtt();
}

inline G4Color J4CALHDLayer::GetColor()
{
  return OpenParameterList()->GetLayerColor();
}

#endif
