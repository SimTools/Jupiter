// $Id$
// ====================================================================
//    J4MaterialStore.cc
//
//
// ====================================================================

#include "J4VMaterialStore.hh"

// ====================================================================
//
// class description
//
// ====================================================================

////////////////////////////////////////////
J4VMaterialStore::J4VMaterialStore()
////////////////////////////////////////////
{
  fMaterialCatalog = J4MaterialCatalog::OpenCatalog();
}

/////////////////////////////////////////////
J4VMaterialStore::~J4VMaterialStore()
/////////////////////////////////////////////
{
}


/////////////////////////////////////////////////////////////////////////
G4Material* J4VMaterialStore::Order(const G4String& name) 
/////////////////////////////////////////////////////////////////////////
{  	
  G4Material* material= 0;
  material = fMaterialCatalog->Order(name);
  
  if(!material) {
  	
  	G4cerr << "*** Your orderd material " << name << " is not in catalog! ***" << G4endl;
  	
  	material = Create(name);
  	
  	if(!material) {
  	   G4cerr << "*** You couldnot get new material" << name << " ! ***" << G4endl;
  	}	
  }
  return material;
}

/////////////////////////////////////////////////////////////////////////
G4Material* J4VMaterialStore::Create(const G4String& name) 
/////////////////////////////////////////////////////////////////////////
{  
  	   G4cerr << "*********************************************" << G4endl;
  	   G4cerr << "*** You called J4VMaterialStore::Create() ***" << G4endl;
  	   G4cerr << "*********************************************" << G4endl;
    return 0;
}


