// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC1Thermal
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRQC1Thermal.hh"

#include "G4Tubs.hh"
#include <math.h>
#include "J4IRQC1ParameterList.hh"
// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC1Thermal::fName("IRQC1Thermal");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC1Thermal::J4IRQC1Thermal(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
			       G4int  copyno):
            J4VIRAcceleratorComponent( fName, parent, nclones,
				       nbrothers, me, copyno  ) 
{   
}
//=====================================================================
//* destructor --------------------------------------------------------

J4IRQC1Thermal::~J4IRQC1Thermal()
{
  if (Deregister(fvacVess) ) delete fvacVess;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC1Thermal::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  J4IRQC1ParameterList* qc1List=new J4IRQC1ParameterList(OpenParameterList()); 
  G4double qc1InnerRadius = qc1List->GetQC1CoolingRadius();
  G4double qc1ThermalRadius = qc1List->GetQC1ThermalRadius();
  G4double qc1ThermalThickness=qc1List->GetQC1ThermalThick();
  G4double qc1ZLength     = qc1List->GetQC1ZLength();
  G4String qc1Material    = qc1List->GetQC1ThermalMaterial();
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".Thermal";
    // define geometry

    // G4VSolid *qc1 = new G4Tubs( name, 
    //  		_QC1INRADIUS_HE_,
    //  		_QC1INRADIUS_HE_+_QC1THICK_HE_,
    //              _QC1ZLEN_/2., 
    //  		0, twopi);  
    //     G4VSolid *qc1 = new G4Tubs( name, 
    //    		_QC1INRADIUS_COOLING_,
    //    		_QC1INRADIUS_THERMAL_+_QC1THICK_THERMAL_,
    //                _QC1ZLEN_/2., 
    //    		0, twopi);  
     G4VSolid *qc1 = new G4Tubs( name, 
    		qc1InnerRadius,
    		qc1ThermalRadius+qc1ThermalThickness,
                qc1ZLength/2., 
    		0, twopi);  
                                       
    SetSolid(qc1);	// Don't forgat call it!
    Register(qc1);

    // MakeLogicalVolume -------------
    //    MakeLVWith(OpenMaterialStore()->Order(_QC1MAT_HE_));
        MakeLVWith(OpenMaterialStore()->Order(qc1Material));
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 0, 1));

    // Install daughter PV -----------
    fvacVess = new J4IRQC1VacuumVessel(this,1,1,0,-1);
    Register(fvacVess);
    fvacVess->InstallIn(this);
    SetDaughter(fvacVess);
  }     
}
//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRQC1Thermal::Cabling()
{
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRQC1Thermal::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRQC1Thermal::Print() const
{
}

	
	

