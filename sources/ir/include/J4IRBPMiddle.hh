// $Id$
#ifndef __J4IRBPMIDDLE__
#define __J4IRBPMIDDLE__
//*************************************************************************
//* --------------------
//* J4IRBPMiddle
//* --------------------
//* (Description)
//* 	For beam pipe out side beryllium central part to before QC1
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2005/07/25  A.Miyamoto  Modified from T.Aso's original
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRBPMiddle : public J4VIRAcceleratorComponent {	

public:
  J4IRBPMiddle(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1,
	                   G4bool reflect = false);

  virtual ~J4IRBPMiddle();

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();

  virtual void	Draw()      ;
  virtual void	Print() const ;
  void InstallIn(J4VComponent      *, // mother
                               G4RotationMatrix  *prot=0,
                                const G4ThreeVector     &tlate=0); 

  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  
};

#endif




