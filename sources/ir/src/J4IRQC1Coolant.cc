// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC1Coolant
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRQC1Coolant.hh"

#include "G4Tubs.hh"
#include <cmath>
#include "J4IRQC1ParameterList.hh"
// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC1Coolant::fName("IRQC1Coolant");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC1Coolant::J4IRQC1Coolant(J4VAcceleratorComponent *parent,
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

J4IRQC1Coolant::~J4IRQC1Coolant()
{
  if (Deregister(fthVess) ) delete fthVess;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC1Coolant::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  J4IRQC1ParameterList* qc1List=new J4IRQC1ParameterList(OpenParameterList()); 
  G4double qc1InnerRadius = qc1List->GetQC1CoolingRadius();
  G4double qc1HeRadius = qc1List->GetQC1HeRadius();
  G4double qc1Thickness=qc1List->GetQC1HeThick();
  G4double qc1ZLength     = qc1List->GetQC1ZLength();
  G4String qc1Material    = qc1List->GetQC1HeMaterial();
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".Coolant";
    // define geometry

    // G4VSolid *qc1 = new G4Tubs( name, 
    //  		_QC1INRADIUS_HE_,
    //  		_QC1INRADIUS_HE_+_QC1THICK_HE_,
    //              _QC1ZLEN_/2., 
    //  		0, twopi);  
    // G4VSolid *qc1 = new G4Tubs( name, 
    //		_QC1INRADIUS_COOLING_,
    //		_QC1INRADIUS_HE_+_QC1THICK_HE_,
    //            _QC1ZLEN_/2., 
    //		0, twopi);  
     G4VSolid *qc1 = new G4Tubs( name, 
    		qc1InnerRadius,
    		qc1HeRadius+qc1Thickness,
                qc1ZLength/2., 
    		0, twopi);  
                                       
    SetSolid(qc1);	// Don't forgat call it!
    Register(qc1);

    // MakeLogicalVolume -------------
    //MakeLVWith(OpenMaterialStore()->Order(_QC1MAT_HE_));
    MakeLVWith(OpenMaterialStore()->Order(qc1Material));
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 0, 1));

    // Install daughter PV -----------
    fthVess = new J4IRQC1ThermalVessel(this,1,1,0,-1);
    Register(fthVess);
    fthVess->InstallIn(this);
    SetDaughter(fthVess);
  }     
}
//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRQC1Coolant::Cabling()
{
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRQC1Coolant::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRQC1Coolant::Print() const
{
}

	
	

