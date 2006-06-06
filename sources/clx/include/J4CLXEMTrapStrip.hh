// $Id$
#ifndef __J4CLXEMTRAPSTRIP__
#define __J4CLXEMTRAPSTRIP__
//*************************************************************************
//* --------------------
//* J4CLXEMTrapStrip
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
class J4CLXEMTrapStrip : public J4VCLXTrapStrip {

public:
  
  J4CLXEMTrapStrip( G4bool isBarrel,
                J4VDetectorComponent *parent = 0,
                G4int  nclones   = 1,
	        G4int  nbrothers = 1,
	        G4int  me        = 0,
	        G4int  copyno    = -1 );
  
  virtual ~J4CLXEMTrapStrip();

  virtual G4bool   IsEM         () const;
  virtual G4String GetFirstName () const  { return fgFirstName ; }
  
protected:
  virtual J4VCLXStrip *Create( J4VDetectorComponent *parent    = 0,
		               G4int  nclones   = 1,
	                       G4int  nbrothers = 1,
			       G4int  me        = 0,
			       G4int  copyno    = 0 );

  virtual J4VCLXStrip *CreateBound( J4VDetectorComponent *parent    = 0,
				    G4int  nclones   = 1,
				    G4int  nbrothers = 1,
				    G4int  me        = 0,
				    G4int  copyno    = 0 );  
  
private:
  static const G4String fgFirstName;

};

//=====================================================================
//* Inline Implementation of Pure Virtuals of Base Class --------------

inline G4bool J4CLXEMTrapStrip::IsEM() const
{
  return true;
}

#endif
