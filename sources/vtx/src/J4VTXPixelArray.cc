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
//*	2002/11/20  T.Aso       ParameterList
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
            fPixel(0) 
{   
  // Define PixelArray parameters ----------------//    
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXPixelArray::~J4VTXPixelArray()
{
  if (Deregister(fPixel))          delete fPixel;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTXPixelArray::Assemble() 
{   
  if (!GetLV())
  {	  
    // define geometry
    J4VTXParameterList* list = OpenParameterList();
    G4ThreeVector dxyzPixelArray = list->GetPixelArraySize();
    cout << " Pixel Array size " << dxyzPixelArray << endl;
    // MakeSolid ----------//
    G4VSolid *solid = new G4Box(GetName(),
				 dxyzPixelArray.x()/2.,
		                 dxyzPixelArray.y()/2.,
		                 dxyzPixelArray.z()/2.);
    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()-> Order(list->GetPixelAreaMaterial()));
    
    // SetVisAttribute ----//
    PaintLV(list->GetPixelVisAtt(),list->GetPixelAreaColor());    

    SetMaxAllowedStep(list->GetMaxAllowedStep());
        
    // Install daughter PV //
    // Install PixelArray      //
#if 1
    fPixel = new J4VTXPixel(this, list->GetNxPixels());
    Register(fPixel);
    fPixel->InstallIn(this);
    SetDaughter(fPixel);
#endif
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
  SetPVReplica(kZAxis, OpenParameterList()->GetPixelArraySize().z());

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
}
