// $Id$
#ifndef __J4IRQC1COOLANT__
#define __J4IRQC1COOLANT__
//*************************************************************************
//* --------------------
//* J4IRQC1Coolant
//* --------------------
//* (Description)
//* 	Derivation class for Coolant
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
//#include "J4IRQC1Parameter.hh"

#include "J4IRQC1ThermalVessel.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRQC1Coolant : public J4VIRAcceleratorComponent {	

public:
  J4IRQC1Coolant(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1,
                           G4int  me        = 0,
		 G4int  copyno    = -1);

  virtual ~J4IRQC1Coolant();

  virtual void	Draw()      ;
  virtual void	Print() const ;

private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  J4IRQC1ThermalVessel* fthVess;
  
};

#endif




