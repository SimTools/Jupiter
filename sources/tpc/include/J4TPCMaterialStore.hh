// $Id$
#ifndef __J4TPCMATERIALSTORE__
#define __J4TPCMATERIALSTORE__
//********************************************************************
//* ---------------------
//* J4TPCMaterialStore.hh
//* ---------------------
//* (Description)
//* 	Material Store class for TPC.
//*     Define Materials for TPC here.
//*     
//* (Update Record)
//*	2000/12/20  K.Hoshina	Original version.
//********************************************************************

#include "J4VMaterialStore.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4TPCMaterialStore : public J4VMaterialStore {
 
public:
  J4TPCMaterialStore() {};   
  ~J4TPCMaterialStore(){};  
    
private:
  
  G4Material* Create(const G4String& name,
                    G4MaterialPropertiesTable *mtable=0); //Define User Materials
  
};


#endif
