// J4IRBPParameterList.cc
//*************************************************************************
//* --------------------
//* J4IRBPParameterList
//* --------------------
//* (Description)
//*     Class for describing his/her detector compornents.
//*
//* (Update Record)
//*     2002/11/19  T.Aso   Original version.
//*************************************************************************

#include "J4IRBPParameterList.hh"

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBPParameterList::J4IRBPParameterList(J4IRParameterList* list)
{
  fIRList = list;
  SetParameters();
  SetMaterials();
  SetVisAttributes();
  SetColors();
}
//=====================================================================
//* destructor -------------------------------------------------------

J4IRBPParameterList::~J4IRBPParameterList()
{
  delete  fIRList;
  delete  fBPColor;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4IRBPParameterList::SetMaterials()
{
  SetBPIPMaterial("Beryllium");
  SetBPSTDMaterial("Aluminum");
}

//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRBPParameterList::SetParameters()
{
  SetDefaults();
  BuildParameters();
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRBPParameterList::SetDefaults()
{
  // Margin for avoiding volume intersection.
  SetMargin(0.5*cm);

  // Be BP Pipe 
  //SetBPRadiusSmall(1.8*cm);   // moved to IRParameterList
  //SetBPBeThick(0.05*cm);      // moved to IRParameterList
  SetBPIPZPosition(0.*cm);
#ifdef __GLD_V1__
  SetBPIPZLength(14*cm);
#else
  SetBPIPZLength(10*cm);
#endif

  // Al BP Pipe
  SetBPRadiusLarge(7.3*cm);
  SetBPAlThick(0.2*cm);

  // Al BP End
  SetBPENDRadius(3.5*cm);
  SetBPENDZLength(24.8*cm);

  // Drum
  SetBPDrumcapZLength(0.2*cm);
  SetBPDrumZPosition(49.624*cm);

}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRBPParameterList::BuildParameters()
{
}
//=====================================================================
//* SetVtsAttributes ------------------------------------------------------
void J4IRBPParameterList::SetVisAttributes()
{
  SetBPVisAtt(TRUE);
}
//=====================================================================
//* SetColors ---------------------------------------------------------
void J4IRBPParameterList::SetColors()
{
   SetBPColor(new G4Color(0.0,0.5,0.5));  // cyan
}


