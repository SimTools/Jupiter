// $Id$
//********************************************************************
//* ---------------------
//* J4CALMaterialStore.hh
//* ---------------------
//* (Description)
//* 	The J4CALMaterialStore provides materials for CAL.
//*     If you cannot find your material in the J4MaterialCatalog,
//*	you can define new material at create() method.
//*     
//* (Update Record)
//*	2000/12/20  K.Hoshina	Original version.
//********************************************************************

#include "J4CALMaterialStore.hh"
#include "G4Element.hh"
#include "G4Material.hh"

// ====================================================================
// -----------------
// class description
// -----------------


G4Material* J4CALMaterialStore::Create(const G4String& name,
        G4MaterialPropertiesTable* /* mtable */ ) 
{  	

  G4Material* material= 0;

  if(name == "DummyCal") { 		// CO2Isobutane(90:10)  
  
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
