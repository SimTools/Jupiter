// $Id$
#ifndef __J4CTENDCAP__
#define __J4CTENDCAP__
//*************************************************************************
//* --------------------
//* J4CTEndcap
//* --------------------
//* (Description)
//* 	Derivation class for CT.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCTDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CTEndcap : public J4VCTDetectorComponent {	

public:
  J4CTEndcap(J4VDetectorComponent *parent    = 0,
                             G4int  nclones   = 1,
                             G4int  nbrothers = 1, 
                             G4int  me        = 0,
                             G4int  copyno    = -1 );
  virtual ~J4CTEndcap();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fFirstName;
  
};

#endif




