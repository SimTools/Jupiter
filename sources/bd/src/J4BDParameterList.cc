// $Id$
//*************************************************************************
//* --------------------
//* J4BDParameterList
//* --------------------
//* (Description)
//*
//* (Update Record)
//*	2003/02/28  K.Hoshina	Original version.
//*************************************************************************

#include "J4BDParameterList.hh"
#include "J4ParameterList.hh"
#include "J4IRParameterList.hh"
 
J4BDParameterList * J4BDParameterList::fInstance = 0;

//=====================================================================
//* constructor -------------------------------------------------------

J4BDParameterList::J4BDParameterList()
{
   fInstance = this;

   J4ParameterList   *paramlist = J4ParameterList::GetInstance();    
   J4IRParameterList *irlist    = J4IRParameterList::GetInstance();    

   fMaterial       = "Air";
   fVisAtt         = FALSE;
   fColor          = new G4Color(0.5, 0.5, 0.5);
   fOuterHalfX     = paramlist->GetEXPHallHalfX();
   fOuterHalfY     = paramlist->GetEXPHallHalfY();
   fOuterHalfZ     = paramlist->GetEXPHallHalfZ();
   fInnerHalfX     = irlist->GetIRBoxHalfX(); 
   fInnerHalfY     = irlist->GetIRBoxHalfY(); 
   fInnerHalfZ     = irlist->GetZMax(); 
 
}



