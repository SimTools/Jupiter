// $Id$
//*************************************************************************
//* --------------------
//* J4CTOuterCylinder
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CTOuterCylinder.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CTOuterCylinder::fFirstName("OuterCylinder");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CTOuterCylinder::J4CTOuterCylinder(G4double rmin,
				 G4double rmax,
				 G4double len,
				 G4double totalphi,
				 J4VDetectorComponent *parent,
                                 G4int  nclones,
                                 G4int  nbrothers, 
                                 G4int  me,
                                 G4int  copyno ) :
                 J4VCTDetectorComponent( fFirstName, parent, nclones,
  					  nbrothers, me, copyno  ),
                 fRmin(rmin), fRmax(rmax), fLen(len), fTotalPhi(totalphi)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CTOuterCylinder::~J4CTOuterCylinder()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CTOuterCylinder::Assemble() 
{   
   if(!GetLV()){
      J4CTParameterList *list = OpenParameterList();
      // MakeSolid ----------//
      OrderNewTubs (fRmin, fRmax, fLen, fTotalPhi);
    
      // MakeLogicalVolume --//
      G4String material = list->GetOuterCylinderMaterial();
      MakeLVWith(OpenMaterialStore()->Order(material));
    
       // SetVisAttribute ----//
      PaintLV(list->GetSupportTubVisAtt(), 
              list->GetSupportTubColor());
  	
      // Install daughter PV //

      // * No Daughter!! 
       
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CTOuterCylinder::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CTOuterCylinder::InstallIn(J4VComponent       * /* mother */,
                                G4RotationMatrix     * /* prot   */, 
                                const G4ThreeVector  & /* tlate  */) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}

//* Draw  --------------------------------------------------------
void J4CTOuterCylinder::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CTOuterCylinder::Print() const
{
}

	
	

