// $Id$
//*************************************************************************
//* --------------------
//* J4CLXEMActiveLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CLXEMActiveLayer.hh"
#include "J4CLXEMBoard.hh"
#include "G4Trap.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXEMActiveLayer::fFirstName= "EMActiveLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXEMActiveLayer::J4CLXEMActiveLayer(J4VDetectorComponent *parent,
                                                      G4int  nclones,
                                                      G4int  nbrothers,
                                                      G4int  me,
                                                      G4int  copyno )
: J4VCLXSubLayer( fFirstName, parent, nclones, nbrothers, me, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CLXEMActiveLayer::~J4CLXEMActiveLayer()
{
}

//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4CLXEMActiveLayer::Cabling()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXBoard *J4CLXEMActiveLayer::Create(J4VDetectorComponent *parent,
				 G4int nclones,
				 G4int nbrothers,
				 G4int me,
				 G4int copyno)
{
    return new J4CLXEMBoard(parent, nclones, nbrothers, me, copyno);
}
