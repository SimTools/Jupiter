// $Id$
//*************************************************************************
//* --------------------
//* J4IRBPAlDrum
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRBPAlDrum.hh"
#include "J4IRBPParameterList.hh"

#include "G4Tubs.hh"
#include <math.h>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBPAlDrum::fName("IRBPAlDrum");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBPAlDrum::J4IRBPAlDrum(J4VAcceleratorComponent *parent,
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

J4IRBPAlDrum::~J4IRBPAlDrum()
{
    if (Deregister(fdrumPipe)) delete fdrumPipe;
    if (Deregister(fdrumCap)) delete fdrumCap;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBPAlDrum::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRBPParameterList *bpList = new J4IRBPParameterList(OpenParameterList());
    G4double rmax = bpList->GetBPDrumRadius()+bpList->GetBPDrumThick();
    G4double zlen = bpList->GetBPDrumZLength()+bpList->GetBPDrumcapZLength();
    // MakeSolid ---------------
    G4String drumname( GetName() );
    drumname += ".drum";
    G4VSolid *drum = new G4Tubs( drumname, 
				   0,
				   rmax,
				   zlen/2., 
				   0, 2*M_PI);
    Register(drum);
    SetSolid(drum);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order("vacuum"));
    
    // SetVisAttribute ---------------
    PaintLV(FALSE, G4Color(0, 1, 1));
  	
    // Install daughter PV -----------
    fdrumPipe = new J4IRBPAlDrumPipe(this,1,1,1,-1);
    Register(fdrumPipe);
    fdrumPipe->InstallIn(this);
    SetDaughter(fdrumPipe);
    fdrumCap = new J4IRBPAlDrumCap(this,1,1,1,-1);
    Register(fdrumCap);
    fdrumCap->InstallIn(this);
    SetDaughter(fdrumCap);
  }     
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRBPAlDrum::Cabling()
{
}

//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRBPAlDrum::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRBPAlDrum::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 
  J4IRBPParameterList* bpList = new J4IRBPParameterList(OpenParameterList()); 
  G4double zpos = bpList->GetBPDrumZPosition()
    +( bpList->GetBPDrumZLength()+bpList->GetBPDrumcapZLength() )/2.;
  //position->setZ(_BPZPOS_DRUM_+ (_BPZLEN_DRUM_+_BPZLEN_DRUMCAP_)/2.);
  position->setZ(zpos);
  return *position;
}

//* Draw  --------------------------------------------------------
void J4IRBPAlDrum::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRBPAlDrum::Print() const
{
}
