// $Id$
//*************************************************************************
//* --------------------
//* J4CALHDAbsLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALHDAbsLayer.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALHDAbsLayer::fFirstName= "HDAbsLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALHDAbsLayer::J4CALHDAbsLayer(J4VDetectorComponent *parent,
                                                G4int  nclones,
                                                G4int  nbrothers, 
                                                G4int  me,
                                                G4int  copyno )
: J4VCALSubLayer( fFirstName, parent, nclones, nbrothers, me, copyno )
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALHDAbsLayer::~J4CALHDAbsLayer()
{
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALHDAbsLayer::Cabling()
{
}

