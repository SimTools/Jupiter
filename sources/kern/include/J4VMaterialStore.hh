// $Id$
#ifndef __J4VMATERIALSTORE__
#define __J4VMATERIALSTORE__
// ====================================================================
//    J4VMaterialStore.hh
//
/// ====================================================================

#include "J4MaterialCatalog.hh"

// ====================================================================
//
// class definition
//
// ====================================================================
 
class J4VMaterialStore {
 
public:
  J4VMaterialStore();   
  virtual ~J4VMaterialStore();

  virtual G4Material* 	Order(const G4String& name) ;
   
protected:
  J4MaterialCatalog* 	fMaterialCatalog;
  
private:  
  virtual G4Material* 	Create(const G4String& name) ;   
};


#endif
