// $Id$
#ifndef __J4MAGNETICFIELD__
#define __J4MAGNETICFIELD__
//*************************************************************************
//* --------------------
//* J4MagneticField
//* --------------------
//* (Description)
//* 	This class applies magnetic field.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*                             This class is very temporary and
//*                             will be removed eventually.
//*************************************************************************
 
#include "G4MagneticField.hh"
class J4SOLParameterList;

// ====================================================================
// -----------------------
// class definition
// -----------------------
 
class J4MagneticField : public G4MagneticField {
 
public:
  J4MagneticField(J4SOLParameterList *p = 0) : fParameterList(p) {}
  ~J4MagneticField() {}
  
  virtual void  GetFieldValue(const  G4double Point[3], 
	                             G4double* Bfield) const;  
  inline      J4SOLParameterList *GetParameterList() { return fParameterList; }

  inline void SetParameterList(J4SOLParameterList *p) { fParameterList = p; }

private:
  J4SOLParameterList *fParameterList; // should be moved to
                                      // solenoid class
                                      // eventually
};

#endif
