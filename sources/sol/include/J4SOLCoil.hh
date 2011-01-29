// $Id$
#ifndef __J4SOLCOIL__
#define __J4SOLCOIL__
//*************************************************************************
//* -----
//* J4SOLCoil
//* -----
//* (Description)
//* 	Derivation class for SOLCoil.
//*     Mother class : J4VSOLDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VSOLDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4SOLCoil : public J4VSOLDetectorComponent {	

public:
  J4SOLCoil( J4VDetectorComponent *parent    = 0,
                            G4int  nclones   = 1,
                            G4int  nbrothers = 1, 
                            G4int  me        = 0,
                            G4int  copyno    = -1 );
  virtual ~J4SOLCoil();

  virtual void  InstallIn( J4VComponent         *mother,
                           G4RotationMatrix     *prot  = 0,
                           const G4ThreeVector  &tlate = G4ThreeVector(0.) );

  virtual void	Draw()        ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fFirstName;
};

#endif
