// $Id$
#ifndef __J4SOLMFIELD__
#define __J4SOLMFIELD__
//*************************************************************************
//* --------------------
//* J4SOLMField
//* --------------------
//* (Description)
//* 	Derivation class for magnetic field of Solenoid
//*     Mother class : J4VMField
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VMField.hh"
#include "J4SOLParameterList.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4SOLMField : public J4VMField {	

public:

  J4SOLMField(J4SOLParameterList *list);

  virtual ~J4SOLMField();

  void GetLocalFieldValue(G4ThreeVector &position,
			  G4ThreeVector &bfield,
                          G4bool        &onlyFlag );  

  void GetLocalValidBox(G4double* lpos);

private:  

  J4SOLParameterList* fParameterList;

};

#endif


