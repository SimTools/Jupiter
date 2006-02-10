// $Id$
#ifndef __J4CLXEMLAYER__
#define __J4CLXEMLAYER__
//*************************************************************************
//* --------------------
//* J4CLXEMLayer
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXLayer.hh"
#include "J4CLXEMAbsLayer.hh"
#include "J4CLXEMActiveLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CLXEMAbsLayer;
class J4CLXEMActiveLayer;
class J4CLXEMLayer : public J4VCLXLayer {

public:
  J4CLXEMLayer(J4VDetectorComponent  *parent    = 0,
                               G4int  nclones   = 1,
                               G4int  nbrothers = 1,
                               G4int  me        = 0,
                               G4int  copyno    = -1 );
  virtual ~J4CLXEMLayer();

  virtual G4String GetFirstName     () const { return fFirstName; }
  virtual G4double GetLayerThickness();
    virtual G4int GetNLayers();
  virtual G4String GetMaterial      ();
  virtual G4bool   GetVisAtt        ();
  virtual G4Color  GetColor         ();

protected:
  virtual J4VCLXSubLayer *CreateAbs( J4VDetectorComponent *parent    = 0,
                                                    G4int  nclones   = 1,
                                                    G4int  nbrothers = 1,
                                                    G4int  me        = 0,
                                                    G4int  copyno    = -1 );

  virtual J4VCLXSubLayer *CreateActive( J4VDetectorComponent *parent    = 0,
                                                       G4int  nclones   = 1,
                                                       G4int  nbrothers = 1,
                                                       G4int  me        = 0,
                                                       G4int  copyno    = -1 );

private:
  static const G4String   fFirstName;

};

//=====================================================================
//* Inline Implementation of Pure Virtuals of Base Class --------------

inline G4double J4CLXEMLayer::GetLayerThickness()
{
  return OpenParameterList()->GetEMLayerThickness();
}

inline G4String J4CLXEMLayer::GetMaterial()
{
  return OpenParameterList()->GetLayerMaterial();
}

inline G4int J4CLXEMLayer::GetNLayers()
{
    return OpenParameterList() -> GetEMNLayers();
}

inline G4bool J4CLXEMLayer::GetVisAtt()
{
  return OpenParameterList()->GetLayerVisAtt();
}

inline G4Color J4CLXEMLayer::GetColor()
{
  return OpenParameterList()->GetLayerColor();
}

#endif
