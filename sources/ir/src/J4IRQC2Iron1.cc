// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC2Iron1
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  T.Aso	Original version.
//*************************************************************************

#include "J4IRQC2Iron1.hh"

#include "G4Box.hh"
#include <cmath>

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC2Iron1::fName("IRQC2Iron1");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC2Iron1::J4IRQC2Iron1(J4VAcceleratorComponent *parent,
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

J4IRQC2Iron1::~J4IRQC2Iron1()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC2Iron1::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".Iron1";
    // define geometry
     G4VSolid *solid = new G4Box( name, 
				  _QC2HBOX_IRON1_/2.,
				  _QC2VBOX_IRON1_/2.,
				  _QC2ZLEN_/2.);

     Register (solid);
    SetSolid(solid);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(_QC2MAT_IRON_));
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 0, 0));

    // Install daughter PV -----------
  }
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRQC2Iron1::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 
  G4double ypos = _QC2YPOS_IRON1_;
  switch( GetMyID()%2) {
  case 0:
    ypos = -1.*ypos;
    break;
  case 1:
    ypos = +1.*ypos;
    break;
  }
  position->setY(ypos);
  return *position;
}

//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRQC2Iron1::Cabling()
{
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRQC2Iron1::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRQC2Iron1::Print() const
{
}

	
	

