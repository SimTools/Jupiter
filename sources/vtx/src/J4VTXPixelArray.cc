// $Id$
//*************************************************************************
//* --------------------
//* J4VTXPixelArray
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VTXPixelArray.hh"
#include "G4Box.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4VTXPixelArray::fFirstName("PixelArray");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4VTXPixelArray::J4VTXPixelArray(J4VDetectorComponent *parent,
                       G4int                 nclones,
                       G4int                 nbrothers,
                       G4int                 me,
                       G4int                 copyno )
  	   :J4VVTXDetectorComponent(fFirstName, parent, nclones, nbrothers,
                                    me, copyno), 
            fDxyzPixelArray(0), fPixel(0) 
{   
  // Define PixelArray parameters ----------------//    
  fDxyzPixelArray = new G4ThreeVector(DXYZ_PIXELAREA.x(),
                                      DXYZ_PIXELAREA.y(),
                                      ZPIXELSIZE);
  Register(fDxyzPixelArray);
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXPixelArray::~J4VTXPixelArray()
{
  if (Deregister(fDxyzPixelArray)) delete fDxyzPixelArray;
  if (Deregister(fPixel))          delete fPixel;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTXPixelArray::Assemble() 
{   
  if (!GetLV())
  {	  
    // define geometry
      
    // MakeSolid ----------//
    G4VSolid *solid = new G4Box(GetName(),fDxyzPixelArray->x()/2.,
		                 fDxyzPixelArray->y()/2.,
		                 fDxyzPixelArray->z()/2.);
    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()-> Order(_PIXELAREAMATERIAL_));
    
    // SetVisAttribute ----//
    PaintLV( _PIXELAREAVISATT_ , G4Color(0.0,0.0,0.0));    

    SetMaxAllowedStep(0.001*mm);
        
    // Install daughter PV //
    // Install PixelArray      //

    fPixel = new J4VTXPixel(this, NXPIXEL);
    Register(fPixel);
    fPixel->InstallIn(this);
    SetDaughter(fPixel);

  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VTXPixelArray::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VTXPixelArray::InstallIn(J4VComponent         *mother,
                                G4RotationMatrix     *prot, 
                                const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//
  SetPVReplica(kZAxis, ZPIXELSIZE);

  if (!GetSD()) Cabling(); 
  
}


//* SwitchOn  --------------------------------------------------------
void J4VTXPixelArray::SwitchOn(G4String opt)
{
  J4VDetectorComponent::SwitchOn(opt);
}

//* SwitchOff  --------------------------------------------------------
void J4VTXPixelArray::SwitchOff(G4String opt)
{
  J4VDetectorComponent::SwitchOff(opt);
}

//* Draw  --------------------------------------------------------
void J4VTXPixelArray::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4VTXPixelArray::Print() const
{
  G4cout << "-J4VTXPixelArray(mm)-  " <<G4endl;
  G4cout << "dx " << fDxyzPixelArray->x()/mm 
       << " dy "<< fDxyzPixelArray->y()/mm 
       << " dz "<< fDxyzPixelArray->z()/mm 
       << G4endl;
  G4cout << "----------------" << G4endl;
  
}
