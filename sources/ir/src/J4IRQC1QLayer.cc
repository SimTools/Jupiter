// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC1QLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRQC1QLayer.hh"

#include "G4Tubs.hh"
#include <math.h>

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC1QLayer::fName("IRQC1QLayer");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC1QLayer::J4IRQC1QLayer(J4VAcceleratorComponent *parent,
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

J4IRQC1QLayer::~J4IRQC1QLayer()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC1QLayer::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    //G4double len  = ((G4Tubs *)GetMother()->GetLV()->GetSolid())->
    //  GetZHalfLength() ;
    G4double len = _QC1ZLEN_/2.;
    G4double rmin = ((G4Tubs *)GetMother()->GetLV()->GetSolid())->
      GetInnerRadius() ;
    G4double rmax = ((G4Tubs *)GetMother()->GetLV()->GetSolid())->
      GetOuterRadius() ;
    G4double motherDphi = ((G4Tubs *)GetMother()->GetLV()->
			   GetSolid())->GetDeltaPhiAngle();

    G4double thick = ( rmax - rmin )/(G4double)GetNbrothers();
    rmin = rmin+thick*(G4double)GetMyID();
    rmax = rmin+thick;
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".QLayer";
    // define geometry
    G4VSolid *qc1 = new G4Tubs( name, rmin,rmax,len,0.,motherDphi);
                                       
    SetSolid(qc1);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(_QC1MAT_COIL_));
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(1, 1, 0));

    // Install daughter PV -----------
  }     
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRQC1QLayer::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  //rotM->rotateZ(-_QC1DPHI_COIL_);
  return rotM;
}
//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRQC1QLayer::Cabling()
{
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRQC1QLayer::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRQC1QLayer::Print() const
{
}

	
	

