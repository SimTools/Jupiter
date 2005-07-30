// $Id$
#ifndef __J4IRWMask3__
#define __J4IRWMask3__
//*************************************************************************
//* --------------------
//* J4IRWMask3
//* --------------------
//* (Description)
//* 	Derivation class for IRWMask3
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2005/07/08  A.Miyamoto	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRWMask3 : public J4VIRAcceleratorComponent {	

public:
  J4IRWMask3(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
 	                  G4int  copyno    = -1,
	                   G4bool reflect = false);

  virtual ~J4IRWMask3();

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();

  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  
};

#endif




