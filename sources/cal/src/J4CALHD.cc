// $Id$
//*************************************************************************
//* --------------------
//* J4CALHD
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALHD.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String  J4CALHD::fFirstName= "HD" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALHD::J4CALHD( J4VDetectorComponent *parent,
                                 G4int  nclones,
                                 G4int  nbrothers, 
                                 G4int  me,
                                 G4int  copyno ) 
: J4VCALBlock( fFirstName, parent, nclones, nbrothers, me, copyno  )

{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALHD::~J4CALHD()
{
}

//===================================================================
//* Create ----------------------------------------------------------
J4VCALMiniCone *J4CALHD::Create( J4VDetectorComponent *parent,
                         			G4int  nclones,
                         			G4int  nbrothers,
                           			G4int  me,
                        			G4int  copyno )
{
  return new J4CALHDMiniCone( parent, nclones, nbrothers, me, copyno ); 
}
