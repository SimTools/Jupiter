// $Id$
#ifndef __J4CALMATERIALSTORE__
#define __J4CALMATERIALSTORE__
//********************************************************************
//* ---------------------
//* J4CALMaterialStore.hh
//* ---------------------
//* (Description)
//* 	Material Store class for CAL.
//*     Define Materials for CAL here.
//*     
//* (Update Record)
//*	2000/12/20  K.Hoshina	Original version.
//********************************************************************

#include "J4VMaterialStore.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4CALMaterialStore : public J4VMaterialStore {
 
public:
  J4CALMaterialStore() {};   
  ~J4CALMaterialStore(){};  
    
private:
  
  G4Material* Create(const G4String& name,
        G4MaterialPropertiesTable *mtable=0 ) ; //Define User Materials
  
};


#endif
