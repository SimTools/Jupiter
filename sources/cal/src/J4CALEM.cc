// $Id$
//*************************************************************************
//* --------------------
//* J4CALEM
//* --------------------
//* (Description)
//*    Class to represent EM block of CAL.
//*     
//* (Update Record)
//*    2000/12/08  K.Hoshina	Original version.
//*    2004/11/14  K.Fujii	Most of the function is now in its
//*				base class.
//*************************************************************************

#include "J4CALEM.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALEM::fFirstName = "EM";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALEM::J4CALEM(J4VDetectorComponent *parent,
                                G4int  nclones,
                                G4int  nbrothers, 
                                G4int  me,
                                G4int  copyno ) 
       : J4CALBlock(fFirstName, true, parent, nclones, nbrothers, me, copyno)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALEM::~J4CALEM()
{
}
