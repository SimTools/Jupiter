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
//*	2002/11/20  T.Aso       ParameterList.
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
                                    me, copyno)
{   
  // Define Pixel parameters ----------------//    
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXPixel::~J4VTXPixel()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTXPixel::Assemble() 
{   
  if (!GetLV())
  {	  
    // define geometry
    J4VTXParameterList* list = OpenParameterList();
    G4ThreeVector dxyzPixel = list->GetPixelSize();
    cout << " Pixel  size " << dxyzPixel << endl;      
    // MakeSolid ----------//
    G4VSolid *solid = new G4Box(GetName(),
				 dxyzPixel.x()/2.,
		                 dxyzPixel.y()/2.,
		                 dxyzPixel.z()/2.);
    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()-> Order(list->GetPixelAreaMaterial()));
    
    // SetVisAttribute ----//
    PaintLV(list->GetPixelVisAtt(),list->GetPixelAreaColor());    

    SetMaxAllowedStep(list->GetMaxAllowedStep());
        
    // Install daughter PV //
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VTXPixel::Cabling()
{
  if(!GetLV()) Assemble();

  if ( OpenParameterList()->IsPixelSD()){
    J4VTXPixelSD* sd = new J4VTXPixelSD(this);
    Register(sd);
    SetSD(sd);
  }
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
  SetPVReplica(kXAxis,OpenParameterList()->GetPixelSize().x());

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
}


