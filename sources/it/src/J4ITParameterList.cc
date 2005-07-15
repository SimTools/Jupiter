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
#if 1
  //   fITMaterial          = "Air";
  //   fLayerMaterial       = "Silicon";
   
   fITMaterial = J4ParameterTable::GetValue("J4IT.Material","Air");
   fLayerMaterial = J4ParameterTable::GetValue("J4IT.Layer.Material","Silicon");

#else
   fITMaterial          = "vacuum";
   fLayerMaterial       = "vacuum";
#endif
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4ITParameterList::SetParameters()
{
   // IT
   fITDeltaPhi          = 360.*deg;
   fITPhiOffset         = 0.*deg;
   
   // Layer
   fNlayers             = 5;
#ifdef __GLD_V1__
   fNlayers             = 4;
#endif
   fNlayers = J4ParameterTable::GetValue("J4IT.NLayers",4);

   fLayerPhiOffset      = new G4double[fNlayers];
   for(int i=0;i<fNlayers;i++) { fLayerPhiOffset[i] = 0.*rad ; }

   //   fLayerThick          = 0.5616*mm; 
   //   fLayerRspacing       = 7.0*cm;
   fLayerThick = J4ParameterTable::GetValue("J4IT.Layer.Thickness",0.05616)*cm;
   fLayerRspacing = J4ParameterTable::GetValue("J4IT.Layer.RSpacing",7.0)*cm;
#if 1
   fLayerHalfZincrement = 14.5*cm;
   fLayerDeltaPhi       = 360.*deg;
   fFirstLayerHalfZ     = 18.5*cm;
   fFirstLayerInnerR    = 9.0*cm;
   
   fLayerHalfZincrement = J4ParameterTable::GetValue("J4IT.Layer.HalfZIncrement",14.5)*cm;
   fLayerDeltaPhi       = 360.*deg;
   fFirstLayerHalfZ     = J4ParameterTable::GetValue("J4IT.FirstLayer.HalfZ",18.5)*cm;
   fFirstLayerInnerR    = J4ParameterTable::GetValue("J4IT.FirstLayer.InnerRadius",9.0)*cm;

#else
   fLayerHalfZincrement = 14.0*cm;
   fLayerDeltaPhi       = 360.*deg;
   fFirstLayerHalfZ     = 20.0*cm;
   fFirstLayerInnerR    = 10.0*cm;
#endif
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


