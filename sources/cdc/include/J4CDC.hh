// $Id$
#ifndef __J4CDC__
#define __J4CDC__
//*************************************************************************
//* --------------------
//* J4CDC
//* --------------------
//* (Description)
//* 	Derivation class for CDC.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CDCLayer.hh"
#include "J4CDCSupportTub.hh"
#include "J4CDCEndcap.hh"
#include "J4VCDCDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CDCSuperLayer;
class J4CDC : public J4VCDCDetectorComponent {	

public:
  	
  J4CDC(J4VDetectorComponent *parent    = 0,
                       G4int  nclones   = 1,
                       G4int  nbrothers = 1, 
                       G4int  me        = 0,
                       G4int  copyno    = -1 );
  virtual ~J4CDC();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String    fFirstName;
  J4CDCSupportTub   *fOuterSupportTub;
  J4CDCSupportTub   *fInnerSupportTub;
  J4CDCEndcap      **fEndcaps;
  J4CDCSuperLayer  **fLayers;
  
};

//=====================================================================
//---------------------
// inline function
//---------------------

#endif


