// $Id$
#ifndef __J4IRSD0MFIELD__
#define __J4IRSD0MFIELD__
//*************************************************************************
//* --------------------
//* J4IRSD0MField
//* --------------------
//* (Description)
//* 	Derivation class for SD0 Magnetic field
//*     Mother class : J4MagneticField
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*	2002/12/05  T.Aso	k and Beam energy is given via  Constructor
//*************************************************************************

#include "J4VMField.hh"
#include "J4IRSD0Parameter.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRSD0MField : public J4VMField {	

public:
  J4IRSD0MField(G4double beamE, G4double k);
  virtual ~J4IRSD0MField();

  void GetLocalFieldValue(G4ThreeVector& lpos,
			     G4ThreeVector& lb,G4bool& onlyFlag );  
  void GetLocalValidBox(G4double* Lpos);

private:  

  G4double fGradient;

};

#endif




