// $Id$
#ifndef __J4IRSD0__
#define __J4IRSD0__
//*************************************************************************
//* --------------------
//* J4IRSD0
//* --------------------
//* (Description)
//* 	Derivation class for SD0
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4IRSD0Parameter.hh"
#include "J4AttMFieldMap.hh"
#include "J4IRSD0SUS.hh"
#include "J4IRSD0Collar.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRSD0 : public J4VIRAcceleratorComponent, public J4AttMFieldMap  {

public:
  J4IRSD0(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1,
	                   G4bool reflect = false);

  virtual ~J4IRSD0();

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();

  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  J4IRSD0SUS** fsus;
  J4IRSD0Collar** fcol;
};

#endif




