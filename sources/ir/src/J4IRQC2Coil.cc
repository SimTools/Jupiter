// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC2Coil
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  T.Aso	Original version.
//*************************************************************************

#include "J4IRQC2Coil.hh"

#include "G4Box.hh"
#include <math.h>

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC2Coil::fName("IRQC2Coil");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC2Coil::J4IRQC2Coil(J4VAcceleratorComponent *parent,
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

J4IRQC2Coil::~J4IRQC2Coil()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC2Coil::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".Coil";
    // define geometry
     G4VSolid *solid = new G4Box( name, 
				  _QC2HBOX_COIL_/2.,
				  _QC2VBOX_COIL_/2.,
				  _QC2ZLEN_/2.);

     Register(solid);
    SetSolid(solid);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(_QC2MAT_COIL_));
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 0, 0));

    // Install daughter PV -----------
  }
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRQC2Coil::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 
  G4double xpos1 = _QC2XPOS1_COIL_; 
  G4double xpos2 = _QC2XPOS2_COIL_; 
  G4double xpos=0.;
  G4double ypos = _QC2YPOS_COIL_; 
  switch (GetMyID()%8) {
  case 0:
    xpos = +1.*xpos1;
    ypos = +1.*ypos;
    break;
  case 1:
    xpos = -1.*xpos1;
    ypos = +1.*ypos;
    break;
  case 2:
    xpos = -1.*xpos1;
    ypos = -1.*ypos;
    break;
  case 3:
    xpos = +1.*xpos1;
    ypos = -1.*ypos;
    break;
  case 4:
    xpos = +1.*xpos2;
    ypos = +1.*ypos;
    break;
  case 5:
    xpos = -1.*xpos2;
    ypos = +1.*ypos;
    break;
  case 6:
    xpos = -1.*xpos2;
    ypos = -1.*ypos;
    break;
  case 7:
    xpos = +1.*xpos2;
    ypos = -1.*ypos;
    break;
  }

  position->setX(xpos);
  position->setY(ypos);
  return *position;
}

//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRQC2Coil::Cabling()
{
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRQC2Coil::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRQC2Coil::Print() const
{
}

	
	

