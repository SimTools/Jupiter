// $Id$
#ifndef __J4IRQC1VACUUMVESSEL__
#define __J4IRQC1VACUUMVESSEL__
//*************************************************************************
//* --------------------
//* J4IRQC1VacuumVessel
//* --------------------
//* (Description)
//* 	Derivation class for Vaccume Vessel
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
//#include "J4IRQC1Parameter.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRQC1VacuumVessel : public J4VIRAcceleratorComponent {	

public:
  J4IRQC1VacuumVessel(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1,
                           G4int  me        = 0,
		 G4int  copyno    = -1);

  virtual ~J4IRQC1VacuumVessel();

  virtual void	Draw()      ;
  virtual void	Print() const ;

private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  
};

#endif




