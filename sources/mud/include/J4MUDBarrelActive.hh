// $Id$
#ifndef __J4MUDBARRELACTIVE__
#define __J4MUDBARRELACTIVE__
//*************************************************************************
//* --------------------
//* J4MUDBarrelActive
//* --------------------
//* (Description)
//* 	Derivation class for MUD BarrelActive.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "J4VMUDBarrelTrap.hh"
#include "J4MUDBarrelActiveSD.hh"
#include "J4VMUDDetectorComponent.hh"
#include "J4MUDParameterList.hh"
//#include "J4VMUDActiveSD.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
//class J4MUDBarrelActiveSD;
class J4MUDBarrelActive : public J4VMUDBarrelTrap {

public:
  J4MUDBarrelActive( J4VDetectorComponent* parent    = 0,
                     G4int                 nclones   = 1,
                     G4int                 nbrothers = 1, 
  	             G4int                 me        = 0,
                     G4int                 copyno    = -1 );
  	     
  virtual ~J4MUDBarrelActive();

//  virtual void  InstallIn( J4VComponent*        mother,
//                           G4RotationMatrix*    prot  = 0,
//                           const G4ThreeVector& tlate = 0 );

//  virtual void Draw() { };
//  virtual void Print() const { };

  virtual G4String GetFirstName () const { return fFirstName; }
  virtual G4double GetFront     ( G4int i );
  virtual G4double GetHalfL     ( G4int i );
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
inline G4double J4MUDBarrelActive::GetFront( G4int layerID ) {
  return OpenParameterList()->GetBarrelActiveFront( layerID );
}

inline G4double J4MUDBarrelActive::GetHalfL( G4int layerID ) {
  return OpenParameterList()->GetBarrelActiveHalfL( layerID );
}

inline G4double J4MUDBarrelActive::GetThick() {
  return OpenParameterList()->GetBarrelActiveThick();
}

inline G4String J4MUDBarrelActive::GetMaterial(){
  return OpenParameterList()->GetBarrelActiveMaterial();
}

inline G4bool J4MUDBarrelActive::GetVisAtt(){
  return OpenParameterList()->GetBarrelActiveVisAtt();
}

inline G4Color J4MUDBarrelActive::GetColor(){
  return OpenParameterList()->GetBarrelActiveColor();
}
#endif
