// $Id$
#ifndef __J4MUDFRONTENDCAPACTIVESD__
#define __J4MUDFRONTENDCAPACTIVESD__
//*************************************************************************
//* --------------------
//* J4MUDFrontEndcapActiveSD
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
class J4MUDFrontEndcapActiveSD : public J4VMUDActiveSD {
  
public:
  J4MUDFrontEndcapActiveSD( J4VDetectorComponent* detector );
  ~J4MUDFrontEndcapActiveSD();

   using J4VSD<J4MUDHit>::operator=;

   virtual G4bool IsBarrel();
   virtual G4bool IsFront();
};
 
inline G4bool J4MUDFrontEndcapActiveSD::IsBarrel() 
{
  return false;
}

inline G4bool J4MUDFrontEndcapActiveSD::IsFront() 
{
  return true;
}
#endif
