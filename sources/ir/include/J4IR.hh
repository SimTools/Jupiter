// $Id$
#ifndef __J4IR__
#define __J4IR__
//*************************************************************************
//* --------------------
//* J4IR
//* --------------------
//* (Description)
//* 	Derivation class for Beampipe.
//*     Mother class : J4VAcceleratorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2002/05/15  K.Hoshina	Argument changed in InstallIn().
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IR : public J4VIRAcceleratorComponent {	

public:
  J4IR(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1 );

  virtual ~J4IR();

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




