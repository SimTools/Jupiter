// $Id$
#ifndef __J4CLXHDABSLAYER__
#define __J4CLXHDABSLAYER__
//*************************************************************************
//* --------------------
//* J4CLXHDAbsLayer
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXSubLayer.hh"
#include "J4VCLXBoard.hh"
#include "G4Trap.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4VCLXBoard;
class J4CLXHDAbsLayer : public J4VCLXSubLayer {

public:
  J4CLXHDAbsLayer( J4VDetectorComponent  *parent   = 0,
                                   G4int  nclones   = 1,
                                   G4int  nbrothers = 1, 
                                   G4int  me        = 0,
                                   G4int  copyno    = -1 );
  virtual ~J4CLXHDAbsLayer();

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
 
inline G4double J4CLXHDAbsLayer::GetStartThickness()
{
  return 0.;
}

inline G4double J4CLXHDAbsLayer::GetEndThickness()
{
  return OpenParameterList()->GetHDAbsLayerThickness();
}

inline G4double J4CLXHDAbsLayer::GetPx()
{
    G4Trap *mother = (G4Trap *)(GetMother() -> GetSolid());
    return mother -> GetXHalfLength1();
}

inline G4double J4CLXHDAbsLayer::GetPlx()
{
    return GetPx() + GetEndThickness() * std::tan(.5 * OpenParameterList() -> GetTrapDeltaPhi());
}

inline G4String J4CLXHDAbsLayer::GetMaterial()
{
  return OpenParameterList()->GetHDAbsLayerMaterial();
}

inline G4bool J4CLXHDAbsLayer::GetVisAtt()
{
  return OpenParameterList()->GetSubLayerVisAtt();
}

inline G4Color J4CLXHDAbsLayer::GetColor()
{
  return OpenParameterList()->GetSubLayerColor();
}

inline G4bool J4CLXHDAbsLayer::IsActive()
{
    return false;
}

#endif
