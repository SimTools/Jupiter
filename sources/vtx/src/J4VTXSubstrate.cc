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
//*	2002/11/19  T.Aso       ParameterList
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
  	   J4VVTXDetectorComponent(fFirstName, parent, 1,1, 0, -1)

{   
  // Define Substrate parameters ----------------//    
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXSubstrate::~J4VTXSubstrate()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTXSubstrate::Assemble() 
{   
  if(!GetLV())
  {	  
    // define geometry
    J4VTXParameterList* list = OpenParameterList();
    G4ThreeVector dxyzSubstrate = list->GetSubstrateSize();

    // MakeSolid ----------//
    G4VSolid *solid = new G4Box(GetName(),dxyzSubstrate.x()/2.,
		                 dxyzSubstrate.y()/2.,
		                 dxyzSubstrate.z()/2.);
    Register(solid);
    SetSolid(solid);

    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(list->GetSubstrateMaterial()));
    // SetVisAttribute ----//
    PaintLV(list->GetSubstrateVisAtt(),list->GetSubstrateColor());    

    SetMaxAllowedStep(list->GetMaxAllowedStep());
        
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

void J4VTXSubstrate::InstallIn(J4VComponent         * /* mother */,
                               G4RotationMatrix     *prot, 
                               const G4ThreeVector  & /* tlate  */) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  G4ThreeVector xyzSubstrate  = OpenParameterList()->GetSubstratePosition();  
  // Placement function into mother object ------//
  SetPVPlacement(prot, xyzSubstrate);
}


//* Draw  --------------------------------------------------------
void J4VTXSubstrate::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4VTXSubstrate::Print() const
{
}
