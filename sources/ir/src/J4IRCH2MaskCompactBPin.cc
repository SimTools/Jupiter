// $Id$
//*************************************************************************
//* --------------------
//* J4IRCH2MaskCompactBPin
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/12  T.Aso	Original version.
//*************************************************************************

#include "J4IRCH2MaskCompactBPin.hh"
#include "J4IRCH2MaskParameterList.hh"

#include "G4Cons.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRCH2MaskCompactBPin::fName("IRCH2MaskCompactBPin");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRCH2MaskCompactBPin::J4IRCH2MaskCompactBPin(J4VAcceleratorComponent *parent,
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

J4IRCH2MaskCompactBPin::~J4IRCH2MaskCompactBPin()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRCH2MaskCompactBPin::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRCH2MaskParameterList* ch2List = 
      new J4IRCH2MaskParameterList(OpenParameterList());
    G4double angle = OpenParameterList()->GetCrossAngle();
    G4double rmin = 0.*mm;
    G4double r1max = 5.*mm;
    G4double zlen = ch2List->GetCH2MaskZLength();
    G4double r2max = r1max+2.*zlen*std::sin(std::abs(angle));
    
    G4cout << r1max/mm <<" " << r2max/mm << " " << zlen/mm << G4endl;
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".BPin";
    G4VSolid *cone = new G4Cons( name, rmin,r1max,rmin,r2max,
				 zlen/2.,0.,2*M_PI);  
                                       
    Register(cone);
    SetSolid(cone);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order("vacuum"));
    
    // SetVisAttribute ---------------
    PaintLV(ch2List->GetCH2MaskVisAtt(), G4Color(0,0,0));
  	
    // Install daughter PV -----------
  		  
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRCH2MaskCompactBPin::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRCH2MaskCompactBPin::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRCH2MaskCompactBPin::GetTranslation(){
  J4IRCH2MaskParameterList* ch2List = 
    new J4IRCH2MaskParameterList(OpenParameterList());
  G4double angle = OpenParameterList()->GetCrossAngle();

  G4double zpos = 
    ch2List->GetCH2MaskZPosition();
  G4double xpos = zpos*std::sin(-angle);

  G4ThreeVector* position = new G4ThreeVector;
  position->setX(xpos);

  //G4ThreeVector* position = new G4ThreeVector(0,0.,
  //			     _CH2MASKZPOS_+_CH2MASKZLEN_/2.);
  return *position;
}




//* Draw  --------------------------------------------------------
void J4IRCH2MaskCompactBPin::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRCH2MaskCompactBPin::Print() const
{
}

	
	

