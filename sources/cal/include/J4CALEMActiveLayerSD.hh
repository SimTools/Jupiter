// $Id$
#ifndef __J4CALEMACTIVELAYERSD__
#define __J4CALEMACTIVELAYERSD__
//*************************************************************************
//* --------------------
//* J4CALEMActiveLayerSD
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
class J4CALEMActiveLayerSD : public J4VCALSubLayerSD{

public:

  J4CALEMActiveLayerSD( J4VDetectorComponent* ptrDetector );
  ~J4CALEMActiveLayerSD();

  using J4VSD<J4CALHit>::operator=;

  virtual G4bool IsEM ();
};

//=====================================================================               
//* Inline Implementation of Pure Virtuals of Base Class --------------               
 
inline G4bool J4CALEMActiveLayerSD::IsEM()
{
  return true;
}

#endif
