// $Id$
#ifndef __J4IRSD0COLLAR__
#define __J4IRSD0COLLAR__
//*************************************************************************
//* --------------------
//* J4IRSD0Collar
//* --------------------
//* (Description)
//* 	Derivation class for Beampipe.
//*     Mother class : J4VAcceleratorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4IRSD0Parameter.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRSD0Collar : public J4VIRAcceleratorComponent {	

public:
  J4IRSD0Collar(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1,
                           G4int  me        = 0,
		 G4int  copyno    = -1);

  virtual ~J4IRSD0Collar();


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




