// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC1Cooling
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/12  T.Aso	Original version.
//*************************************************************************

#include "J4IRQC1Cooling.hh"

#include "G4Tubs.hh"
#include <math.h>

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC1Cooling::fName("IRQC1Cooling");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC1Cooling::J4IRQC1Cooling(J4VAcceleratorComponent *parent,
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

J4IRQC1Cooling::~J4IRQC1Cooling()
{
  if (Deregister(fheVess) ) delete fheVess;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC1Cooling::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".Cooling";
    // define geometry
     G4VSolid *qc1 = new G4Tubs( name, 
    		_QC1INRADIUS_COOLING_,
    		_QC1INRADIUS_COOLING_+_QC1THICK_COOLING_,
                _QC1ZLEN_/2., 
    		0, twopi);  
                                       
    SetSolid(qc1);	// Don't forgat call it!
    Register(qc1);

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(_QC1MAT_COOLING_));
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 0, 1));

    // Install daughter PV -----------


#if 1
    fheVess = new J4IRQC1HeVessel(this,1,1,0,-1);
    Register(fheVess);
    fheVess->InstallIn(this);
    SetDaughter(fheVess);
#endif
  }     
}
//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRQC1Cooling::Cabling()
{
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRQC1Cooling::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRQC1Cooling::Print() const
{
}

	
	

