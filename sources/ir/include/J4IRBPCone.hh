// $Id$
#ifndef __J4IRBPCONE__
#define __J4IRBPCONE__
//*************************************************************************
//* --------------------
//* J4IRBPCone
//* --------------------
//* (Description)
//* 	Derivation class for Coneampipe.
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4IRBPBeCone.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRBPCone : public J4VIRAcceleratorComponent {	

public:
  J4IRBPCone(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1,
	                   G4bool reflect   = false);

  virtual ~J4IRBPCone();

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();

  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  J4IRBPBeCone* fcone  ;
};

#endif




