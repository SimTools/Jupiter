// $Id$
#ifndef __J4MUDBARRELACTIVESD__
#define __J4MUDBARRELACTIVESD__
//*************************************************************************
//* --------------------
//* J4MUDBarrelActiveSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4MUD
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
#include "J4VSD.hh"
#include "J4MUDHit.hh"
#include "J4VMUDActiveSD.hh"
#include "J4VMUDDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4MUDBarrelActiveSD : public J4VMUDActiveSD {
  
public:
  J4MUDBarrelActiveSD( J4VDetectorComponent* detector );
  ~J4MUDBarrelActiveSD();
  
  using J4VSD<J4MUDHit>::operator=;

  virtual G4bool IsBarrel();
  virtual G4bool IsFront();
};
 
inline G4bool J4MUDBarrelActiveSD::IsBarrel() 
{
  return true;
}

inline G4bool J4MUDBarrelActiveSD::IsFront()
{
  return false;
}

#endif
