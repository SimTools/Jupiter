// $Id$
#ifndef __J4MUDMFIELD__
#define __J4MUDMFIELD__
//*************************************************************************
//* --------------------
//* J4MUDMField
//* --------------------
//* (Description)
//* 	Derivation class for magnetic field of Solenoid
//*     Mother class : J4VMField
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*	2005/05/26  H.Ono	Edit from SOL Magnetic field
//*************************************************************************

#include "J4VMField.hh"
#include "J4MUDParameterList.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4MUDMField : public J4VMField {	

public:

  J4MUDMField( J4MUDParameterList* );

  virtual ~J4MUDMField();

  void GetLocalFieldValue( G4ThreeVector &position,
			   G4ThreeVector &bfiled,
			   G4bool &onlyFlag );  

  void GetLocalValidBox( G4double* lpos );

private:  

  J4MUDParameterList* fParameterList;

};

#endif
