// $Id$
//*************************************************************************
//* --------------------
//* J4IRSD0SUS
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  T.Aso	Original version.
//*************************************************************************

#include "J4IRSD0SUS.hh"

#include "G4Trap.hh"
#include <math.h>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRSD0SUS::fName("IRSD0SUS");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRSD0SUS::J4IRSD0SUS(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
		       G4int  copyno):
            J4VIRAcceleratorComponent( fName, parent, nclones,
                                    nbrothers, me, copyno,FALSE  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRSD0SUS::~J4IRSD0SUS()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRSD0SUS::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".SUS";

    G4ThreeVector pt[8];
    pt[0]= G4ThreeVector(-_SD0X1_SUS_/2.,-_SD0Y1_SUS_/2.,-_SD0ZLEN_/2.);
    pt[1]= G4ThreeVector(_SD0X1_SUS_/2.,-_SD0Y1_SUS_/2.,-_SD0ZLEN_/2.);
    pt[2]= G4ThreeVector(-_SD0X2_SUS_/2.,_SD0Y1_SUS_/2.,-_SD0ZLEN_/2.);
    pt[3]= G4ThreeVector(_SD0X2_SUS_/2.,_SD0Y1_SUS_/2.,-_SD0ZLEN_/2.);

    pt[4]= G4ThreeVector(-_SD0X1_SUS_/2.,-_SD0Y1_SUS_/2.,_SD0ZLEN_/2.);
    pt[5]= G4ThreeVector(_SD0X1_SUS_/2.,-_SD0Y1_SUS_/2.,_SD0ZLEN_/2.);
    pt[6]= G4ThreeVector(-_SD0X2_SUS_/2.,_SD0Y1_SUS_/2.,_SD0ZLEN_/2.);
    pt[7]= G4ThreeVector(_SD0X2_SUS_/2.,_SD0Y1_SUS_/2.,_SD0ZLEN_/2.);


    G4VSolid *trap = new G4Trap( name, pt);
                                       
    Register(trap);
    SetSolid(trap);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(_SD0MAT_SUS_));
    
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(1, 0, 0));
    // Install daughter PV -----------
  		  
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRSD0SUS::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRSD0SUS::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  rotM->rotateZ(GetMyID()*_SD0PHI_SUS_-pi/2.+pi/6.);
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRSD0SUS::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 

  G4double radius = 
    (_SD0INRADIUS_+_SD0THICK_-0.5*_SD0Y1_SUS_/cos(_SD0PHI_SUS_/2.))
    *cos(_SD0PHI_SUS_/2.);

  position->setX(radius*cos(GetMyID()*_SD0PHI_SUS_+_SD0PHI_SUS_));
  position->setY(-radius*sin(GetMyID()*_SD0PHI_SUS_+_SD0PHI_SUS_));
  return *position;
}
//* Draw  --------------------------------------------------------
void J4IRSD0SUS::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRSD0SUS::Print() const
{
}

	
	

