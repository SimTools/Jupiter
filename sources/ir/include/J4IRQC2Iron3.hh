// $Id$
#ifndef __J4IRQC2IRON3__
#define __J4IRQC2IRON3__
//*************************************************************************
//* --------------------
//* J4IRQC2Iron3
//* --------------------
//* (Description)
//* 	Derivation class for QC2 Iron3
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4IRQC2Parameter.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRQC2Iron3 : public J4VIRAcceleratorComponent {	

public:
  J4IRQC2Iron3(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1,
                           G4int  me        = 0,
		 G4int  copyno    = -1);

  virtual ~J4IRQC2Iron3();

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




