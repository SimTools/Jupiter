//*************************************************************************
//* --------------------
//* J4TPC
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4TPC.hh"
#include "J4TPCParameterList.hh"
#include "J4VTPCDetectorComponent.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4TPC::fFirstName("TPC");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4TPC::J4TPC(J4VDetectorComponent *parent,
                            G4int  nclones,
                            G4int  nbrothers, 
                            G4int  me,
                            G4int  copyno ) :
       J4VTPCDetectorComponent( fFirstName, parent, nclones,
                                nbrothers, me, copyno ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4TPC::~J4TPC()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4TPC::Assemble() 
{   
  if(!GetLV()){
  	
    J4TPCParameterList *list = OpenParameterList(); 
    G4double rmin = list->GetTPCInnerR(); 
    G4double rmax = list->GetTPCOuterR();
    G4double len  = list->GetTPCHalfZ();
    G4double dphi = list->GetTPCDeltaPhi();
  	
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(list->GetTPCMaterial()));
    
    // SetVisAttribute ----//
    PaintLV(list->GetTPCVisAtt(), list->GetTPCColor());
  	
    // Install daughter PV //
    // Install TPCHalf
                                                                               
    fTPCHalfs = new J4TPCHalf* [2];
    Register(fTPCHalfs);

    for (G4int i = 0; i < 2; i++) {
      fTPCHalfs [i] = new J4TPCHalf(this, 1, 2, i);
      Register(fTPCHalfs[i]);
      fTPCHalfs [i]->InstallIn(this);
      SetDaughter(fTPCHalfs[i]);
    }  

  }
}



//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4TPC::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4TPC::InstallIn(J4VComponent        *,
                      G4RotationMatrix    *,
                      const G4ThreeVector &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}



//* Draw  --------------------------------------------------------
void J4TPC::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4TPC::Print() const
{
}
