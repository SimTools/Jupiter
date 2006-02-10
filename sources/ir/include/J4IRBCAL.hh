// $Id$
#ifndef __J4IRBCAL__
#define __J4IRBCAL__
//*************************************************************************
//* --------------------
//* J4IRBCAL
//* --------------------
//* (Description)
//* 	Derivation class for IR BCAL
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2005/07/08  A.Miyamoto	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4IRBCALLayer.hh"
//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRBCAL : public J4VIRAcceleratorComponent {	

public:
  J4IRBCAL(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
 	                  G4int  copyno    = -1,
	                   G4bool reflect = false);

  virtual ~J4IRBCAL();

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();

  virtual void	Draw()      ;
  virtual void	Print() const ;
  inline G4int  GetShape(){ return fShape; }
  inline G4double GetZpos(){ return fZpos; }

private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  G4int fShape; // =0 shape for 2mrad collision
                // =1 shape for 20mrad collision
  J4IRBCALLayer        **fLayers;  
  G4double fZpos; 
};

#endif




