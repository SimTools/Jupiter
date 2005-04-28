// J4IRWMaskParameterList.cc
//*************************************************************************
//* --------------------
//* J4IRWMaskParameterList
//* --------------------
//* (Description)
//*     Class for describing his/her detector compornents.
//*
//* (Update Record)
//*     2002/11/19  T.Aso   Original version.
//*************************************************************************

#include "J4IRWMaskParameterList.hh"
#include "J4ParameterTable.hh"

J4IRWMaskParameterList *J4IRWMaskParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------

J4IRWMaskParameterList *J4IRWMaskParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4IRWMaskParameterList("IRWMask");
   }
   return fgInstance;
}

//* constructor -------------------------------------------------------

J4IRWMaskParameterList::J4IRWMaskParameterList(const G4String& name)
  : J4VParameterList(name)
{
  //  fList = list;
  fbpList = J4IRBPParameterList::GetInstance();
  fch2List = J4IRCH2MaskParameterList::GetInstance();
  fwsiList = J4IRWSiCALParameterList::GetInstance();
  SetParameters();
  SetMaterials();
  SetVisAttributes();
  SetColors();
}
//=====================================================================
//* destructor -------------------------------------------------------

J4IRWMaskParameterList::~J4IRWMaskParameterList()
{
  //  delete  fbpList;
  //  delete  fch2List;
  //  delete  fwsiList;
  //  delete  fList;
  delete  fWMaskColor;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4IRWMaskParameterList::SetMaterials()
{
//  SetWMaskMaterial("Tungsten");
  SetWMaskMaterial(J4ParameterTable::GetValue("J4IR.WMask.Material","Tungsten"));

}

//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRWMaskParameterList::SetParameters()
{
  SetDefaults();
  BuildParameters();
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRWMaskParameterList::SetDefaults()
{

// Shape of WMask
  SetMargin(0.05*cm);
  SetWMask1Thick(4.*cm);
  SetMargin(J4ParameterTable::GetValue("J4IR.WMask.Margin",0.05)*cm);
  SetWMask1Thick(J4ParameterTable::GetValue("J4IR.WMask.Thickness",4.0)*cm);

}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRWMaskParameterList::BuildParameters()
{
}
//=====================================================================
//* SetVtsAttributes ------------------------------------------------------
void J4IRWMaskParameterList::SetVisAttributes()
{
//  SetWMaskVisAtt(TRUE);
  SetWMaskVisAtt(J4ParameterTable::GetValue("J4IR.VisAtt.WMask",true));

}
//=====================================================================
//* SetColors ---------------------------------------------------------
void J4IRWMaskParameterList::SetColors()
{
//   SetWMaskColor(new G4Color(1.0,1.0,1.0));  
   std::vector<double> col=J4ParameterTable::GetDValue("J4IR.WMask.Color","1.0 1.0 1.0 1.0",4);
   SetWMaskColor(new G4Color(col[0], col[1], col[2], col[3]));  

}


