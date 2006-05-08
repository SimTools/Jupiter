// $Id$
#ifndef __J4CLXEMSTRIP__
#define __J4CLXEMSTRIP__
//*************************************************************************
//* --------------------
//* J4CLXEMStrip
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

class J4CLXEMStrip : public J4VCLXStrip {

public:
  
  J4CLXEMStrip( G4bool isBarrel,
                J4VDetectorComponent *parent = 0,
                G4int  nclones   = 1,
	        G4int  nbrothers = 1,
	        G4int  me        = 0,
	        G4int  copyno    = -1 );
  
  virtual ~J4CLXEMStrip();

  virtual G4bool   IsEM         () const;
  virtual G4String GetFirstName () const  { return fgFirstName ; }
  
//  virtual G4double GetHalfX     ( G4int i = 0 ) ;
//  virtual G4double GetHalfY     ( G4int i = 0 ) ;
//  virtual G4double GetHalfZ     ( G4int i = 0 ) ;

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

inline G4bool J4CLXEMStrip::IsEM() const
{
  return true;
}

#endif
