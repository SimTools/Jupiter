// J4IRQC1ParameterList.cc
//*************************************************************************
//* --------------------
//* J4IRQC1ParameterList
//* --------------------
//* (Description)
//*     Class for describing his/her detector compornents.
//*
//* (Update Record)
//*     2002/11/19  T.Aso   Original version.
//*************************************************************************

#include "J4IRQC1ParameterList.hh"

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC1ParameterList::J4IRQC1ParameterList(J4IRParameterList* list)
{
  fList = list;
  SetParameters();
  SetMaterials();
  SetVisAttributes();
  SetColors();
}
//=====================================================================
//* destructor -------------------------------------------------------

J4IRQC1ParameterList::~J4IRQC1ParameterList()
{
  delete  fList;
  delete  fQC1Color;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4IRQC1ParameterList::SetMaterials()
{
  SetQC1Material("vacuum");
  SetQC1SUSMaterial("Iron");
  SetQC1CollarMaterial("Iron");
  SetQC1CoilMaterial("Cupper");
  SetQC1CoolingMaterial( "vacuum");
  SetQC1VacuumVesselMaterial("Iron");
  SetQC1ThermalMaterial("vacuum");
  SetQC1ThermalVesselMaterial("Iron");
  SetQC1HeMaterial("vacuum");
  SetQC1HeVesselMaterial("Iron");
}

//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRQC1ParameterList::SetParameters()
{
  SetDefaults();
  BuildParameters();
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRQC1ParameterList::SetDefaults()
{

// Shape of QC1
  SetQC1NCollar(4);
// Master volume (Tube) for QC1
  SetQC1Radius(80*mm);
  SetQC1Thick(85*mm);
  SetQC1ZLength(1.67640*2*m);
// Only PI/4 part is defined.
// Iron.
  SetQC1SUSRadius(150.*mm);
  SetQC1SUSThick(15*mm);
// Collar
  SetQC1CollarRadius(110*mm);
  SetQC1CollarThick(40*mm);
  SetQC1CollarPhi(pi/4);
  SetQC1CollarDPhi(pi/14); // +-10degree=total 20degree 
// S-Magnet 4Layer
  SetQC1NCoil(4);
  SetQC1CoilPhi(0.);
  SetQC1CoilDPhi(pi);  // minus avoid intersection
// Vessel
    SetQC1VacuumVesselThick( 2.*mm);
// Thermal
  SetQC1ThermalThick(8.*mm);
//Thermal Vessel
  SetQC1ThermalVesselThick(8.*mm);
// He
  SetQC1HeThick(6.*mm);
// He Vessel
  SetQC1HeVesselThick(6.*mm);

}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRQC1ParameterList::BuildParameters()
{
}
//=====================================================================
//* SetVtsAttributes ------------------------------------------------------
void J4IRQC1ParameterList::SetVisAttributes()
{
  SetQC1VisAtt(TRUE);
}
//=====================================================================
//* SetColors ---------------------------------------------------------
void J4IRQC1ParameterList::SetColors()
{
   SetQC1Color(new G4Color(0.0,1.0,0.));  // green
}


