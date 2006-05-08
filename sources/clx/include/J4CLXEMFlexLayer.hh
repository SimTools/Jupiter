// $Id$
#ifndef __J4CLXEMFLEXLAYER__
#define __J4CLXEMFLEXLAYER__
//*************************************************************************
//* --------------------
//* J4CLXEMFlexLayer
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXLayer.hh"
#include "J4VCLXSubLayer.hh"
#include "J4CLXParameterList.hh"
#include "J4VCLXDetectorComponent.hh"
#include "G4Trap.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCLXTrapStrip;
class J4CLXEMFlexLayer : public J4VCLXSubLayer {

public:
  
  J4CLXEMFlexLayer( G4bool isBarrel,
		    J4VDetectorComponent *parent = 0,
		    G4int  nclones   = 1,
		    G4int  nbrothers = 1,
		    G4int  me        = 0,
		    G4int  copyno    = -1 );
  
  virtual ~J4CLXEMFlexLayer();

  virtual G4bool   IsActive     () const;
  virtual G4bool   IsEM         () const;
  virtual G4String GetFirstName () const  { return fgFirstName ; }

  virtual G4double GetHalfX     ( G4int i = 0 ) ;
  virtual G4double GetHalfXL    ( G4int i = 0 ) ;
  virtual G4double GetYmin      ( G4int i = 0 ) ;  
  virtual G4double GetYmax      ( G4int i = 0 ) ;
  virtual G4double GetHalfZ     ( G4int i = 0 ) ;
  virtual G4double GetDphi      ( G4int i = 0 ) ;
  virtual G4double GetSphi      ( G4int i = 0 ) ;

  virtual G4String GetMaterial  ();

protected:
  virtual J4VCLXTrapStrip *Create( J4VDetectorComponent *parent    = 0,
				   G4int  nclones   = 1,
				   G4int  nbrothers = 1,
				   G4int  me        = 0,
				   G4int  copyno    = 0 );

private:
  static const G4String fgFirstName;
};

//=====================================================================
//* Inline Implementation of Pure Virtuals of Base Class --------------
inline G4bool J4CLXEMFlexLayer::IsActive() const
{
  return false;
}

inline G4bool J4CLXEMFlexLayer::IsEM() const
{
  return true;
}

inline G4double J4CLXEMFlexLayer::GetHalfX( G4int )
{
  G4double absThick    = OpenParameterList()->GetEMAbsLayerThickness();
  G4double activeThick = OpenParameterList()->GetEMActiveLayerThickness();
  return ( IsBarrel() )
    ? ((G4Trap*)(GetMother()->GetSolid()))->GetXHalfLength1()+(absThick+activeThick)*std::tan( 0.5*GetDphi() )
    : ((G4Trap*)(GetMother()->GetSolid()))->GetXHalfLength1();
}

inline G4double J4CLXEMFlexLayer::GetHalfXL( G4int )
{
  G4double flexThick = OpenParameterList()->GetEMFlexLayerThickness();
  return ( IsBarrel() )
    ? GetHalfX()+flexThick*std::tan( 0.5*GetDphi() )
    : ((G4Trap*)(GetMother()->GetSolid()))->GetXHalfLength2();
}

inline G4double J4CLXEMFlexLayer::GetYmin( G4int )
{
  G4int    motherID   = GetMother()->GetMyID();
  G4double motherYmin = ((J4VCLXLayer*)GetMother())->GetYmin( motherID );
  return ( IsBarrel() )
    ? motherYmin + OpenParameterList()->GetEMAbsLayerThickness() + OpenParameterList()->GetEMActiveLayerThickness()
    : OpenParameterList()->GetEndcapInnerR();
}

inline G4double J4CLXEMFlexLayer::GetYmax( G4int )
{
  return ( IsBarrel() )
    ? GetYmin() + OpenParameterList()->GetEMFlexLayerThickness()
    : OpenParameterList()->GetEMEndcapYmax();
}

inline G4double J4CLXEMFlexLayer::GetHalfZ( G4int )
{
  return ( IsBarrel() )
    ? OpenParameterList()->GetEMHalfZ()
    : 0.5*OpenParameterList()->GetEMFlexLayerThickness();
}

inline G4double J4CLXEMFlexLayer::GetDphi( G4int )
{
  return OpenParameterList()->GetTrapDeltaPhi();
}

inline G4double J4CLXEMFlexLayer::GetSphi( G4int )
{
  return 0.;
}

inline G4String J4CLXEMFlexLayer::GetMaterial()
{
  return OpenParameterList()->GetEMFlexLayerMaterial();
}

#endif
