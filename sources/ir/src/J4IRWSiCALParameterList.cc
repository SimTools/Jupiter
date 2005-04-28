// J4IRWSiCALParameterList.cc
//*************************************************************************
//* --------------------
//* J4IRWSiCALParameterList
//* --------------------
//* (Description)
//*     Class for describing his/her detector compornents.
//*
//* (Update Record)
//*     2002/11/19  T.Aso   Original version.
//*************************************************************************

#include "J4IRWSiCALParameterList.hh"
#include "J4ParameterTable.hh"

J4IRWSiCALParameterList* J4IRWSiCALParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4IRWSiCALParameterList* J4IRWSiCALParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4IRWSiCALParameterList("IRWSiCAL");
   }
   return fgInstance;
}
//* constructor -------------------------------------------------------

J4IRWSiCALParameterList::J4IRWSiCALParameterList(const G4String& name)
  : J4VParameterList(name)
{
  //  fList = list;
  fbpList = J4IRBPParameterList::GetInstance();
  SetParameters();
  SetMaterials();
  SetVisAttributes();
  SetColors();
}
//=====================================================================
//* destructor -------------------------------------------------------

J4IRWSiCALParameterList::~J4IRWSiCALParameterList()
{
  // delete  fbpList;
  // delete  fList;
  delete  fWSiCALColor;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4IRWSiCALParameterList::SetMaterials()
{
//  SetWSiCALMaterial("Tungsten");
  SetWSiCALMaterial(J4ParameterTable::GetValue("J4IR.WSiCal.Material","Tungsten"));

}

//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRWSiCALParameterList::SetParameters()
{
  SetDefaults();
  BuildParameters();
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRWSiCALParameterList::SetDefaults()
{

// Shape of WSiCAL
  SetWSiCALNLayer(J4ParameterTable::GetValue("J4IR.WSiCal.NLayers",128));
  SetWSiCAL2ZLength(J4ParameterTable::GetValue("J4IR.WSiCal.ZLength",64.0)*cm);
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRWSiCALParameterList::BuildParameters()
{
}
//=====================================================================
//* SetVtsAttributes ------------------------------------------------------
void J4IRWSiCALParameterList::SetVisAttributes()
{
//  SetWSiCALVisAtt(TRUE);
  SetWSiCALVisAtt(J4ParameterTable::GetValue("J4IR.VisAtt.WSiCal",true));

}
//=====================================================================
//* SetColors ---------------------------------------------------------
void J4IRWSiCALParameterList::SetColors()
{
//   SetWSiCALColor(new G4Color(1.0,0.0,1.));  
   std::vector<double> col=J4ParameterTable::GetDValue("J4IR.WSiCal.Color","1.0 0.0 1.0 1.0",4);
   SetWSiCALColor(new G4Color(col[0], col[1], col[2], col[3]));  

}


