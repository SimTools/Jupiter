// $Id$
#ifndef __J4CDCMATERIALSTORE__
#define __J4CDCMATERIALSTORE__
//********************************************************************
//* ---------------------
//* J4CDCMaterialStore.hh
//* ---------------------
//* (Description)
//* 	Material Store class for CDC.
//*     Define Materials for CDC here.
//*     
//* (Update Record)
//*	2000/12/20  K.Hoshina	Original version.
//********************************************************************

#include "J4VMaterialStore.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4CDCMaterialStore : public J4VMaterialStore {
 
public:
  J4CDCMaterialStore() {};   
  ~J4CDCMaterialStore(){};  
    
private:
  
  G4Material* Create(const G4String& name) ; //Define User Materials
  
};


#endif
