// $Id$
//*************************************************************************
//* --------------------
//* J4CALHDActiveLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALHDActiveLayer.hh"
#include "J4VCALSubLayerSD.hh"
#include "J4CALHDActiveLayerSD.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALHDActiveLayer::fFirstName= "HDActiveLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALHDActiveLayer::J4CALHDActiveLayer(J4VDetectorComponent *parent,
                                                      G4int  nclones,
                                                      G4int  nbrothers, 
                                                      G4int  me,
                                                      G4int  copyno )
: J4VCALSubLayer( fFirstName, parent, nclones, nbrothers, me, copyno )
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALHDActiveLayer::~J4CALHDActiveLayer()
{
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALHDActiveLayer::Cabling()
{
  if( !GetSD() ) {
    J4CALHDActiveLayerSD* sd = new J4CALHDActiveLayerSD(this);
    Register(sd);
    SetSD(sd);
  }
}

