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
#include "J4EXPHall.hh"
#include "J4TypeDef.hh"
#include "J4VComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4DetectorConstruction : public G4VUserDetectorConstruction, 
                               public J4Object 
{
	
public:
  J4DetectorConstruction();
  ~J4DetectorConstruction();

  G4VPhysicalVolume   *Construct(); 
    
  static  J4EXPHall   *GetEXPHall()             { return fEXPHall; }

  J4ObjArray  	       GetComponents()    const { return fComponents; }

  const G4ThreeVector &GetSizeOfEXPHall() const 
                       { return fEXPHall->GetSizeOfEXPHall(); }
  
  void	AddComponent(J4VComponent *dtc) 
        { 
           Register(dtc);
           fComponents.append(dtc); 
        }     

private:
  static J4EXPHall    *fEXPHall;
  J4ObjArray           fComponents;
  	  
};

#endif

