//$Id$
//********************************************************************
//* ---------------------
//* J4CTMaterialStore.hh
//* ---------------------
//* (Description)
//* 	The J4CTMaterialStore provides materials for CT.
//*     If you cannot find your material in the J4MaterialCatalog,
//*	you can define new material at create() method.
//*     
//* (Update Record)
//*	2003/08/13  Akiya Miyamoto	Original version.
//********************************************************************

#include "J4CTMaterialStore.hh"
#include "G4Element.hh"
#include "G4Material.hh"

// ====================================================================
// -----------------
// class description
// -----------------


G4Material* J4CTMaterialStore::Create(const G4String& name,
	        G4MaterialPropertiesTable *mtable) 
{  	

  G4Material* material= 0;

  if(name == "CO2Isobutane") { 		// CO2Isobutane(90:10)  
  
    //--------------
    // elements...  
    //--------------
      G4double A, Z;
      G4String name, symbol;
  
      A= 1.00794 *g/mole;
      G4Element* elH= new G4Element(name="Hydrogen", symbol="H", Z=1., A);

      A= 12.011 *g/mole;
      G4Element* elC= new G4Element(name="Carbon", symbol="C", Z=6., A);

      A= 15.9994 *g/mole;
      G4Element* elO= new G4Element(name="Oxygen", symbol="O", Z=8., A);

    //--------------
    // materials...
    //--------------
      G4double density, massfraction;
      G4int natoms, nel, ncomponents;
    // temperature of experimental hall is controlled at 20 degree.
      const G4double expTemp= STP_Temperature+20.*kelvin; 
    
    // CO2 gas
      const G4double denCO2= 1.977e-3 *g/cm3 * STP_Temperature/expTemp;
      G4Material* CO2= new G4Material(name="CO2Gas", denCO2, ncomponents=2,
				       kStateGas, expTemp);
      CO2-> AddElement(elC, natoms=1);
      CO2-> AddElement(elO, natoms=2);
  
    // Isobutane gas (C4H10)
      const G4double denIsobutane= 2.67e-3 *g/cm3 * STP_Temperature/expTemp;
      G4Material* Isobutane= new G4Material(name="Isobutane", denIsobutane, 
  				            ncomponents=2,
				            kStateGas, expTemp);
      Isobutane-> AddElement(elC, natoms=4);
      Isobutane-> AddElement(elH, natoms=10);

  
    // CO2(90%) + Isobutane(10%) mixture
      density=  denCO2*0.9 + denIsobutane*0.1;
      G4Material* CO2Isobutane= new G4Material(name="CO2Isobutane", density, 
    			 	  	       nel=2, kStateGas, expTemp);
    			 		     
      CO2Isobutane-> AddMaterial(CO2      , massfraction= 90. * perCent);
      CO2Isobutane-> AddMaterial(Isobutane, massfraction= 10. * perCent);
      
      material = CO2Isobutane;
      
      G4cerr << "CO2Isobutane is installed" << G4endl;
  
  }

  return material;

}


