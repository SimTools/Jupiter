// $Id$
#ifndef __J4IRSENSORMATERIALSTORE__
#define __J4IRSENSORMATERIALSTORE__
//********************************************************************
//* ---------------------
//* J4IRSensorMaterialStore.hh
//* ---------------------
//* (Description)
//* 	Material Store class for IR sensitive detector
//*     Define Materials for IR here.
//*     
//* (Update Record)
//*	2006/01/27  A.Miyamoto	Original version.
//********************************************************************

#include "J4VMaterialStore.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4IRSensorMaterialStore : public J4VMaterialStore {
 
public:
  J4IRSensorMaterialStore() {};   
  ~J4IRSensorMaterialStore(){};  
    
private:
  
  G4Material* Create(const G4String& name, 
    G4MaterialPropertiesTable *mtable=0 ) ; //Define User Materials
  
};


#endif
