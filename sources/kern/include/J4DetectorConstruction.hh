// $Id$
#ifndef __J4DETECTORCONSTRUCTION__
#define __J4DETECTORCONSTRUCTION__

//*************************************************************************
//* --------------------------
//* J4DetectorConstruction.hh
//* --------------------------
//* (Description)
//* 	Class for describing his/her detector setup.
//*     Mother class : G4VUserDetectorConstruction (abstruct class)
//*    
//* (Update Record)
//*	2001/01/18  K.Hoshina	Original version.
//*************************************************************************

#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "J4ExpHall.hh"
#include "J4TypeDef.hh"
#include "J4VComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4DetectorConstruction : public G4VUserDetectorConstruction, public J4Object {
	
public:
  J4DetectorConstruction();
  ~J4DetectorConstruction();

  G4VPhysicalVolume* Construct(); 
    
  J4VComponent         *GetExpHall()       const { return fExpHall; }
  const G4ThreeVector  &GetSizeOfExpHall() const { return fExpHall->GetCenter();}
  J4ObjArray  	        GetComponents()    const { return fComponents; }
  
  void	AddComponent(J4VComponent *dtc) 
        { 
           Register(dtc);
           fComponents.append(dtc); 
        }     
    
  static J4ExpHall    *fExpHall;

private:

  J4ObjArray           fComponents;
  	  
};

#endif
