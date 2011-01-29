// $Id$
#ifndef __J4VTXSUBSTRATE_
#define __J4VTXSUBSTRATE__
//*************************************************************************
//* --------------------
//* J4VTXSubstrate
//* --------------------
//* (Description)
//* 	Derivation class for VTX Substrate.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2001/06/06  T.Aso	Original version.
//*	2002/11/19  T.Aso	ParameterList
//*************************************************************************

#include "J4VVTXDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VTXSubstrate : public J4VVTXDetectorComponent {	

public:

  J4VTXSubstrate(J4VDetectorComponent* parent       = 0);
  	     
  virtual ~J4VTXSubstrate();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:
  
  static G4String fFirstName;

};

#endif


