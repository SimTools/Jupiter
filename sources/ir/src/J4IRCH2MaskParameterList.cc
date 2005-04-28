// J4IRCH2MaskParameterList.cc
//*************************************************************************
//* --------------------
//* J4IRCH2MaskParameterList
//* --------------------
//* (Description)
//*     Class for describing his/her detector compornents.
//*
//* (Update Record)
//*     2002/11/19  T.Aso   Original version.
//*************************************************************************

#include "J4IRCH2MaskParameterList.hh"
#include "J4ParameterTable.hh"

J4IRCH2MaskParameterList* J4IRCH2MaskParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4IRCH2MaskParameterList* J4IRCH2MaskParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4IRCH2MaskParameterList("IRCH2Mask");
   }
   return fgInstance;
}
//* constructor -------------------------------------------------------

J4IRCH2MaskParameterList::J4IRCH2MaskParameterList(const G4String& name)
  : J4VParameterList(name)
{
  fgInstance=this;
  //  fList = list;
  fbpList = J4IRBPParameterList::GetInstance();
  fqc1List = J4IRQC1ParameterList::GetInstance();
  SetParameters();
  SetMaterials();
  SetVisAttributes();
  SetColors();
}
//=====================================================================
//* destructor -------------------------------------------------------

J4IRCH2MaskParameterList::~J4IRCH2MaskParameterList()
{
  //  delete  fList;
  //  delete  fbpList;
  //  delete  fqc1List;
  delete  fCH2MaskColor;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4IRCH2MaskParameterList::SetMaterials()
{
  SetCH2MaskMaterial(J4ParameterTable::GetValue("J4IR.CH2Mask.Material","Polyethylene"));
}

//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRCH2MaskParameterList::SetParameters()
{
  SetDefaults();
  BuildParameters();
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRCH2MaskParameterList::SetDefaults()
{
//  SetDrMargin(0.5*mm);
//  SetDzMargin(1.0*cm);
  SetDzMargin(J4ParameterTable::GetValue("J4IR.CH2Mask.DzMargin",1.0)*cm);  
  SetDrMargin(J4ParameterTable::GetValue("J4IR.CH2Mask.DrMargin",0.05)*cm);  

// Master volume (Tube) for CH2MASK
//  SetCH2MaskZLength(15.*cm);
  SetCH2MaskZLength(J4ParameterTable::GetValue("J4IR.CH2Mask.ZLength",15.0)*cm);  
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRCH2MaskParameterList::BuildParameters()
{
}
//=====================================================================
//* SetVtsAttributes ------------------------------------------------------
void J4IRCH2MaskParameterList::SetVisAttributes()
{
//  SetCH2MaskVisAtt(TRUE);
  SetCH2MaskVisAtt(J4ParameterTable::GetValue("J4IR.VisAtt.CH2Mask",true));

}
//=====================================================================
//* SetColors ---------------------------------------------------------
void J4IRCH2MaskParameterList::SetColors()
{
//   SetCH2MaskColor(new G4Color(0.0,0.0,1.));  // blue
   std::vector<double> col=J4ParameterTable::GetDValue("J4IR.Color.CH2Mask","0.0 0.0 1.0 1.0",4);
   SetCH2MaskColor(new G4Color(col[0], col[1], col[2], col[3]));  // blue

}


