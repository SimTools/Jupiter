//*************************************************************************
//* --------------------
//* J4TPCLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4TPCLayer.hh"
#include "J4TPCLayerSD.hh"
#include "J4TPCParameterList.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4TPCLayer::fFirstName("Layer");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4TPCLayer::J4TPCLayer(J4VDetectorComponent* parent,
                                      G4int  nclones,
                                      G4int  nbrothers, 
                                      G4int  me,
                                      G4int  copyno ) :
  	    J4VTPCDetectorComponent(fFirstName, parent, nclones,
                                    nbrothers, me, copyno)
{   
}


//=====================================================================
//* destructor --------------------------------------------------------

J4TPCLayer::~J4TPCLayer()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4TPCLayer::Assemble() 
{   
  if(!GetLV())
  {	  
    // define geometry
    J4TPCParameterList * list = OpenParameterList();

    G4double rmin = list->GetLayerInnerR(GetMyID());
    G4double rmax = list->GetLayerOuterR(GetMyID());
    G4double len  = list->GetDriftRegionHalfZ();
    G4double dphi = list->GetLayerDeltaPhi();
      
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi);
    
    // MakeLogicalVolume --//  
      MakeLVWith(OpenMaterialStore()->Order(list->GetLayerMaterial()));

    // SetVisAttribute ----//
    PaintLV(list->GetLayerVisAtt() , list->GetLayerColor());    
        
    // Install daughter PV //
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4TPCLayer::Cabling()
{
  J4TPCLayerSD* sd = new J4TPCLayerSD(this);
  Register(sd);
  SetSD(sd);
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4TPCLayer::InstallIn(J4VComponent       *,
                          G4RotationMatrix    *,
                          const G4ThreeVector &tlate) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ... 
    SetPVPlacement(0, tlate);

  if (!GetSD()) Cabling(); 
  
}


//* Draw  --------------------------------------------------------
void J4TPCLayer::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4TPCLayer::Print() const
{
}

