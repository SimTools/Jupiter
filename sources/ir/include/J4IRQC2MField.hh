// $Id$
#ifndef __J4IRQC2MFIELD__
#define __J4IRQC2MFIELD__
//*************************************************************************
//* --------------------
//* J4IRQC2MField
//* --------------------
//* (Description)
//* 	Derivation class for QC2 Magnetic field
//*     Mother class : J4MagneticField
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*	2002/12/05  T.Aso	k1 and Beam energy is given via  Constructor
//*************************************************************************

#include "J4VMField.hh"
#include "J4IRQC2Parameter.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRQC2MField : public J4VMField {	

public:
  J4IRQC2MField(G4double beamE, G4double k);
  virtual ~J4IRQC2MField();

  void GetLocalFieldValue(G4ThreeVector& lpos,
			     G4ThreeVector& lb,G4bool& onlyFlag );  
  void GetLocalValidBox(G4double* Lpos);

private:  

  G4double fGradient;

};

#endif




