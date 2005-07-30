// $Id$
//*************************************************************************
//* --------------------
//* J4ITParameterList
//* --------------------
//* (Description)
//* 	Parameter list for Intermediate Tracker.
//*
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*     2005/07/16  A.Miyamoto  Modified to include FT
//*************************************************************************

#include "J4ITParameterList.hh"
#include "J4ParameterTable.hh"
#include <vector>

J4ITParameterList * J4ITParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4ITParameterList* J4ITParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4ITParameterList("IT");
   }
   return fgInstance;
}

//=====================================================================
//* protected constructor ---------------------------------------------

J4ITParameterList::J4ITParameterList(const G4String& name)
                  :J4VParameterList(name)
{
   SetMaterials();
   SetParameters();
   SetVisAttributes();
   SetColors();
}

//=====================================================================
//* destructor -------------------------------------------------------

J4ITParameterList::~J4ITParameterList()
{
   delete  fLayerPhiOffset;
   fgInstance = 0;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4ITParameterList::SetMaterials()
{
   fITMaterial = J4ParameterTable::GetValue("J4IT.Material","Air");
   fLayerMaterial = J4ParameterTable::GetValue("J4IT.Layer.Material","Silicon");
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4ITParameterList::SetParameters()
{
   // IT
   fITDeltaPhi          = 360.*deg;
   fITPhiOffset         = 0.*deg;
   
   // Layer
   fLayerThick = J4ParameterTable::GetValue("J4IT.Layer.Thickness",0.05616)*cm;

}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4ITParameterList::SetVisAttributes()
{
  //   fITVisAtt          = FALSE;
  //   fLayerVisAtt       = TRUE;

   fITVisAtt = J4ParameterTable::GetValue("J4IT.VisAtt",false);
   fLayerVisAtt = J4ParameterTable::GetValue("J4IT.VisAtt.Layer",true);

}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4ITParameterList::SetColors()
{
  std::vector<double> col;
  col=J4ParameterTable::GetDValue("J4IT.Color","1.0 0.0 1.0 1.0",4);
  SetITColor(G4Color(col[0], col[1], col[2], col[3]));
  col=J4ParameterTable::GetDValue("J4IT.Color.Layer","1.0 0.0 1.0 1.0",4);
  SetLayerColor(G4Color(col[0], col[1], col[2], col[3]));

  //   SetITColor(G4Color(1., 0., 1.));
  //   SetLayerColor(G4Color(1., 0., 1.));
  
}


