// $Id$
//*************************************************************************
//* --------------------
//* J4VTXPixelArea
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2002/11/19  T.Aso       ParameterList.
//*************************************************************************

#include "J4VTXPixelArea.hh"
#include "J4VTXPixelAreaSD.hh"
#include "G4Box.hh"
// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4VTXPixelArea::fFirstName("PixelArea");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4VTXPixelArea::J4VTXPixelArea(J4VDetectorComponent* parent)
  	   :J4VVTXDetectorComponent(fFirstName, parent, 1,1, 0, -1) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXPixelArea::~J4VTXPixelArea()
{
  if (Deregister(fPixelArray)) delete fPixelArray; 
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTXPixelArea::Assemble() 
{   
  if (!GetLV())
  {	  
    // define geometry
    J4VTXParameterList* list = OpenParameterList();
    G4ThreeVector dxyzPixelArea = list->GetPixelAreaSize();
      
    // MakeSolid ----------//
    G4VSolid *solid = new G4Box(GetName(),dxyzPixelArea.x()/2.,
		                 dxyzPixelArea.y()/2.,
		                 dxyzPixelArea.z()/2.);
    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()-> Order(list->GetPixelAreaMaterial()));
    
    // SetVisAttribute ----//
    PaintLV(list->GetPixelAreaVisAtt(),list->GetPixelAreaColor());    

    SetMaxAllowedStep(list->GetMaxAllowedStep());
        
    // Install daughter PV //
    // Install PixelArea      //
#if 1  
    if ( !(OpenParameterList()->IsPixelAreaSD()) ){    
      fPixelArray = new J4VTXPixelArray(this,list->GetNzPixels());
      Register(fPixelArray); 
      fPixelArray->InstallIn(this);
      SetDaughter(fPixelArray);
    }
#endif
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VTXPixelArea::Cabling()
{
  if(!GetLV()) Assemble();

  if ( OpenParameterList()->IsPixelAreaSD()){
    J4VTXPixelAreaSD* sd = new J4VTXPixelAreaSD(this);
    Register(sd);
    SetSD(sd);
  }

}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VTXPixelArea::InstallIn(J4VComponent         *mother,
                               G4RotationMatrix     *prot, 
                               const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  // Placement function into mother object ------//
  SetPVPlacement(prot,OpenParameterList()->GetPixelAreaPosition());

  if (!GetSD()) Cabling(); 

}


//* SwitchOn  --------------------------------------------------------
void J4VTXPixelArea::SwitchOn(G4String opt)
{
  J4VDetectorComponent::SwitchOn(opt);
}

//* SwitchOff  --------------------------------------------------------
void J4VTXPixelArea::SwitchOff(G4String opt)
{
  J4VDetectorComponent::SwitchOff(opt);
}

//* Draw  --------------------------------------------------------
void J4VTXPixelArea::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4VTXPixelArea::Print() const
{
}
