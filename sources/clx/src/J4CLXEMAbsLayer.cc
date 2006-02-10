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
//*************************************************************************

#include "J4CLXEMAbsLayer.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXEMAbsLayer::fFirstName= "EMAbsLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXEMAbsLayer::J4CLXEMAbsLayer(J4VDetectorComponent *parent,
                                                G4int  nclones,
                                                G4int  nbrothers,
                                                G4int  me,
                                                G4int  copyno )
: J4VCLXSubLayer( fFirstName, parent, nclones, nbrothers, me, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CLXEMAbsLayer::~J4CLXEMAbsLayer()
{
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CLXEMAbsLayer::Cabling()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXBoard *J4CLXEMAbsLayer::Create(J4VDetectorComponent* ,
				 G4int ,
				 G4int ,
				 G4int ,
				 G4int )
{
    return NULL;
}
