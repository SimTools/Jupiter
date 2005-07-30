// $Id$
#ifndef __J4IRQMFIELD__
#define __J4IRQMFIELD__
//*************************************************************************
//* --------------------
//* J4IRQMField
//* --------------------
//* (Description)
//* 	Provide magnetic field produced by Qs on the beamline
//*     Mother class : J4MagneticField
//*    
//* (Update Record)
//*     2005/07/24  A.Miyamoto  Original version derived from the code 
//*                             written by Aso san.
//*************************************************************************

#include "J4VMField.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRQMField : public J4VMField {	

public:
  J4IRQMField(G4double beamE, G4double k, 
	G4double rmin, G4double rmax, G4double zlength );
//  J4IRQMField(G4double beamE, G4double grad, G4String tag);
  virtual ~J4IRQMField();

  void GetLocalFieldValue(G4ThreeVector& lpos,
			     G4ThreeVector& lb,G4bool& onlyFlag );  
  void GetLocalValidBox(G4double* Lpos);

private:
  G4double fRmin;
  G4double fRmax;
  G4double fZlength;
  G4double fGradient;

};

#endif




