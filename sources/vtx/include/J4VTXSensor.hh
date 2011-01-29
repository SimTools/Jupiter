// $Id$
#ifndef __J4VTXSENSOR_
#define __J4VTXSENSOR__
//*************************************************************************
//* --------------------
//* J4VTXSensor
//* --------------------
//* (Description)
//* 	Derivation class for VTX Sensor.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2001/06/06  T.Aso	Original version.
//*************************************************************************

#include "J4VVTXDetectorComponent.hh"
#include "J4VTXSubstrate.hh"
#include "J4VTXEpitaxial.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VTXSensor : public J4VVTXDetectorComponent {	

private:

  void 	Assemble();    
  void  Cabling ();

  static G4String fFirstName;

 
  J4VTXSubstrate  *fSubstrate; 
  J4VTXEpitaxial  *fEpitaxial; 

public:

  J4VTXSensor(J4VDetectorComponent *parent       = 0,
              G4int                 numOfSensors = 1,
              G4int                 nbrothers    = 1,
              G4int                 me           = 0,
              G4int                 copyno       = -1);

  J4VTXSensor(const J4VTXSensor &orig,
	             G4int        copyno);

  virtual ~J4VTXSensor();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw()      ;
  virtual void	Print() const ;

};

#endif


