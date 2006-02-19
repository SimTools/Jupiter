// $Id$
#ifndef __J4CLXEMACTIVELAYER__
#define __J4CLXEMACTIVELAYER__
//*************************************************************************
//* --------------------
//* J4CLXEMActiveLayer
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CLXEMLayer.hh"
#include "J4CLXEMBoard.hh"
#include "G4Trap.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CLXEMBoard;
class J4CLXEMActiveLayer : public J4VCLXSubLayer {

public:
  J4CLXEMActiveLayer( J4VDetectorComponent  *parent    = 0,
                                      G4int  nclones   = 1,
                                      G4int  nbrothers = 1,
                                      G4int  me        = 0,
                                      G4int  copyno    = -1 );
  virtual ~J4CLXEMActiveLayer();

  virtual G4String GetFirstName      () const { return fFirstName; }
    virtual G4double GetPlx();
    virtual G4double GetPx();
  virtual G4double GetStartThickness ();
  virtual G4double GetEndThickness   ();
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
inline G4double J4CLXEMActiveLayer::GetStartThickness()
{
  return OpenParameterList()->GetEMAbsLayerThickness();
}

inline G4double J4CLXEMActiveLayer::GetEndThickness()
{
  return OpenParameterList()->GetEMActiveLayerThickness();
}

inline G4double J4CLXEMActiveLayer::GetPlx()
{
    G4Trap *mother = (G4Trap *)(GetMother() -> GetSolid());
    return mother -> GetXHalfLength2();
}

inline G4double J4CLXEMActiveLayer::GetPx()
{
    return GetPlx() - GetEndThickness() * std::tan(.5 * OpenParameterList() -> GetTrapDeltaPhi());
}

inline G4String J4CLXEMActiveLayer::GetMaterial()
{
  return OpenParameterList()->GetEMActiveLayerMaterial();
}

inline G4bool J4CLXEMActiveLayer::GetVisAtt()
{
  return OpenParameterList()->GetSubLayerVisAtt();
}

inline G4Color J4CLXEMActiveLayer::GetColor()
{
  return OpenParameterList()->GetSubLayerColor();
}

inline G4bool J4CLXEMActiveLayer::IsActive()
{
    return true;
}

#endif