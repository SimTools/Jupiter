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
//*	2002/11/19  T.Aso       ParameterList.
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
  	   J4VVTXDetectorComponent(fFirstName, parent, 1,1, 0, -1)
{   
  // Define Epitaxial parameters ----------------//    
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXEpitaxial::~J4VTXEpitaxial()
{
  if (Deregister(fPixelArea))     delete fPixelArea;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTXEpitaxial::Assemble() 
{   
  if(!GetLV())
  {	  
    // define geometry
    J4VTXParameterList* list = OpenParameterList();
    G4ThreeVector dxyzEpitaxial = list->GetEpitaxialSize();
    G4ThreeVector xyzEpitaxial  = list->GetEpitaxialPosition();
      
    // MakeSolid ----------//
    G4VSolid *solid =  new G4Box(GetName(),dxyzEpitaxial.x()/2.,
		                 dxyzEpitaxial.y()/2.,
		                 dxyzEpitaxial.z()/2.);
    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()-> Order(list->GetEpitaxialMaterial()));
    
    // SetVisAttribute ----//
    PaintLV( list->GetEpitaxialVisAtt() , list->GetEpitaxialColor());    

    SetMaxAllowedStep(list->GetMaxAllowedStep());
        
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

void J4VTXEpitaxial::InstallIn(J4VComponent         * /* mother */,
                               G4RotationMatrix     *prot, 
                               const G4ThreeVector  & /* tlate  */) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				//

  // Placement function into mother object ------//
  SetPVPlacement(prot,OpenParameterList()->GetEpitaxialPosition());

}

//* Draw  --------------------------------------------------------
void J4VTXEpitaxial::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4VTXEpitaxial::Print() const
{
}




