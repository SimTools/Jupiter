// $Id$
#ifndef __J4SOLMATERIALSTORE__
#define __J4SOLMATERIALSTORE__
//********************************************************************
//* ---------------------
//* J4SOLMaterialStore.hh
//* ---------------------
//* (Description)
//* 	Material Store class for SOL.
//*     Define Materials for SOL here.
//*     
//* (Update Record)
//*	2002/10/28  R.Kuboshima	Original version.
//********************************************************************

#include "J4VMaterialStore.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4SOLMaterialStore : public J4VMaterialStore {
 
public:
  J4SOLMaterialStore() {};   
  ~J4SOLMaterialStore(){};  
    
private:
  
  G4Material* Create(const G4String& name,
	        G4MaterialPropertiesTable *mtable=0 ) ; //Define User Materials
  
};


#endif
