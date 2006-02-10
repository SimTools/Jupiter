// $Id$
#ifndef __J4CLXHDLAYER__
#define __J4CLXHDLAYER__
//*************************************************************************
//* --------------------
//* J4CLXHDLayer
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXLayer.hh"
#include "J4CLXHDAbsLayer.hh"
#include "J4CLXHDActiveLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CLXHDAbsLayer;
class J4CLXHDActiveLayer;
class J4CLXHDLayer : public J4VCLXLayer {

public:
  J4CLXHDLayer(J4VDetectorComponent  *parent    = 0,
                               G4int  nclones   = 1,
                               G4int  nbrothers = 1,
                               G4int  me        = 0,
                               G4int  copyno    = -1 );
  virtual ~J4CLXHDLayer();

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

inline G4double J4CLXHDLayer::GetLayerThickness()
{
  return OpenParameterList()->GetHDLayerThickness();
}

inline G4int J4CLXHDLayer::GetNLayers()
{
    return OpenParameterList() -> GetHDNLayers();
}

inline G4String J4CLXHDLayer::GetMaterial()
{
  return OpenParameterList()->GetLayerMaterial();
}

inline G4bool J4CLXHDLayer::GetVisAtt()
{
  return OpenParameterList()->GetLayerVisAtt();
}

inline G4Color J4CLXHDLayer::GetColor()
{
  return OpenParameterList()->GetLayerColor();
}

#endif
