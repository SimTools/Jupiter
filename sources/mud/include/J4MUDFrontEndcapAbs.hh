// $Id$
#ifndef __J4MUDFRONTENDCAPABS__
#define __J4MUDFRONTENDCAPABS__
//*************************************************************************
//* --------------------
//* J4MUDFrontEndcapAbs
//* --------------------
//* (Description)
//* 	Derivation class for MUD FrontEndcapAbs.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "J4VMUDEndcapTrap.hh"
#include "J4VMUDDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4MUDFrontEndcapAbs : public J4VMUDEndcapTrap {	

public:
  J4MUDFrontEndcapAbs( J4VDetectorComponent* parent    = 0,
                  G4int                 nclones   = 1,
                  G4int                 nbrothers = 1, 
                  G4int                 me        = 0,
                  G4int                 copyno    = -1 );
  	     
  virtual ~J4MUDFrontEndcapAbs();

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
  
//private:
//  void 	Assemble();    
  void  Cabling ();
  
private:
  static G4String fFirstName;

};

//=====================================================================               
//* Inline Implementation of Pure Virtuals of Base Class --------------
inline G4double J4MUDFrontEndcapAbs::GetFront( G4int layerID ) 
{
  if ( layerID < OpenParameterList()->GetFrontEndcapNAbsLayers() )
    return OpenParameterList()->GetFrontEndcapAbsFront( layerID );
  else
    return OpenParameterList()->GetFrontEndcapAbsFront( layerID - OpenParameterList()->GetFrontEndcapNAbsLayers() );
}

inline G4double J4MUDFrontEndcapAbs::GetHeight( G4int layerID ) 
{
  if ( layerID < OpenParameterList()->GetFrontEndcapNAbsLayers() )
    return OpenParameterList()->GetFrontEndcapAbsHeight( layerID );
  else
    return OpenParameterList()->GetFrontEndcapAbsHeight( layerID - OpenParameterList()->GetFrontEndcapNAbsLayers() );
}

inline G4double J4MUDFrontEndcapAbs::GetEndcapZ( G4int layerID ) 
{
  if ( layerID < OpenParameterList()->GetFrontEndcapNAbsLayers() )
    return OpenParameterList()->GetFrontEndcapAbsZ( layerID );
  else
    return OpenParameterList()->GetFrontEndcapAbsZ( layerID - OpenParameterList()->GetFrontEndcapNAbsLayers() );
}

inline G4int J4MUDFrontEndcapAbs::GetNLayers() 
{
  return OpenParameterList()->GetFrontEndcapNAbsLayers();
}

inline G4double J4MUDFrontEndcapAbs::GetThick()
{
  return OpenParameterList()->GetFrontEndcapAbsThick();
}

inline G4String J4MUDFrontEndcapAbs::GetMaterial()
{
  return OpenParameterList()->GetFrontEndcapAbsMaterial();
}

inline G4bool J4MUDFrontEndcapAbs::GetVisAtt()
{
  return OpenParameterList()->GetFrontEndcapAbsVisAtt();
}

inline G4Color J4MUDFrontEndcapAbs::GetColor()
{
  return OpenParameterList()->GetFrontEndcapAbsColor();
}

#endif
