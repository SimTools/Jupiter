//$Id$
#ifndef __J4MUDMATERIALSTORE__
#define __J4MUDMATERIALSTORE__
//********************************************************************
//* ---------------------
//* J4MUDMaterialStore.hh
//* ---------------------
//* (Description)
//* 	Material Store class for MUD.
//*     Define Materials for MUD here.
//*     
//* (Update Record)
//*	2003/08/13  A.Miyamoto	Original version. (Modified from J4IT....)
//********************************************************************

#include "J4VMaterialStore.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4MUDMaterialStore : public J4VMaterialStore {
 
public:
  J4MUDMaterialStore() {};   
  ~J4MUDMaterialStore(){};  
    
private:
  
  G4Material* Create(const G4String& name,
	        G4MaterialPropertiesTable *mtable=0 ) ; //Define User Materials
  
};


#endif
