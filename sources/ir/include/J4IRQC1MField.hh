// $Id$
#ifndef __J4IRQC1MFIELD__
#define __J4IRQC1MFIELD__
//*************************************************************************
//* --------------------
//* J4IRQC1MField
//* --------------------
//* (Description)
//* 	Derivation class for QC1 Magnetic field
//*     Mother class : J4MagneticField
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*	2002/12/05  T.Aso	k1 and Beam energy is given via  Constructor
//*************************************************************************

#include "J4VMField.hh"
//#include "J4IRQC1Parameter.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRQC1MField : public J4VMField {	

public:
  J4IRQC1MField(G4double beamE, G4double k);
  J4IRQC1MField(G4double beamE, G4double grad, G4String tag);
  virtual ~J4IRQC1MField();

  void GetLocalFieldValue(G4ThreeVector& lpos,
			     G4ThreeVector& lb,G4bool& onlyFlag );  
  void GetLocalValidBox(G4double* Lpos);

private:  
  G4double fqc1ZLength;
  G4double fqc1InnerRadius;
  G4double fqc1Thickness;
  G4double fGradient;

};

#endif




