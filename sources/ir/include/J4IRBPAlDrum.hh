// $Id$
#ifndef __J4IRBPALDRUM__
#define __J4IRBPALDRUM__
//*************************************************************************
//* --------------------
//* J4IRBPAlDrum
//* --------------------
//* (Description)
//* 	Derivation class for Beampipe.
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4IRBPAlDrumPipe.hh"
#include "J4IRBPAlDrumCap.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRBPAlDrum : public J4VIRAcceleratorComponent {	

public:
  J4IRBPAlDrum(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1,
	                   G4bool reflect = false);

  virtual ~J4IRBPAlDrum();

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();

  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  J4IRBPAlDrumPipe* fdrumPipe;
  J4IRBPAlDrumCap* fdrumCap;
};

#endif




