//$Id$
//********************************************************************
//* ---------------------
//* J4MUDMaterialStore.hh
//* ---------------------
//* (Description)
//* 	The J4MUDMaterialStore provides materials for MUD.
//*     If you cannot find your material in the J4MaterialCatalog,
//*	you can define new material at create() method.
//*     
//* (Update Record)
//*	2003/08/13  Akiya Miyamoto	Original version.
//********************************************************************
#include "J4MUDMaterialStore.hh"
#include "G4Element.hh"
#include "G4Material.hh"

G4Material* J4MUDMaterialStore::Create( const G4String& /*name*/, G4MaterialPropertiesTable * /* mtable */ ) 
{
  G4Material* material = 0;
  return material;
}
