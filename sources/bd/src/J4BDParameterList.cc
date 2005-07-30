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
#include "J4ParameterTable.hh"
//#include "J4IRParameterList.hh"
 
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
//   J4IRParameterList *irlist    = J4IRParameterList::GetInstance();    

   fBDMaterial       = J4ParameterTable::GetValue("J4BD.Material","vacuum");
   fBDVisAtt         = J4ParameterTable::GetValue("J4BD.VisAtt",false);

   fBDOuterHalfX     = paramlist->GetEXPHallHalfX();
   fBDOuterHalfY     = paramlist->GetEXPHallHalfY();
   fBDOuterHalfZ     = paramlist->GetEXPHallHalfZ();

   fBDInnerHalfX = fBDOuterHalfX;
   fBDInnerHalfY = fBDOuterHalfY;
   fBDInnerHalfZ = paramlist->GetIRBoxEndZ();

    std::vector<double> col=J4ParameterTable::GetDValue("J4BD.Color","0.5 0.5 0.5 0.0",4);
    G4Color icolor(col[0], col[1], col[2], col[3]);  // cyan
    SetBDColor(icolor);
 

}

//=====================================================================
//* destructor --------------------------------------------------------
J4BDParameterList::~J4BDParameterList()
{
   fgInstance = 0;
}


