// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC2Iron2
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  T.Aso	Original version.
//*************************************************************************

#include "J4IRQC2Iron2.hh"
#include "J4IRQC1ParameterList.hh"
#include "G4Box.hh"
#include <cmath>

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC2Iron2::fName("IRQC2Iron2");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC2Iron2::J4IRQC2Iron2(J4VAcceleratorComponent *parent,
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

J4IRQC2Iron2::~J4IRQC2Iron2()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC2Iron2::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  	
    // MakeSolid ---------------
    G4String name2( GetName() );
    name2 += ".Iron2";
    // define geometry
     G4VSolid *solid2 = new G4Box( name2, 
				  _QC2HBOX_IRON2_/2.,
				  _QC2VBOX_IRON2_/2.,
				  _QC2ZLEN_/2.);
     Register(solid2);
    SetSolid(solid2);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(_QC2MAT_IRON_));
    // SetVisAttribute ---------------
//    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 0, 0));
    J4IRQC1ParameterList *qc1List=J4IRQC1ParameterList::GetInstance();
    PaintLV(qc1List->GetQC1VisAtt(), G4Color(1,1,0));

    // Install daughter PV -----------
  }
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRQC2Iron2::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 
  G4double xpos = _QC2XPOS_IRON2_; 
  G4double ypos = _QC2YPOS_IRON2_; 
  switch (GetMyID()%4) {
  case 0:
    xpos = +1.*xpos;
    ypos = +1.*ypos;
    break;
  case 1:
    xpos = -1.*xpos;
    ypos = +1.*ypos;
    break;
  case 2:
    xpos = -1.*xpos;
    ypos = -1.*ypos;
    break;
  case 3:
    xpos = +1.*xpos;
    ypos = -1.*ypos;
    break;
  }

  position->setX(xpos);
  position->setY(ypos);
  return *position;
}

//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRQC2Iron2::Cabling()
{
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRQC2Iron2::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRQC2Iron2::Print() const
{
}

	
	

