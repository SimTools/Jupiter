// $Id$
//*************************************************************************
//* --------------------
//* J4IRCH2MaskCompact
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/12  T.Aso	Original version.
//*************************************************************************

#include "J4IRCH2MaskCompact.hh"
#include "J4IRCH2MaskParameterList.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRCH2MaskCompact::fName("IRCH2MaskCompact");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRCH2MaskCompact::J4IRCH2MaskCompact(J4VAcceleratorComponent *parent,
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

J4IRCH2MaskCompact::~J4IRCH2MaskCompact()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRCH2MaskCompact::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRCH2MaskParameterList* ch2List = 
      new J4IRCH2MaskParameterList(OpenParameterList());
    G4double rmin = 0.*mm;
    G4double rmax = OpenParameterList()->GetIRSupportInnerRadius();
    G4double zlen = ch2List->GetCH2MaskZLength();
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".CH2Compact";
    G4VSolid *tube = new G4Tubs( name, rmin,rmax,zlen/2.,0.,2*M_PI);  
                                       
    Register(tube);
    SetSolid(tube);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(ch2List->GetCH2MaskMaterial()));
    
    // SetVisAttribute ---------------
    PaintLV(ch2List->GetCH2MaskVisAtt(), ch2List->GetCH2MaskColor());
  	
    // Install daughter PV -----------
    fbpIn = new J4IRCH2MaskCompactBPin(this,1,1,0,-1);
    Register(fbpIn);
    fbpIn->InstallIn(this);
    SetDaughter(fbpIn);

    fbpOut = new J4IRCH2MaskCompactBPout(this,1,1,0,-1);
    Register(fbpOut);
    fbpOut->InstallIn(this);
    SetDaughter(fbpOut);
  		  
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRCH2MaskCompact::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRCH2MaskCompact::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRCH2MaskCompact::GetTranslation(){
  J4IRCH2MaskParameterList* ch2List = 
    new J4IRCH2MaskParameterList(OpenParameterList());
  G4double zpos = 
    ch2List->GetCH2MaskZPosition()+ch2List->GetCH2MaskZLength()/2.;
  G4ThreeVector* position = new G4ThreeVector;
  position->setZ(zpos);

  //G4ThreeVector* position = new G4ThreeVector(0,0.,
  //			     _CH2MASKZPOS_+_CH2MASKZLEN_/2.);
  return *position;
}




//* Draw  --------------------------------------------------------
void J4IRCH2MaskCompact::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRCH2MaskCompact::Print() const
{
}

	
	

