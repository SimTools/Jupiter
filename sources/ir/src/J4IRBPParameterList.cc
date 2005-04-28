// J4IRBPParameterList.cc
//*************************************************************************
//* --------------------
//* J4IRBPParameterList
//* --------------------
//* (Description)
//*     Class for describing his/her detector compornents.
//*
//* (Update Record)
//*     2002/11/19  T.Aso   Original version.
//*************************************************************************

#include "J4IRBPParameterList.hh"
#include "J4ParameterTable.hh"

J4IRBPParameterList* J4IRBPParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------

J4IRBPParameterList* J4IRBPParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4IRBPParameterList("IRBP");
   }
   return fgInstance;
}
//* constructor -------------------------------------------------------

J4IRBPParameterList::J4IRBPParameterList(const G4String& name )
  : J4VParameterList(name)
{
  fgInstance = this;
  //  fIRList = list;
  SetParameters();
  SetMaterials();
  SetVisAttributes();
  SetColors();
}
//=====================================================================
//* destructor -------------------------------------------------------

J4IRBPParameterList::~J4IRBPParameterList()
{
  //  delete  fIRList;
  delete  fBPColor;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4IRBPParameterList::SetMaterials()
{
  SetBPIPMaterial(J4ParameterTable::GetValue("J4IR.BeamPipeIP.Material","Beryllium"));
  SetBPSTDMaterial(J4ParameterTable::GetValue("J4IR.BeamPipeSTD.Material","Aluminum"));
}

//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRBPParameterList::SetParameters()
{
  SetDefaults();
  BuildParameters();
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRBPParameterList::SetDefaults()
{
  // Margin for avoiding volume intersection.
  SetMargin(0.5*cm);

  // Be BP Pipe 
  //SetBPRadiusSmall(1.8*cm);   // moved to IRParameterList
  //SetBPBeThick(0.05*cm);      // moved to IRParameterList
  SetBPIPZPosition(0.*cm);
#ifdef __GLD_V1__
  SetBPIPZLength(14*cm);
#else
  SetBPIPZLength(10*cm);
#endif
  SetBPIPZLength(J4ParameterTable::GetValue("J4IR.BeamPipeIP.ZLength",14.0)*cm);

  // Al BP Pipe
//  SetBPRadiusLarge(7.3*cm);
//  SetBPAlThick(0.2*cm);
  SetBPRadiusLarge(J4ParameterTable::GetValue("J4IR.BeamPipe.Pipe.Radius",7.3)*cm);
  SetBPAlThick(J4ParameterTable::GetValue("J4IR.BeamPipe.Al.Thickness",0.2)*cm);

  // Al BP End
//  SetBPENDRadius(3.5*cm);
//  SetBPENDZLength(24.8*cm);
  SetBPENDRadius(J4ParameterTable::GetValue("J4IR.BeamPipe.End.Radius",3.5)*cm);
  SetBPENDZLength(J4ParameterTable::GetValue("J4IR.BeamPipe.End.ZLength",24.8)*cm);

  // Drum
//  SetBPDrumcapZLength(0.2*cm);
//  SetBPDrumZPosition(49.624*cm);
  SetBPDrumcapZLength(J4ParameterTable::GetValue("J4IR.BeamPipe.Drumcap.ZLength",0.2)*cm);
  SetBPDrumZPosition(J4ParameterTable::GetValue("J4IR.BeamPipe.Drum.ZPosition",49.624)*cm);


}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRBPParameterList::BuildParameters()
{
}
//=====================================================================
//* SetVtsAttributes ------------------------------------------------------
void J4IRBPParameterList::SetVisAttributes()
{
//  SetBPVisAtt(TRUE);
  SetBPVisAtt(J4ParameterTable::GetValue("J4IR.VisAtt.BeamPipe",true));

}
//=====================================================================
//* SetColors ---------------------------------------------------------
void J4IRBPParameterList::SetColors()
{
//   SetBPColor(new G4Color(0.0,0.5,0.5));  // cyan
  std::vector<double> col=J4ParameterTable::GetDValue("J4IR.BeamPipe.Color","0.0 0.5 0.5 1.0",4);
  SetBPColor(new G4Color(col[0], col[1], col[2], col[3]));  // cyan

}


