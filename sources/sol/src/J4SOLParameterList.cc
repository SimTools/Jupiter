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
#include "J4ParameterTable.hh"
#include <vector>

J4SOLParameterList * J4SOLParameterList::fgInstance = 0;

//=====================================================================
J4SOLParameterList::J4SOLParameterList( G4double /*ri*/, G4double /*ro*/, G4double /*len*/ )
  : J4VParameterList("SOL")
{
   fSOLMaterial = J4ParameterTable::GetValue("J4SOL.Material","Air");
   fSOLVisAtt   = J4ParameterTable::GetValue("J4SOL.VisAtt",true);
   std::vector<double> col=J4ParameterTable::GetDValue("J4SOL.Color","0.7 0.5 0.5 1.0",4);
   fSOLColor=G4Color(col[0], col[1], col[2], col[3]);
//   fFieldR = J4ParameterTable::GetValue("J4SOL.FieldR",157.0)*cm;
   fBField = J4ParameterTable::GetValue("J4SOL.BField",3.0)*tesla;
   
   fBFieldType = J4ParameterTable::GetValue("J4SOL.BFieldType",0);
   fBFieldMapFileName = J4ParameterTable::GetValue("J4SOL.BFieldMapFileName","map.file");
   fDIDFieldFactor = J4ParameterTable::GetValue("J4SOL.DIDFieldFactor",1.0);
   
   // Coil
   fSOLCoilInnerR   = J4ParameterTable::GetValue("J4SOL.Coil.InnerR",397.5)*cm;
   fSOLCoilOuterR   = J4ParameterTable::GetValue("J4SOL.Coil.OuterR",402.5)*cm;
   fSOLCoilHalfZ    = J4ParameterTable::GetValue("J4SOL.Coil.HalfZ",430.0)*cm;
   fSOLCoilMaterial = J4ParameterTable::GetValue("J4SOL.Coil.Material","Copper");
   fSOLCoilVisAtt   = J4ParameterTable::GetValue("J4SOL.Coil.VisAtt",true);
   std::vector<double> coilcol=J4ParameterTable::GetDValue("J4SOL.Coil.Color","0.0 1.0 0.0 1.0",4);
   fSOLCoilColor=G4Color(coilcol[0], coilcol[1], coilcol[2], coilcol[3]);

}

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
