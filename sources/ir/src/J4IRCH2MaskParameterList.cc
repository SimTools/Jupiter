// J4IRCH2MaskParameterList.cc
//*************************************************************************
//* --------------------
//* J4IRCH2MaskParameterList
//* --------------------
//* (Description)
//*     Class for describing his/her detector compornents.
//*
//* (Update Record)
//*     2002/11/19  T.Aso   Original version.
//*************************************************************************

#include "J4IRCH2MaskParameterList.hh"

//=====================================================================
//* constructor -------------------------------------------------------

J4IRCH2MaskParameterList::J4IRCH2MaskParameterList(J4IRParameterList* list)
{
  fList = list;
  fbpList = new J4IRBPParameterList(fList);
  fqc1List = new J4IRQC1ParameterList(fList);
  SetParameters();
  SetMaterials();
  SetVisAttributes();
  SetColors();
}
//=====================================================================
//* destructor -------------------------------------------------------

J4IRCH2MaskParameterList::~J4IRCH2MaskParameterList()
{
  delete  fList;
  delete  fbpList;
  delete  fqc1List;
  delete  fCH2MaskColor;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4IRCH2MaskParameterList::SetMaterials()
{
  SetCH2MaskMaterial("Polyethylene");
}

//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRCH2MaskParameterList::SetParameters()
{
  SetDefaults();
  BuildParameters();
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRCH2MaskParameterList::SetDefaults()
{
  SetDrMargin(0.5*mm);
  SetDzMargin(1.0*cm);

// Master volume (Tube) for CH2MASK
  SetCH2MaskZLength(15.*cm);
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRCH2MaskParameterList::BuildParameters()
{
}
//=====================================================================
//* SetVtsAttributes ------------------------------------------------------
void J4IRCH2MaskParameterList::SetVisAttributes()
{
  SetCH2MaskVisAtt(TRUE);
}
//=====================================================================
//* SetColors ---------------------------------------------------------
void J4IRCH2MaskParameterList::SetColors()
{
   SetCH2MaskColor(new G4Color(0.0,0.0,1.));  // blue
}


