// $Id$
#ifndef __J4BDMATERIALSTORE__
#define __J4BDMATERIALSTORE__
//********************************************************************
//* ---------------------
//* J4BDMaterialStore.hh
//* ---------------------
//*     
//* (Update Record)
//*	2000/12/20  K.Hoshina	Original version.
//********************************************************************

//_________________________________________________________________________
//
// J4BDMaterialStore
//
// The J4BDMaterialStore provides materials for Beam Delivery Area.
// If you cannot find your material in the J4MaterialCatalog,
// you can define new material at Create() method.
//

#include "J4VMaterialStore.hh"

// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4BDMaterialStore : public J4VMaterialStore {
 
public:
  J4BDMaterialStore() {};   
  ~J4BDMaterialStore(){};  
    
private:
  
  G4Material* Create(const G4String& name) ; //Define User Materials
  
};


#endif
