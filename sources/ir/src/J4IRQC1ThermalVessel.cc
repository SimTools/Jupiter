// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC1ThermalVessel
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  T.Aso	Original version.
//*************************************************************************

#include "J4IRQC1ThermalVessel.hh"

#include "G4Tubs.hh"
#include <math.h>

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC1ThermalVessel::fName("IRQC1ThermalVessel");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC1ThermalVessel::J4IRQC1ThermalVessel(J4VAcceleratorComponent *parent,
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

J4IRQC1ThermalVessel::~J4IRQC1ThermalVessel()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC1ThermalVessel::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".ThermalVessel";
    // define geometry
    // G4VSolid *qc1 = new G4Tubs( name, 
    //		_QC1INRADIUS_THERMALVESSEL_,
    //		_QC1INRADIUS_THERMALVESSEL_+_QC1THICK_THERMALVESSEL_,
    //            _QC1ZLEN_/2., 
    //		0, twopi);  
     G4VSolid *qc1 = new G4Tubs( name, 
    		_QC1INRADIUS_COOLING_,
    		_QC1INRADIUS_THERMALVESSEL_+_QC1THICK_THERMALVESSEL_,
                _QC1ZLEN_/2., 
    		0, twopi);  
                                       
    SetSolid(qc1);	// Don't forgat call it!
    Register(qc1);

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(_QC1MAT_THERMALVESSEL_));
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 0, 1));

    // Install daughter PV -----------
    fthermal = new J4IRQC1Thermal(this,1,1,0,-1);
    Register(fthermal);
    fthermal->InstallIn(this);
    SetDaughter(fthermal);

  }     
}
//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRQC1ThermalVessel::Cabling()
{
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRQC1ThermalVessel::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRQC1ThermalVessel::Print() const
{
}

	
	

