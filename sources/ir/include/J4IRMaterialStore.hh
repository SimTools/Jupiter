// $Id$
#ifndef __J4IRMATERIALSTORE__
#define __J4IRMATERIALSTORE__
//********************************************************************
//* ---------------------
//* J4IRMaterialStore.hh
//* ---------------------
//* (Description)
//* 	Material Store class for IR.
//*     Define Materials for IR here.
//*     
//* (Update Record)
//*	2000/12/20  K.Hoshina	Original version.
//********************************************************************

#include "J4VMaterialStore.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4IRMaterialStore : public J4VMaterialStore {
 
public:
  J4IRMaterialStore() {};   
  ~J4IRMaterialStore(){};  
    
private:
  
  G4Material* Create(const G4String& name,
	      G4MaterialPropertiesTable *mtable=0 ) ; //Define User Materials
  
};


#endif
