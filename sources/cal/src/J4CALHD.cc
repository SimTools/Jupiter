// $Id$
//*************************************************************************
//* --------------------
//* J4CALHD
//* --------------------
//* (Description)
//*    Class to represent HD block of CAL.
//*     
//* (Update Record)
//*    2000/12/08  K.Hoshina	Original version.
//*    2004/11/14  K.Fujii	Most of the function is now in its
//*				base class.
//*************************************************************************

#include "J4CALHD.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALHD::fFirstName = "HD";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALHD::J4CALHD(J4VDetectorComponent *parent,
                                G4int  nclones,
                                G4int  nbrothers, 
                                G4int  me,
                                G4int  copyno ) 
       : J4CALBlock(fFirstName, false, parent, nclones, nbrothers, me, copyno)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALHD::~J4CALHD()
{
}
