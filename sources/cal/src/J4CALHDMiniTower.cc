// $Id$
//*************************************************************************
//* --------------------
//* J4CALHDMiniTower
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALHDMiniTower.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALHDMiniTower::fFirstName= "HDMiniTower" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALHDMiniTower::J4CALHDMiniTower( J4VDetectorComponent *parent,
                                               G4int  nclones,
                                               G4int  nbrothers, 
                                               G4int  me,
                                               G4int  copyno ) 
: J4VCALMiniTower ( fFirstName, parent, nclones, nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALHDMiniTower::~J4CALHDMiniTower()
{
}

//===================================================================
//* Create ----------------------------------------------------------
J4VCALLayer *J4CALHDMiniTower::Create( J4VDetectorComponent *parent,
                                                      G4int  nclones,
                                                      G4int  nbrothers,
                                                      G4int  me,
                                                      G4int  copyno )
{
  return new J4CALHDLayer( parent, nclones, nbrothers, me, copyno ); 
}
