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
 
J4BDParameterList* J4BDParameterList::fgInstance = 0;

//=====================================================================
//* public get function -----------------------------------------------

J4BDParameterList* J4BDParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4BDParameterList("BD");
   }
   return fgInstance;
}

//=====================================================================
//* protected constructor ---------------------------------------------

J4BDParameterList::J4BDParameterList(const G4String & /* name */)
{
   J4ParameterList   *paramlist = J4ParameterList::GetInstance();    
   J4IRParameterList *irlist    = J4IRParameterList::GetInstance();    

   fBDMaterial       = "Air";
   fBDVisAtt         = FALSE;
   fBDOuterHalfX     = paramlist->GetEXPHallHalfX();
   fBDOuterHalfY     = paramlist->GetEXPHallHalfY();
   fBDOuterHalfZ     = paramlist->GetEXPHallHalfZ();

   fBDInnerHalfX     = irlist->GetDxyzIRBox().x();   
   fBDInnerHalfY     = irlist->GetDxyzIRBox().y(); 
   fBDInnerHalfZ     = irlist->GetIRZMax(); 

   SetBDColor(G4Color(0.5, 0.5, 0.5));
 
}

//=====================================================================
//* destructor --------------------------------------------------------
J4BDParameterList::~J4BDParameterList()
{
   fgInstance = 0;
}


