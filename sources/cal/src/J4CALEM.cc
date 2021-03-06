// $Id$
//*************************************************************************
//* --------------------
//* J4CALEM
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALEM.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String  J4CALEM::fFirstName= "EM" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALEM::J4CALEM( J4VDetectorComponent *parent,
                                 G4int  nclones,
                                 G4int  nbrothers, 
                                 G4int  me,
                                 G4int  copyno ) 
: J4VCALBlock( fFirstName, parent, nclones, nbrothers, me, copyno  )
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALEM::~J4CALEM()
{
}

//===================================================================
//* Create ----------------------------------------------------------
J4VCALMiniCone *J4CALEM::Create( J4VDetectorComponent *parent,
                         			G4int  nclones,
                         			G4int  nbrothers,
                           			G4int  me,
                        			G4int  copyno )
{
  return new J4CALEMMiniCone( parent, nclones, nbrothers, me, copyno ); 
}
