// $Id$
//*************************************************************************
//* --------------------
//* J4CALEMActiveLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALEMActiveLayer.hh"
#include "J4VCALSubLayerSD.hh"
#include "J4CALEMActiveLayerSD.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALEMActiveLayer::fFirstName= "EMActiveLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALEMActiveLayer::J4CALEMActiveLayer(J4VDetectorComponent *parent,
                                                      G4int  nclones,
                                                      G4int  nbrothers, 
                                                      G4int  me,
                                                      G4int  copyno )
: J4VCALSubLayer( fFirstName, parent, nclones, nbrothers, me, copyno )
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALEMActiveLayer::~J4CALEMActiveLayer()
{
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALEMActiveLayer::Cabling()
{
  if( !GetSD() ) {
    J4CALEMActiveLayerSD* sd = new J4CALEMActiveLayerSD(this);
    Register(sd);
    SetSD(sd);
  }
}
