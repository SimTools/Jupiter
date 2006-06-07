// $Id$
#ifndef __J4OptDetMaterialStore__
#define __J4OptDetMaterialStore__
//********************************************************************
//* ---------------------
//* J4OptDetMaterialStore.hh
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
 
class J4OptDetMaterialStore : public J4VMaterialStore {
 
public:
  J4OptDetMaterialStore() {};   
  ~J4OptDetMaterialStore(){};  
    
private:
  
  G4Material* Create(const G4String& name,
	      G4MaterialPropertiesTable *mtable=0 ) ; //Define User Materials)
  
};


#endif
