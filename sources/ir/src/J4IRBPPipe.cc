// $Id$
//*************************************************************************
//* --------------------
//* J4IRBPPipe
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRBPPipe.hh"
#include "J4IRBPParameterList.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBPPipe::fName("IRBPPipe");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBPPipe::J4IRBPPipe(J4VAcceleratorComponent *parent,
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

J4IRBPPipe::~J4IRBPPipe()
{
  if( Deregister(fpipe) ) delete fpipe;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBPPipe::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRBPParameterList *bpList=new J4IRBPParameterList(OpenParameterList());
    G4double rmax =  bpList->GetBPIPRadius()+bpList->GetBPIPThick();
    G4double zlen   =  bpList->GetBPIPZLength();

    // MakeSolid ---------------
    G4String iptubename( GetName() );
    iptubename += ".PipeTube";
    G4VSolid *iptube = new G4Tubs( iptubename, 0,rmax,zlen, 0, 2*M_PI);  

    Register(iptube);
    SetSolid(iptube);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order("vacuum"));
    
    // SetVisAttribute ---------------
    //PaintLV(bpList->GetBPVisAtt(), bpList->GetBPColor());
    PaintLV(FALSE, bpList->GetBPColor());
  	
    // Install daughter PV -----------
    fpipe = new J4IRBPBePipe(this,1,1,0,-1);
    Register(fpipe);
    fpipe->InstallIn(this);
    SetDaughter(fpipe);

  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRBPPipe::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4IRBPPipe::InstallIn(J4VComponent         *, // mother
                           G4RotationMatrix     *, // prot
                           const G4ThreeVector  &) // tlate
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}


//* Draw  --------------------------------------------------------
void J4IRBPPipe::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRBPPipe::Print() const
{
}

	
	

