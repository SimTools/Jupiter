// $Id$
#ifndef __J4MATERIALCATALOG__
#define __J4MATERIALCATALOG__
// ====================================================================
//    J4MaterialCatalog.hh
//
/// ====================================================================
#include "tpordvec.h"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4MaterialPropertiesTable.hh"
#include "J4Object.hh"



// ====================================================================
//
// class definition
//
// ====================================================================
 
class J4MaterialCatalog : public J4Object 
{

protected:
  J4MaterialCatalog();   // constructor should NOT be public. 
  
public:
  ~J4MaterialCatalog();
  
  inline static  J4MaterialCatalog*  OpenCatalog();
  G4Material*    Order(const G4String& name,
                       G4MaterialPropertiesTable* mtable=0) const;

private:  
  void  ReadMaterialCatalog();
    
private:
  static J4MaterialCatalog* 	fMaterialCatalog;
  const  G4MaterialTable*       fMaterialTable;
  const  G4ElementTable*        fElementTable;
  
  
  
  
};

// ====================================================================
// inline definition
// ====================================================================

J4MaterialCatalog* J4MaterialCatalog::OpenCatalog()
{
  if (!fMaterialCatalog) {
     fMaterialCatalog= new J4MaterialCatalog();
  } 
  
  return fMaterialCatalog;
}

#endif
