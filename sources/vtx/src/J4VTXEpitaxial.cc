// $Id$
//*************************************************************************
//* --------------------
//* J4VTXEpitaxial
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VTXEpitaxial.hh"
#include "G4Box.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4VTXEpitaxial::fFirstName("Epitaxial");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4VTXEpitaxial::J4VTXEpitaxial(J4VDetectorComponent* parent):
  	   J4VVTXDetectorComponent(fFirstName, parent, 1,1, 0, -1),
           fPixelArea(0), fDxyzEpitaxial(0), fxyzEpitaxial(0)

{   
  // Define Epitaxial parameters ----------------//    
  fDxyzEpitaxial = new G4ThreeVector(DXYZ_EPITAXIAL);
  Register(fDxyzEpitaxial);
  fxyzEpitaxial  = new G4ThreeVector(XYZ_EPITAXIAL);
  Register(fxyzEpitaxial);
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXEpitaxial::~J4VTXEpitaxial()
{
  if (Deregister(fPixelArea))     delete fPixelArea;
  if (Deregister(fDxyzEpitaxial)) delete fDxyzEpitaxial;
  if (Deregister(fxyzEpitaxial))  delete fxyzEpitaxial;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTXEpitaxial::Assemble() 
{   
  if(!GetLV())
  {	  
    // define geometry
      
    // MakeSolid ----------//
    G4VSolid *solid =  new G4Box(GetName(),fDxyzEpitaxial->x()/2.,
		                 fDxyzEpitaxial->y()/2.,
		                 fDxyzEpitaxial->z()/2.);
    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()-> Order(_EPITAXIALMATERIAL_));
    
    // SetVisAttribute ----//
    PaintLV( _EPITAXIALVISATT_ , G4Color(0.0,1.,0.0));    

    SetMaxAllowedStep(0.001*mm);
        
    // Install daughter PV //
    // Install PixelArea      //
    fPixelArea = new J4VTXPixelArea(this);
    Register(fPixelArea); 
    fPixelArea->InstallIn(this);  
    SetDaughter(fPixelArea);
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VTXEpitaxial::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VTXEpitaxial::InstallIn(J4VComponent         *mother,
                               G4RotationMatrix     *prot, 
                               const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//
  SetPVPlacement(prot,*fxyzEpitaxial);
}


//* Draw  --------------------------------------------------------
void J4VTXEpitaxial::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4VTXEpitaxial::Print() const
{
  G4cout << "-J4VTXEpitaxial(mm)  "<< G4endl;
  G4cout << "dx " << fDxyzEpitaxial->x()/mm 
       << " dy "<< fDxyzEpitaxial->y()/mm 
       << " dz "<< fDxyzEpitaxial->z()/mm 
       << G4endl;
  G4cout << "x " << fxyzEpitaxial->x()/mm 
       << " y "<< fxyzEpitaxial->y()/mm 
       << " z "<< fxyzEpitaxial->z()/mm 
       << G4endl;
  G4cout << "----------------" << G4endl;
  
}




