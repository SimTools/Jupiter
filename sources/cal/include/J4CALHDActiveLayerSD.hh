// $Id$
#ifndef __J4CALHDACTIVELAYERSD__
#define __J4CALHDACTIVELAYERSD__
//*************************************************************************
//* --------------------
//* J4CALHDActiveLayerSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4CALSubLayer
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	      Original version.
//*	2004/08/30  Ono Hiroaki       Add GetCellID <ono@hep.sc.niigata-u.ac.jp>
//*     2004/10/12  Allister Sanchez  Removed GetCellID.
//*                                   Use std:multimap for monitoring hits.
//*************************************************************************

#include "J4VSD.hh"
#include "J4CALHit.hh"
#include "J4VCALSubLayerSD.hh"
#include "J4VCALDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4CALHDActiveLayerSD : public J4VCALSubLayerSD{
  
public:

  J4CALHDActiveLayerSD( J4VDetectorComponent* ptrDetector );
  ~J4CALHDActiveLayerSD();

  using J4VSD<J4CALHit>::operator=;

  virtual G4bool IsEM ();
};

//=====================================================================               
//* Inline Implementation of Pure Virtuals of Base Class --------------               
 
inline G4bool J4CALHDActiveLayerSD::IsEM()
{
  return false;
}

#endif
