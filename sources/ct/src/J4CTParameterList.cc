// $Id$
//*************************************************************************
//* --------------------
//* J4CTParameterList
//* --------------------
//* (Description)
//* 	Parameter list for Intermediate Tracker.
//*
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4CTParameterList.hh"

J4CTParameterList * J4CTParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4CTParameterList* J4CTParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4CTParameterList("CT");
   }
   return fgInstance;
}

//=====================================================================
//* protected constructor ---------------------------------------------

J4CTParameterList::J4CTParameterList(const G4String& name)
                  :J4VParameterList(name)
{
   SetMaterials();
   SetParameters();
   SetVisAttributes();
   SetColors();
}

//=====================================================================
//* destructor -------------------------------------------------------

J4CTParameterList::~J4CTParameterList()
{
   delete  fLayerPhiOffset;
   fgInstance = 0;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4CTParameterList::SetMaterials()
{
/*
   fCTMaterial          = "CO2Isobutane";
   fLayerMaterial       = "CO2Isobutane";
   fEndcapMaterial      = "Aluminum" ;
   fSupportTubMaterial  = "CarbonFiber" ;
   fOuterCylinderMaterial   = "Aluminum";
*/
   fCTMaterial          = "vacuum";
   fLayerMaterial       = "CO2Isobutane";
//   fCTMaterial          = "vacuum";
//   fLayerMaterial       = "vacuum";
   fEndcapMaterial      = "Aluminum" ;
   fSupportTubMaterial  = "vacuum" ;
   fOuterCylinderMaterial   = "Aluminum";

}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4CTParameterList::SetParameters()
{
   // CT
   fCTDeltaPhi          = 360.*deg;
   fCTPhiOffset         = 0.*deg;
   
   // Layer
   fNlayers             = 100;    // Note that we doubled the number of layers 
                                  // Two layer forms one real layer.
   fLayerPhiOffset      = new G4double[fNlayers];
   for(int i=0;i<fNlayers;i++){
     fLayerPhiOffset[i]   = 0.*rad; // 
   }

   fSupportTubHalfThick = 0.25*cm;
   fEndcapHalfThick     = 1.0*cm;
   fOuterCylinderHalfThick = 0.5*cm; 

   fFirstLayerRadius    = 45.0*cm;
   fLastLayerRadius     = 155.0*cm;

   fLayerRspacing       = (fLastLayerRadius- fFirstLayerRadius)/(G4double)fNlayers;

}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4CTParameterList::SetVisAttributes()
{
   fCTVisAtt          = FALSE;
   fLayerVisAtt       = TRUE;
   fSupportTubVisAtt  = FALSE;
}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4CTParameterList::SetColors()
{
   SetCTColor(G4Color(1., 0., 1.));
   SetLayerColor(G4Color(1., 0., 1.));
   SetSupportTubColor(G4Color(1., 0., 1.));
}


