// $Id$
#ifndef __J4MUDBARRELABS__
#define __J4MUDBARRELABS__
//*************************************************************************
//* --------------------
//* J4MUDBarrelAbs
//* --------------------
//* (Description)
//* 	Derivation class for MUD BarrelAbs.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "G4Trap.hh"
#include "J4VMUDBarrelTrap.hh"
#include "J4VMUDDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4MUDBarrelAbs : public J4VMUDBarrelTrap {	

public:
  J4MUDBarrelAbs( J4VDetectorComponent* parent    = 0,
                  G4int                 nclones   = 1,
                  G4int                 nbrothers = 1, 
                  G4int                 me        = 0,
                  G4int                 copyno    = -1 );
  	     
  virtual ~J4MUDBarrelAbs();

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
  
//private:
//  void 	Assemble();    
  void  Cabling ();
  
private:
  static G4String fFirstName;
};

//=====================================================================               
//* Inline Implementation of Pure Virtuals of Base Class --------------
inline G4double J4MUDBarrelAbs::GetFront( G4int layerID ) {
  return OpenParameterList()->GetBarrelAbsFront( layerID );
}

inline G4double J4MUDBarrelAbs::GetHalfL( G4int layerID ) {
  return OpenParameterList()->GetBarrelAbsHalfL( layerID );
}

inline G4double J4MUDBarrelAbs::GetThick() {
  return OpenParameterList()->GetBarrelAbsThick();
}

inline G4String J4MUDBarrelAbs::GetMaterial(){
  return OpenParameterList()->GetBarrelAbsMaterial();
}

inline G4bool J4MUDBarrelAbs::GetVisAtt(){
  return OpenParameterList()->GetBarrelAbsVisAtt();
}

inline G4Color J4MUDBarrelAbs::GetColor(){
  return OpenParameterList()->GetBarrelAbsColor();
}

#endif
