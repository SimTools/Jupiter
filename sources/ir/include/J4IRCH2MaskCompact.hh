// $Id$
#ifndef __J4IRCH2MASKCOMPACT__
#define __J4IRCH2MASKCOMPACT__
//*************************************************************************
//* --------------------
//* J4IRCH2MASK
//* --------------------
//* (Description)
//* 	Derivation class for CH2MaskCompact
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"

#include "J4IRCH2MaskCompactBPin.hh"
#include "J4IRCH2MaskCompactBPout.hh"
//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRCH2MaskCompact : public J4VIRAcceleratorComponent {	

public:
  J4IRCH2MaskCompact(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
 	                  G4int  copyno    = -1,
	                   G4bool reflect = false);

  virtual ~J4IRCH2MaskCompact();

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();

  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;

  J4IRCH2MaskCompactBPin*  fbpIn;
  J4IRCH2MaskCompactBPout* fbpOut;
  
};

#endif




