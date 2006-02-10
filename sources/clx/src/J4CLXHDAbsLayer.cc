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

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXHDAbsLayer::fFirstName= "HDAbsLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXHDAbsLayer::J4CLXHDAbsLayer(J4VDetectorComponent *parent,
                                                G4int  nclones,
                                                G4int  nbrothers,
                                                G4int  me,
                                                G4int  copyno )
: J4VCLXSubLayer( fFirstName, parent, nclones, nbrothers, me, copyno )
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CLXHDAbsLayer::~J4CLXHDAbsLayer()
{
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CLXHDAbsLayer::Cabling()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXBoard *J4CLXHDAbsLayer::Create(J4VDetectorComponent* ,
				 G4int ,
				 G4int ,
				 G4int ,
				 G4int )
{
    return NULL;
}
