// $Id$
#ifndef __J4IRQC2IRON1__
#define __J4IRQC2IRON1__
//*************************************************************************
//* --------------------
//* J4IRQC2Iron1
//* --------------------
//* (Description)
//* 	Derivation class for QC2Iron1
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

class J4IRQC2Iron1 : public J4VIRAcceleratorComponent {	

public:
  J4IRQC2Iron1(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1,
                           G4int  me        = 0,
		 G4int  copyno    = -1);

  virtual ~J4IRQC2Iron1();


  virtual void	Draw()      ;
  virtual void	Print() const ;

  G4ThreeVector&  GetTranslation();

private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  
};

#endif




