// $Id$
#ifndef __J4IRQC2__
#define __J4IRQC2__
//*************************************************************************
//* --------------------
//* J4IRQC2
//* --------------------
//* (Description)
//* 	Derivation class for QC2
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4IRQC2Parameter.hh"
#include "J4AttMFieldMap.hh"
#include "J4IRQC2Iron1.hh"
#include "J4IRQC2Iron2.hh"
#include "J4IRQC2Iron3.hh"
#include "J4IRQC2Coil.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRQC2 : public J4VIRAcceleratorComponent, public J4AttMFieldMap {

public:
  J4IRQC2(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1,
	                   G4bool reflect=false);

  virtual ~J4IRQC2();

  virtual void	Draw()      ;
  virtual void	Print() const ;

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  J4IRQC2Iron1** firon1;
  J4IRQC2Iron2** firon2;
  J4IRQC2Iron3** firon3;
  J4IRQC2Coil**  fcoil;
};

#endif




