// J4IRWSiCALParameterList.cc
//*************************************************************************
//* --------------------
//* J4IRWSiCALParameterList
//* --------------------
//* (Description)
//*     Class for describing his/her detector compornents.
//*
//* (Update Record)
//*     2002/11/19  T.Aso   Original version.
//*************************************************************************

#include "J4IRWSiCALParameterList.hh"

//=====================================================================
//* constructor -------------------------------------------------------

J4IRWSiCALParameterList::J4IRWSiCALParameterList(J4IRParameterList* list)
{
  fList = list;
  fbpList = new J4IRBPParameterList(fList);
  SetParameters();
  SetMaterials();
  SetVisAttributes();
  SetColors();
}
//=====================================================================
//* destructor -------------------------------------------------------

J4IRWSiCALParameterList::~J4IRWSiCALParameterList()
{
  delete  fbpList;
  delete  fList;
  delete  fWSiCALColor;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4IRWSiCALParameterList::SetMaterials()
{
  SetWSiCALMaterial("Tungsten");
}

//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRWSiCALParameterList::SetParameters()
{
  SetDefaults();
  BuildParameters();
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRWSiCALParameterList::SetDefaults()
{

// Shape of WSiCAL
  SetWSiCALNLayer(128);
  SetWSiCAL2ZLength(64.*cm);
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRWSiCALParameterList::BuildParameters()
{
}
//=====================================================================
//* SetVtsAttributes ------------------------------------------------------
void J4IRWSiCALParameterList::SetVisAttributes()
{
  SetWSiCALVisAtt(TRUE);
}
//=====================================================================
//* SetColors ---------------------------------------------------------
void J4IRWSiCALParameterList::SetColors()
{
   SetWSiCALColor(new G4Color(1.0,0.0,1.));  
}


