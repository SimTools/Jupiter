// $Id$
#ifndef __J4CT__
#define __J4CT__
//*************************************************************************
//* --------------------
//* J4CT
//* --------------------
//* (Description)
//* 	Derivation class for CT.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2003/08/13  A.Miyamoto Original version.(Copied from J4IT)
//*************************************************************************

#include "J4CTLayer.hh"
#include "J4CTSupportTub.hh"
#include "J4CTOuterCylinder.hh"
#include "J4CTEndcap.hh"
#include "J4VCTDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CT : public J4VCTDetectorComponent {	

public:
  J4CT(J4VDetectorComponent *parent = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4CT();

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
  J4CTSupportTub       *fSupportTub;
  J4CTOuterCylinder    *fOuterCylinder;
  J4CTEndcap          **fEndcaps;
  J4CTLayer           **fLayers;
  
};

#endif


