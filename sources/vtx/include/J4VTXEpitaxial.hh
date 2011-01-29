// $Id$
#ifndef __J4VTXEPITAXIAL_
#define __J4VTXEPITAXIAL__
//*************************************************************************
//* --------------------
//* J4VTXEpitaxial
//* --------------------
//* (Description)
//* 	Derivation class for VTX Epitaxial.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2001/06/06  T.Aso	Original version.
//*	2002/11/19  T.Aso	ParameterList
//*************************************************************************

#include "J4VVTXDetectorComponent.hh"
#include "J4VTXPixelArea.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VTXEpitaxial : public J4VVTXDetectorComponent {	

public:

  J4VTXEpitaxial(J4VDetectorComponent* parent       = 0);
  	     
  virtual ~J4VTXEpitaxial();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0) );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:
  
  static G4String fFirstName;
  J4VTXPixelArea *fPixelArea;

};

#endif


