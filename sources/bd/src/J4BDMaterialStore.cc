// $Id$
//********************************************************************
//* ---------------------
//* J4BDMaterialStore.cc
//* ---------------------
//*     
//* (Update Record)
//*	2000/12/20  K.Hoshina	Original version.
//********************************************************************

#include "J4BDMaterialStore.hh"
#include "G4Element.hh"
#include "G4Material.hh"


G4Material* J4BDMaterialStore::Create(const G4String& name,
                                      G4MaterialPropertiesTable *) 
{  	
  // Define your materials here.
  
  G4Material* material= 0;

  if(name == "Dummy") { 		//   
  
    //--------------
    // elements...  
    //--------------
    //  G4double A, Z;
    //  G4String name, symbol;
  
    //--------------
    // materials...
    //--------------
    //  G4double density, massfraction;
    //  G4int natoms, nel, ncomponents;
    // temperature of experimental hall is controlled at 20 degree.
    //  const G4double expTemp= STP_Temperature+20.*kelvin; 
    
  
  }
  
  return material;

}


