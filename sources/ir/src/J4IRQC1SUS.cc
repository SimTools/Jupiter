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
#include <math.h>

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
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".SUS";
    // define geometry
    G4VSolid *qc1sus = new G4Tubs( name, 
				   _QC1INRADIUS_SUS_,
				  _QC1INRADIUS_SUS_+_QC1THICK_SUS_,
				   _QC1ZLEN_/2., 
				   0, twopi);  
                                       
    Register(qc1sus);
    SetSolid(qc1sus);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(_QC1MAT_SUS_));
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

	
	

