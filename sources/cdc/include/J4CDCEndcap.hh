// $Id$
#ifndef __J4CDCENDCAP__
#define __J4CDCENDCAP__
//*************************************************************************
//* --------------------
//* J4CDCEndcap
//* --------------------
//* (Description)
//* 	Derivation class for CDC.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCDCDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CDCEndcap : public J4VCDCDetectorComponent {	

public:
  J4CDCEndcap(J4VDetectorComponent *parent    = 0,
                             G4int  nclones   = 1,
                             G4int  nbrothers = 1, 
                             G4int  me        = 0,
                             G4int  copyno    = -1 );
  virtual ~J4CDCEndcap();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fFirstName;
  
};

#endif




