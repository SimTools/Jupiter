// $Id$
#ifndef __J4IRQC1COIL__
#define __J4IRQC1COIL__
//*************************************************************************
//* --------------------
//* J4IRQC1Coil
//* --------------------
//* (Description)
//* 	Derivation class for QC1Coil
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
//#include "J4IRQC1Parameter.hh"

#include "J4IRQC1Collar.hh"
//#include "J4IRQC1QLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRQC1Coil : public J4VIRAcceleratorComponent {	

public:
  J4IRQC1Coil(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1,
                           G4int  me        = 0,
		 G4int  copyno    = -1);

  virtual ~J4IRQC1Coil();


  G4RotationMatrix* GetRotation();

  virtual void	Draw()      ;
  virtual void	Print() const ;

private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  J4IRQC1Collar** fcollar;

  //J4IRQC1QLayer** fqlayer  ;
};

#endif




