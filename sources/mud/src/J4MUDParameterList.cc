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
   fMUDMaterial           = "vacuum";
   fBarrelMaterial        = "Iron";
   fEndcapMaterial        = "Iron" ;
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4MUDParameterList::SetParameters()
{
  // MUD
  fBarrelInnerR    = 450.0*cm;
  fBarrelOuterR    = 700.0*cm;
  fEndcapFrontZ    = 430.0*cm;
  fEndcapInnerR    = 40.0*cm;
  fEndcapThickness = 415.0*cm;
  fDeltaPhi        = 360.*deg;
  fNBarrelLayers   = 5;
  fNEndcapLayers   = 8;
  fBarrelHalfZ     = fEndcapFrontZ + fEndcapThickness;
  fBarrelLayer     = ( fBarrelOuterR - fBarrelInnerR ) / fNBarrelLayers;
  fEndcapLayer     = fEndcapThickness / fNEndcapLayers;
}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4MUDParameterList::SetVisAttributes()
{
   fMUDVisAtt        = TRUE;
   fBarrelVisAtt     = TRUE;
   fEndcapVisAtt     = TRUE;
}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4MUDParameterList::SetColors()
{
   SetMUDColor( G4Color( 0., 1., 0. ) );
   SetBarrelColor( G4Color( 0., 1., 0. ) );
   SetEndcapColor( G4Color( 0., 1., 0. ) );
}
