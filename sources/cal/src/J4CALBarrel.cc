// $Id$
//*************************************************************************
//* --------------------
//* J4CALBarrel
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALBarrel.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CALBarrel::fFirstName("Barrel");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALBarrel::J4CALBarrel(J4VDetectorComponent *parent,
                                        G4int  nclones,
                                        G4int  nbrothers, 
                                        G4int  me,
                                        G4int  copyno ) :
             J4VCALDetectorComponent( fFirstName, parent, nclones,
                                      nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALBarrel::~J4CALBarrel()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALBarrel::Assemble() 
{   
  if(!GetLV()){
  	
    G4double rmin = _CALBARRELIR_;
    G4double rmax = _CALBARRELOR_;
    G4double len  = _CALBARRELLEN_;
    G4double dphi = _CALBARRELDPHI_;
  	
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(_CALMATERIAL_));
    
    G4cerr << "J4CALBarrel::LogicalVolumePtr " << GetLV() << G4endl;
    
    // SetVisAttribute ----//
    PaintLV(_CALBARRELVISATT_, G4Color(1, 1, 0));
  }
  	
    // Install daughter PV //
  		  
      
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALBarrel::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALBarrel::InstallIn(J4VComponent         *mother,
                            G4RotationMatrix     *prot, 
                            const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}


//* Draw  --------------------------------------------------------
void J4CALBarrel::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CALBarrel::Print() const
{
}

	
	



