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
#include <cmath>
#include "J4IRQC1ParameterList.hh"

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
  J4IRQC1ParameterList* qc1List=new J4IRQC1ParameterList(OpenParameterList()); 
  G4double qc1CollarInnerRadius = qc1List->GetQC1CollarRadius();
  G4double qc1CollarThickness   = qc1List->GetQC1CollarThick();
  G4double qc1CollarZLength     = qc1List->GetQC1ZLength();
  G4String qc1CollarMaterial    = qc1List->GetQC1CollarMaterial();
  G4double qc1CollarDPhi        = qc1List->GetQC1CollarDPhi();
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".Collar";

    // define geometry
    //     G4VSolid *qc1collar = new G4Tubs( name, 
    //    		_QC1INRADIUS_COLLAR_,
    //    		_QC1INRADIUS_COLLAR_+_QC1THICK_COLLAR_,
    //                _QC1ZLEN_/2., 
    //                0.,_QC1DPHI_COLLAR_*2. );  
         G4VSolid *qc1collar = new G4Tubs( name, 
			qc1CollarInnerRadius,		   
		   qc1CollarInnerRadius+qc1CollarThickness,		   
                    qc1CollarZLength/2., 
                    0.,qc1CollarDPhi*2. );  
                                       
     Register(qc1collar);
    SetSolid(qc1collar);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    //    MakeLVWith(OpenMaterialStore()->Order(_QC1MAT_COLLAR_));
        MakeLVWith(OpenMaterialStore()->Order(qc1CollarMaterial));
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 0, 1));

    // Install daughter PV -----------
  }     
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRQC1Collar::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  J4IRQC1ParameterList* qc1List=new J4IRQC1ParameterList(OpenParameterList()); 
  G4double phi = qc1List->GetQC1CollarPhi();
  G4double dphi = qc1List->GetQC1CollarDPhi();
  //rotM->rotateZ((_QC1PHI_COLLAR_+_QC1DPHI_COLLAR_)+pi/2.*GetMyID());
  rotM->rotateZ((phi+dphi)+pi/2.*GetMyID());
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

	
	

