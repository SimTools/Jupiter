// $Id$
//*************************************************************************
//* --------------------
//* J4IRBPBePipe
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRBPBePipe.hh"
#include "J4IRBPParameterList.hh"

#include "G4Tubs.hh"
#include <math.h>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBPBePipe::fName("IRBPBePipe");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBPBePipe::J4IRBPBePipe(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno ) :
            J4VIRAcceleratorComponent( fName, parent, nclones,
                                    nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRBPBePipe::~J4IRBPBePipe()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBPBePipe::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRBPParameterList *bpList=new J4IRBPParameterList(OpenParameterList());
    G4double rin  = bpList->GetBPIPRadius();
    G4double rout = bpList->GetBPIPRadius()+bpList->GetBPIPThick();
    G4double zlen = bpList->GetBPIPZLength();
  	
    // MakeSolid ---------------
    G4String iptubename( GetName() );
    iptubename += ".BePipeTube";
    G4VSolid *iptube = new G4Tubs( iptubename, rin,rout,zlen, 0, 2*M_PI);  

    Register(iptube);
    SetSolid(iptube);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(bpList->GetBPIPMaterial()));
    
    // SetVisAttribute ---------------
    PaintLV(bpList->GetBPVisAtt(),bpList->GetBPColor());
  	
    // Install daughter PV -----------
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRBPBePipe::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4IRBPBePipe::InstallIn(J4VComponent *mother,
                             G4RotationMatrix     *prot, 
                             const G4ThreeVector  &tlate )
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}


//* Draw  --------------------------------------------------------
void J4IRBPBePipe::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRBPBePipe::Print() const
{
}

	
	

