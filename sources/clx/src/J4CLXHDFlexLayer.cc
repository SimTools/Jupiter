// $Id$
//*************************************************************************
//* --------------------
//* J4CLXHDFlexLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2006/05/01  H.Ono       Derived from J4CALHDAbsLayer
//*************************************************************************

#include "J4CLXHDFlexLayer.hh"
#include "J4VCLXTrapStrip.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXHDFlexLayer::fgFirstName= "HDFlexLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXHDFlexLayer::J4CLXHDFlexLayer( G4bool isBarrel, 
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

J4CLXHDFlexLayer::~J4CLXHDFlexLayer()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXTrapStrip *J4CLXHDFlexLayer::Create( J4VDetectorComponent* ,
				           G4int ,
				           G4int ,
				           G4int ,
				           G4int )
{
  return 0;
}
