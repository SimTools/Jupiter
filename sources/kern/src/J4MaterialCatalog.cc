// $Id$
// ====================================================================
//    J4MaterialCatalog.cc
//
//    Default elements/materials catalog 
//
// ====================================================================

#include "J4MaterialCatalog.hh"

J4MaterialCatalog* J4MaterialCatalog::fMaterialCatalog= 0;

////////////////////////////////////////////
J4MaterialCatalog::J4MaterialCatalog()
////////////////////////////////////////////
{
  fElementTable = G4Element::GetElementTable();
  fMaterialTable= G4Material::GetMaterialTable();
  ReadMaterialCatalog();
  
  // list elements/materials
  G4cout << *fElementTable << G4endl;
  G4cout << *fMaterialTable << G4endl;

}

/////////////////////////////////////////////
J4MaterialCatalog::~J4MaterialCatalog()
/////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////
G4Material* J4MaterialCatalog::Order(const G4String& name, 
                                     G4MaterialPropertiesTable* mtable) const
/////////////////////////////////////////////////////////////////////////
{
  G4Material* material= 0;

  G4int i;
  for(i=0; i< (G4int)G4Material::GetNumberOfMaterials(); i++) {
    G4Material* aMaterial = (*fMaterialTable)[i];
    G4String    aName     = aMaterial-> GetName();
    if(aName==name) {
      material= aMaterial;
      break;
    }
  }

  if (material && mtable) material->SetMaterialPropertiesTable(mtable);

  return material;
}

/////////////////////////////////////////////////////////////////////////////////
void J4MaterialCatalog::Print()
{
  G4int i;
  G4cout << "===============================================" << G4endl;
  G4cout << (G4int)G4Material::GetNumberOfMaterials() 
	<< " materials are defined " << G4endl;
  const G4MaterialTable *ft=G4Material::GetMaterialTable();
  for(i=0; i< (G4int)G4Material::GetNumberOfMaterials(); i++) {
    G4Material* aMaterial = (*ft)[i];
    G4String    aName     = aMaterial-> GetName();

    G4cout << "==" << aName << G4endl 
           << " Radiation Length=" << aMaterial->GetRadlen()/cm << " cm " << G4endl
           << " Nuclear Interaction Length=" 
	   <<  aMaterial->GetNuclearInterLength()/cm << " cm" << G4endl
           << " Density = " << aMaterial->GetDensity()/g*cm3 << " g/cm3" << G4endl ;

  }

}


#include "J4MaterialCatalog.icc"


