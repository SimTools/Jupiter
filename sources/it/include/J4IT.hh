// $Id$
#ifndef __J4IT__
#define __J4IT__
//*************************************************************************
//* --------------------
//* J4IT
//* --------------------
//* (Description)
//* 	Derivation class for IT.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4ITLayer.hh"
#include "J4VITDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IT : public J4VITDetectorComponent {	

public:
  J4IT(J4VDetectorComponent *parent = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );
  virtual ~J4IT();

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
  J4ITLayer**		fLayers;
  
};

#endif


