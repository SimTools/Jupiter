// $Id$
#ifndef __J4CLXHDTRAPSTRIP__
#define __J4CLXHDTRAPSTRIP__
//*************************************************************************
//* --------------------
//* J4CLXHDTrapStrip
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXTrapStrip.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCLXStrip;
class J4CLXHDTrapStrip : public J4VCLXTrapStrip {

public:
  
  J4CLXHDTrapStrip( G4bool isBarrel,
                    J4VDetectorComponent *parent = 0,
                    G4int  nclones   = 1,
	            G4int  nbrothers = 1,
	            G4int  me        = 0,
	            G4int  copyno    = -1 );
  
  virtual ~J4CLXHDTrapStrip();

  virtual G4bool   IsEM         () const;
  virtual G4String GetFirstName () const  { return fgFirstName ; }
  
protected:
  virtual J4VCLXStrip *Create( J4VDetectorComponent *parent = 0,
		               G4int  nclones   = 1,
	                       G4int  nbrothers = 1,
			       G4int  me        = 0,
			       G4int  copyno    = 0 );

  virtual J4VCLXStrip *CreateBound( J4VDetectorComponent *parent = 0,
				    G4int  nclones   = 1,
				    G4int  nbrothers = 1,
				    G4int  me        = 0,
				    G4int  copyno    = 0 );
  
private:
  static const G4String fgFirstName;

};

//=====================================================================
//* Inline Implementation of Pure Virtuals of Base Class --------------

inline G4bool J4CLXHDTrapStrip::IsEM() const
{
  return false;
}

#endif
