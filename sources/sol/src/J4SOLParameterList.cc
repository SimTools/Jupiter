// $Id$
//*************************************************************************
//* --------------------
//* J4SOLParameterList
//* --------------------
//* (Description)
//* 	Parameter list for Intermediate Tracker.
//*
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4SOLParameterList.hh"

J4SOLParameterList * J4SOLParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4SOLParameterList* J4SOLParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4SOLParameterList();
   }
   return fgInstance;
}

//=====================================================================
//* destructor -------------------------------------------------------

J4SOLParameterList::~J4SOLParameterList()
{
   fgInstance = 0;
}


