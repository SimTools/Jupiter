// $Id$
//*************************************************************************
//* --------------------
//* J4CALHDMiniCone
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALHDMiniCone.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALHDMiniCone::fFirstName= "HDMiniCone" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALHDMiniCone::J4CALHDMiniCone( J4VDetectorComponent *parent,
                                                 G4int  nclones,
                                                 G4int  nbrothers, 
                                                 G4int  me,
                                                 G4int  copyno )
: J4VCALMiniCone( fFirstName, parent, nclones, nbrothers, me, copyno )
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALHDMiniCone::~J4CALHDMiniCone()
{
}

//===================================================================
//* Create ----------------------------------------------------------
J4VCALMiniTower *J4CALHDMiniCone::Create( J4VDetectorComponent *parent,
                                                         G4int  nclones,
                                                         G4int  nbrothers,
                                                         G4int  me,
                                                         G4int  copyno )
{
  return new J4CALHDMiniTower( parent, nclones, nbrothers, me, copyno ); 
}
