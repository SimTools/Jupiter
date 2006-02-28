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
  fMUDMaterial               = J4ParameterTable::GetValue("J4MUD.Material","Air");
  fBlockMaterial             = J4ParameterTable::GetValue("J4MUD.BlockMaterial","Air");
  fBarrelActiveMaterial      = J4ParameterTable::GetValue("J4MUD.Barrel.ActiveMaterial","Scintillator");
  fEndcapActiveMaterial      = J4ParameterTable::GetValue("J4MUD.Endcap.ActiveMaterial","Scintillator");
  fFrontEndcapActiveMaterial = J4ParameterTable::GetValue("J4MUD.FrontEndcap.ActiveMaterial","Scintillator");
  fBarrelAbsMaterial         = J4ParameterTable::GetValue("J4MUD.Barrel.AbsMaterial","Iron");
  fEndcapAbsMaterial         = J4ParameterTable::GetValue("J4MUD.Endcap.AbsMaterial","Iron");
  fFrontEndcapAbsMaterial    = J4ParameterTable::GetValue("J4MUD.FrontEndcap.AbsMaterial","Iron");
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4MUDParameterList::SetParameters()
{
  //* Switch front layer to active or absorber ------------------------
  fIsFrontActive    = J4ParameterTable::GetValue("J4MUD.IsFrontActive", true );
  
  //* Magnetic field magnitude ----------------------------------------
  fBarrelBField     = J4ParameterTable::GetValue("J4MUD.BarrelBFiled",2.0 )*tesla;
  fCornerBField     = J4ParameterTable::GetValue("J4MUD.CornerBFiled",1.5 )*tesla;
  fEndcapBField     = J4ParameterTable::GetValue("J4MUD.EndcapBFiled",2.5 )*tesla;
  fReturnBField     = J4ParameterTable::GetValue("J4MUD.ReturnBFiled",3.0 )*tesla;
  
  //* Detector outer size = 700.0*cm ----------------------------------
  fMUDHeight        = J4ParameterTable::GetValue("J4MUD.Height",765.0)*cm;

  //* Total phi of MUD ------------------------------------------------
  fDeltaPhi         = 360.*deg;

  //* MUD polygon shape parameter -------------------------------------
  fNTraps           = J4ParameterTable::GetValue("J4MUD.NTraps",12);

  //* Number of Layers in MUD -----------------------------------------
  fNLayers          = J4ParameterTable::GetValue("J4MUD.NLayers", 9);

  //* Angle of each trapezoid (default : 12.25*deg for octagonal shape) --
  fTrapDeltaPhi     = fDeltaPhi/fNTraps;

  //* Tolerance for MUD and Block size difference ---------------------
  fTolerance        = J4ParameterTable::GetValue("J4MUD.Tolerance",0.001)*mm;

  //* Phi Tolerance between each block or trap ------------------------
  fPhiTolerance     = J4ParameterTable::GetValue("J4MUD.PhiTolerance",0.0001)*mrad;

  //* Active Layer thickness ------------------------------------------
  fActiveThick      = J4ParameterTable::GetValue("J4MUD.ActiveThickness",5.0)*cm;

  //* Front Active Layer ----------------------------------------------
  fFrontActiveThick = J4ParameterTable::GetValue("J4MUD.FrontActiveThickness",5.0)*cm;
  
  //* Absorber thickness ----------------------------------------------
  std::vector<double> absVector;
  fAbsThick = new G4double [fNLayers];
  absVector = J4ParameterTable::GetDValue("J4MUD.AbsThickness", "25.0 25.0 25.0 25.0 25.0 25.0 25.0 50.0 50.0", fNLayers );
  for ( G4int i = 0; i < fNLayers; i++ ) { fAbsThick[i] = absVector[i]*cm; }
  
  //**** Barrel Parameters *******************************************
  //* Barrel inner radius --------------------------------------------
  fBarrelInnerR          = J4ParameterTable::GetValue("J4MUD.Barrel.InnerRadius",450.0)*cm;
  
  //* Barrel thickness -----------------------------------------------
  fBarrelThick           = fMUDHeight - fBarrelInnerR;
  
  //* Number of Barrel Active Layer ----------------------------------
  fBarrelNActiveLayers   = ( fIsFrontActive ) ? fNLayers : fNLayers -1;
  
  //* Number of Barrel Absorber Layer --------------------------------
  fBarrelNAbsLayers      = fNLayers;
  
  //* Barrel Active Layer thickness ----------------------------------
  fBarrelActiveThick     = fActiveThick;
  
  //**** Endcap Parametes ********************************************
#ifdef __GLD_V1__
  //* Endcap front z-axis position -----------------------------------
  fEndcapFrontZ          = J4ParameterTable::GetValue("J4MUD.Endcap.FrontZ",485.0)*cm;
  //* Endcap thickness -----------------------------------------------
  fEndcapThick           = J4ParameterTable::GetValue("J4MUD.Endcap.Thickness",315.0)*cm;
#else
  //* Endcap front z-axis position -----------------------------------
  fEndcapFrontZ          = 430.0*cm;
  //* Endcap thickness -----------------------------------------------
  fEndcapThick           = 415.0*cm;
#endif

  //* Half length of Barrel front layer ------------------------------
  fBarrelFrontHalfL      = fEndcapFrontZ;
  
  //* Endcap inner radius --------------------------------------------
  fEndcapInnerR          = J4ParameterTable::GetValue("J4MUD.Endcap.InnerRadius",45.0)*cm;

  //* Number of Endcap Active Layers  --------------------------------
  fEndcapNActiveLayers   = ( fIsFrontActive ) ? fNLayers : fNLayers -1;
  
  //* NUmber of Endcap Absorber Layers -------------------------------
  fEndcapNAbsLayers      = fNLayers;

  //* Endcap Active Layer thickness ----------------------------------
  fEndcapActiveThick     = fActiveThick;
  
  //**** frontEndcap Parameters **************************************
  //* FrontEndcap front z-axis position ------------------------------
  fFrontEndcapFrontZ        = J4ParameterTable::GetValue("J4MUD.FrontEndcap.FrontZ",425.1)*cm;
  
  //* FrontEndcap Outer radius ---------------------------------------
  fFrontEndcapOuterR        = J4ParameterTable::GetValue("J4MUD.FrontEndcap.OuterRadius",260.0)*cm;
  
  //* Number of FrontEndcap SuperLayer -------------------------------
  fFrontEndcapNSuperLayers  = J4ParameterTable::GetValue("J4MUD.FrontEndcap.NSuperLayers",2);
  
  //* Number of FrontEndcap Abs Layer --------------------------------
  fFrontEndcapNAbsLayers    = fFrontEndcapNSuperLayers;

  //* Number of FrontEndcap Active Layer -----------------------------
  fFrontEndcapNActiveLayers = ( fIsFrontActive ) ? fFrontEndcapNSuperLayers-1 : fFrontEndcapNSuperLayers;
  
  //* FrontEndcap Active Layer Thickness -----------------------------
  fFrontEndcapActiveThick   = fActiveThick;

  //* FrontEndcap Thickness ------------------------------------------
  fFrontEndcapThick         = fEndcapFrontZ - fFrontEndcapFrontZ;
  
  //**** Block parameters ********************************************
  //* Block is fTolerance size smaller than MUD ----------------------
  //******************************************************************
  if ( fIsFrontActive ) {
    fBlockInnerR            = fBarrelInnerR - fFrontActiveThick;
    fBlockEndcapFrontZ      = fEndcapFrontZ - fFrontActiveThick;
    fBlockEndcapThick       = fEndcapThick + fFrontActiveThick;
    fBlockFrontEndcapThick  = fFrontEndcapThick - fFrontActiveThick;
  } else {
    fBlockInnerR            = fBarrelInnerR;
    fBlockEndcapFrontZ      = fEndcapFrontZ;
    fBlockEndcapThick       = fEndcapThick;
    fBlockFrontEndcapThick  = fFrontEndcapThick;
  }
  
  //* FrontEndcap Absorber thickness ---------------------------------
  fFrontEndcapAbsThick      = ( fBlockFrontEndcapThick - fFrontEndcapNActiveLayers*fFrontEndcapActiveThick ) / fFrontEndcapNAbsLayers ;

  //****************************************************************
  fBlockOuterR              = fMUDHeight/std::cos( 0.5*fTrapDeltaPhi );
  fBlockEndcapInnerR        = fEndcapInnerR;
  fBlockFrontEndcapOuterR   = fFrontEndcapOuterR;
  fBlockFrontEndcapFrontZ   = fFrontEndcapFrontZ;
  fBlockHalfL               = fBlockEndcapFrontZ + fBlockEndcapThick;
  
  //**** MUD Paramters ********************************************
  fMUDOuterR                = fMUDHeight/std::cos( 0.5*fTrapDeltaPhi ) + fTolerance;
  fMUDInnerR                = GetBlockInnerR() - fTolerance;
  fMUDEndcapFrontZ          = fBlockEndcapFrontZ - fTolerance;
  fMUDEndcapInnerR          = fEndcapInnerR - fTolerance;
  fMUDEndcapThick           = GetBlockEndcapThick() + 2*fTolerance;
  fMUDFrontEndcapThick      = fBlockFrontEndcapThick;
  fMUDFrontEndcapFrontZ     = fBlockFrontEndcapFrontZ - fTolerance;
  fMUDFrontEndcapOuterR     = fFrontEndcapOuterR + fTolerance;
  fMUDHalfL                 = fMUDEndcapFrontZ + fMUDEndcapThick;
}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4MUDParameterList::SetVisAttributes()
{
   fMUDVisAtt               = J4ParameterTable::GetValue("J4MUD.VisAtt",false);
   fBlockVisAtt             = J4ParameterTable::GetValue("J4MUD.VisAtt.Block",false);
   fBarrelActiveVisAtt      = J4ParameterTable::GetValue("J4MUD.VisAtt.BarrelActive",true);
   fBarrelAbsVisAtt         = J4ParameterTable::GetValue("J4MUD.VisAtt.BarrelAbs",true);
   fEndcapActiveVisAtt      = J4ParameterTable::GetValue("J4MUD.VisAtt.EndcapActive",true);
   fEndcapAbsVisAtt         = J4ParameterTable::GetValue("J4MUD.VisAtt.EndcapAbs",true);
   fFrontEndcapActiveVisAtt = J4ParameterTable::GetValue("J4MUD.VisAtt.FrontEndcapActive",true);
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

//=========================================================
//* Getter for Geometrical parameters

//* Accumulate thickness of absorber ----------------------
G4double J4MUDParameterList::GetTotalAbsThick( G4int layerID ) const
{
  G4double absThick = 0;
  if ( layerID != 0 ) {
    for ( G4int i = 0; i < layerID; i++ ) {
      absThick += GetAbsThick( i );
    }
  }
  return absThick;
}

//* Front Position of Barrel Active Layer ---------------
G4double J4MUDParameterList::GetBarrelActiveFront( G4int layerID ) const
{
  return ( fIsFrontActive )
    ? GetBarrelInnerR() + GetTotalAbsThick( layerID ) + (layerID-1)*GetBarrelActiveThick()
    : GetBarrelAbsFront( layerID ) + GetBarrelAbsThick( layerID );
}

//* Front Position of Barrrel Abs layer -----------------
G4double J4MUDParameterList::GetBarrelAbsFront( G4int layerID ) const
{
  return ( fIsFrontActive )
    ? GetBarrelActiveFront( layerID ) + GetBarrelActiveThick()
    : GetBarrelInnerR() + GetTotalAbsThick( layerID ) + layerID*GetBarrelActiveThick();
}

//* Front Position of Endcap Active Layer ---------------
G4double J4MUDParameterList::GetEndcapActiveFront( G4int layerID ) const
{
  return ( fIsFrontActive )
    ? GetEndcapFrontZ() + GetTotalAbsThick( layerID ) + (layerID-1)*GetEndcapActiveThick()
    : GetEndcapAbsFront( layerID ) + GetEndcapAbsThick( layerID );
}

//* Front Position of Endcap Absorber -------------------
G4double J4MUDParameterList::GetEndcapAbsFront( G4int layerID ) const
{
  return ( fIsFrontActive )
    ? GetEndcapActiveFront( layerID ) + GetEndcapActiveThick()
    : GetEndcapFrontZ() + GetTotalAbsThick( layerID ) + layerID*GetEndcapActiveThick();
}

//* Front Position of Front Endcap Active Layer ---------
G4double J4MUDParameterList::GetFrontEndcapActiveFront( G4int layerID ) const
{
  return GetFrontEndcapAbsFront( layerID ) + GetFrontEndcapAbsThick();
  //return ( fIsFrontActive )
  //  ? GetBlockFrontEndcapFrontZ() + layerID*(GetFrontEndcapAbsThick()+GetFrontEndcapActiveThick())
  //  : GetFrontEndcapAbsFront( layerID ) + GetFrontEndcapAbsThick();
}

//* Front Position of Front Endcap Absorber -------------
G4double J4MUDParameterList::GetFrontEndcapAbsFront( G4int layerID ) const
{
  return GetFrontEndcapFrontZ() + layerID*(GetFrontEndcapAbsThick()+GetFrontEndcapActiveThick());
  //return ( fIsFrontActive )
  //  ? GetFrontEndcapActiveFront( layerID ) + GetFrontEndcapActiveThick()
  //  : GetFrontEndcapFrontZ() + layerID*(GetFrontEndcapAbsThick()+GetFrontEndcapActiveThick());
}

//* Height of Endcap Active Layer -------------------------
G4double J4MUDParameterList::GetEndcapActiveHeight( G4int layerID ) const
{
  return ( fIsFrontActive )
    ? GetBarrelAbsFront( layerID )
    : GetBarrelAbsFront( layerID+1 );
}

//* Height of Endcap Abs Layer ----------------------------
G4double J4MUDParameterList::GetEndcapAbsHeight( G4int layerID ) const
{
  return ( fIsFrontActive )  
    ? GetBarrelActiveFront( layerID+1 )
    : GetBarrelActiveFront( layerID );
}

//* Half Length of Barrel Active Layer -------------------
G4double J4MUDParameterList::GetBarrelActiveHalfL( G4int layerID ) const
{
  return GetEndcapActiveFront( layerID );
}

//* Half Length of Barrel Absorber ------------------------
G4double J4MUDParameterList::GetBarrelAbsHalfL( G4int layerID ) const
{
  return GetEndcapAbsFront( layerID );
}

//* Z Position of Endcap Abs Layer ------------------------
G4double J4MUDParameterList::GetEndcapAbsZ( G4int layerID ) const
{
  return GetEndcapAbsFront( layerID ) + 0.5*GetEndcapAbsThick( layerID );
}

//* Z Position of Endcap Active Layer ---------------------
G4double J4MUDParameterList::GetEndcapActiveZ( G4int layerID ) const
{
  return GetEndcapActiveFront(layerID) + 0.5*GetEndcapActiveThick();
}

//* Height of Front Endcap Abs Layer ----------------------
G4double J4MUDParameterList::GetFrontEndcapAbsHeight( G4int /*layerID*/ ) const
{
  return GetFrontEndcapOuterR() * std::cos( 0.5*GetTrapDeltaPhi() );
}

//* Height of Front Endcap Active Layer -------------------
G4double J4MUDParameterList::GetFrontEndcapActiveHeight( G4int /*layerID*/ ) const
{
  return GetFrontEndcapOuterR() * std::cos( 0.5*GetTrapDeltaPhi() );
}

//* Z Position of Front Endcap Abs Layer ------------------
G4double J4MUDParameterList::GetFrontEndcapAbsZ( G4int layerID )  const
{
  return GetFrontEndcapAbsFront( layerID ) + 0.5*GetFrontEndcapAbsThick();
}

//* Z Position of Front Endcap Active Layer ---------------
G4double J4MUDParameterList::GetFrontEndcapActiveZ( G4int layerID ) const
{
  return GetFrontEndcapActiveFront( layerID ) + 0.5*GetFrontEndcapActiveThick();
}
