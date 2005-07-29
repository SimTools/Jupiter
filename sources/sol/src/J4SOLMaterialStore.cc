// $Id$
//********************************************************************
//* ---------------------
//* J4SOLMaterialStore.hh
//* ---------------------
//* (Description)
//* 	The J4SOLMaterialStore provides materials for SOL.
//*     If you cannot find your material in the J4MaterialCatalog,
//*	you can define new material at create() method.
//*     
//* (Update Record)
//*     2002/10/28  R.Kuboshima Original version.
//********************************************************************

#include "J4SOLMaterialStore.hh"
#include "G4Element.hh"
#include "G4Material.hh"

// ====================================================================
// -----------------
// class description
// -----------------


G4Material* J4SOLMaterialStore::Create(const G4String& name,
	G4MaterialPropertiesTable *) 
{  	

  G4Material* material= 0;

  if(name == "DummySol") { 		// CO2Isobutane(90:10)  
  
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

  G4double A, Z;
  G4String mname;
  G4double density;
  
  if ( name == "Copper" ) {
    //--------------
    // materials...
    //--------------
    A       = 63.546 *g/mole;
    density = 8.96 *g/cm3;
    G4Material* Cu   = new G4Material( mname="Copper", Z=29., A, density );
    material = Cu;
  }
  
  return material;

}


