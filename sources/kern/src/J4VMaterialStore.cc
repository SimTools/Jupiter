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
G4Material* J4VMaterialStore::Order(const G4String& name,
                                    G4MaterialPropertiesTable* mtable) 
/////////////////////////////////////////////////////////////////////////
{  	
  G4Material* material= 0;
  material = fMaterialCatalog->Order(name, mtable);
  
  if(!material) {
  	
  	std::cerr << "*** Your orderd material " << name << " is not in catalog! ***" << std::endl;
  	
  	std::cerr << "*** Creating your material... ***" << std::endl;
  	material = Create(name, mtable);
  	
  	if(!material) {
  	   std::cerr << "*** You cannot get new material " << name << " ! ***" << std::endl;
           abort();
  	} else {
  	   std::cerr << "*** Material " << name << " is generated! ***" << std::endl;
  	}	
  }
  return material;
}

/////////////////////////////////////////////////////////////////////////
G4Material* J4VMaterialStore::Create(const G4String&, 
                                     G4MaterialPropertiesTable*) 
/////////////////////////////////////////////////////////////////////////
{  
  	   std::cerr << "*********************************************" << std::endl;
  	   std::cerr << "*** You called J4VMaterialStore::Create() ***" << std::endl;
  	   std::cerr << "*********************************************" << std::endl;
    return 0;
}


