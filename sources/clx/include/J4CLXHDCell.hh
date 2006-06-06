// $Id$
#ifndef __J4CLXHDCELL__
#define __J4CLXHDCELL__
//*************************************************************************
//* --------------------
//* J4CLXHDCell
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXCell.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CLXHDCell : public J4VCLXCell {

public:
  
  J4CLXHDCell( G4bool isBarrel,
	       G4bool isBoundary,
	       J4VDetectorComponent *parent = 0,
	       G4int  nclones   = 1,
	       G4int  nbrothers = 1,
	       G4int  me        = 0,
	       G4int  copyno    = -1 );
  
  virtual ~J4CLXHDCell();

  virtual G4bool   IsEM         () const;
  virtual G4String GetFirstName () const  { return fgFirstName ; }

  virtual void Cabling();

private:
  static const G4String fgFirstName;

};

//=====================================================================
//* Inline Implementation of Pure Virtuals of Base Class --------------

inline G4bool J4CLXHDCell::IsEM() const
{
  return false;
}

#endif
