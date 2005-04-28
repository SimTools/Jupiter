// $Id$
//*************************************************************************
//* --------------------
//* J4IRCH2Mask
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/12  T.Aso	Original version.
//*************************************************************************

#include "J4IRCH2Mask.hh"
#include "J4IRCH2MaskParameterList.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRCH2Mask::fName("IRCH2Mask");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRCH2Mask::J4IRCH2Mask(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno,G4bool reflect ) :
            J4VIRAcceleratorComponent( fName, parent, nclones,
                                    nbrothers, me, copyno,reflect  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRCH2Mask::~J4IRCH2Mask()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRCH2Mask::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRCH2MaskParameterList* ch2List = J4IRCH2MaskParameterList::GetInstance();
    G4double rmin = ch2List->GetCH2MaskRadius();
    G4double rmax = ch2List->GetCH2MaskRadius()+ch2List->GetCH2MaskThick();
    G4double zlen = ch2List->GetCH2MaskZLength();
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".CH2";
    G4VSolid *tube = new G4Tubs( name, rmin,rmax,zlen/2.,0.,2*M_PI);  
                                       
    Register(tube);
    SetSolid(tube);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(ch2List->GetCH2MaskMaterial()));
    
    // SetVisAttribute ---------------
    PaintLV(ch2List->GetCH2MaskVisAtt(), ch2List->GetCH2MaskColor());
  	
    // Install daughter PV -----------
  		  
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRCH2Mask::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRCH2Mask::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRCH2Mask::GetTranslation(){
  J4IRCH2MaskParameterList* ch2List = J4IRCH2MaskParameterList::GetInstance();
  G4double zpos = 
    ch2List->GetCH2MaskZPosition()+ch2List->GetCH2MaskZLength()/2.;
  G4ThreeVector* position = new G4ThreeVector;
  position->setZ(zpos);

  //G4ThreeVector* position = new G4ThreeVector(0,0.,
  //			     _CH2MASKZPOS_+_CH2MASKZLEN_/2.);
  return *position;
}




//* Draw  --------------------------------------------------------
void J4IRCH2Mask::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRCH2Mask::Print() const
{
}

	
	

