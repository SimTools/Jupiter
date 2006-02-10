// $Id$
#ifndef __J4IRFCALLayer__
#define __J4IRFCALLayer__
//*************************************************************************
//* --------------------
//* J4IRFCALLayer
//* --------------------
//* (Description)
//* 	Derivation class for IR FCAL
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2006/01/29  A.Miyamoto	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4IRFCALSubLayer.hh"
#include "J4IRFCALSensor.hh"
//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRFCALLayer : public J4VIRAcceleratorComponent {	

public:
  J4IRFCALLayer(J4VAcceleratorComponent *parent = 0,
                           G4int  nbrothers = 1, 
		           G4int  me        = 0);

  virtual ~J4IRFCALLayer();

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();

  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  J4IRFCALSubLayer      **fSubLayers;
  J4IRFCALSensor         *fSensor;
};

#endif




