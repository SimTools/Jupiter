// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC1Collar
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRQC1Collar.hh"

#include "G4Tubs.hh"
#include <math.h>

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC1Collar::fName("IRQC1Collar");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC1Collar::J4IRQC1Collar(J4VAcceleratorComponent *parent,
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

J4IRQC1Collar::~J4IRQC1Collar()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC1Collar::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".Collar";

    // define geometry
     G4VSolid *qc1collar = new G4Tubs( name, 
    		_QC1INRADIUS_COLLAR_,
    		_QC1INRADIUS_COLLAR_+_QC1THICK_COLLAR_,
                _QC1ZLEN_/2., 
                0.,_QC1DPHI_COLLAR_*2. );  
                                       
     Register(qc1collar);
    SetSolid(qc1collar);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(_QC1MAT_COLLAR_));
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 0, 1));

    // Install daughter PV -----------
  }     
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRQC1Collar::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  rotM->rotateZ((_QC1PHI_COLLAR_+_QC1DPHI_COLLAR_)+pi/2.*GetMyID());
  return rotM;
}
//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRQC1Collar::Cabling()
{
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRQC1Collar::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRQC1Collar::Print() const
{
}

	
	

