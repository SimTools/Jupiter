// $Id$
//*************************************************************************
//* --------------------
//* J4CLXHDAbsLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CLXHDAbsLayer.hh"
#include "J4VCLXTrapStrip.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXHDAbsLayer::fgFirstName= "HDAbsLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXHDAbsLayer::J4CLXHDAbsLayer( G4bool isBarrel, 
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

J4CLXHDAbsLayer::~J4CLXHDAbsLayer()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXTrapStrip *J4CLXHDAbsLayer::Create( J4VDetectorComponent* ,
                                          G4int ,
                                          G4int ,
                                          G4int ,
                                          G4int )
{
  return 0;
}
