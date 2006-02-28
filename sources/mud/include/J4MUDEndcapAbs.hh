// $Id$
#ifndef __J4MUDENDCAPABS__
#define __J4MUDENDCAPABS__
//*************************************************************************
//* --------------------
//* J4MUDEndcapAbs
//* --------------------
//* (Description)
//* 	Derivation class for MUD EndcapAbs.
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
class J4MUDEndcapAbs : public J4VMUDEndcapTrap {	

public:
  J4MUDEndcapAbs( J4VDetectorComponent* parent    = 0,
                  G4int                 nclones   = 1,
                  G4int                 nbrothers = 1, 
                  G4int                 me        = 0,
                  G4int                 copyno    = -1 );
  	     
  virtual ~J4MUDEndcapAbs();

//  virtual void  InstallIn( J4VComponent*        mother,
//                           G4RotationMatrix*    prot  = 0,
//                           const G4ThreeVector& tlate = 0 );

//  virtual void Draw() { };
//  virtual void Print() const { };

  virtual G4String GetFirstName () const { return fFirstName; }
  virtual G4double GetFront     ( G4int i );
  virtual G4double GetHeight    ( G4int i );
  virtual G4double GetEndcapZ   ( G4int i );
  virtual G4double GetThick     ( G4int i );  
  virtual G4int    GetNLayers   ();
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
inline G4double J4MUDEndcapAbs::GetFront( G4int layerID ) 
{
  if ( layerID < OpenParameterList()->GetEndcapNAbsLayers() )
    return OpenParameterList()->GetEndcapAbsFront( layerID );
  else
    return OpenParameterList()->GetEndcapAbsFront( layerID - OpenParameterList()->GetEndcapNAbsLayers() );
}

inline G4double J4MUDEndcapAbs::GetHeight( G4int layerID ) 
{
  if ( layerID < OpenParameterList()->GetEndcapNAbsLayers() )
    return OpenParameterList()->GetEndcapAbsHeight( layerID );
  else
    return OpenParameterList()->GetEndcapAbsHeight( layerID - OpenParameterList()->GetEndcapNAbsLayers() );
}

inline G4double J4MUDEndcapAbs::GetEndcapZ( G4int layerID ) 
{
  if ( layerID < OpenParameterList()->GetEndcapNAbsLayers() )
    return OpenParameterList()->GetEndcapAbsZ( layerID );
  else
    return OpenParameterList()->GetEndcapAbsZ( layerID - OpenParameterList()->GetEndcapNAbsLayers() );
}

inline G4double J4MUDEndcapAbs::GetThick( G4int layerID )
{
  if ( layerID < OpenParameterList()->GetEndcapNAbsLayers() )
    return OpenParameterList()->GetEndcapAbsThick( layerID );
  else
    return OpenParameterList()->GetEndcapAbsThick( layerID - OpenParameterList()->GetEndcapNAbsLayers() );
}

inline G4int J4MUDEndcapAbs::GetNLayers() 
{
  return OpenParameterList()->GetEndcapNAbsLayers();
}

inline G4String J4MUDEndcapAbs::GetMaterial()
{
  return OpenParameterList()->GetEndcapAbsMaterial();
}

inline G4bool J4MUDEndcapAbs::GetVisAtt()
{
  return OpenParameterList()->GetEndcapAbsVisAtt();
}

inline G4Color J4MUDEndcapAbs::GetColor()
{
  return OpenParameterList()->GetEndcapAbsColor();
}

#endif
