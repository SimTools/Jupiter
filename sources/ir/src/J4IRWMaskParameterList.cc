// J4IRWMaskParameterList.cc
//*************************************************************************
//* --------------------
//* J4IRWMaskParameterList
//* --------------------
//* (Description)
//*     Class for describing his/her detector compornents.
//*
//* (Update Record)
//*     2002/11/19  T.Aso   Original version.
//*************************************************************************

#include "J4IRWMaskParameterList.hh"

//=====================================================================
//* constructor -------------------------------------------------------

J4IRWMaskParameterList::J4IRWMaskParameterList(J4IRParameterList* list)
{
  fList = list;
  fbpList = new J4IRBPParameterList(fList);
  fch2List = new J4IRCH2MaskParameterList(fList);
  fwsiList = new J4IRWSiCALParameterList(fList);
  SetParameters();
  SetMaterials();
  SetVisAttributes();
  SetColors();
}
//=====================================================================
//* destructor -------------------------------------------------------

J4IRWMaskParameterList::~J4IRWMaskParameterList()
{
  delete  fbpList;
  delete  fch2List;
  delete  fwsiList;
  delete  fList;
  delete  fWMaskColor;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4IRWMaskParameterList::SetMaterials()
{
  SetWMaskMaterial("Tungsten");
}

//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRWMaskParameterList::SetParameters()
{
  SetDefaults();
  BuildParameters();
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRWMaskParameterList::SetDefaults()
{

// Shape of WMask
  SetMargin(0.05*cm);
  SetWMask1Thick(4.*cm);
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRWMaskParameterList::BuildParameters()
{
}
//=====================================================================
//* SetVtsAttributes ------------------------------------------------------
void J4IRWMaskParameterList::SetVisAttributes()
{
  SetWMaskVisAtt(TRUE);
}
//=====================================================================
//* SetColors ---------------------------------------------------------
void J4IRWMaskParameterList::SetColors()
{
   SetWMaskColor(new G4Color(1.0,1.0,1.0));  
}


