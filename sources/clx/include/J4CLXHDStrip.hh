// $Id$
#ifndef __J4CLXHDSTRIP__
#define __J4CLXHDSTRIP__
//*************************************************************************
//* --------------------
//* J4CLXHDStrip
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXCell.hh"
#include "J4VCLXStrip.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CLXHDStrip : public J4VCLXStrip {

public:
  
  J4CLXHDStrip( G4bool isBarrel,
                J4VDetectorComponent *parent = 0,
                G4int  nclones   = 1,
	        G4int  nbrothers = 1,
	        G4int  me        = 0,
	        G4int  copyno    = -1 );
  
  virtual ~J4CLXHDStrip();

  virtual G4bool   IsBoundary   () const;
  virtual G4bool   IsEM         () const;
  virtual G4String GetFirstName () const  { return fgFirstName ; }
  
protected:
  virtual J4VCLXCell *Create( J4VDetectorComponent *parent    = 0,
		              G4int  nclones   = 1,
			      G4int  nbrothers = 1,
			      G4int  me        = 0,
			      G4int  copyno    = 0 );

private:
  static const G4String fgFirstName;
};

//=====================================================================
//* Inline Implementation of Pure Virtuals of Base Class --------------

inline G4bool J4CLXHDStrip::IsBoundary() const
{
  return false;
}

inline G4bool J4CLXHDStrip::IsEM() const
{
  return false; 
}

#endif
