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
#include "J4CLXHDFlexLayer.hh"
#include "G4Trap.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CLXHDAbsLayer;
class J4CLXHDActiveLayer;
class J4CLXHDFlexLayer;
class J4CLXHDLayer : public J4VCLXLayer {

public:
  
  J4CLXHDLayer( G4bool isBarrel, 
                J4VDetectorComponent *parent = 0,
		G4int  nclones   = 1,
		G4int  nbrothers = 1,
		G4int  me        = 0,
		G4int  copyno    = -1 );
  
  virtual ~J4CLXHDLayer();

  virtual G4bool   IsEM         () const;
  virtual G4String GetFirstName () const  { return fgFirstName ; }
  
  virtual G4double GetYmin      ( G4int i = 0 ) ;  
  virtual G4double GetYmax      ( G4int i = 0 ) ;
  virtual G4double GetHalfZ     ( G4int i = 0 ) ;
  virtual G4double GetHalfX     ( G4int i = 0 ) ;
  virtual G4double GetHalfXL    ( G4int i = 0 ) ;

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

  virtual J4VCLXSubLayer *CreateFlex( J4VDetectorComponent *parent    = 0,
                                                     G4int  nclones   = 1,
                                                     G4int  nbrothers = 1,
                                                     G4int  me        = 0,
                                                     G4int  copyno    = -1 );
private:
  static const G4String fgFirstName;
};

//=====================================================================
//* Inline Implementation of Pure Virtuals of Base Class --------------
inline G4bool J4CLXHDLayer::IsEM() const
{
  return false;
}

inline G4double J4CLXHDLayer::GetHalfX( G4int myID ) {
  return ( IsBarrel() )
    ? (((G4Trap*)GetMother()->GetSolid()))->GetXHalfLength1()+(G4double)myID*OpenParameterList()->GetHDLayerThickness()*tan( 0.5*GetDphi() )
    : (((G4Trap*)GetMother()->GetSolid()))->GetXHalfLength1();
}

inline G4double J4CLXHDLayer::GetHalfXL( G4int myID ) {
  return ( IsBarrel() )
    ? GetHalfX( myID ) + OpenParameterList()->GetHDLayerThickness()*tan( 0.5*GetDphi() )
    : ((G4Trap*)GetMother()->GetSolid())->GetXHalfLength2();
}

inline G4double J4CLXHDLayer::GetYmin( G4int myID )
{
  return ( IsBarrel() )
    ? OpenParameterList()->GetEMYmax()+(G4double)myID*( OpenParameterList()->GetHDLayerThickness() )
    : OpenParameterList()->GetEndcapInnerR(); 
}

inline G4double J4CLXHDLayer::GetYmax( G4int myID )
{
  return ( IsBarrel() )
    ? GetYmin( myID ) + OpenParameterList()->GetHDLayerThickness()
    : OpenParameterList()->GetHDYmax();
}

inline G4double J4CLXHDLayer::GetHalfZ( G4int )
{
  return ( IsBarrel() )
    ? OpenParameterList()->GetHDHalfZ()
    : 0.5*OpenParameterList()->GetHDLayerThickness(); 
}

#endif
