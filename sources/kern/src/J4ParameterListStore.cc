// $Id$
//*************************************************************************
//* --------------------
//* J4ParameterListStore
//* --------------------
//* (Description)
//*
//* (Update Record)
//*	2002/12/20  K.Hoshina	Original version.
//*************************************************************************

#include "G4ExceptionHandler.hh"
#include "J4ParameterListStore.hh"
 
#define __NMAXPARAMLISTS__  1000

J4ParameterListStore* J4ParameterListStore::fgParameterListStore = 0;
J4ObjArray J4ParameterListStore::fgParameterLists(__NMAXPARAMLISTS__);

//=====================================================================
//* constructor -------------------------------------------------------

J4ParameterListStore::J4ParameterListStore()
{

   if (fgParameterListStore) {
      G4Exception("J4ParameterListStore constructed twice."); 
   }  
   fgParameterListStore = this;

}

//=====================================================================
//* destructor -------------------------------------------------------

J4ParameterListStore::~J4ParameterListStore()
{
}


//=====================================================================
//* PrintAllParameters ------------------------------------------------

void J4ParameterListStore::PrintAllParameters()
{

}


