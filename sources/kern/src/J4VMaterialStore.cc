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
  	
  	std::cerr << "*** Your orderd material " << name << " is not in catalog! ***" << std::endl;
  	
  	material = Create(name);
  	
  	if(!material) {
  	   std::cerr << "*** You couldnot get new material" << name << " ! ***" << std::endl;
  	}	
  }
  return material;
}

/////////////////////////////////////////////////////////////////////////
G4Material* J4VMaterialStore::Create(const G4String& name) 
/////////////////////////////////////////////////////////////////////////
{  
  	   std::cerr << "*********************************************" << std::endl;
  	   std::cerr << "*** You called J4VMaterialStore::Create() ***" << std::endl;
  	   std::cerr << "*********************************************" << std::endl;
    return 0;
}


