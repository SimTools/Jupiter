// $Id$
//*************************************************************************
//* --------------------
//* J4VTXPixel
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VTXPixel.hh"
#include "J4VTXPixelSD.hh"
#include "G4Box.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4VTXPixel::fFirstName("Pixel");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4VTXPixel::J4VTXPixel(J4VDetectorComponent *parent,
                       G4int                 nclones,
                       G4int                 nbrothers,
                       G4int                 me,
                       G4int                 copyno )
  	   :J4VVTXDetectorComponent(fFirstName, parent, nclones, nbrothers,
                                    me, copyno), fDxyzPixel(0) 
{   
  // Define Pixel parameters ----------------//    
  fDxyzPixel = new G4ThreeVector(XPIXELSIZE, DXYZ_PIXELAREA.y(), ZPIXELSIZE);
  Register(fDxyzPixel);
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXPixel::~J4VTXPixel()
{
  if (Deregister(fDxyzPixel)) delete fDxyzPixel;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTXPixel::Assemble() 
{   
  if (!GetLV())
  {	  
    // define geometry
      
    // MakeSolid ----------//
    G4VSolid *solid = new G4Box(GetName(),fDxyzPixel->x()/2.,
		                 fDxyzPixel->y()/2.,
		                 fDxyzPixel->z()/2.);
    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()-> Order(_PIXELAREAMATERIAL_));
    
    // SetVisAttribute ----//
    PaintLV( _PIXELAREAVISATT_ , G4Color(0.0,0.0,0.0));    

    SetMaxAllowedStep(0.001*mm);
        
    // Install daughter PV //
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VTXPixel::Cabling()
{
  if(!GetLV()) Assemble();

  J4VTXPixelSD* sd = new J4VTXPixelSD(this);
  Register(sd);
  SetSD(sd);

}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VTXPixel::InstallIn(J4VComponent         *mother,
                           G4RotationMatrix     *prot, 
                           const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//
  SetPVReplica(kXAxis, XPIXELSIZE);

  if (!GetSD()) Cabling(); 
  
}


//* SwitchOn  --------------------------------------------------------
void J4VTXPixel::SwitchOn(G4String opt)
{
  J4VDetectorComponent::SwitchOn(opt);
}

//* SwitchOff  --------------------------------------------------------
void J4VTXPixel::SwitchOff(G4String opt)
{
  J4VDetectorComponent::SwitchOff(opt);
}

//* Draw  --------------------------------------------------------
void J4VTXPixel::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4VTXPixel::Print() const
{
  G4cout << "-J4VTXPixel(mm)-  " <<G4endl;
  G4cout << "dx " << fDxyzPixel->x()/mm 
       << " dy "<< fDxyzPixel->y()/mm 
       << " dz "<< fDxyzPixel->z()/mm 
       << G4endl;
  G4cout << "----------------" << G4endl;
  
}
