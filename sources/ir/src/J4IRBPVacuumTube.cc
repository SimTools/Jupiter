// $Id$
//*************************************************************************
//* --------------------
//* J4IRBPVacuumTube
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRBPVacuumTube.hh"
#include "J4IRBPParameterList.hh"
#include "J4IRWMaskParameterList.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBPVacuumTube::fName("IRBPVacuumTube");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBPVacuumTube::J4IRBPVacuumTube(J4VAcceleratorComponent *parent,
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

J4IRBPVacuumTube::~J4IRBPVacuumTube()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBPVacuumTube::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRBPParameterList* bpList=new J4IRBPParameterList(OpenParameterList());
    J4IRWMaskParameterList* wmList =
      new J4IRWMaskParameterList(OpenParameterList());
    G4double rmax = bpList->GetBPDrumRadius()+bpList->GetBPDrumThick();
    G4double zlen  = wmList->GetWMask2ZLength();

    // MakeSolid ---------------
    G4String pipename( GetName() );
    pipename += ".pipe";
    G4VSolid *pipe = new G4Tubs( pipename, 0.,rmax,zlen/2., 0, 2*M_PI);

    Register(pipe);
    SetSolid(pipe);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order("vacuum"));
    
    // SetVisAttribute ---------------
    PaintLV(FALSE, G4Color(0, 1, 1));
  	
    // Install daughter PV -----------
  }     
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRBPVacuumTube::Cabling()
{
}

//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRBPVacuumTube::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRBPVacuumTube::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 
  J4IRBPParameterList* bpList=new J4IRBPParameterList(OpenParameterList());
  G4double zpos = bpList->GetBPENDZPosition()+bpList->GetBPENDZLength()/2.;
  position->setZ(zpos);
  //position->setZ(_BPZPOS_+_BPZLEN_/2.);
  return *position;
}

//* Draw  --------------------------------------------------------
void J4IRBPVacuumTube::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRBPVacuumTube::Print() const
{
}

