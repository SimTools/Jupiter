// $Id$
#ifndef __J4MUDENDCAPACTIVE__
#define __J4MUDENDCAPACTIVE__
//*************************************************************************
//* --------------------
//* J4MUDEndcapActive
//* --------------------
//* (Description)
//* 	Derivation class for MUD EndcapActive.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "J4VMUDDetectorComponent.hh"
#include "G4Trap.hh"
#include "J4VMUDEndcapTrap.hh"
//#include "J4VMUDActiveSD.hh"
#include "J4MUDEndcapActiveSD.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

//class J4MUDEndcapActiveSD;
class J4MUDEndcapActive : public J4VMUDEndcapTrap {

public:
  J4MUDEndcapActive( J4VDetectorComponent* parent    = 0,
                     G4int                 nclones   = 1,
  	             G4int                 nbrothers = 1, 
  	             G4int                 me        = 0,
                     G4int                 copyno    = -1 );
  	     
  virtual ~J4MUDEndcapActive();

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
inline G4double J4MUDEndcapActive::GetFront( G4int layerID ) 
{
  if ( layerID < OpenParameterList()->GetEndcapNActiveLayers() )
    return OpenParameterList()->GetEndcapActiveFront( layerID );
  else
    return OpenParameterList()->GetEndcapActiveFront( layerID - OpenParameterList()->GetEndcapNActiveLayers() );
}

inline G4double J4MUDEndcapActive::GetHeight( G4int layerID ) 
{
  if ( layerID < OpenParameterList()->GetEndcapNActiveLayers() )
    return OpenParameterList()->GetEndcapActiveHeight( layerID );
  else
    return OpenParameterList()->GetEndcapActiveHeight( layerID - OpenParameterList()->GetEndcapNActiveLayers() );
}

inline G4double J4MUDEndcapActive::GetEndcapZ( G4int layerID ) 
{
  if ( layerID < OpenParameterList()->GetEndcapNActiveLayers() )
    return OpenParameterList()->GetEndcapActiveZ( layerID );
  else
    return OpenParameterList()->GetEndcapActiveZ( layerID - OpenParameterList()->GetEndcapNActiveLayers() );
}

inline G4int J4MUDEndcapActive::GetNLayers() 
{
  return OpenParameterList()->GetEndcapNActiveLayers();
}

inline G4double J4MUDEndcapActive::GetThick() 
{
  return OpenParameterList()->GetEndcapActiveThick();
}

inline G4String J4MUDEndcapActive::GetMaterial()
{
  return OpenParameterList()->GetEndcapActiveMaterial();
}

inline G4bool J4MUDEndcapActive::GetVisAtt()
{
  return OpenParameterList()->GetEndcapActiveVisAtt();
}

inline G4Color J4MUDEndcapActive::GetColor()
{
  return OpenParameterList()->GetEndcapActiveColor();
}

#endif
