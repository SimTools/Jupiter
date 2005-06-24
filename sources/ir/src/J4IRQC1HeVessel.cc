// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC1HeVessel
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRQC1HeVessel.hh"

#include "G4Tubs.hh"
#include <cmath>
#include "J4IRQC1ParameterList.hh"
// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC1HeVessel::fName("IRQC1HeVessel");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC1HeVessel::J4IRQC1HeVessel(J4VAcceleratorComponent *parent,
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

J4IRQC1HeVessel::~J4IRQC1HeVessel()
{
  if (Deregister(fcoolant) ) delete fcoolant;

}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC1HeVessel::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  J4IRQC1ParameterList* qc1List=J4IRQC1ParameterList::GetInstance();
  G4double qc1InnerRadius = qc1List->GetQC1CoolingRadius();
  G4double qc1HeVesselRadius = qc1List->GetQC1HeVesselRadius();
  G4double qc1Thickness=qc1List->GetQC1HeVesselThick();
  G4double qc1ZLength     = qc1List->GetQC1ZLength();
  G4String qc1Material    = qc1List->GetQC1HeVesselMaterial();
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".HeVessel";
    // define geometry
    //     G4VSolid *qc1 = new G4Tubs( name, 
    //		_QC1INRADIUS_HEVESSEL_,
    //		_QC1INRADIUS_HEVESSEL_+_QC1THICK_HEVESSEL_,
    //            _QC1ZLEN_/2., 
    //		0, twopi);  
    // G4VSolid *qc1 = new G4Tubs( name, 
    //		_QC1INRADIUS_COOLING_,
    //		_QC1INRADIUS_HEVESSEL_+_QC1THICK_HEVESSEL_,
    //            _QC1ZLEN_/2., 
    //		0, twopi);  
     G4VSolid *qc1 = new G4Tubs( name, 
    		qc1InnerRadius,
    		qc1HeVesselRadius+qc1Thickness,
                qc1ZLength/2., 
    		0, twopi);  
                                       
    SetSolid(qc1);	// Don't forgat call it!
    Register(qc1);

    // MakeLogicalVolume -------------
    //MakeLVWith(OpenMaterialStore()->Order(_QC1MAT_HEVESSEL_));
    MakeLVWith(OpenMaterialStore()->Order(qc1Material));
    // SetVisAttribute ---------------
//    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 0, 1));
    PaintLV(qc1List->GetQC1VisAtt(), G4Color(0,0,1) );

    // Install daughter PV -----------
    fcoolant = new J4IRQC1Coolant(this,1,1,0,-1);
    Register(fcoolant);
    fcoolant->InstallIn(this);
    SetDaughter(fcoolant);

  }     
}
//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRQC1HeVessel::Cabling()
{
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRQC1HeVessel::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRQC1HeVessel::Print() const
{
}

	
	

