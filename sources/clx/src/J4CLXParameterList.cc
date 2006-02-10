 // $Id$
//*************************************************************************
//* --------------------
//* J4CLXParameterList
//* --------------------
//* (Description)
//* 	Parameter list for Intermediate Tracker.
//*
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4CLXParameterList.hh"
#include <algorithm>
#include <vector>
#include <fstream.h>
#include <iostream>
#include "TVNewton.hh"
#include "geomdefs.hh"
#include "J4ParameterTable.hh"

J4CLXParameterList* J4CLXParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4CLXParameterList* J4CLXParameterList::GetInstance()
{
   if ( !fgInstance ) {
      fgInstance = new J4CLXParameterList("CLX");
   }
   return fgInstance;
}

//=====================================================================
//* protected constructor ---------------------------------------------

J4CLXParameterList::J4CLXParameterList( const G4String& name )
  : J4VParameterList(name)
  //: J4VParameterList(name),  fSubLayerParameterList(0) 
{
   fgInstance = this;
   
   SetMaterials();
   SetParameters();
   SetVisAttributes();
   SetColors();
}

//=====================================================================
//* destructor -------------------------------------------------------

J4CLXParameterList::~J4CLXParameterList()
{
   delete fgInstance;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4CLXParameterList::SetMaterials()
{
   fCLXMaterial           = "Air";
   fBlockMaterial         = "Air";
   fEMMaterial            = "Air";
   fHDMaterial            = "Air";
   fLayerMaterial         = "Air";
   fEMAbsLayerMaterial    = J4ParameterTable::GetValue("J4CLX.EM.AbsLayerMaterial","Tungsten");
   fEMActiveLayerMaterial = "Air";
   fHDAbsLayerMaterial    = J4ParameterTable::GetValue("J4CLX.HD.AbsLayerMaterial","Iron");
   fHDActiveLayerMaterial = "Air";
   fBoardMaterial         = "Air";
   fLargeBoxCellMaterial  = "Air";
   fEMCellMaterial        = J4ParameterTable::GetValue("J4CLX.EM.CellMaterial","Scintillator");
   fHDCellMaterial        = J4ParameterTable::GetValue("J4CLX.HD.CellMaterial","Scintillator");
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4CLXParameterList::SetParameters()
{
   // ==== Basic parameters ========================================= 
   // CLX --------------------- 
   fCLXDeltaPhi     = 360.*deg;
   fCLXPhiOffset    =   0.*deg;

   // Octagonal shape of CLX
   fNTraps = J4ParameterTable::GetValue("J4CLX.NTraps", 8);
   // Angle of each trapezoid (45*deg)
   fTrapDeltaPhi             = fCLXDeltaPhi / fNTraps;
  
   // Barrel ------------------ 
   fBarrelDeltaPhi  = 360.*deg;
   fBarrelPhiOffset =   0.*deg;

   // Endcap ------------------ 
#if defined(__GLD_V1__)
   fEndcapInnerR    =  J4ParameterTable::GetValue("J4CLX.Endcap.InnerRadius",39.9)*cm;
#else
   fEndcapInnerR    =  45.*cm;
#endif
   fEndcapDeltaPhi  = 360.*deg;
   fEndcapPhiOffset =   0.*deg;

   // EM ------------------
   fEMAbsLayerThickness = J4ParameterTable::GetValue("J4CLX.EM.AbsLayerThickness",0.3)*cm;
   fEMActiveLayerThickness = J4ParameterTable::GetValue("J4CLX.EM.ActiveLayerThickness",0.2)*cm;
   fEMNLayers          = J4ParameterTable::GetValue("J4CLX.EM.NLayers",38);


   // HD ------------------
   fHDAbsLayerThickness = J4ParameterTable::GetValue("J4CLX.HD.AbsLayerThickness",2.0)*cm;
   fHDActiveLayerThickness = J4ParameterTable::GetValue("J4CLX.HD.ActiveLayerThickness",0.5)*cm;

   G4double calthickness = GetCLXOuterR() * std::cos(.5 * fTrapDeltaPhi) - GetCLXInnerR();
   G4int nlayers = (G4int)((calthickness - (fEMAbsLayerThickness + fEMActiveLayerThickness) * (fEMNLayers + .5))
			   / (fHDAbsLayerThickness + fHDActiveLayerThickness) - .5);
   fHDNLayers          = J4ParameterTable::GetValue("J4CLX.HD.NLayers",nlayers);


   // Cell ----------------
   fCellSize = J4ParameterTable::GetValue("J4CLX.Cell.Size",1.0)*cm;

}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4CLXParameterList::SetVisAttributes()
{
   fCLXVisAtt         = J4ParameterTable::GetValue("J4CLX.VisAtt",false);
   fBarrelVisAtt      = J4ParameterTable::GetValue("J4CLX.VisAtt.Barrel",false);
   fEndcapVisAtt      = J4ParameterTable::GetValue("J4CLX.VisAtt.Endcap",false);

   fBlockVisAtt       = J4ParameterTable::GetValue("J4CLX.VisAtt.Block",true);
   fEMVisAtt          = J4ParameterTable::GetValue("J4CLX.VisAtt.EM",false);
   fHDVisAtt          = J4ParameterTable::GetValue("J4CLX.VisAtt.HD",false);
   fLayerVisAtt       = J4ParameterTable::GetValue("J4CLX.VisAtt.Layer",false);
   fSubLayerVisAtt    = J4ParameterTable::GetValue("J4CLX.VisAtt.SubLayer",false);
   fBoardVisAtt       = J4ParameterTable::GetValue("J4CLX.VisAtt.Board",false);
   fLargeBoxCellVisAtt= J4ParameterTable::GetValue("J4CLX.VisAtt.LargeBoxCell",false);
   fEMCellVisAtt      = J4ParameterTable::GetValue("J4CLX.VisAtt.EMCell",false);
   fHDCellVisAtt      = J4ParameterTable::GetValue("J4CLX.VisAtt.HDCell",false);
}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4CLXParameterList::SetColors()
{

   std::vector<double> col;
   col=J4ParameterTable::GetDValue("J4CLX.Color","0.0 0.0 1.0 1.0",4);
   SetCLXColor(G4Color(col[0], col[1], col[2], col[3]));
   col=J4ParameterTable::GetDValue("J4CLX.Color.Barrel","0.0 0.0 1.0 1.0",4);
   SetBarrelColor(G4Color(col[0], col[1], col[2], col[3]));
   col=J4ParameterTable::GetDValue("J4CLX.Color.Endcap","0.0 0.0 1.0 1.0",4);
   SetEndcapColor(G4Color(col[0], col[1], col[2], col[3]));
   col=J4ParameterTable::GetDValue("J4CLX.Color.Block","0.0 0.0 1.0 1.0",4);
   SetBlockColor(G4Color(col[0], col[1], col[2], col[3]));
   col=J4ParameterTable::GetDValue("J4CLX.Color.EM","0.0 0.0 1.0 1.0",4);
   SetEMColor(G4Color(col[0], col[1], col[2], col[3]));
   col=J4ParameterTable::GetDValue("J4CLX.Color.HD","1.0 0.0 0.0 1.0",4);
   SetHDColor(G4Color(col[0], col[1], col[2], col[3]));
   col=J4ParameterTable::GetDValue("J4CLX.Color.Layer","0.0 1.0 0.0 1.0",4);
   SetLayerColor(G4Color(col[0], col[1], col[2], col[3]));
   col=J4ParameterTable::GetDValue("J4CLX.Color.SubLayer","0.0 1.0 0.0 1.0",4);
   SetSubLayerColor(G4Color(col[0], col[1], col[2], col[3]));
   col=J4ParameterTable::GetDValue("J4CLX.Color.Board","0.0 1.0 0.0 1.0",4);
   SetBoardColor(G4Color(col[0], col[1], col[2], col[3]));
   col=J4ParameterTable::GetDValue("J4CLX.Color.LargeBoxCell","0.0 1.0 0.0 1.0",4);
   SetBoardColor(G4Color(col[0], col[1], col[2], col[3]));
   col=J4ParameterTable::GetDValue("J4CLX.Color.EMCell","0.0 1.0 0.0 1.0",4);
   SetEMCellColor(G4Color(col[0], col[1], col[2], col[3]));
   col=J4ParameterTable::GetDValue("J4CLX.Color.HDCell","0.0 1.0 0.0 1.0",4);
   SetHDCellColor(G4Color(col[0], col[1], col[2], col[3]));
}
