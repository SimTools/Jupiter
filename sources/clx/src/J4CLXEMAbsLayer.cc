// $Id$
//*************************************************************************
//* --------------------
//* J4CLXEMAbsLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2006/05/01  H.Ono       Derived from J4CALEMAbsLayer
//*************************************************************************

#include "J4VCLXTrapStrip.hh"
#include "J4VCLXLayer.hh"
#include "J4CLXEMAbsLayer.hh"
#include "J4VCLXSubLayer.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXEMAbsLayer::fgFirstName= "EMAbsLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXEMAbsLayer::J4CLXEMAbsLayer( G4bool isBarrel,
				  J4VDetectorComponent *parent,
				  G4int  nclones,
				  G4int  nbrothers,
				  G4int  me,
				  G4int  copyno )
  : J4VCLXSubLayer( isBarrel, fgFirstName, parent, nclones, nbrothers, me, copyno )
{ 
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CLXEMAbsLayer::~J4CLXEMAbsLayer()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXTrapStrip *J4CLXEMAbsLayer::Create( J4VDetectorComponent* /*parent*/,
                                          G4int /*nclones*/,
                                          G4int /*nbrothers*/,
                                          G4int /*me*/,
                                          G4int /*copyno*/ )
{
  return 0;
}
