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
#include <vector>

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
   fDriftRegionMaterial     = "P10";
   fInnerSupportTubMaterial = "InShellC";
   fCentralMembraneMaterial = "Mylar";

   fTPCMaterial             = J4ParameterTable::GetValue("J4TPC.Material","P10");
   fLayerMaterial           = J4ParameterTable::GetValue("J4TPC.Material.Layer","P10");
   fPadPlaneMaterial        = J4ParameterTable::GetValue("J4TPC.Material.PadPlane","P10");
   fPadRowMaterial          = J4ParameterTable::GetValue("J4TPC.Material.PadRow","P10");
   fDriftRegionMaterial     = J4ParameterTable::GetValue("J4TPC.Material.DriftRegion","P10");
   fInnerSupportTubMaterial = J4ParameterTable::GetValue("J4TPC.Material.InnerSupportTube","InShellC");
   fCentralMembraneMaterial = J4ParameterTable::GetValue("J4TPC.Material.CentralMembrane","Mylar");

#else
   fTPCMaterial             = "vacuum";
   fLayerMaterial           = "vacuum";
   fPadPlaneMaterial        = "vacuum";
   fPadRowMaterial          = "vacuum";
   fInnerSupportTubMaterial = "vacuum";
   fCentralMembraneMaterial = "vacuum";
   fDriftRegionMaterial     = "vacuum";
#endif
   fOuterSupportTubMaterial = J4ParameterTable::GetValue("J4TPC.Material.OuterSupportTube","OutShellC");
   fEndcapMaterial          = J4ParameterTable::GetValue("J4TPC.Material.Endcap","EndCu");
   fPadMaterial             = J4ParameterTable::GetValue("J4TPC.Material.Pad","EndCu");
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4TPCParameterList::SetParameters()
{
   // TPC
   fTPCDeltaPhi         = 360.*deg;
   fTPCPhiOffset        = 0.*deg;
   
   // Endcap
   fEndcapHalfThick     = J4ParameterTable::GetValue("J4TPC.Endcap.HalfThickness",1.0)*cm;
                                                                                
   // SupportTub
   fInnerSupportTubHalfThick = J4ParameterTable::GetValue("J4TPC.InnerSupportTube.HalfThickness",2.1075)*cm;
   fOuterSupportTubHalfThick = J4ParameterTable::GetValue("J4TPC.OuterSupportTube.HalfThickness",4.1175)*cm;

   // Layer
   fNlayers             = J4ParameterTable::GetValue("J4TPC.NLayers",200);
   fFirstLayerInnerR    = J4ParameterTable::GetValue("J4TPC.FirstLayer.InnerRadius",0.5)*cm;
   // fLayerThick is used only when "J4TPC.UseThinLayer" is true
   fLayerThick          = J4ParameterTable::GetValue("J4TPC.Layer.Thickness",1.e-4);

   // CentralMembrane
   fCentralMembraneHalfThick = J4ParameterTable::GetValue("J4TPC.CentralMembrane.HalfThickness",0.00125)*cm;

   // PadPlane 
   fPadPlaneHalfThick   = J4ParameterTable::GetValue("J4TPC.PadPlane.HalfThickness",1.5)*cm;

   // PadRow
   fNpadRows            = J4ParameterTable::GetValue("J4TPC.NPadRows",2);

   // Pad
   fNfirstPads          = J4ParameterTable::GetValue("J4TPC.NFirstPads",6);

}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4TPCParameterList::SetVisAttributes()
{
  /*
   fTPCVisAtt             = FALSE;
   fTPCHalfVisAtt         = FALSE;
   fLayerVisAtt           = FALSE;
   fEndcapVisAtt          = TRUE;
   fSupportTubVisAtt      = TRUE;
   fCentralMembraneVisAtt = TRUE;
   fPadPlaneVisAtt        = FALSE;
   fPadRowVisAtt          = FALSE;
   fPadVisAtt             = TRUE;
   fDriftRegionVisAtt     = FALSE;
  */
   fTPCVisAtt             = J4ParameterTable::GetValue("J4TPC.VisAtt",false);
   fTPCHalfVisAtt         = J4ParameterTable::GetValue("J4TPC.VisAtt.Half",false);
   fLayerVisAtt           = J4ParameterTable::GetValue("J4TPC.VisAtt.Layer",false);
   fEndcapVisAtt          = J4ParameterTable::GetValue("J4TPC.VisAtt.Endcap",true);
   fSupportTubVisAtt      = J4ParameterTable::GetValue("J4TPC.VisAtt.SupportTube",true);
   fCentralMembraneVisAtt = J4ParameterTable::GetValue("J4TPC.VisAtt.CentralMembrane",true);
   fPadPlaneVisAtt        = J4ParameterTable::GetValue("J4TPC.VisAtt.PadPlane",false);
   fPadRowVisAtt          = J4ParameterTable::GetValue("J4TPC.VisAtt.PadRow",false);
   fPadVisAtt             = J4ParameterTable::GetValue("J4TPC.VisAtt.Pad",true);
   fDriftRegionVisAtt     = J4ParameterTable::GetValue("J4TPC.VisAtt.DriftRegion",false);

}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4TPCParameterList::SetColors()
{
  std::vector<double> col;
  col=J4ParameterTable::GetDValue("J4TPC.Color","1.0 0.0 0.0 1.0",4);
  SetTPCColor(G4Color(col[0], col[1], col[2], col[3]));
  col=J4ParameterTable::GetDValue("J4TPC.Color.Half","1.0 0.0 1.0 1.0",4);
  SetTPCHalfColor(G4Color(col[0], col[1], col[2], col[3]));
  col=J4ParameterTable::GetDValue("J4TPC.Color.Endcap","0.0 0.0 1.0 1.0",4);
  SetEndcapColor(G4Color(col[0], col[1], col[2], col[3]));
  col=J4ParameterTable::GetDValue("J4TPC.Color.SupportTube","0.0 1.0 0.0 1.0",4);
  SetSupportTubColor(G4Color(col[0], col[1], col[2], col[3]));
  col=J4ParameterTable::GetDValue("J4TPC.Color.Layer","1.0 0.0 1.0 1.0",4);
  SetLayerColor(G4Color(col[0], col[1], col[2], col[3]));
  col=J4ParameterTable::GetDValue("J4TPC.Color.CentralMembrane","1.0 1.0 0.0 1.0",4);
  SetCentralMembraneColor(G4Color(col[0], col[1], col[2], col[3]));
  col=J4ParameterTable::GetDValue("J4TPC.Color.PadPlane","1.0 1.0 1.0 1.0",4);
  SetPadPlaneColor(G4Color(col[0], col[1], col[2], col[3]));
  col=J4ParameterTable::GetDValue("J4TPC.Color.PadRow","1.0 1.0 1.0 1.0",4);
  SetPadRowColor(G4Color(col[0], col[1], col[2], col[3]));
  col=J4ParameterTable::GetDValue("J4TPC.Color.Pad","1.0 0.0 0.0 1.0",4);
  SetPadColor(G4Color(col[0], col[1], col[2], col[3]));
  col=J4ParameterTable::GetDValue("J4TPC.Color.DriftRegion","1.0 0.0 0.0 1.0",4);
  SetDriftRegionColor(G4Color(col[0], col[1], col[2], col[3]));
}

