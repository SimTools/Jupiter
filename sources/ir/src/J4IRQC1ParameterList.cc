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
#include "J4ParameterTable.hh"

J4IRQC1ParameterList* J4IRQC1ParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4IRQC1ParameterList* J4IRQC1ParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4IRQC1ParameterList("IRQC1");
   }
   return fgInstance;
}

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC1ParameterList::J4IRQC1ParameterList(const G4String& name)
  : J4VParameterList(name)
{
  fgInstance=this;
  //  fList = list;
  SetParameters();
  SetMaterials();
  SetVisAttributes();
  SetColors();
}
//=====================================================================
//* destructor -------------------------------------------------------

J4IRQC1ParameterList::~J4IRQC1ParameterList()
{
  //  delete  fList;
  delete  fQC1Color;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4IRQC1ParameterList::SetMaterials()
{
/*
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
*/
  SetQC1Material(J4ParameterTable::GetValue("J4IR.QC1.Material","vacuum"));
  SetQC1SUSMaterial(J4ParameterTable::GetValue("J4IR.QC1.Material.SUS","Iron"));
  SetQC1CollarMaterial(J4ParameterTable::GetValue("J4IR.QC1.Material.Collar","Iron"));
  SetQC1CoilMaterial(J4ParameterTable::GetValue("J4IR.QC1.Material.Coil","Cupper"));
  SetQC1CoolingMaterial(J4ParameterTable::GetValue("J4IR.QC1.Material.Cooling", "vacuum"));
  SetQC1VacuumVesselMaterial(J4ParameterTable::GetValue("J4IR.QC1.Material.VacuumVessel","Iron"));
  SetQC1ThermalMaterial(J4ParameterTable::GetValue("J4IR.QC1.Material.ThermalShield","vacuum"));
  SetQC1ThermalVesselMaterial(J4ParameterTable::GetValue("J4IR.QC1.Material.ThermalVessel","Iron"));
  SetQC1HeMaterial(J4ParameterTable::GetValue("J4IR.QC1.Material.He","vacuum"));
  SetQC1HeVesselMaterial(J4ParameterTable::GetValue("J4IR.QC1.Material.HeVessel","Iron"));

}

//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRQC1ParameterList::SetParameters()
{
  if ( J4IRParameterList::GetInstance()->IsCompact() )  SetCompact();  // New
  else                       SetDefaults(); //
  BuildParameters();
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRQC1ParameterList::SetCompact()
{
   SetDefaults();  // All ways call SetDefaults so that parameters are defined by J4ParameterTable::GetValue(...)
/*
// Shape of QC1
  SetQC1NCollar(4);
// Master volume (Tube) for QC1
  SetQC1Radius(10*mm);
  SetQC1Thick(45*mm);  // Rout = 55mm
  SetQC1ZLength(1.67640*2*m);
// Only PI/4 part is defined.
// Iron.
  SetQC1SUSRadius(40.*mm);
  SetQC1SUSThick(15*mm);
// Collar
  SetQC1CollarRadius(15*mm);
  SetQC1CollarThick(25*mm);
  SetQC1CollarPhi(pi/4);
  SetQC1CollarDPhi(pi/14); // +-10degree=total 20degree 
// S-Magnet 4Layer
  SetQC1NCoil(4);
  SetQC1CoilPhi(0.);
  SetQC1CoilDPhi(pi);  // minus avoid intersection
// He Vessel
  SetQC1HeVesselThick(1.*mm);
// He
  SetQC1HeThick(1.*mm);
//Thermal Vessel
  SetQC1ThermalVesselThick(1.*mm);
// Thermal
  SetQC1ThermalThick(1.*mm);
// Vessel
    SetQC1VacuumVesselThick( 1.*mm);
*/
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRQC1ParameterList::SetDefaults()
{
/*
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
*/

// Master volume (Tube) for QC1
  SetQC1Radius(J4ParameterTable::GetValue("J4IR.QC1.Radius",8.0)*cm);
  SetQC1Thick(J4ParameterTable::GetValue("J4IR.QC1.Thickness",8.5)*cm); 
  SetQC1ZLength(J4ParameterTable::GetValue("J4IR.QC1.ZLength",1.67640*200.)*cm);
// Only PI/4 part is defined.
// Iron.
  SetQC1SUSRadius(J4ParameterTable::GetValue("J4IR.QC1.SUS.Radius",15.0)*cm);
  SetQC1SUSThick(J4ParameterTable::GetValue("J4IR.QC1.SUS.Thickness",1.5)*cm);
// Collar
  SetQC1CollarRadius(J4ParameterTable::GetValue("J4IR.QC1.CollarRadius",11.0)*cm);
  SetQC1CollarThick(J4ParameterTable::GetValue("J4IR.QC1.CollarThickness",4.0)*cm);
//  SetQC1CollarPhi(pi/(double)J4ParameterTable::GetValue("J4IR.QC1.NPhi",4));
//  SetQC1CollarDPhi(pi/(double)J4ParameterTable::GetValue("J4IR.QC1.NDphi",14)); // +-10degree=total 20degree 
// S-Magnet 4Layer
  SetQC1NCoil(J4ParameterTable::GetValue("J4IR.QC1.NCoil",4));
  SetQC1CoilPhi(0.);
  SetQC1CoilDPhi(pi);  // minus avoid intersection
// Vessel
  SetQC1VacuumVesselThick(J4ParameterTable::GetValue("J4IR.QC1.VaccumeVessel.Thickness",0.2)*cm);
// Thermal
  SetQC1ThermalThick(J4ParameterTable::GetValue("J4IR.QC1.ThermalShield.Thickness",0.8)*cm);
//Thermal Vessel
  SetQC1ThermalVesselThick(J4ParameterTable::GetValue("J4IR.QC1.ThermalVessel.Thickness",0.8)*cm);
// He
  SetQC1HeThick(J4ParameterTable::GetValue("J4IR.QC1.He.Thickness",0.6)*cm);
// He Vessel
  SetQC1HeVesselThick(J4ParameterTable::GetValue("J4IR.QC1.HeVessel.Thickness",0.6)*cm);


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
//  SetQC1VisAtt(TRUE);
  SetQC1VisAtt(J4ParameterTable::GetValue("J4IR.VisAtt.QC1",true));

}
//=====================================================================
//* SetColors ---------------------------------------------------------
void J4IRQC1ParameterList::SetColors()
{
//   SetQC1Color(new G4Color(0.0,1.0,0.));  // green
  std::vector<double> col=J4ParameterTable::GetDValue("J4IR.Color.QC1","0.0 1.0 0.0 1.0",4);
   SetQC1Color(new G4Color(col[0], col[1], col[2], col[3]));  // green

}


