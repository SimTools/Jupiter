// $Id$
//*************************************************************************
//* --------------------
//* J4CALEndcap
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALEndcap.hh"
#include "J4CALParameter.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CALEndcap::fFirstName("Endcap");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALEndcap::J4CALEndcap(J4VDetectorComponent *parent,
                                        G4int  nclones,
                                        G4int  nbrothers, 
                                        G4int  me,
                                        G4int  copyno ) :
J4VCALDetectorComponent( fFirstName, parent, nclones,
  			 nbrothers, me, copyno ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALEndcap::~J4CALEndcap()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALEndcap::Assemble() 
{   
  if(!GetLV()){
  	
    G4double rmin = _CALENDCAPIR_;
    G4double rmax = _CALENDCAPOR_;
    G4double len  = _CALENDCAPLEN_;
    G4double dphi = _CALENDCAPDPHI_;
  	
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(_CALMATERIAL_));
    
    G4cerr << "J4CALEndcap::LogicalVolumePtr " << GetLV() << G4endl;
    
    // SetVisAttribute ----//
    PaintLV(_CALENDCAPVISATT_, G4Color(1, 0, 1));
  }
  	
    // Install daughter PV //
  		  
      
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALEndcap::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALEndcap::InstallIn(J4VComponent         *mother,
                            G4RotationMatrix     *prot, 
                            const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  G4double z = _CALENDCAPFRONTZ_ + _CALENDCAPLEN_;
  
  if (GetMyID() == 0) 
  {
  	G4ThreeVector tlate(0., 0., z ) ;
  	SetPVPlacement(0, tlate);
  }
  else if (GetMyID() == 1)
  {
  	G4ThreeVector tlate(0., 0., -1 * z) ;
  	SetPVPlacement(0, tlate);
  }	  	
  
}

//* Draw  --------------------------------------------------------
void J4CALEndcap::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CALEndcap::Print() const
{
}

	
	

