// $Id$
//*************************************************************************
//* --------------------
//* J4CAL
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CAL.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CAL::fFirstName("CAL");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CAL::J4CAL(J4VDetectorComponent *parent,
                            G4int  nclones,
                            G4int  nbrothers, 
                            G4int  me,
                            G4int  copyno ) :
       J4VCALDetectorComponent(fFirstName, parent, nclones,
                               nbrothers, me, copyno),
  		fBarrel(0), fEndcaps(0)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CAL::~J4CAL()
{
  if (Deregister(fBarrel)) delete fBarrel;
  if (fEndcaps)
  {
 	 G4int i;
 	 G4int calnum = _CALENDCAPNUM_ ;
 	 for (i=0; i < calnum ; i++) {
  		if (Deregister(fEndcaps[i])) delete fEndcaps[i];
  	 }
  	 if (Deregister(fEndcaps)) delete [] fEndcaps;
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CAL::Assemble() 
{   
  if(!GetLV()){
  	
    G4double rmin = _CALIR_;
    G4double rmax = _CALOR_;
    G4double len  = _CALLEN_;
    G4double dphi = _CALDPHI_;
    G4double endcapthickness = (_CALLEN_ - _CALFRONTZ_) / 2. ;
    G4double endcaprmin      = _CALENDCAPIR_ ;
  	
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi, endcapthickness, endcaprmin);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(_CALMATERIAL_));
    
    // SetVisAttribute ----//
    PaintLV(_CALVISATT_, G4Color(1, 1, 0));
  	
    // Install daughter PV //
  		  
    fBarrel = new J4CALBarrel(this, 1, 1, 0 );
    Register(fBarrel);
    fBarrel->InstallIn(this);
    SetDaughter(fBarrel);
    
    G4int i;
    G4int nendcaps = _CALENDCAPNUM_ ;
    fEndcaps = new J4CALEndcap* [nendcaps];
    Register(fEndcaps);
    for(i=0; i<nendcaps; i++)
    {
   	 fEndcaps[i] = new J4CALEndcap(this, 1, nendcaps, i );
         Register(fEndcaps[i]);
  	 fEndcaps[i] ->InstallIn(this);
  	 SetDaughter(fEndcaps[i]);
    } 
    
  }
      
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CAL::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CAL::InstallIn(J4VComponent         *mother,
                      G4RotationMatrix     *prot, 
                      const G4ThreeVector  &tlate )
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}


//* Draw  --------------------------------------------------------
void J4CAL::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CAL::Print() const
{
}

	
	


