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
  fMUDMaterial                = "Air";
  fBlockMaterial              = "Air";
//  fBarrelActiveMaterial       = "Scintillator";
//  fEndcapActiveMaterial       = "Scintillator";
//  fFrontEndcapActiveMaterial  = "Scintillator";
  fBarrelActiveMaterial       = "Air";  // Gas chamber reserved
  fEndcapActiveMaterial       = "Air";  // Gas chamber reserved
  fFrontEndcapActiveMaterial  = "Air";  // Gas chamber reserved
  fBarrelAbsMaterial          = "Iron";
  fEndcapAbsMaterial          = "Iron";
  fFrontEndcapAbsMaterial     = "Iron";
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4MUDParameterList::SetParameters()
{
  fMUDHeight                = 700.0*cm;                           // Detector outer size = 700.0*cm
  fDeltaPhi                 = 360.*deg;                           
  fNTraps                   = 8;                                  // Octagonal shape of MUD
  fTrapDeltaPhi             = fDeltaPhi / fNTraps;                // Angle of each trapezoid (45*deg)
  //fTolerance                = 1.0*mm;                               // Tolerance for MUD and Block size difference
  fTolerance                = 0.1*mm;                               // Tolerance for MUD and Block size difference
  
  // Endcap ----------------------------------------------------------//
#ifdef __GLD_V1__
  fEndcapFrontZ             = 535.0*cm;                            // Endcap front z-axis position
  fEndcapThick              = 310.0*cm;                            // Endcap thickness
#else								   
  fEndcapFrontZ             = 430.0*cm;				   // Endcap fornt z-axis position
  fEndcapThick              = 415.0*cm;                            // Endcap thickness
#endif								   
								   
  fEndcapInnerR             = 45.0*cm;                             // Endcap inner radius
  //fEndcapInnerR             = 50.0*cm;                             // Endcap inner radius
  fEndcapNSuperLayers       = 5;                                   // Number of Endcap SuperLayer
  fEndcapNAbsLayers         = fEndcapNSuperLayers + 1;             // Number of Endcap Active Layer
  fEndcapNActiveLayers      = fEndcapNSuperLayers;                 // Number of Endcap Active Layer
  fEndcapActiveThick        = 10.0*cm;                             // Endcap Active Layer thickness
  fEndcapAbsThick           = (fEndcapThick - fEndcapNActiveLayers*fEndcapActiveThick ) / fEndcapNAbsLayers; // Endcap Absorber thickness
  
  // frontEndcap -----------------------------------------------------//
  fFrontEndcapNSuperLayers  = 2;                                   // Number of FrontEndcap SuperLayer
  fFrontEndcapNAbsLayers    = fFrontEndcapNSuperLayers;            // Number of FrontEndcap Abs Layer
  fFrontEndcapNActiveLayers = fFrontEndcapNSuperLayers;            // Number of FrontEndcap Active Layer
  fFrontEndcapFrontZ        = 430.0*cm;                            // FrontEndcap front z-axis position
  //fFrontEndcapOuterR        = 370.0*cm;                            // FrontEndcap Outer radius
  fFrontEndcapOuterR        = 360.0*cm;                            // FrontEndcap Outer radius
  fFrontEndcapThick         = fEndcapFrontZ - fFrontEndcapFrontZ;  // FrontEndcap Thickness
  fFrontEndcapActiveThick   = 10.0*cm;                             // FrontEndcap Active Layer Thickness
  fFrontEndcapAbsThick      = ( fFrontEndcapThick - fFrontEndcapNActiveLayers*fFrontEndcapActiveThick ) / fFrontEndcapNAbsLayers; // FrontEndcap Absorber thickness
  
  // Barrel -----------------------------------------------------------//
  //fBarrelInnerR             = 455.0*cm;                            // Barrel inner radius
  fBarrelInnerR             = 460.0*cm;                            // Barrel inner radius
  fBarrelThick              = fMUDHeight - fBarrelInnerR;          // Barrel thickness : 250cm 
  fBarrelFrontHalfL         = fEndcapFrontZ;                       // Half length of Barrel front layer
  fBarrelNSuperLayers       = 4;                                   // Number of Barrel SuperLayer
  fBarrelNAbsLayers         = fBarrelNSuperLayers + 1;             // Number of Barrel Active Layer
  fBarrelNActiveLayers      = fBarrelNSuperLayers;                 // Number of Barrel Active Layer
  fBarrelActiveThick        = 10.0*cm;                             // Barrel Active Layer thickness
  fBarrelAbsThick           = (fBarrelThick - fBarrelNActiveLayers*fBarrelActiveThick ) / fBarrelNAbsLayers; // Barrel Absorber thickness

  // MUD and Block, MUD is fTolerance size larger than Block ---------------------//
  fMUDInnerR                = fBarrelInnerR - fTolerance;
  //fMUDOuterR                = fMUDHeight / std::cos( 0.5* fTrapDeltaPhi ) + fTolerance;
  fMUDOuterR                = 780.0*cm;       // fMUDOuterR = fMUDHeight / std::cos(22.5*deg) + fTolerance
  fMUDEndcapFrontZ          = fEndcapFrontZ - fTolerance;
  fMUDEndcapInnerR          = fEndcapInnerR - fTolerance;
  fMUDEndcapThick           = fEndcapThick + 2*fTolerance;
  fMUDFrontEndcapThick      = fFrontEndcapThick;
  fMUDFrontEndcapFrontZ     = fFrontEndcapFrontZ - fTolerance;
  fMUDFrontEndcapOuterR     = fFrontEndcapOuterR + fTolerance;
  fMUDHalfL                 = fMUDEndcapFrontZ + fMUDEndcapThick; // Half length of MUD : 845cm

  fBlockInnerR              = fBarrelInnerR;
  fBlockOuterR              = fMUDHeight / std::cos( 0.5*fTrapDeltaPhi );  
  fBlockEndcapFrontZ        = fEndcapFrontZ;
  fBlockEndcapInnerR        = fEndcapInnerR;
  fBlockEndcapThick         = fEndcapThick;
  fBlockFrontEndcapThick    = fFrontEndcapThick;
  fBlockFrontEndcapFrontZ   = fFrontEndcapFrontZ;
  fBlockFrontEndcapOuterR   = fFrontEndcapOuterR;
  fBlockHalfL               = fBlockEndcapFrontZ + fBlockEndcapThick; // Half length of MUD : 845cm
  
}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4MUDParameterList::SetVisAttributes()
{
   //fMUDVisAtt               = false;
   //fBlockVisAtt             = false;
   fMUDVisAtt               = true;
   fBlockVisAtt             = true;
   //fBarrelActiveVisAtt      = true;
   //fBarrelAbsVisAtt         = true;
   //fEndcapActiveVisAtt      = true;
   //fEndcapAbsVisAtt         = true;
   //fFrontEndcapActiveVisAtt = true;
   //fFrontEndcapAbsVisAtt    = true;
   fBarrelActiveVisAtt      = false;
   fBarrelAbsVisAtt         = false;
   fEndcapActiveVisAtt      = false;
   fEndcapAbsVisAtt         = false;
   fFrontEndcapActiveVisAtt = false;
   fFrontEndcapAbsVisAtt    = false;
}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4MUDParameterList::SetColors()
{
   SetMUDColor( G4Color( 1., 0., 0. ) );
   SetBlockColor( G4Color( 0., 1., 0. ) );
   SetBarrelActiveColor( G4Color( 0.5, 1., 0.5 ) );
   SetEndcapActiveColor( G4Color( 0.5, 1., 0.5 ) );
   SetBarrelAbsColor( G4Color( 0.3, 0.3, 1.0 ) );
   SetEndcapAbsColor( G4Color( 0.3, 0.3, 1.0 ) );
   SetFrontEndcapActiveColor( G4Color( 0.5, 1., 0.5 ) );
   SetFrontEndcapAbsColor( G4Color( 0.3, 0.3, 1.0 ) );
}
