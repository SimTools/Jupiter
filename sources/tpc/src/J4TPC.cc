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

#if 0
    for (G4int i = 0; i < 2; i++) {
      fTPCHalfs [i] = new J4TPCHalf(this, 1, 2, i);
      Register(fTPCHalfs[i]);
      fTPCHalfs [i]->InstallIn(this);
      SetDaughter(fTPCHalfs[i]);
    }  
#else
    // Create positive Z half first

    fTPCHalfs [0] = new J4TPCHalf(this, 1, 1, 0, 0);
    Register(fTPCHalfs[0]);
    G4ThreeVector tlatepz(0., 0., +0.5 * len); 
    fTPCHalfs [0]->InstallIn(this, 0, tlatepz);
    SetDaughter(fTPCHalfs[0]);

    // Then create negative Z half as a copy
    // Make sure that the original has been InstalledIn before
    // making a copy, or the copy will have no parts in it

    fTPCHalfs [1] = new J4TPCHalf(*fTPCHalfs[0], 1);
    Register(fTPCHalfs[1]);
    G4ThreeVector tlatemz(0., 0., -0.5 * len); 
    G4RotationMatrix *rotp = new G4RotationMatrix();
    G4ThreeVector xv(1., 0., 0);
    G4ThreeVector yv(0.,-1., 0);
    G4ThreeVector zv(0., 0.,-1);
    rotp->rotateAxes(xv, yv, zv);
    fTPCHalfs [1]->InstallIn(this, rotp, tlatemz);
    SetDaughter(fTPCHalfs[1]);
#endif
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
