// $Id$
//*************************************************************************
//* --------------------
//* J4CLXHDActiveLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CLXHDActiveLayer.hh"
#include "J4CLXHDBoard.hh"
#include "G4Trap.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXHDActiveLayer::fFirstName= "HDActiveLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXHDActiveLayer::J4CLXHDActiveLayer(J4VDetectorComponent *parent,
                                                      G4int  nclones,
                                                      G4int  nbrothers, 
                                                      G4int  me,
                                                      G4int  copyno )
: J4VCLXSubLayer( fFirstName, parent, nclones, nbrothers, me, copyno )
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CLXHDActiveLayer::~J4CLXHDActiveLayer()
{
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CLXHDActiveLayer::Cabling()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXBoard *J4CLXHDActiveLayer::Create(J4VDetectorComponent *parent,
				 G4int nclones,
				 G4int nbrothers,
				 G4int me,
				 G4int copyno)
{
    return new J4CLXHDBoard(parent, nclones, nbrothers, me, copyno);
}
