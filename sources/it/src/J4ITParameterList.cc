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
   fITMaterial          = "Air";
   fLayerMaterial       = "Silicon";
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
   fLayerPhiOffset      = new G4double[fNlayers];
   fLayerPhiOffset[0]   = 0.*rad; // 
   fLayerPhiOffset[1]   = 0.*rad; //
   fLayerPhiOffset[2]   = 0.*rad; // 
   fLayerPhiOffset[3]   = 0.*rad; // 
   fLayerPhiOffset[4]   = 0.*rad; //

   fLayerThick          = 0.5616*mm; 
   fLayerRspacing       = 7.0*cm;
#if 1
   fLayerHalfZincrement = 14.5*cm;
   fLayerDeltaPhi       = 360.*cm;
   fFirstLayerHalfZ     = 18.5*cm;
   fFirstLayerInnerR    = 9.0*cm;
#else
   fLayerHalfZincrement = 14.0*cm;
   fLayerDeltaPhi       = 360.*cm;
   fFirstLayerHalfZ     = 20.0*cm;
   fFirstLayerInnerR    = 10.0*cm;
#endif
}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4ITParameterList::SetVisAttributes()
{
   fITVisAtt          = FALSE;
   fLayerVisAtt       = TRUE;
}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4ITParameterList::SetColors()
{
   SetITColor(G4Color(1., 0., 1.));
   SetLayerColor(G4Color(1., 0., 1.));
}


