// $Id$

#ifndef __J4IRBPALTUBE__
#define __J4IRBPALTUBE__
//*************************************************************************
//* --------------------
//* J4IRBPAlTube
//* --------------------
//* (Description)
//* 	Derivation class for Beampipe.
//*     Mother class : J4VAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4IRBPAlPipe.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRBPAlTube : public J4VIRAcceleratorComponent {	

public:
  J4IRBPAlTube(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1,
	                   G4bool reflect = false);

  virtual ~J4IRBPAlTube();

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();

  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  J4IRBPAlPipe* fpipe;
  
};

#endif




