// $Id$
#ifndef __J4IRCH2MASKCOMPACTBPOUT__
#define __J4IRCH2MASKCOMPACTBPOUT__
//*************************************************************************
//* --------------------
//* J4IRCH2MASK
//* --------------------
//* (Description)
//* 	Derivation class for CH2MaskCompactBPout
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

class J4IRCH2MaskCompactBPout : public J4VIRAcceleratorComponent {	

public:
  J4IRCH2MaskCompactBPout(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
 	                  G4int  copyno    = -1,
	                   G4bool reflect = false);

  virtual ~J4IRCH2MaskCompactBPout();

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




