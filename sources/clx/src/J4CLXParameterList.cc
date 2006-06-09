// $Id$
//*************************************************************************
//* --------------------
//* J4CLXParameterList
//* --------------------
//* (Description)
//* 	Parameter list for Intermediate Tracker.
//*
//* (Update Record)
//*	2006/05/01  H.Ono Original version.
//*************************************************************************

#include "J4CLXParameterList.hh"
#include <algorithm>
#include <vector>
#include <fstream>
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
   fLayerMaterial         = "Air";
   fEMActiveLayerMaterial = "Air";   
   fHDActiveLayerMaterial = "Air";
   fEMAbsLayerMaterial    = J4ParameterTable::GetValue("J4CLX.EM.AbsLayerMaterial","Tungsten");
   fHDAbsLayerMaterial    = J4ParameterTable::GetValue("J4CLX.HD.AbsLayerMaterial","Iron");
   fEMFlexLayerMaterial   = J4ParameterTable::GetValue("J4CLX.EM.FlexLayerMaterial","Air");
   fHDFlexLayerMaterial   = J4ParameterTable::GetValue("J4CLX.HD.FlexLayerMaterial","Air");
   fTrapStripMaterial     = "Air";
   fStripMaterial         = "Air";
   fEMCellMaterial        = J4ParameterTable::GetValue("J4CLX.EM.CellMaterial","Scintillator");
   fHDCellMaterial        = J4ParameterTable::GetValue("J4CLX.HD.CellMaterial","Scintillator");
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4CLXParameterList::SetParameters()
{
  // ==== Basic parameters ==========================================================
  // CLX ----------------------------------------------------------------------------
  fCLXDeltaPhi     = 360.*deg;
  fCLXPhiOffset    = 0.*deg;
  
  //* Dodecagonal shape of CLX
  fNTraps          = J4ParameterTable::GetValue("J4CLX.NTraps", 12);
  
  //* Angle of each trapezoid ( 360*deg / nTrap )
  fTrapDeltaPhi    = fCLXDeltaPhi / fNTraps;
  
  //* Tolerance for trapezoid shape
  fLayerTolerance  = 0.0001*mm;
  fPhiTolerance    = 0.0001*mrad;

  //* Barrel/Endcap gap space
  fBarrelEndcapGap = J4ParameterTable::GetValue("J4CXL.BarrelEndcapGap",10.0)*cm;
  
  // Barrel--------------------------------------------------------------------------
  fBarrelInnerR    = J4ParameterTable::GetValue("J4CLX.Barrel.InnerRadius",210.0)*cm;
  //fBarrelHalfZ     = J4ParameterTable::GetValue("J4CLX.Barrel.HalfZ",270.0)*cm;
  fBarrelHalfZ     = J4ParameterTable::GetValue("J4CLX.Barrel.HalfZ",280.0)*cm;
  fBarrelDeltaPhi  = 360.*deg;
  fBarrelPhiOffset =   0.*deg;
   
  // Endcap--------------------------------------------------------------------------
#if defined(__GLD_V1__)
  //fEndcapInnerR    =  J4ParameterTable::GetValue("J4CLX.Endcap.InnerRadius",39.9)*cm;
  fEndcapInnerR    =  J4ParameterTable::GetValue("J4CLX.Endcap.InnerRadius",40.0)*cm;
#else
  fEndcapInnerR    =  45.*cm;
#endif
  fEndcapDeltaPhi  = 360.*deg;
  fEndcapPhiOffset =   0.*deg;
  
  //* Endcap frontZ position : BarrelHalfZ + Gap
  //fEndcapFrontZ    = fBarrelHalfZ + fBarrelEndcapGap;
  fEndcapFrontZ    = fBarrelHalfZ;
  
  // EM------------------------------------------------------------------------------
  //* EMThickness = (0.3cm + 0.2cm + 0.1cm) x 33 = 18cm
  fEMAbsLayerThickness    = J4ParameterTable::GetValue("J4CLX.EM.AbsLayerThickness",0.3)*cm;
  fEMActiveLayerThickness = J4ParameterTable::GetValue("J4CLX.EM.ActiveLayerThickness",0.2)*cm;
  fEMFlexLayerThickness   = J4ParameterTable::GetValue("J4CLX.EM.FlexLayerThickness",0.1)*cm;
  fEMNLayers              = J4ParameterTable::GetValue("J4CLX.EM.NLayers",33);
  fEMNSubLayers           = J4ParameterTable::GetValue("J4CLX.EM.NSubLayers",3);
  fEMNStrips              = J4ParameterTable::GetValue("J4CLX.EM.NStrips",3);
    
  // HD-----------------------------------------------------------------------------
  //* HDThickness = (2.0cm + 0.4cm + 0.1cm ) x 48 = 120cm
  fHDAbsLayerThickness    = J4ParameterTable::GetValue("J4CLX.HD.AbsLayerThickness",2.0)*cm;
  fHDActiveLayerThickness = J4ParameterTable::GetValue("J4CLX.HD.ActiveLayerThickness",0.5)*cm;
  fHDFlexLayerThickness   = J4ParameterTable::GetValue("J4CLX.HD.FlexLayerThickness",0.1)*cm;
  fHDNLayers              = J4ParameterTable::GetValue("J4CLX.HD.NLayers",46);
  fHDNSubLayers           = J4ParameterTable::GetValue("J4CLX.HD.NSubLayers",3);
  fHDNStrips              = J4ParameterTable::GetValue("J4CLX.HD.NStrips",3);
  
  // Cell----------------------------------------------------------------------------
  fCellSize = J4ParameterTable::GetValue("J4CLX.Cell.Size",1.0)*cm;

  // Nubmer of CAL types
  fNIsEM      = J4ParameterTable::GetValue("J4CLX.NumberOfCalTypes",2);
  
  //* Number of types of EM/HD, Barrel/Endcap
  fNIsBarrel  = J4ParameterTable::GetValue("J4CLX.NumberOfBarrelTypes",2);
  
  //* Maximum number of Strips-----------------------------------------------
  fEMNTrapStrips = (G4int)( 2*GetEMHalfZ()/fCellSize );
  fHDNTrapStrips = (G4int)( 2*GetHDHalfZ()/fCellSize );
  fMaxNStrips = fHDNCells;
  //
  // Maximum number of strips defined as
  // Number of strips at Barrel HD Length of Z
  //
  //  <- Barrel EM/HD Z Length ->
  //   _ _ _ _ _ _ _ _ _ _ _ _ _ 
  //  | | | | | | | | | | | | | |
  //  | | | | | | | | | | | | | |
  //  | | | | | | | | | | | | | |
  //  | | | | | | | | | | | | | |   
  //  |_|_|_|_|_|_|_|_|_|_|_|_|_|
  //
  //  ---------------------------> Z
  //         EM/HD HalfZ

  //* Maximum number of cells-----------------------------------------------
  fEMNCells   = (G4int)( 2*GetEMYmax()*std::tan( 0.5*fTrapDeltaPhi ) / fCellSize );
  fHDNCells   = (G4int)( 2*GetHDYmax()*std::tan( 0.5*fTrapDeltaPhi ) / fCellSize );
  fMaxNCells  = fHDNCells;
  //
  // Maximum number of cells defined as
  // Number of cells at HD Ymax part.
  //
  // <- Endcap EM/HD X width ->
  //  _______________________  /|\   Y
  //  \_|_|_|_|_|_|_|_|_|_|_/   | 
  //   \|_|_|_|_|_|_|_|_|_|/    |
  //    \                 /     | EM/HD Ymax
  //     \               /      |
  //      \             /       |
  //       \___________/        |
  //
  
}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4CLXParameterList::SetVisAttributes()
{
   fCLXVisAtt         = J4ParameterTable::GetValue("J4CLX.VisAtt",false);
   fEMVisAtt          = J4ParameterTable::GetValue("J4CLX.VisAtt.EM",false);
   fHDVisAtt          = J4ParameterTable::GetValue("J4CLX.VisAtt.HD",false);
   fLayerVisAtt       = J4ParameterTable::GetValue("J4CLX.VisAtt.Layer",false);
   fSubLayerVisAtt    = J4ParameterTable::GetValue("J4CLX.VisAtt.SubLayer",false);
   fTrapStripVisAtt   = J4ParameterTable::GetValue("J4CLX.VisAtt.TrapStrip",false);
   fStripVisAtt       = J4ParameterTable::GetValue("J4CLX.VisAtt.Strip",false);
   fCellVisAtt        = J4ParameterTable::GetValue("J4CLX.VisAtt.Cell",false);
}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4CLXParameterList::SetColors()
{
  std::vector<double> col;
  col=J4ParameterTable::GetDValue("J4CLX.Color","0.0 0.0 1.0 1.0",4);
  SetCLXColor( G4Color(col[0], col[1], col[2], col[3]) );
  col=J4ParameterTable::GetDValue("J4CLX.Color.EM","0.0 1.0 1.0 1.0",4);
  SetEMColor( G4Color(col[0], col[1], col[2], col[3]) );
  col=J4ParameterTable::GetDValue("J4CLX.Color.HD","1.0 0.0 0.0 1.0",4);
  SetHDColor( G4Color(col[0], col[1], col[2], col[3]) );
  col=J4ParameterTable::GetDValue("J4CLX.Color.Layer","0.0 1.0 0.0 1.0",4);
  SetLayerColor( G4Color(col[0], col[1], col[2], col[3]) );
  col=J4ParameterTable::GetDValue("J4CLX.Color.SubLayer","0.0 1.0 0.0 1.0",4);
  SetSubLayerColor( G4Color(col[0], col[1], col[2], col[3]) );
  col=J4ParameterTable::GetDValue("J4CLX.Color.TrapStrip","0.0 1.0 0.0 1.0",4);
  SetTrapStripColor( G4Color(col[0], col[1], col[2], col[3]) );
  col=J4ParameterTable::GetDValue("J4CLX.Color.Strip","0.0 1.0 0.0 1.0",4);
  SetStripColor( G4Color(col[0], col[1], col[2], col[3]) );    
  col=J4ParameterTable::GetDValue("J4CLX.Color.Cell","0.0 1.0 0.0 1.0",4);
  SetCellColor( G4Color(col[0], col[1], col[2], col[3]) );  
}
