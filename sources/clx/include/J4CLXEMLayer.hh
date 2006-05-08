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
#include "J4VCLXSubLayer.hh"
#include "J4CLXEMAbsLayer.hh"
#include "J4CLXEMActiveLayer.hh"
#include "J4CLXEMFlexLayer.hh"
#include "G4Trap.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CLXEMAbsLayer;
class J4CLXEMActiveLayer;
class J4CLXEMFlexLayer;
class J4CLXEMLayer : public J4VCLXLayer {

public:
  
  J4CLXEMLayer( G4bool isBarrel, 
                J4VDetectorComponent *parent = 0,
		G4int  nclones   = 1,
		G4int  nbrothers = 1,
		G4int  me        = 0,
		G4int  copyno    = -1 );
  
  virtual ~J4CLXEMLayer();

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
inline G4bool J4CLXEMLayer::IsEM() const
{
  return true;
}

inline G4double J4CLXEMLayer::GetHalfX( G4int myID )
{
  return ( IsBarrel() )
    ? ((G4Trap*)(GetMother()->GetSolid()))->GetXHalfLength1() + (G4double)myID*OpenParameterList()->GetEMLayerThickness()*tan( 0.5*GetDphi() )
    : ((G4Trap*)(GetMother()->GetSolid()))->GetXHalfLength1();
}

inline G4double J4CLXEMLayer::GetHalfXL( G4int myID )
{
  return ( IsBarrel() )
    ? GetHalfX( myID ) + OpenParameterList()->GetEMLayerThickness()*tan( 0.5*GetDphi() )
    : ((G4Trap*)(GetMother()->GetSolid()))->GetXHalfLength2();
}

inline G4double J4CLXEMLayer::GetYmin( G4int myID )
{
  return ( IsBarrel() )
    ? OpenParameterList()->GetCLXInnerR()+myID*( OpenParameterList()->GetEMLayerThickness() )
    : OpenParameterList()->GetEndcapInnerR();
}

inline G4double J4CLXEMLayer::GetYmax( G4int myID )
{
  return ( IsBarrel() )
    ? GetYmin( myID ) + OpenParameterList()->GetEMLayerThickness()
    : OpenParameterList()->GetEMEndcapYmax();
}

inline G4double J4CLXEMLayer::GetHalfZ( G4int )
{
  return ( IsBarrel() )
    ? OpenParameterList()->GetEMHalfZ()
    : 0.5*OpenParameterList()->GetEMLayerThickness(); 
}

#endif
