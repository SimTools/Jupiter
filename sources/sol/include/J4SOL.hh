// $Id$
#ifndef __J4SOL__
#define __J4SOL__
//*************************************************************************
//* -----
//* J4SOL
//* -----
//* (Description)
//* 	Derivation class for SOL.
//*     Mother class : J4VSOLDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VSOLDetectorComponent.hh"
#include "J4MagneticField.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4SOL : public J4VSOLDetectorComponent {	

public:
  J4SOL(J4VDetectorComponent *parent = 0,
                       G4int  nclones   = 1,
                       G4int  nbrothers = 1, 
                       G4int  me        = 0,
                       G4int  copyno    = -1 );
  virtual ~J4SOL();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void  SetMagField();

  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fFirstName;
  J4MagneticField     * fMagField;

};

#endif
