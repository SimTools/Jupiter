// $Id$
//*************************************************************************
//* --------------------
//* J4IRBPBeCone
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRBPBeCone.hh"
#include "J4IRBPParameterList.hh"

#include "G4Cons.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBPBeCone::fName("IRBPBeCone");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBPBeCone::J4IRBPBeCone(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno,
			                  G4bool reflect) :
            J4VIRAcceleratorComponent( fName, parent, nclones,
                                    nbrothers, me, copyno ,reflect ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRBPBeCone::~J4IRBPBeCone()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBPBeCone::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRBPParameterList *bpList = new J4IRBPParameterList(OpenParameterList());
    G4double rmin1 = bpList->GetBPIPRadius();
    G4double rmax1 = bpList->GetBPIPRadius()+bpList->GetBPIPThick();
    G4double rmin2 = bpList->GetBPDrumRadius();
    G4double rmax2 = bpList->GetBPDrumRadius()+bpList->GetBPDrumThick();
    G4double zlen  = (bpList->GetBPDrumZPosition()-bpList->GetBPIPZLength()); 
    // MakeSolid ---------------
    G4String ipconename( GetName() );
    ipconename += ".ipcone";
    G4VSolid *ipcone = new G4Cons( ipconename, rmin1,rmax1,rmin2,rmax2,
				   zlen/2., 0, 2*M_PI); 
    Register(ipcone);
    SetSolid(ipcone);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(bpList->GetBPIPMaterial()));
    
    // SetVisAttribute ---------------
    PaintLV(bpList->GetBPVisAtt(), bpList->GetBPColor());
  	
    // Install daughter PV -----------
  }     
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRBPBeCone::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRBPBeCone::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 
  // Mother BPCone. Translation is needless.
  //position->setZ(_BPZLEN_IP_+(_BPZPOS_DRUM_-_BPZLEN_IP_)/2.);
  return *position;
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRBPBeCone::Cabling()
{
}

//* Draw  --------------------------------------------------------
void J4IRBPBeCone::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRBPBeCone::Print() const
{
}

	
	

