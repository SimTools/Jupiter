// $Id$
//*************************************************************************
//* --------------------
//* J4CDCParameterList
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*
//* (Update Record)
//*	2002/10/06  K.Hoshina	Original version.
//*************************************************************************

#include "J4CDCParameterList.hh"
 
//=====================================================================
//* constructor -------------------------------------------------------

J4CDCParameterList::J4CDCParameterList()
{
   SetMaterials();
   SetParameters();
   SetVisAttributes();
   SetColors();
}

//=====================================================================
//* destructor -------------------------------------------------------

J4CDCParameterList::~J4CDCParameterList()
{
   delete  fCDCColor;
   delete  fEndcapColor;
   delete  fSupportTubColor;
   delete  fSuperLayerColor;
   delete  fLayerColor;
   delete  fCellColor;
   delete  fDriftRegionColor;
   delete  fStereoCellColor;
   delete  fStereoDriftRegionColor;
   delete  fDummyDriftRegionColor;
   delete  fSenseWireColor;
   delete  fTwistedAngle;
   delete  fSuperLayerPhiOffset;
   delete  fNcellsParLayer;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4CDCParameterList::SetMaterials()
{
   fCDCMaterial         = "Air";
   fSupportTubMaterial  = "Aluminum";
   fEndcapMaterial      = "Aluminum";
   fLayerMaterial       = "CO2Isobutane";
   fCellMaterial        = "CO2Isobutane";
   fDriftRegionMaterial = "CO2Isobutane";
   fSenseWireMaterial   = "CO2Isobutane";
   //fSenseWireMaterial   = "Tungsten";
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4CDCParameterList::SetParameters()
{
   // CDC
   fCDCInnerRadius      = 44.*cm;
   fCDCOuterRadius      = 157.*cm;
   fCDCHalfZLength      = 157.*cm;
   fCDCDeltaPhi         = 360.*deg;
   fCDCPhiOffset        = 360.*deg;
   
   // Endcap
   fEndcapHalfThickness = 1.*cm;
   
   // SupportTub
   fSupportTubThickness = 1.*cm;
   
   // Layer
   fNlayers           = 10;
   fTwistedAngle      = new G4double[fNlayers];
   fLayerPhiOffset    = new G4double[fNlayers];
   fIsAxialOnly       = TRUE; // TRUE: Axial only, FALSE: with Stereo cell
   
   fTwistedAngle[0]   =  0.   *rad; // axial
   fTwistedAngle[1]   =  0.512*rad; // stereo
   fTwistedAngle[2]   = -0.475*rad; // stereo
   fTwistedAngle[3]   =  0.   *rad; // axial
   fTwistedAngle[4]   =  0.415*rad; // stereo
   fTwistedAngle[5]   = -0.394*rad; // stereo
   fTwistedAngle[6]   =  0.   *rad; // axial
   fTwistedAngle[7]   =  0.358*rad; // stereo
   fTwistedAngle[8]   = -0.344*rad; // stereo
   fTwistedAngle[9]   =  0.   *rad; // axial
   
   fLayerPhiOffset[0] =  0.   *rad; // axial
   fLayerPhiOffset[1] =  0.032*rad; // stereo
   fLayerPhiOffset[2] = -0.032*rad; // stereo 
   fLayerPhiOffset[3] =  0.   *rad; // axial 
   fLayerPhiOffset[4] =  0.032*rad; // stereo
   fLayerPhiOffset[5] = -0.032*rad; // stereo 
   fLayerPhiOffset[6] =  0.   *rad; // axial 
   fLayerPhiOffset[7] =  0.016*rad; // stereo 
   fLayerPhiOffset[8] = -0.016*rad; // stereo 
   fLayerPhiOffset[9] =  0.   *rad; // axial 
   
   
   // SuperLayer
   fIsAxialInnermost       = TRUE; // innermost superlayer is small.
   fNlayersPerSuperLayer   = 3;
   fNsuperLayers           = (fNlayers - 1) / fNlayersPerSuperLayer + 1;
   fSuperLayerInnerGap     = 4.*cm;
   fSuperLayerOuterGap     = 4.*cm;
   fAxialToStereoGap       = 5.*cm;
   fStereoToStereoGap      = 3.*cm;
   fSuperLayerPhiOffset    = new G4double[fNsuperLayers];
   fNcellsParLayer         = new G4int[fNsuperLayers];
   // now, fNsuperLayers = 4
   
   fNcellsParLayer[0]      = 42;
   fNcellsParLayer[1]      = 63;
   fNcellsParLayer[2]      = 84;
   fNcellsParLayer[3]      = 105;

   fSuperLayerPhiOffset[0] =  0    *rad;
   fSuperLayerPhiOffset[1] =  0    *rad;
   fSuperLayerPhiOffset[2] = -0.016*rad;
   fSuperLayerPhiOffset[3] =  0.016*rad;
   
   // Cell
   
   // DriftRegion
   fNdriftRegions        = 5;             // per cell
   fDriftRegionThickness = 1.*cm;
   
   // DummyDriftRegion
   fDummyDriftRegionThickness = 1.*cm;
   
   // SenseWire
   fSenseWireRadius      = 0.015*mm;
   //fSenseWireRadius      = 1.5*mm;  // for printing
   
   // calcurated parameters
   
   fCellThickness = fNdriftRegions * fDriftRegionThickness 
                    + 2 * fDummyDriftRegionThickness;

   fStereoToAxialGap = 
      (GetOuterSupportTubIR() - GetInnerSupportTubOR()
       - fSuperLayerInnerGap - fSuperLayerOuterGap
       - fNlayers * fCellThickness
       - (fNsuperLayers - 1) * (fAxialToStereoGap + fStereoToStereoGap))
      / (fNsuperLayers - 1);
}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4CDCParameterList::SetVisAttributes()
{
   fCDCVisAtt         = TRUE;
   fEndcapVisAtt      = TRUE;
   fSupportTubVisAtt  = TRUE;
   fSuperLayerVisAtt  = FALSE;
   fLayerVisAtt       = FALSE;
   fCellVisAtt        = TRUE; 
   fDriftRegionVisAtt = FALSE;
   fSenseWireVisAtt   = TRUE;
   
   fStereoCellVisAtt  = FALSE; 
   fStereoDriftRegionVisAtt = FALSE;
   fDummyDriftRegionVisAtt  = FALSE;
}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4CDCParameterList::SetColors()
{
   fCDCColor         = new G4Color(0., 0., 1.);
   fEndcapColor      = new G4Color(0., 0., 1.);
   fSupportTubColor  = new G4Color(0., 0., 1.);
   fSuperLayerColor  = new G4Color(0., 0., 1.);
   fLayerColor       = new G4Color(0., 1., 0.);
   fCellColor        = new G4Color(0., 1., 1.);
   fDriftRegionColor = new G4Color(0., 1., 1.);
   fSenseWireColor   = new G4Color(1., 0., 1.);
   fDummyDriftRegionColor  = new G4Color(0., 1., 1.);
   fStereoCellColor        = new G4Color(0., 1., 1.);
   fStereoDriftRegionColor = new G4Color(0., 1., 1.);
}

//=====================================================================
//* GetLayerNumber ----------------------------------------------------
G4int J4CDCParameterList::GetLayerNumber(G4int superlayerid, 
                                         G4int myid) const
{
   if (fIsAxialInnermost) {
      return superlayerid * 3 + myid;
   } else {
      if (superlayerid == 0) return 0;
      return (superlayerid - 1) * 3 + 1 + myid;
   }
}



