// $Id$
#ifndef __J4MUDFRONTENDCAPACTIVE__
#define __J4MUDFRONTENDCAPACTIVE__
//*************************************************************************
//* --------------------
//* J4MUDFrontEndcapActive
//* --------------------
//* (Description)
//* 	Derivation class for MUD FrontEndcapActive.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "J4VMUDDetectorComponent.hh"
#include "G4Trap.hh"
#include "J4VMUDEndcapTrap.hh"
//#include "J4VMUDActiveSD.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

//class J4VMUDActiveSD;
class J4MUDFrontEndcapActive : public J4VMUDEndcapTrap {

public:
  J4MUDFrontEndcapActive( J4VDetectorComponent* parent    = 0,
                     G4int                 nclones   = 1,
  	             G4int                 nbrothers = 1, 
  	             G4int                 me        = 0,
                     G4int                 copyno    = -1 );
  	     
  virtual ~J4MUDFrontEndcapActive();

//  virtual void  InstallIn( J4VComponent*        mother,
//                           G4RotationMatrix*    prot  = 0,
//                           const G4ThreeVector& tlate = 0 );

//  virtual void Draw() { };
//  virtual void Print() const { };

  virtual G4String GetFirstName () const { return fFirstName; }
  virtual G4double GetFront     ( G4int i );
  virtual G4double GetHeight    ( G4int i );
  virtual G4double GetEndcapZ   ( G4int i );
  virtual G4int    GetNLayers   ();
  virtual G4double GetThick     ();
  virtual G4String GetMaterial  ();
  virtual G4bool   GetVisAtt    ();
  virtual G4Color  GetColor     ();
  
private:
//  void 	Assemble();    
  void  Cabling();
  
private:
    static G4String fFirstName;
};

//=====================================================================               
//* Inline Implementation of Pure Virtuals of Base Class --------------
inline G4double J4MUDFrontEndcapActive::GetFront( G4int layerID ) 
{
  if ( layerID < OpenParameterList()->GetFrontEndcapNActiveLayers() )
    return OpenParameterList()->GetFrontEndcapActiveFront( layerID );
  else
    return OpenParameterList()->GetFrontEndcapActiveFront( layerID - OpenParameterList()->GetFrontEndcapNActiveLayers() );
}

inline G4double J4MUDFrontEndcapActive::GetHeight( G4int layerID ) 
{
  if ( layerID < OpenParameterList()->GetEndcapNActiveLayers() )
    return OpenParameterList()->GetFrontEndcapActiveHeight( layerID );
  else
    return OpenParameterList()->GetFrontEndcapActiveHeight( layerID - OpenParameterList()->GetFrontEndcapNActiveLayers() );
}

inline G4double J4MUDFrontEndcapActive::GetEndcapZ( G4int layerID ) 
{
  if ( layerID < OpenParameterList()->GetFrontEndcapNActiveLayers() )
    return OpenParameterList()->GetFrontEndcapActiveZ( layerID );
  else
    return OpenParameterList()->GetFrontEndcapActiveZ( layerID - OpenParameterList()->GetFrontEndcapNActiveLayers() );
}

inline G4int J4MUDFrontEndcapActive::GetNLayers() 
{
  return OpenParameterList()->GetFrontEndcapNActiveLayers();
}

inline G4double J4MUDFrontEndcapActive::GetThick() 
{
  return OpenParameterList()->GetFrontEndcapActiveThick();
}

inline G4String J4MUDFrontEndcapActive::GetMaterial()
{
  return OpenParameterList()->GetFrontEndcapActiveMaterial();
}

inline G4bool J4MUDFrontEndcapActive::GetVisAtt()
{
  return OpenParameterList()->GetFrontEndcapActiveVisAtt();
}

inline G4Color J4MUDFrontEndcapActive::GetColor()
{
  return OpenParameterList()->GetFrontEndcapActiveColor();
}

#endif
