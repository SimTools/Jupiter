// $Id$
#ifndef __J4CALEMLAYER__
#define __J4CALEMLAYER__
//*************************************************************************
//* --------------------
//* J4CALEMLayer
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALLayer.hh"
#include "J4CALEMAbsLayer.hh"
#include "J4CALEMActiveLayer.hh"
#include "G4Sphere.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALEMAbsLayer;
class J4CALEMActiveLayer;
class J4CALEMLayer : public J4VCALLayer {	

public:
  J4CALEMLayer(J4VDetectorComponent  *parent    = 0,
                               G4int  nclones   = 1,
                               G4int  nbrothers = 1, 
                               G4int  me        = 0,
                               G4int  copyno    = -1 );
  virtual ~J4CALEMLayer();

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
 
inline G4double J4CALEMLayer::GetLayerThickness()
{
  return OpenParameterList()->GetEMLayerThickness();
}

inline G4String J4CALEMLayer::GetMaterial()
{
  return OpenParameterList()->GetLayerMaterial();
}

inline G4bool J4CALEMLayer::GetVisAtt()
{
  return OpenParameterList()->GetLayerVisAtt();
}

inline G4Color J4CALEMLayer::GetColor()
{
  return OpenParameterList()->GetLayerColor();
}

#endif
