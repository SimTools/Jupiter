// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC1SUS
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRQC1SUS.hh"

#include "G4Tubs.hh"
#include <cmath>

#include "J4IRQC1ParameterList.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC1SUS::fName("IRQC1SUS");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC1SUS::J4IRQC1SUS(J4VAcceleratorComponent *parent,
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

J4IRQC1SUS::~J4IRQC1SUS()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC1SUS::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  J4IRQC1ParameterList* qc1List=new J4IRQC1ParameterList(OpenParameterList()); 
  G4double qc1SUSInnerRadius = qc1List->GetQC1SUSRadius();
  G4double qc1SUSThickness   = qc1List->GetQC1SUSThick();
  G4double qc1SUSZLength     = qc1List->GetQC1ZLength();
  G4String qc1SUSMaterial    = qc1List->GetQC1SUSMaterial();
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".SUS";
    // define geometry
    //    G4VSolid *qc1sus = new G4Tubs( name, 
    //				   _QC1INRADIUS_SUS_,
    //				  _QC1INRADIUS_SUS_+_QC1THICK_SUS_,
    //				   _QC1ZLEN_/2., 
    //				   0, twopi);  
     G4VSolid *qc1sus = new G4Tubs( name, 
    				   qc1SUSInnerRadius,
				    qc1SUSInnerRadius+qc1SUSThickness,
    				   qc1SUSZLength/2., 
    				   0, twopi);  
                                       
    Register(qc1sus);
    SetSolid(qc1sus);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(qc1SUSMaterial));
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 0, 1));

    // Install daughter PV -----------
  }     
}
//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRQC1SUS::Cabling()
{
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRQC1SUS::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRQC1SUS::Print() const
{
}

	
	

