// $Id$
//*************************************************************************
//* --------------------
//* J4IRBPAlPipe
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRBPAlPipe.hh"
#include "J4IRBPParameterList.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBPAlPipe::fName("IRBPAlPipe");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBPAlPipe::J4IRBPAlPipe(J4VAcceleratorComponent *parent,
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

J4IRBPAlPipe::~J4IRBPAlPipe()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBPAlPipe::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRBPParameterList* bpList=new J4IRBPParameterList(OpenParameterList());
    G4double rmin = bpList->GetBPENDRadius();
    G4double rmax = bpList->GetBPENDRadius()+bpList->GetBPENDThick();
    G4double zlen = bpList->GetBPENDZLength();

    // MakeSolid ---------------
    G4String pipename( GetName() );
    pipename += ".pipe";
    G4VSolid *pipe = new G4Tubs( pipename,rmin,rmax,zlen/2., 
				   0, 2*M_PI);
    Register(pipe);
    SetSolid(pipe);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(bpList->GetBPSTDMaterial()));
    
    // SetVisAttribute ---------------
    PaintLV(bpList->GetBPVisAtt(),bpList->GetBPColor());
  	
    // Install daughter PV -----------
  }     
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRBPAlPipe::Cabling()
{
}

//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRBPAlPipe::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRBPAlPipe::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 
  //position->setX(0.*cm);
  //position->setY(0.*cm);
  //position->setZ(_BPZPOS_+_BPZLEN_/2.);
  return *position;
}

//* Draw  --------------------------------------------------------
void J4IRBPAlPipe::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRBPAlPipe::Print() const
{
}

