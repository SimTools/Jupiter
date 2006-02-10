// $Id$
#ifndef __J4IRBCALSubLayer__
#define __J4IRBCALSubLayer__
//*************************************************************************
//* --------------------
//* J4IRBCALSubLayer
//* --------------------
//* (Description)
//* 	Derivation class for IR BCAL
//*     for BCAL Sub Layers: Absorber, Sensor, and Gap
//*    
//* (Update Record)
//*	2006/01/29  A.Miyamoto	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRMaterialStore;

class J4IRBCALSubLayer : public J4VIRAcceleratorComponent {	

public:
  J4IRBCALSubLayer(J4VAcceleratorComponent *parent = 0,
		           G4int  me        = 0);

  virtual ~J4IRBCALSubLayer();

  virtual void	Draw()      ;
  virtual void	Print() const ;

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();

  class  GeoInfo {
  public:
    G4String name;
    G4String material;
    bool   visatt;
    G4String color;
  public:
    GeoInfo(G4String n, G4String m, bool v, G4String c):
      name(n),material(m),visatt(v),color(c) {}
  };


private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  G4double             fZpos[4];


};

#endif




