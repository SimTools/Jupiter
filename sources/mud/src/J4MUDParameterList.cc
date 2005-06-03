// $Id$
//*************************************************************************
//* --------------------
//* J4MUDParameterList
//* --------------------
//* (Description)
//* 	Parameter list for Intermediate Tracker.
//*
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
#include "J4MUDParameterList.hh"
#include "J4ParameterTable.hh"
#include <vector>

J4MUDParameterList* J4MUDParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4MUDParameterList* J4MUDParameterList::GetInstance()
{
  if ( !fgInstance ) {
     fgInstance = new J4MUDParameterList( "MUD" );
  }
  return fgInstance;
}

//=====================================================================
//* protected constructor ---------------------------------------------
J4MUDParameterList::J4MUDParameterList( const G4String& name )
 : J4VParameterList( name )
{
   SetMaterials();
   SetParameters();
   SetVisAttributes();
   SetColors();
}

//=====================================================================
//* destructor -------------------------------------------------------
J4MUDParameterList::~J4MUDParameterList()
{
  fgInstance = 0;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4MUDParameterList::SetMaterials()
{
  fMUDMaterial   = J4ParameterTable::GetValue("J4MUD.Material","Air");
  fBlockMaterial = J4ParameterTable::GetValue("J4MUD.BlockMaterial","Air");
//  fBarrelActiveMaterial       = "Scintillator";
//  fEndcapActiveMaterial       = "Scintillator";
//  fFrontEndcapActiveMaterial  = "Scintillator";
  fBarrelActiveMaterial       = J4ParameterTable::GetValue("J4MUD.Barrel.ActiveMaterial","Air");  // Gas chamber reserved
  fEndcapActiveMaterial       = J4ParameterTable::GetValue("J4MUD.Endcap.ActiveMaterial","Air");  // Gas chamber reserved
  fFrontEndcapActiveMaterial  = J4ParameterTable::GetValue("J4MUD.FrontEndcap.ActiveMaterial","Air");  // Gas chamber reserved
  fBarrelAbsMaterial          = J4ParameterTable::GetValue("J4MUD.Barrel.AbsMaterial","Iron");
  fEndcapAbsMaterial          = J4ParameterTable::GetValue("J4MUD.Endcap.AbsMaterial","Iron");
  fFrontEndcapAbsMaterial     = J4ParameterTable::GetValue("J4MUD.FrontEndcap.AbsMaterial","Iron");
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4MUDParameterList::SetParameters()
{
  // Magnetic field magnitude
  fBarrelBField    = J4ParameterTable::GetValue("J4MUD.BarrelBFiled",2.0 )*tesla;
  fCornerBField    = J4ParameterTable::GetValue("J4MUD.CornerBFiled",1.5 )*tesla;
  fEndcapBField    = J4ParameterTable::GetValue("J4MUD.EndcapBFiled",2.5 )*tesla;
  fReturnBField    = J4ParameterTable::GetValue("J4MUD.ReturnBFiled",3.0 )*tesla;
  
  // Detector outer size = 700.0*cm
  fMUDHeight = J4ParameterTable::GetValue("J4MUD.Height",700.0)*cm;
  fDeltaPhi                 = 360.*deg;                           
  // Octagonal shape of MUD
  fNTraps   = J4ParameterTable::GetValue("J4MUD.NTraps",8);
  // Angle of each trapezoid (45*deg)
  fTrapDeltaPhi             = fDeltaPhi / fNTraps;        
  // Tolerance for MUD and Block size difference
  fTolerance = J4ParameterTable::GetValue("J4MUD.Tolerance",0.01)*cm;
  
  // Endcap ----------------------------------------------------------//
#ifdef __GLD_V1__
  // Endcap front z-axis position
  fEndcapFrontZ = J4ParameterTable::GetValue("J4MUD.Endcap.FrontZ",535.0)*cm; 
  // Endcap thickness
  fEndcapThick  = J4ParameterTable::GetValue("J4MUD.Endcap.Thickness",310.0)*cm; 
#else								   
  fEndcapFrontZ             = 430.0*cm;				   // Endcap fornt z-axis position
  fEndcapThick              = 415.0*cm;                            // Endcap thickness
#endif								   
								   
  // Endcap inner radius
  fEndcapInnerR = J4ParameterTable::GetValue("J4MUD.Endcap.InnerRadius",45.0)*cm;

  // Number of Endcap SuperLayer
  fEndcapNSuperLayers  = J4ParameterTable::GetValue("J4MUD.Endcap.NSuperLayers",5);
  // Number of Endcap Active Layer
  fEndcapNAbsLayers         = fEndcapNSuperLayers + 1;            
  // Number of Endcap Active Layer
  fEndcapNActiveLayers      = fEndcapNSuperLayers;               
  // Endcap Active Layer thickness
  fEndcapActiveThick = J4ParameterTable::GetValue("J4MUD.Endcap.ActiveThickness",10.0)*cm;
  // Endcap Absorber thickness
  fEndcapAbsThick    = (fEndcapThick - fEndcapNActiveLayers*fEndcapActiveThick ) / fEndcapNAbsLayers; 
  
  // frontEndcap -----------------------------------------------------//
  // Number of FrontEndcap SuperLayer
  fFrontEndcapNSuperLayers  = J4ParameterTable::GetValue("J4MUD.FrontEndcap.NSuperLayers",2);                                   
  // Number of FrontEndcap Abs Layer
  fFrontEndcapNAbsLayers    = fFrontEndcapNSuperLayers;            
  // Number of FrontEndcap Active Layer
  fFrontEndcapNActiveLayers = fFrontEndcapNSuperLayers;           
  // FrontEndcap front z-axis position
  fFrontEndcapFrontZ        = J4ParameterTable::GetValue("J4MUD.FrontEndcap.FrontZ",430.0)*cm;
  // FrontEndcap Outer radius
  fFrontEndcapOuterR        = J4ParameterTable::GetValue("J4MUD.FrontEndcap.OuterRadius",360.0)*cm;
  // FrontEndcap Thickness
  fFrontEndcapThick         = fEndcapFrontZ - fFrontEndcapFrontZ;  
  // FrontEndcap Active Layer Thickness
  fFrontEndcapActiveThick   = J4ParameterTable::GetValue("J4MUD.FrontEndcap.ActiveThickness",10.0)*cm;
  // FrontEndcap Absorber thickness
  fFrontEndcapAbsThick      = ( fFrontEndcapThick - fFrontEndcapNActiveLayers*fFrontEndcapActiveThick ) / fFrontEndcapNAbsLayers; 
  
  // Barrel -----------------------------------------------------------//
  //fBarrelInnerR             = 455.0*cm;                            // Barrel inner radius
  // Barrel inner radius
  fBarrelInnerR  = J4ParameterTable::GetValue("J4MUD.Barrel.InnerRadius",460.0)*cm;
  // Barrel thickness : 250cm 
  fBarrelThick              = fMUDHeight - fBarrelInnerR;         
  // Half length of Barrel front layer
  fBarrelFrontHalfL         = fEndcapFrontZ;                     
  // Number of Barrel SuperLayer
  fBarrelNSuperLayers  = J4ParameterTable::GetValue("J4MUD.Barrel.NSuperLayers",4);
  // Number of Barrel Active Layer
  fBarrelNAbsLayers         = fBarrelNSuperLayers + 1;            
  // Number of Barrel Active Layer
  fBarrelNActiveLayers      = fBarrelNSuperLayers;               
  // Barrel Active Layer thickness
  fBarrelActiveThick   = J4ParameterTable::GetValue("J4MUD.Barrel.ActiveThickness",10.0)*cm;
  // Barrel Absorber thickness
  fBarrelAbsThick           = (fBarrelThick - fBarrelNActiveLayers*fBarrelActiveThick ) / fBarrelNAbsLayers; 

  // MUD and Block, MUD is fTolerance size larger than Block ---------------------//
  fMUDInnerR                = fBarrelInnerR - fTolerance;
  //fMUDOuterR                = fMUDHeight / std::cos( 0.5* fTrapDeltaPhi ) + fTolerance;
  // fMUDOuterR = fMUDHeight / std::cos(22.5*deg) + fTolerance
  fMUDOuterR                = J4ParameterTable::GetValue("J4MUD.OuterRadius",780.0)*cm;       
  fMUDEndcapFrontZ          = fEndcapFrontZ - fTolerance;
  fMUDEndcapInnerR          = fEndcapInnerR - fTolerance;
  fMUDEndcapThick           = fEndcapThick + 2*fTolerance;
  fMUDFrontEndcapThick      = fFrontEndcapThick;
  fMUDFrontEndcapFrontZ     = fFrontEndcapFrontZ - fTolerance;
  fMUDFrontEndcapOuterR     = fFrontEndcapOuterR + fTolerance;

  // Half length of MUD : 845cm
  fMUDHalfL                 = fMUDEndcapFrontZ + fMUDEndcapThick; 

  fBlockInnerR              = fBarrelInnerR;
  fBlockOuterR              = fMUDHeight / std::cos( 0.5*fTrapDeltaPhi );  
  fBlockEndcapFrontZ        = fEndcapFrontZ;
  fBlockEndcapInnerR        = fEndcapInnerR;
  fBlockEndcapThick         = fEndcapThick;
  fBlockFrontEndcapThick    = fFrontEndcapThick;
  fBlockFrontEndcapFrontZ   = fFrontEndcapFrontZ;
  fBlockFrontEndcapOuterR   = fFrontEndcapOuterR;

  // Block Half length of MUD : 845cm
  fBlockHalfL               = fBlockEndcapFrontZ + fBlockEndcapThick; 
}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4MUDParameterList::SetVisAttributes()
{
   //fMUDVisAtt               = false;
   //fBlockVisAtt             = false;
   fMUDVisAtt       = J4ParameterTable::GetValue("J4MUD.VisAtt",false);
   fBlockVisAtt     = J4ParameterTable::GetValue("J4MUD.VisAtt.Block",false);
   //fBarrelActiveVisAtt      = true;
   //fBarrelAbsVisAtt         = true;
   //fEndcapActiveVisAtt      = true;
   //fEndcapAbsVisAtt         = true;
   //fFrontEndcapActiveVisAtt = true;
   //fFrontEndcapAbsVisAtt    = true;
   fBarrelActiveVisAtt      = J4ParameterTable::GetValue("J4MUD.VisAtt.BarrelActive",false);
   fBarrelAbsVisAtt         = J4ParameterTable::GetValue("J4MUD.VisAtt.BarrelAbs",true);
   fEndcapActiveVisAtt      = J4ParameterTable::GetValue("J4MUD.VisAtt.EndcapActive",false);
   fEndcapAbsVisAtt         = J4ParameterTable::GetValue("J4MUD.VisAtt.EndcapAbs",true);
   fFrontEndcapActiveVisAtt = J4ParameterTable::GetValue("J4MUD.VisAtt.FrontEndcapActive",false);
   fFrontEndcapAbsVisAtt    = J4ParameterTable::GetValue("J4MUD.VisAtt.FrontEndcapAbs",true);

}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4MUDParameterList::SetColors()
{
  std::vector<double> col;
  col=J4ParameterTable::GetDValue("J4MUD.Color","1.0 0.0 0.0 1.0",4);
  SetMUDColor( G4Color( col[0], col[1], col[2], col[3] ) );
  col=J4ParameterTable::GetDValue("J4MUD.Color.Block","0.0 1.0 0.0 1.0",4);
  SetBlockColor( G4Color( col[0], col[1], col[2], col[3] ) );
  col=J4ParameterTable::GetDValue("J4MUD.Color.BarrelActive","0.5 1.0 0.5 1.0",4);
  SetBarrelActiveColor( G4Color( col[0], col[1], col[2], col[3] ) );
  col=J4ParameterTable::GetDValue("J4MUD.Color.EndcapActive","0.5 1.0 0.5 1.0",4);
  SetEndcapActiveColor( G4Color( col[0], col[1], col[2], col[3] ) );
  col=J4ParameterTable::GetDValue("J4MUD.Color.BarrelAbs","0.3 0.3 1.0 1.0",4);
  SetBarrelAbsColor( G4Color( col[0], col[1], col[2], col[3] ) );
  col=J4ParameterTable::GetDValue("J4MUD.Color.EndcapAbs","0.3 0.3 1.0 1.0",4);
  SetEndcapAbsColor( G4Color( col[0], col[1], col[2], col[3] ) );
  col=J4ParameterTable::GetDValue("J4MUD.Color.FrontEndcapActive","0.5 1.0 0.5 1.0",4);
  SetFrontEndcapActiveColor( G4Color( col[0], col[1], col[2], col[3] ) );
  col=J4ParameterTable::GetDValue("J4MUD.Color.FrontEndcapAbs","0.3 0.3 1.0 1.0",4);
  SetFrontEndcapAbsColor( G4Color( col[0], col[1], col[2], col[3] ) );
}
