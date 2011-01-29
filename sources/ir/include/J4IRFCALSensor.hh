// $Id$
#ifndef __J4IRFCALSensor__
#define __J4IRFCALSensor__
//*************************************************************************
//* --------------------
//* J4IRFCALSensor
//* --------------------
//* (Description)
//* 	Derivation class for IR FCAL
//*     for FCAL Sub Layers: Absorber, Sensor, and Gap
//*    
//* (Update Record)
//*	2006/01/29  A.Miyamoto	Original version.
//*************************************************************************

#include "J4VDetectorComponent.hh"
#include "J4IRSensorMaterialStore.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4IRFCALSensor : public J4VDetectorComponent {	

public:
  J4IRFCALSensor(J4VComponent *parent = 0);

  virtual ~J4IRFCALSensor();

  virtual void	Draw()      ;
  virtual void	Print() const ;

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
  virtual void  InstallIn(J4VComponent *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  inline G4double GetZCenter(){
    return -fZpos[3]*0.5+(fZpos[1]+fZpos[2])*0.5; }

private:
  void 	Assemble();    
  void  Cabling ();
  J4VMaterialStore* OpenMaterialStore();
  
private:  
  static G4String	fName;
  static J4IRSensorMaterialStore  	*fMaterialStore;
  G4double             fZpos[4];

};

#endif




