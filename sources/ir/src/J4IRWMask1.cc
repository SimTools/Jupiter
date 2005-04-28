// $Id$
//*************************************************************************
//* --------------------
//* J4IRWMask1
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  T.Aso	Original version.
//*************************************************************************

#include "J4IRWMask1.hh"
#include "J4IRWMaskParameterList.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRWMask1::fName("IRWMask1");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRWMask1::J4IRWMask1(J4VAcceleratorComponent *parent,
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

J4IRWMask1::~J4IRWMask1()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRWMask1::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRWMaskParameterList* wmList = J4IRWMaskParameterList::GetInstance();
    G4double rmin = wmList->GetWMask1Radius();
    G4double rmax = wmList->GetWMask1Radius()+wmList->GetWMask1Thick();
    G4double zlen  = wmList->GetWMask1ZLength();

    std::cerr << " IRWMask1  rmin=" << rmin ;
    std::cerr << " rmax=" << rmax << "zlen=" << zlen << std::endl;
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += "/WMask1";
    G4VSolid *tube = new G4Tubs( name,rmin,rmax,zlen/2., 0, 2*M_PI);  

    Register(tube);
    SetSolid(tube);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(wmList->GetWMaskMaterial()));
    
    // SetVisAttribute ---------------
    PaintLV(wmList->GetWMaskVisAtt(),wmList->GetWMaskColor());
  	
    // Install daughter PV -----------
  		  
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRWMask1::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRWMask1::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRWMask1::GetTranslation(){
  J4IRWMaskParameterList* wmList = J4IRWMaskParameterList::GetInstance();
  G4double zpos = wmList->GetWMask1ZPosition()+wmList->GetWMask1ZLength()/2.;

  G4ThreeVector* position = new G4ThreeVector(0,0.,zpos);
  //G4ThreeVector* position = new G4ThreeVector(0,0.,
  //				      _WMASK1ZPOS_+_WMASK1ZLEN_/2.);
  return *position;
}




//* Draw  --------------------------------------------------------
void J4IRWMask1::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRWMask1::Print() const
{
}

	
	

