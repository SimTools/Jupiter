// $Id$
#ifndef __J4VMFIELD__
#define __J4VMFIELD__
//*************************************************************************
//* --------------------
//* J4VMField
//* --------------------
//* (Description)
//* 	This class applies magnetic field.
//*     Mother class : J4Object
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "globals.hh"
#include "J4Object.hh"
#include "G4ThreeVector.hh"

// ====================================================================
// -----------------------
// class definition
// -----------------------

class J4VMField :public J4Object{

public:

  J4VMField();
  virtual ~J4VMField();

  virtual void GetLocalFieldValue(G4ThreeVector& position, 
                                  G4ThreeVector& bfield,G4bool& onlyFlag );  
  virtual void GetLocalValidBox(G4double* lpos);

private:

};

#endif

