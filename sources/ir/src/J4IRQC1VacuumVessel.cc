// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC1VacuumVessel
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  T.Aso Original version.
//*************************************************************************

#include "J4IRQC1VacuumVessel.hh"

#include "G4Tubs.hh"
#include <math.h>

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC1VacuumVessel::fName("IRQC1VacuumVessel");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC1VacuumVessel::J4IRQC1VacuumVessel(J4VAcceleratorComponent *parent,
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

J4IRQC1VacuumVessel::~J4IRQC1VacuumVessel()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC1VacuumVessel::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".VacuumVessel";
    // define geometry
     G4VSolid *qc1 = new G4Tubs( name, 
    		_QC1INRADIUS_VACUUMVESSEL_,
    		_QC1INRADIUS_VACUUMVESSEL_+_QC1THICK_VACUUMVESSEL_,
                _QC1ZLEN_/2., 
    		0, twopi);  
                                       
    SetSolid(qc1);	// Don't forgat call it!
    Register(qc1);

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(_QC1MAT_VACUUMVESSEL_));
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 0, 1));

    // Install daughter PV -----------
  }     
}
//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRQC1VacuumVessel::Cabling()
{
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRQC1VacuumVessel::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRQC1VacuumVessel::Print() const
{
}

	
	

