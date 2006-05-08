// $Id$
#ifndef __J4CLXMATERIALSTORE__
#define __J4CLXMATERIALSTORE__
//********************************************************************
//* ---------------------
//* J4CLXMaterialStore.hh
//* ---------------------
//* (Description)
//* 	Material Store class for CLX.
//*     Define Materials for CLX here.
//*     
//* (Update Record)
//*	2000/12/20  K.Hoshina	Original version.
//********************************************************************

#include "J4VMaterialStore.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4CLXMaterialStore : public J4VMaterialStore {
 
public:
  J4CLXMaterialStore() {};   
  ~J4CLXMaterialStore(){};  
    
private:
  
  G4Material* Create(const G4String& name,
		     G4MaterialPropertiesTable *mtable=0 ) ; //Define User Materials
  
};


#endif
