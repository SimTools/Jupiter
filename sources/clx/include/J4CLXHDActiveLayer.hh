// $Id$
#ifndef __J4CLXHDACTIVELAYER__
#define __J4CLXHDACTIVELAYER__
//*************************************************************************
//* --------------------
//* J4CLXHDActiveLayer
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CLXHDLayer.hh"
#include "J4CLXHDBoard.hh"
#include "G4Trap.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4HDCLXBoard;
class J4CLXHDActiveLayer : public J4VCLXSubLayer {

public:
  J4CLXHDActiveLayer( J4VDetectorComponent  *parent   = 0,
                                      G4int  nclones   = 1,
                                      G4int  nbrothers = 1, 
                                      G4int  me        = 0,
                                      G4int  copyno    = -1 );
  virtual ~J4CLXHDActiveLayer();

  virtual G4String GetFirstName      () const { return fFirstName; }
  virtual G4double GetStartThickness ();
  virtual G4double GetEndThickness   ();
    virtual G4double GetPlx();
    virtual G4double GetPx();
  virtual G4String GetMaterial       ();
  virtual G4bool   GetVisAtt         ();
  virtual G4Color  GetColor          ();

protected:
    virtual J4VCLXBoard *Create(J4VDetectorComponent *parent = 0,
				 G4int nclones = 1,
				 G4int nbrothers = 1,
				 G4int me = 0,
				 G4int copyno = -1);
    virtual G4bool IsActive();

private:
  void  Cabling ();

private:  
  static const G4String fFirstName;

};

//=====================================================================               
//* Inline Implementation of Pure Virtuals of Base Class --------------               
 
inline G4double J4CLXHDActiveLayer::GetStartThickness()
{
  return OpenParameterList()->GetHDAbsLayerThickness();
}

inline G4double J4CLXHDActiveLayer::GetEndThickness()
{
  return OpenParameterList()->GetHDActiveLayerThickness();
}

inline G4double J4CLXHDActiveLayer::GetPlx()
{
    G4Trap *mother = (G4Trap *)(GetMother() -> GetSolid());
    return mother -> GetXHalfLength2();
}

inline G4double J4CLXHDActiveLayer::GetPx()
{
    return GetPlx() - GetEndThickness() * std::tan(.5 * OpenParameterList() -> GetTrapDeltaPhi());
}

inline G4String J4CLXHDActiveLayer::GetMaterial()
{
  return OpenParameterList()->GetHDActiveLayerMaterial();
}

inline G4bool J4CLXHDActiveLayer::GetVisAtt()
{
  return OpenParameterList()->GetSubLayerVisAtt();
}

inline G4Color J4CLXHDActiveLayer::GetColor()
{
  return OpenParameterList()->GetSubLayerColor();
}

inline G4bool J4CLXHDActiveLayer::IsActive()
{
    return true;
}
#endif
