// $Id$
#ifndef __J4IRBPALDRUMCAP__
#define __J4IRBPALDRUMCAP__
//*************************************************************************
//* --------------------
//* J4IRBPAlDrumCap
//* --------------------
//* (Description)
//* 	Derivation class for Beeampipe.
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRBPAlDrumCap : public J4VIRAcceleratorComponent {	

public:
  J4IRBPAlDrumCap(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1,
	                   G4bool reflect = false);

  virtual ~J4IRBPAlDrumCap();

  G4RotationMatrix* GetRotation();
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




