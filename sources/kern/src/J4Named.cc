// $Id$
//*************************************************************************
//* --------------------
//* J4Named
//* --------------------
//* (Description)
//*    
//* (Update Record)
//*	2002/12/20  K.Hoshina       Original version.
//*************************************************************************

#include "J4Named.hh" 

//=====================================================================
//---------------------
// class description
//---------------------


J4Named::J4Named()
        :fName("unnamed")
{
}
J4Named::J4Named(const G4String &name)
        :fName(name)
{
}
