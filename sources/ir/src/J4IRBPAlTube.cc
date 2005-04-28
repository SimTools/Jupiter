// $Id$
//*************************************************************************
//* --------------------
//* J4IRBPAlTube
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRBPAlTube.hh"
#include "J4IRBPParameterList.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBPAlTube::fName("IRBPAlTube");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBPAlTube::J4IRBPAlTube(J4VAcceleratorComponent *parent,
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

J4IRBPAlTube::~J4IRBPAlTube()
{
  if(Deregister(fpipe)) delete fpipe;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBPAlTube::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRBPParameterList* bpList=J4IRBPParameterList::GetInstance();
    G4double rmax = bpList->GetBPENDRadius()+bpList->GetBPENDThick();
    G4double zlen = bpList->GetBPENDZLength();

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
    fpipe = new J4IRBPAlPipe(this,1,1,0,-1);
    Register(fpipe);
    fpipe->InstallIn(this);
    SetDaughter(fpipe);
  		  
  }     
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRBPAlTube::Cabling()
{
}

//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRBPAlTube::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRBPAlTube::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 
  J4IRBPParameterList* bpList=J4IRBPParameterList::GetInstance();
  G4double zpos = bpList->GetBPENDZPosition()+bpList->GetBPENDZLength()/2.;
  position->setZ(zpos);
  //position->setZ(_BPZPOS_+_BPZLEN_/2.);
  return *position;
}

//* Draw  --------------------------------------------------------
void J4IRBPAlTube::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRBPAlTube::Print() const
{
}

