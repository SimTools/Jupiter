// $Id$
//*************************************************************************
//* --------------------
//* J4CALEMMiniTower
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALEMMiniTower.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALEMMiniTower::fFirstName= "EMMiniTower" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALEMMiniTower::J4CALEMMiniTower( J4VDetectorComponent *parent,
                                               G4int  nclones,
                                               G4int  nbrothers, 
                                               G4int  me,
                                               G4int  copyno ) 
: J4VCALMiniTower( fFirstName, parent, nclones, nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALEMMiniTower::~J4CALEMMiniTower()
{
}

//===================================================================
//* Create ----------------------------------------------------------
J4VCALLayer *J4CALEMMiniTower::Create( J4VDetectorComponent *parent,
                                                      G4int  nclones,
                                                      G4int  nbrothers,
                                                      G4int  me,
                                                      G4int  copyno )
{
  return new J4CALEMLayer( parent, nclones, nbrothers, me, copyno ); 
}
