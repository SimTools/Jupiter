// $Id$
#ifndef __J4IRSD0SUS__
#define __J4IRSD0SUS__
//*************************************************************************
//* --------------------
//* J4IRSD0SUS
//* --------------------
//* (Description)
//* 	Derivation class for SD0 Sus
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4IRSD0Parameter.hh"
//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRSD0SUS : public J4VIRAcceleratorComponent {	

public:
  J4IRSD0SUS(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
	     G4int  copyno    = -1);


  virtual ~J4IRSD0SUS();

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




