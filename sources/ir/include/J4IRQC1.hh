// $Id$
#ifndef __J4IRQC1__
#define __J4IRQC1__
//*************************************************************************
//* --------------------
//* J4IRQC1
//* --------------------
//* (Description)
//* 	Derivation class for QC1
//*     Mother class : J4VIRAcceleratorComponent
//*    
//*     QC1 - SUS
//*         - Coil - Collor 
//*                - Cooling - Vacuum
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4AttMFieldMap.hh"
//#include "J4IRQC1Parameter.hh"


#include "J4IRQC1SUS.hh"
#include "J4IRQC1Coil.hh"
#include "J4IRQC1Cooling.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRQC1 : public J4VIRAcceleratorComponent, public J4AttMFieldMap {

public:
  J4IRQC1(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1,
                           G4int  me        = 0,
                           G4int  copyno    = -1 ,
	                    G4bool reflect=false);
  virtual ~J4IRQC1();

  virtual void	Draw()      ;
  virtual void	Print() const ;

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();

  void  InstallIn(J4VComponent *mother,
                  G4RotationMatrix     *prot  = 0,
                  const G4ThreeVector  &tlate = 0 );

private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  J4IRQC1SUS* fsus;
  J4IRQC1Coil* fcoil;  
  J4IRQC1Cooling* fcool;

};

#endif




