// $Id$
//********************************************************************
//* ---------------------
//* J4IRMaterialStore.hh
//* ---------------------
//* (Description)
//* 	The J4IRMaterialStore provides materials for IR.
//*     If you cannot find your material in the J4MaterialCatalog,
//*	you can define new material at create() method.
//*     
//* (Update Record)
//*	2000/12/20  K.Hoshina	Original version.
//********************************************************************

#include "J4IRMaterialStore.hh"
#include "G4Element.hh"
#include "G4Material.hh"

// ====================================================================
// -----------------
// class description
// -----------------


G4Material* J4IRMaterialStore::Create(const G4String& name,
	        G4MaterialPropertiesTable *mtable) 
{  	

  G4Material* material= 0;

  G4double A, Z;
  G4String mname;
  G4double density;
  G4int nel,natoms,ncomponents;
  const G4double expTemp=STP_Temperature+20.*kelvin;

  if(name == "Cupper") { 		// Cupper
    //--------------
    // materials...
    //--------------
      A = 63.546 *g/mole;
      density = 8.96 *g/cm3;
      G4Material* Cu = new G4Material(mname="Cupper",Z=29.,A,density);
      material = Cu;
  
  }else if ( name == "Polyethylene") {

    G4String ename,symbol;

    A= 1.00794 *g/mole;
    G4Element* elH= new G4Element(ename="Hydrogen", symbol="H", Z=1., A);

    A= 12.011 *g/mole;
    G4Element* elC= new G4Element(ename="Carbon", symbol="C", Z=6., A);

    density = 0.92*g/cm3;
    G4Material* Polyethylene = new G4Material(mname="Polyethylene",density,
					      nel=2,kStateSolid,expTemp);
    Polyethylene->AddElement(elC,natoms=2);
    Polyethylene->AddElement(elH,natoms=4);

    material = Polyethylene;
  }
  
  return material;

}


