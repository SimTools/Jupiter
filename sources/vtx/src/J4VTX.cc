// $Id$
//*************************************************************************
//* --------------------
//* J4VTX
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VTX.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4VTX::fFirstName("VTX");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4VTX::J4VTX(J4VDetectorComponent *parent ,
                            G4int  nclones,
                            G4int  nbrothers, 
                            G4int  me,
                            G4int  copyno ) :
       J4VVTXDetectorComponent( fFirstName, parent, 1,1,0,copyno)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTX::~J4VTX()
{
  if (fLayers) {  
    G4int i; 
    for (i = 0; i < NLAYER ; i++) {
     if(Deregister(fLayers[i])) delete fLayers [i];
    }
    if (Deregister(fLayers)) delete [] fLayers;
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTX::Assemble() 
{   
  if(!GetLV()){

    //--- Assemble Master volume for VTX ----
    G4double rmin = VTXMASTER_INNER_R;
    G4double rmax = VTXMASTER_OUTER_R;
    G4double len  = VTXMASTER_Z/2.;
    G4double dphi = VTXMASTER_PHI;
 	
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi);
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(_MASTERMATERIAL_));
    // SetVisAttribute ----//
    PaintLV(_VTXVISATT_, G4Color(0, 0, 0));
  	

    // Install daughter PV //
    // Install Layer       //
    fLayers = new J4VTXLayer* [NLAYER];
    Register(fLayers);
    for (G4int i = 0; i < NLAYER ; i++) {
      fLayers[i] = new J4VTXLayer(this,NLAYER , i );
      Register(fLayers[i]);
      fLayers[i]->InstallIn(this);  
      SetDaughter(fLayers[i]);
      fLayers[i]->Print();
    }  
    Print();
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VTX::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VTX::InstallIn(J4VComponent         *mother,
                      G4RotationMatrix     *prot, 
                      const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}


//* Draw  --------------------------------------------------------
void J4VTX::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4VTX::Print() const
{
    G4double rmin = VTXMASTER_INNER_R;
    G4double rmax = VTXMASTER_OUTER_R;
    G4double len  = VTXMASTER_Z;
    //G4double dphi = VTXMASTER_PHI;
    G4cout << "VTX Master Volume " << G4endl;
    G4cout << "Rmin " << rmin/mm << " Rmax " << rmax/mm<<" Z"<< len/mm<< G4endl;
}

	
	

