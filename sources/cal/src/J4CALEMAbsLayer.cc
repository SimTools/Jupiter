// $Id$
//*************************************************************************
//* --------------------
//* J4CALEMAbsLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALEMAbsLayer.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALEMAbsLayer::fFirstName= "EMAbsLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALEMAbsLayer::J4CALEMAbsLayer(J4VDetectorComponent *parent,
                                                G4int  nclones,
                                                G4int  nbrothers, 
                                                G4int  me,
                                                G4int  copyno )
: J4VCALSubLayer( fFirstName, parent, nclones, nbrothers, me, copyno )
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALEMAbsLayer::~J4CALEMAbsLayer()
{
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALEMAbsLayer::Cabling()
{
}

