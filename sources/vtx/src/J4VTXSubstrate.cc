// $Id$
//*************************************************************************
//* --------------------
//* J4VTXSubstrate
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VTXSubstrate.hh"
#include "G4Box.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4VTXSubstrate::fFirstName("Substrate");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4VTXSubstrate::J4VTXSubstrate(J4VDetectorComponent* parent):
  	   J4VVTXDetectorComponent(fFirstName, parent, 1,1, 0, -1),
           fDxyzSubstrate(0), fxyzSubstrate(0)

{   
  // Define Substrate parameters ----------------//    
  fDxyzSubstrate = new G4ThreeVector(DXYZ_SUBSTRATE);
  Register(fDxyzSubstrate);
  fxyzSubstrate  = new G4ThreeVector(XYZ_SUBSTRATE);
  Register(fxyzSubstrate);
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXSubstrate::~J4VTXSubstrate()
{
  if (Deregister(fDxyzSubstrate)) delete fDxyzSubstrate;
  if (Deregister(fxyzSubstrate))  delete fxyzSubstrate;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTXSubstrate::Assemble() 
{   
  if(!GetLV())
  {	  
    // define geometry
    // MakeSolid ----------//
    G4VSolid *solid = new G4Box(GetName(),fDxyzSubstrate->x()/2.,
		                 fDxyzSubstrate->y()/2.,
		                 fDxyzSubstrate->z()/2.);
    Register(solid);
    SetSolid(solid);

    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()-> Order(_SUBSTRATEMATERIAL_));
    // SetVisAttribute ----//
    PaintLV( _SUBSTRATEVISATT_ , G4Color(0.5,0.,0.5));    

    SetMaxAllowedStep(0.001*mm);
        
    // Install daughter PV //
    // Install Substrate      //
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VTXSubstrate::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VTXSubstrate::InstallIn(J4VComponent         *mother,
                               G4RotationMatrix     *prot, 
                               const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//
  SetPVPlacement(prot, *fxyzSubstrate);
}


//* Draw  --------------------------------------------------------
void J4VTXSubstrate::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4VTXSubstrate::Print() const
{
  G4cout << "-J4VTXSubstrate(mm)-  " <<G4endl;
  G4cout << "dx " << fDxyzSubstrate->x()/mm 
       << " dy "<< fDxyzSubstrate->y()/mm 
       << " dz "<< fDxyzSubstrate->z()/mm 
       << G4endl;
  G4cout << "x " << fxyzSubstrate->x()/mm 
       << " y "<< fxyzSubstrate->y()/mm 
       << " z "<< fxyzSubstrate->z()/mm 
       << G4endl;
  G4cout << "----------------" << G4endl;
  
}
