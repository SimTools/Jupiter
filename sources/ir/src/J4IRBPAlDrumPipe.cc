// $Id$
//*************************************************************************
//* --------------------
//* J4IRBPAlDrumPipe
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4IRBPAlDrumPipe.hh"
#include "J4IRBPParameterList.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBPAlDrumPipe::fName("IRBPAlDrumPipe");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBPAlDrumPipe::J4IRBPAlDrumPipe(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno,
		                          G4bool reflect) :
            J4VIRAcceleratorComponent( fName, parent, nclones,
                                    nbrothers, me, copyno, reflect  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRBPAlDrumPipe::~J4IRBPAlDrumPipe()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBPAlDrumPipe::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRBPParameterList* bpList = new J4IRBPParameterList(OpenParameterList());
    G4double rmin = bpList->GetBPDrumRadius();
    G4double rmax = bpList->GetBPDrumRadius()+bpList->GetBPDrumThick();
    G4double zlen = bpList->GetBPDrumZLength();

    // MakeSolid ---------------
    G4String drumpipename( GetName() );
    drumpipename += ".drumPipe";
    G4VSolid *drumPipe = new G4Tubs( drumpipename, rmin,rmax,zlen/2.,
				   0, 2*M_PI);
    Register(drumPipe);
    SetSolid(drumPipe);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(bpList->GetBPSTDMaterial()));
    
    // SetVisAttribute ---------------
    PaintLV(bpList->GetBPVisAtt(), bpList->GetBPColor());
  	
    // Install daughter PV -----------
    
  		  
  }     
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRBPAlDrumPipe::Cabling()
{
}

//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRBPAlDrumPipe::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRBPAlDrumPipe::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 
  J4IRBPParameterList* bpList = new J4IRBPParameterList(OpenParameterList());
  G4double zpos = bpList->GetBPDrumZLength()/2.
    - ( bpList->GetBPDrumZLength()+bpList->GetBPDrumcapZLength() )/2.;
  //position->setZ(_BPZLEN_DRUM_/2. - (_BPZLEN_DRUM_+_BPZLEN_DRUMCAP_)/2.);
  position->setZ(zpos);
  return *position;
}

//* Draw  --------------------------------------------------------
void J4IRBPAlDrumPipe::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRBPAlDrumPipe::Print() const
{
}


