// $Id$
#ifndef __J4IRQC2IRON2__
#define __J4IRQC2IRON2__
//*************************************************************************
//* --------------------
//* J4IRQC2Iron2
//* --------------------
//* (Description)
//* 	Derivation class for QC2 Iron2
//*     Mother class : J4VAcceleratorComponent
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

class J4IRQC2Iron2 : public J4VIRAcceleratorComponent {	

public:
  J4IRQC2Iron2(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1,
                           G4int  me        = 0,
		 G4int  copyno    = -1);

  virtual ~J4IRQC2Iron2();

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




