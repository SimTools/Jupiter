//*************************************************************************
//* --------------------
//* J4TPCParameterList
//* --------------------
//* (Description)
//* 	Parameter list for Intermediate Tracker.
//*
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4TPCParameterList.hh"

J4TPCParameterList * J4TPCParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4TPCParameterList* J4TPCParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4TPCParameterList("TPC");
   }
   return fgInstance;
}

//=====================================================================
//* protected constructor ---------------------------------------------

J4TPCParameterList::J4TPCParameterList(const G4String& name)
                  :J4VParameterList(name)
{
   SetMaterials();
   SetParameters();
   SetVisAttributes();
   SetColors();
}

//=====================================================================
//* destructor -------------------------------------------------------

J4TPCParameterList::~J4TPCParameterList()
{
   //delete  fLayerPhiOffset;
   fgInstance = 0;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4TPCParameterList::SetMaterials()
{
#if 1
   fTPCMaterial             = "P10";
   fLayerMaterial           = "P10";
   fPadPlaneMaterial        = "P10";
   fPadRowMaterial          = "P10";
#else
   fTPCMaterial             = "vacuum";
   fLayerMaterial           = "vacuum";
   fPadPlaneMaterial        = "vacuum";
   fPadRowMaterial          = "vacuum";
#endif
   fInnerSupportTubMaterial = "InShellC";
   fOuterSupportTubMaterial = "OutShellC";
   fEndcapMaterial          = "EndCu";
   fCentralMembraneMaterial = "Copper";
   fPadMaterial             = "EndCu";
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4TPCParameterList::SetParameters()
{
   // TPC
   fTPCDeltaPhi         = 360.*deg;
   fTPCPhiOffset        = 0.*deg;
   
   // Endcap
   fEndcapHalfThick     = 1.*cm;
                                                                                
   // SupportTub
   fInnerSupportTubHalfThick = 2.1075*cm;
   fOuterSupportTubHalfThick = 4.1175*cm;

   // Layer
#if 1  
   fNlayers             = 200;
   fLayerThick          = 0.001*mm;
   fFirstLayerInnerR    = 5.0*mm;
#else
   fNlayers             = 5;
   fLayerThick          = 0.001*mm;
   fFirstLayerInnerR    = 10.*cm;
#endif

   // CentralMembrane
   fCentralMembraneHalfThick = 0.05*mm;

   // PadPlane 
   fPadPlaneHalfThick   = 1.5*cm;

   // PadRow
   fNpadRows            = 2;

   // Pad
   fNfirstPads          = 6;

}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4TPCParameterList::SetVisAttributes()
{
   fTPCVisAtt             = TRUE;
   fTPCHalfVisAtt         = TRUE;
   fLayerVisAtt           = TRUE;
   fEndcapVisAtt          = TRUE;
   fSupportTubVisAtt      = TRUE;
   fCentralMembraneVisAtt = TRUE;
   fPadPlaneVisAtt        = TRUE;
   fPadRowVisAtt          = TRUE;
   fPadVisAtt             = TRUE;
}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4TPCParameterList::SetColors()
{
   SetTPCColor(G4Color(1., 0., 0.));
   SetTPCHalfColor(G4Color(1., 0., 1.));
   SetEndcapColor(G4Color(0., 0., 1.));
   SetSupportTubColor(G4Color(0., 1., 0.));
   SetLayerColor(G4Color(1., 0., 1.));
   SetCentralMembraneColor(G4Color(1., 1., 0.));
   SetPadPlaneColor(G4Color(1., 1., 1.));
   SetPadRowColor(G4Color(1., 1., 1.));
   SetPadColor(G4Color(1., 0., 0.));
}

