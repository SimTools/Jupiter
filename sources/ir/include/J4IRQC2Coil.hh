// $Id$
#ifndef __J4IRQC2COIL__
#define __J4IRQC2COIL__
//*************************************************************************
//* --------------------
//* J4IRQC2Coil
//* --------------------
//* (Description)
//* 	Derivation class for QC2Coil
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

class J4IRQC2Coil : public J4VIRAcceleratorComponent {	

public:
  J4IRQC2Coil(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1,
                           G4int  me        = 0,
		 G4int  copyno    = -1);

  virtual ~J4IRQC2Coil();

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




