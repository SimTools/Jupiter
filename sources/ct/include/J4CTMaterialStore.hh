//$Id$
#ifndef __J4CTMATERIALSTORE__
#define __J4CTMATERIALSTORE__
//********************************************************************
//* ---------------------
//* J4CTMaterialStore.hh
//* ---------------------
//* (Description)
//* 	Material Store class for CT.
//*     Define Materials for CT here.
//*     
//* (Update Record)
//*	2003/08/13  A.Miyamoto	Original version. (Modified from J4IT....)
//********************************************************************

#include "J4VMaterialStore.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4CTMaterialStore : public J4VMaterialStore {
 
public:
  J4CTMaterialStore() {};   
  ~J4CTMaterialStore(){};  
    
private:
  
  G4Material* Create(const G4String& name,
	        G4MaterialPropertiesTable *mtable=0 ) ; //Define User Materials
  
};


#endif
