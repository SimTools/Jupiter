// $Id$
#ifndef __J4ITMATERIALSTORE__
#define __J4ITMATERIALSTORE__
//********************************************************************
//* ---------------------
//* J4ITMaterialStore.hh
//* ---------------------
//* (Description)
//* 	Material Store class for IT.
//*     Define Materials for IT here.
//*     
//* (Update Record)
//*	2000/12/20  K.Hoshina	Original version.
//********************************************************************

#include "J4VMaterialStore.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4ITMaterialStore : public J4VMaterialStore {
 
public:
  J4ITMaterialStore() {};   
  ~J4ITMaterialStore(){};  
    
private:
  
  G4Material* Create(const G4String& name,
	      G4MaterialPropertiesTable *mtable=0 ) ; //Define User Materials)
  
};


#endif
