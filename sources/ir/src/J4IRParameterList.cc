// $Id$
//*************************************************************************
//* --------------------
//* J4IRParameterList
//* --------------------
//* (Description)
//*
//* (Update Record)
//*	2003/02/28  K.Hoshina	Original version.
//*************************************************************************

#include "J4IRParameterList.hh"
#include "J4ParameterList.hh"
 
J4IRParameterList * J4IRParameterList::fInstance = 0;

//=====================================================================
//* constructor -------------------------------------------------------

J4IRParameterList::J4IRParameterList()
{
   fInstance = this;

   J4ParameterList *paramlist = J4ParameterList::GetInstance();    

   fMaterial       = "Air";
   fVisAtt         = FALSE;
   fColor          = new G4Color(0.5, 0.5, 0.5);
   fZMax           = 10000*cm;
   fZMid           = 40*cm;
   fThetaMax       = 200*mrad;
   fIRBoxHalfX     = paramlist->GetEXPHallHalfX() - 1.0*cm;
   fIRBoxHalfY     = paramlist->GetEXPHallHalfY() - 1.0*cm;
   fSuppTubInnerR  = 40*cm;
   fBeampipeOuterR = 2.0*cm;
 
}



