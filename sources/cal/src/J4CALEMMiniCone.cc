// $Id$
//*************************************************************************
//* --------------------
//* J4CALEMMiniCone
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALEMMiniCone.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALEMMiniCone::fFirstName= "EMMiniCone" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALEMMiniCone::J4CALEMMiniCone( J4VDetectorComponent *parent,
                                                 G4int  nclones,
                                                 G4int  nbrothers, 
                                                 G4int  me,
                                                 G4int  copyno )
: J4VCALMiniCone( fFirstName, parent, nclones, nbrothers, me, copyno )
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALEMMiniCone::~J4CALEMMiniCone()
{
}

//===================================================================
//* Create ----------------------------------------------------------
J4VCALMiniTower *J4CALEMMiniCone::Create( J4VDetectorComponent *parent,
                                                         G4int  nclones,
                                                         G4int  nbrothers,
                                                         G4int  me,
                                                         G4int  copyno )
{
  return new J4CALEMMiniTower( parent, nclones, nbrothers, me, copyno ); 
}

