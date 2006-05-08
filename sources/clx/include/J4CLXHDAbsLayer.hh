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

#include "J4VCLXLayer.hh"
#include "J4VCLXSubLayer.hh"
#include "G4Trap.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCLXTrapStrip;
class J4CLXHDAbsLayer : public J4VCLXSubLayer {

public:
  
  J4CLXHDAbsLayer( G4bool isBarrel,
		   J4VDetectorComponent *parent = 0,
		   G4int  nclones   = 1,
		   G4int  nbrothers = 1,
		   G4int  me        = 0,
		   G4int  copyno    = -1 );
  
  virtual ~J4CLXHDAbsLayer();

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
inline G4bool J4CLXHDAbsLayer::IsActive() const
{
  return false;
}

inline G4bool J4CLXHDAbsLayer::IsEM() const
{
  return false;
}

inline G4double J4CLXHDAbsLayer::GetHalfX( G4int )
{
  return ((G4Trap*)(GetMother()->GetSolid()))->GetXHalfLength1();
}

inline G4double J4CLXHDAbsLayer::GetHalfXL( G4int )
{
  G4double absThick = OpenParameterList()->GetHDAbsLayerThickness();
  return ( IsBarrel() )
    ? GetHalfX()+absThick*std::tan( 0.5*GetDphi() )
    : ((G4Trap*)(GetMother()->GetSolid()))->GetXHalfLength2();
}

inline G4double J4CLXHDAbsLayer::GetYmin( G4int )
{
  G4int    motherID   = GetMother()->GetMyID();
  G4double motherYmin = ((J4VCLXLayer*)GetMother())->GetYmin( motherID );
  return ( IsBarrel() )
    ? motherYmin
    : OpenParameterList()->GetEndcapInnerR();
}

inline G4double J4CLXHDAbsLayer::GetYmax( G4int )
{
  return ( IsBarrel() )
    ? GetYmin() + OpenParameterList()->GetHDAbsLayerThickness()
    : OpenParameterList()->GetHDYmax();
}

inline G4double J4CLXHDAbsLayer::GetHalfZ( G4int )
{
  return ( IsBarrel() )
    ? OpenParameterList()->GetHDHalfZ()
    : 0.5*OpenParameterList()->GetHDAbsLayerThickness(); 
}

inline G4double J4CLXHDAbsLayer::GetDphi( G4int )
{
  return OpenParameterList()->GetTrapDeltaPhi();
}

inline G4double J4CLXHDAbsLayer::GetSphi( G4int )
{
  return 0.;
}


inline G4String J4CLXHDAbsLayer::GetMaterial()
{
  return OpenParameterList()->GetHDAbsLayerMaterial();
}

#endif
