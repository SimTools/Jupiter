// $Id$
//*************************************************************************
//* --------------------
//* J4IRBPCone
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRBPCone.hh"
#include "J4IRBPParameterList.hh"

#include "G4Cons.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBPCone::fName("IRBPCone");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBPCone::J4IRBPCone(J4VAcceleratorComponent *parent,
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

J4IRBPCone::~J4IRBPCone()
{
  if(Deregister(fcone)) delete fcone;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBPCone::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRBPParameterList* bpList = J4IRBPParameterList::GetInstance();
    G4double rmax1 = bpList->GetBPIPRadius()+bpList->GetBPIPThick();
    G4double rmax2 = bpList->GetBPDrumRadius()+bpList->GetBPDrumThick();
    G4double zlen  = bpList->GetBPDrumZPosition()-bpList->GetBPIPZLength();
  	
    std::cout << " J4IRBPCone. " << std::endl;
    std::cout << " IPRadius=" << bpList->GetBPIPRadius() ;
    std::cout << " IPThick=" << bpList->GetBPIPThick();
    std::cout << " DrumRadius=" << bpList->GetBPDrumRadius() ;
    std::cout << " DrumThick=" << bpList->GetBPDrumThick();
    std::cout << std::endl;
    std::cout << " DrumZPosition=" << bpList->GetBPDrumZPosition() ;
    std::cout << " IPZLength=" << bpList->GetBPIPZLength();
    std::cout << std::endl;
    std::cout << " rmax=" << rmax1 << " rmax2=" << rmax2 ;
    std::cout << " zlen=" << zlen << std::endl;

    // MakeSolid ---------------
    G4String ipconename( GetName() );
    ipconename += ".ipcone";
    G4VSolid *ipcone = new G4Cons( ipconename, 
					0.,
				   rmax1,
					0.,
				   rmax2,
				   zlen/2.,
					0, 2*M_PI); 
    Register(ipcone);
    SetSolid(ipcone);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order("vacuum"));
    
    // SetVisAttribute ---------------
    PaintLV(FALSE, G4Color(0, 0.5, 0.5));
  	
    // Install daughter PV -----------
    fcone = new J4IRBPBeCone(this,1,1,0,-1);
    Register(fcone);
    fcone->InstallIn(this);
    SetDaughter(fcone);
  }     
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRBPCone::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRBPCone::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 
  J4IRBPParameterList* bpList = J4IRBPParameterList::GetInstance();
  G4double zpos = bpList->GetBPIPZLength()
    +(bpList->GetBPDrumZPosition() - bpList->GetBPIPZLength())/2.;
    //position->setZ(_BPZLEN_IP_+(_BPZPOS_DRUM_-_BPZLEN_IP_)/2.);
    position->setZ(zpos);
  return *position;
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRBPCone::Cabling()
{
}

//* Draw  --------------------------------------------------------
void J4IRBPCone::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRBPCone::Print() const
{
}

	
	

