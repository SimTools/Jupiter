// $Id$
#ifndef __J4VTXMATERIALSTORE__
#define __J4VTXMATERIALSTORE__
//********************************************************************
//* ---------------------
//* J4VTXMaterialStore.hh
//* ---------------------
//* (Description)
//* 	Material Store class for VTX.
//*     Define Materials for VTX here.
//*     
//* (Update Record)
//*	2000/12/20  K.Hoshina	Original version.
//********************************************************************

#include "J4VMaterialStore.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4VTXMaterialStore : public J4VMaterialStore {
 
public:
  J4VTXMaterialStore() {};   
  ~J4VTXMaterialStore(){};  
    
private:
  
  G4Material* Create(const G4String& name) ; //Define User Materials
  
};


#endif
