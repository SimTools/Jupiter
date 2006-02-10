// $Id$
#ifndef __J4IRBCALLayer__
#define __J4IRBCALLayer__
//*************************************************************************
//* --------------------
//* J4IRBCALLayer
//* --------------------
//* (Description)
//* 	Derivation class for IR BCAL
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2006/01/29  A.Miyamoto	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4IRBCALSubLayer.hh"
#include "J4IRBCALSensor.hh"
//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRBCALLayer : public J4VIRAcceleratorComponent {	

public:
  J4IRBCALLayer(J4VAcceleratorComponent *parent = 0,
                           G4int  nbrothers = 1, 
		           G4int  me        = 0);

  virtual ~J4IRBCALLayer();

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();

  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  J4IRBCALSubLayer      **fSubLayers;
  J4IRBCALSensor         *fSensor;
};

#endif




