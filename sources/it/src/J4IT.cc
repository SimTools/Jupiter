// $Id$
//*************************************************************************
//* --------------------
//* J4IT
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4IT.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IT::fFirstName("IT");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IT::J4IT(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
      J4VITDetectorComponent( fFirstName, parent, nclones,
                              nbrothers, me, copyno ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IT::~J4IT()
{
	
  if (fLayers){	
    G4int i;  
    for (i = 0; i < _ITLAYERNLAYERS_ ; i++) {
     if(Deregister(fLayers[i])) delete fLayers [i];
    } 
    if (Deregister(fLayers)) delete [] fLayers;
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IT::Assemble() 
{   
  if(!GetLV()){
  	
    G4double rmin = _ITIR_;
    G4double rmax = _ITOR_;
    G4double len  = _ITLEN_;
    G4double dphi = _ITDPHI_;
  	
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(_ITMATERIAL_));
    
    // SetVisAttribute ----//
    PaintLV(_ITVISATT_, G4Color(1, 0, 0));
  	
    // Install daughter PV //
    // Install Layer       //
  		  
    fLayers = new J4ITLayer* [_ITLAYERNLAYERS_];
    Register(fLayers);
    G4int i;  
    for (i = 0; i < _ITLAYERNLAYERS_ ; i++) {
      fLayers [i] = new J4ITLayer(this,_ITLAYERNCLONES_ , _ITLAYERNLAYERS_ , i );
      Register(fLayers[i]);
      fLayers [i]->InstallIn(this);  
      
      SetDaughter(fLayers[i]);
    }  
      
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IT::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4IT::InstallIn(J4VComponent         *mother,
                     G4RotationMatrix     *prot, 
                     const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}



//* Draw  --------------------------------------------------------
void J4IT::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IT::Print() const
{
}

	
	
