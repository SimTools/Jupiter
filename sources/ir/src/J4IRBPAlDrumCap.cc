// $Id$
//*************************************************************************
//* --------------------
//* J4IRBPAlDrumCap
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13 T.Aso	Original version.
//*************************************************************************

#include "J4IRBPAlDrumCap.hh"
#include "J4IRBPParameterList.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBPAlDrumCap::fName("IRBPAlDrumCap");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBPAlDrumCap::J4IRBPAlDrumCap(J4VAcceleratorComponent *parent,
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

J4IRBPAlDrumCap::~J4IRBPAlDrumCap()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBPAlDrumCap::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRBPParameterList* bpList=new J4IRBPParameterList(OpenParameterList());
    G4double rmin = bpList->GetBPDrumcapRadius();
    G4double rmax = bpList->GetBPDrumcapRadius()+bpList->GetBPDrumcapThick();
    G4double zlen = bpList->GetBPDrumcapZLength();
    
    // MakeSolid ---------------
    G4String drumcapname( GetName() );
    drumcapname += ".drumcap";
    G4VSolid *drumcap = new G4Tubs( drumcapname,rmin,rmax,zlen/2.,0, 2*M_PI);
    Register(drumcap);
    SetSolid(drumcap);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(bpList->GetBPSTDMaterial()));
    
    // SetVisAttribute ---------------
    PaintLV(bpList->GetBPVisAtt(), bpList->GetBPColor());
  	
    // Install daughter PV -----------
    
  		  
  }     
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRBPAlDrumCap::Cabling()
{
}

//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRBPAlDrumCap::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRBPAlDrumCap::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 
  J4IRBPParameterList* bpList = new J4IRBPParameterList(OpenParameterList());
  G4double zpos = 
    (bpList->GetBPDrumZLength()+bpList->GetBPDrumcapZLength())/2.
    - bpList->GetBPDrumcapZLength()/2.;
  //position->setZ((_BPZLEN_DRUM_+_BPZLEN_DRUMCAP_)/2.-_BPZLEN_DRUMCAP_/2.);
  position->setZ(zpos);  
  return *position;
}

//* Draw  --------------------------------------------------------
void J4IRBPAlDrumCap::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRBPAlDrumCap::Print() const
{
}
