// $Id$
#ifndef __J4VTXLADDER__
#define __J4VTXLADDER__
//*************************************************************************
//* --------------------
//* J4VTXLadder
//* --------------------
//* (Description)
//* 	Derivation class for VTX Ladder.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2001/06/06  T.Aso	Original version.
//*************************************************************************

#include "J4VTXSensor.hh"
#include "J4VVTXDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VTXLadder : public J4VVTXDetectorComponent {	

public:

  J4VTXLadder(J4VDetectorComponent *parent       = 0,
	      G4int                 numOfLadders = 1,
	      G4int                 nbrothers    = 1,
	      G4int                 me           = 0,
	      G4int                 copyno       = -1);

  J4VTXLadder(const J4VTXLadder    &orig,         
	             G4int                 copyno);
  	     
  virtual ~J4VTXLadder();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  virtual G4int GetMyID(){ return -1; } 
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:
  
  static G4String fFirstName;
  J4VTXSensor  **fSensors;

};

#endif


