//********************************************************************
//* ---------------------
//* J4TPCMaterialStore.hh
//* ---------------------
//* (Description)
//* 	The J4TPCMaterialStore provides materials for TPC.
//*     If you cannot find your material in the J4MaterialCatalog,
//*	you can define new material at create() method.
//*     
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//********************************************************************

#include "J4TPCMaterialStore.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "J4ParameterTable.hh"

// ====================================================================
// -----------------
// class description
// -----------------


G4Material* J4TPCMaterialStore::Create(const G4String &iname, 
                                       G4MaterialPropertiesTable *) 
{  	

  G4Material* material= 0;

  if(iname == "DummyTPC") { 		// CO2Isobutane(90:10)  
#if 0
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
    //  temperature of experimental hall is controlled at 20 degree.
    //  const G4double expTemp= STP_Temperature+20.*kelvin; 
#endif  
  }
    
  if (iname == "Mylar") {
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
    G4int natoms, ncomponents;
                                                                                
    // Mylar
    const G4double denMylar= 1.39 *g/cm3;
    G4Material* Mylar= new G4Material(name="Mylar", denMylar, ncomponents=3);
    Mylar-> AddElement(elC, natoms=5);
    Mylar-> AddElement(elH, natoms=4);
    Mylar-> AddElement(elO, natoms=2);
                                                                                
    material = Mylar;
  }

 
  if (iname == "InShellC") {
    G4double A, Z, density;
    G4String name;

    A= 12.011 *g/mole;
    //    density = 0.1317 *g/cm3;
   density = J4ParameterTable::GetValue("J4TPC.InShellC.Density",0.1317)*g/cm3;
    G4Material *InShellC = new G4Material(name="InShellC", Z=6., A, density);

    material = InShellC;
  }

  if (iname == "OutShellC") {
    G4double A, Z, density;
    G4String name;

    A= 12.011 *g/mole;
    //    density = 0.08815 *g/cm3;
    density = J4ParameterTable::GetValue("J4TPC.OutShellC.Density",0.08815)*g/cm3;
    G4Material *OutShellC = new G4Material(name="OutShellC", Z=6., A, density);

    material = OutShellC;

  }


  if (iname == "EndCu") {
    G4double A, Z, density;
    G4String name;

    A = 63.546 *g/mole;
//  When density is 7.716e-2, Radiation length is 166.704cm
//  For 5 cm of Endcap and Pad plane, it is about 3% R.L.
    
    density = 7.716e-2 *g/cm3;
    density = J4ParameterTable::GetValue("J4TPC.EndCu.Density",2.5725E-1)*g/cm3;
    G4Material *EndCu = new G4Material(name="EndCu", Z=29., A, density);

    material = EndCu;


  }   
  if (iname == "PadPlane") {
    G4double A, Z, density;
    G4String name;

    A = 63.546 *g/mole;
//  When density is 7.716e-2, Radiation length is 166.704cm
//  For 5 cm of Endcap and Pad plane, it is about 3% R.L.
    
    density = 7.716e-2 *g/cm3;
    density = J4ParameterTable::GetValue("J4TPC.PadPlane.Density",2.5725E-1)*g/cm3;
    G4Material *PadPlane = new G4Material(name="PadPlane", Z=29., A, density);
    material = PadPlane;


  }   

  if(iname == "P10" || iname == "P5" || iname == "TDR" 
    || iname == "ARCF4_3_ISOB_1" ) {
    //--------------
    // elements...
    //--------------
    G4double A, Z;
    G4String name, symbol;
                                                                                
    A= 1.00794 *g/mole;
    G4Element* elH= new G4Element(name="Hydrogen", symbol="H", Z=1., A);

    A= 12.011 *g/mole;
    G4Element* elC= new G4Element(name="Carbon", symbol="C", Z=6., A);

    A= 18.9984032 *g/mole;
    G4Element *elF=new G4Element(name="Freon", symbol="F", Z=9., A);

    //--------------
    // materials...
    //--------------
    G4double density, massfraction;
    G4int natoms, nel, ncomponents;

    //temperature of experimental hall is controlled at 20 degree.
    const G4double expTemp= STP_Temperature+20.*kelvin;

    // Methane gas (CH4)
    const G4double denMethane= 0.717e-3 *g/cm3 * STP_Temperature/expTemp;
    G4Material* Methane= new G4Material(name="Methane", denMethane,
                                          ncomponents=2,
                                          kStateGas, expTemp);
    Methane-> AddElement(elC, natoms=1);
    Methane-> AddElement(elH, natoms=4);

    // Ar gas
    A= 39.948 *g/mole;
    const G4double denAr= 1.782e-03 *g/cm3 * STP_Temperature/expTemp;
    G4Material* Ar= new G4Material(name="ArgonGas", Z=18., A, denAr,
                                   kStateGas, expTemp);

    if (iname == "TDR") {
      //element O for TDR
      A= 15.9994 *g/mole;
      G4Element* elO= new G4Element(name="Oxygen", symbol="O", Z=8., A);

      // CO2 gas
      const G4double denCO2= 1.977e-3 *g/cm3 * STP_Temperature/expTemp;
      G4Material* CO2= new G4Material(name="CO2Gas", denCO2, ncomponents=2,
                                      kStateGas, expTemp);
      CO2-> AddElement(elC, natoms=1);
      CO2-> AddElement(elO, natoms=2);
                                                                                
      // Ar(93%) + Methane(5%) + CO2(2%) mixture
      density = denMethane*0.05 + denAr*0.93 + denCO2*0.02;
      G4Material* TDR = new G4Material(name="TDR", density, nel=3,
                                       kStateGas, expTemp);
      TDR-> AddMaterial(Ar     , massfraction= 90. * perCent);
      TDR-> AddMaterial(Methane, massfraction= 10. * perCent);
                                                                                
      material = TDR;
 
    } else if ( iname == "ARCF4_3_ISOB_1") {
// ArCF4(3%)Isob(1%)
      // Isobutane
      A=58.12 *g/mole;
      const G4double denIsob=2.595e-3 *g/cm3 * STP_Temperature/expTemp;
      G4Material *Isobutane=new G4Material(name="TPCIsobutane", denIsob, 
	ncomponents=2, kStateGas, expTemp);
      Isobutane->AddElement(elC, natoms=4);
      Isobutane->AddElement(elH, natoms=10);

      // CF4
      A=88.01 *g/mole;
      const G4double denCF4=3.9288e-3 *g/cm3 * STP_Temperature/expTemp;
      G4Material *CF4=new G4Material(name="CF4", denCF4, 
	ncomponents=2, kStateGas, expTemp);
      CF4->AddElement(elC, natoms=1);
      CF4->AddElement(elF, natoms=4);

       density = denAr*0.96 + denCF4*0.03 + denIsob*0.01;
       G4Material* ARCF4= new G4Material(name="ARCF4_3_ISOB_1", density, nel=3,
                                       kStateGas, expTemp);
       ARCF4-> AddMaterial(Ar , massfraction= 96. * perCent);
       ARCF4-> AddMaterial(CF4, massfraction=  3. * perCent);
       ARCF4-> AddMaterial(Isobutane, massfraction=  1. * perCent);
                                                                                
       material = ARCF4;

    } else if ( iname == "P5" ) {
       // Ar(95%) + Methane(5%) mixture
       density = denMethane*0.05 + denAr*0.95;
       G4Material* P5= new G4Material(name="P5", density, nel=2,
                                       kStateGas, expTemp);
       P5-> AddMaterial(Ar     , massfraction= 95. * perCent);
       P5-> AddMaterial(Methane, massfraction=  5. * perCent);
       material = P5;

    } else {
       // Ar(90%) + Methane(10%) mixture
       density = denMethane*0.1 + denAr*0.9;
       G4Material* P10= new G4Material(name="P10", density, nel=2,
                                       kStateGas, expTemp);
       P10-> AddMaterial(Ar     , massfraction= 90. * perCent);
       P10-> AddMaterial(Methane, massfraction= 10. * perCent);
       material = P10;
    }
  }

    std::cerr << "TPC Material : " << iname ;
    std::cerr << "  Radiation Length " << material->GetRadlen()/cm << " cm" ;
    std::cerr << "  Nuclear Interaction Length " << 
	material->GetNuclearInterLength()/cm << " cm" ;
    std::cerr << std::endl;

  return material;

}


