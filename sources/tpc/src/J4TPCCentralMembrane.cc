//*************************************************************************
//* --------------------
//* J4TPCCentralMembrane
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4TPCCentralMembrane.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4TPCCentralMembrane::fFirstName("CentralMembrane");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4TPCCentralMembrane::J4TPCCentralMembrane(J4VDetectorComponent *parent,
                                           G4int  nclones,
                                           G4int  nbrothers, 
                                           G4int  me,
                                           G4int  copyno ) :
                      J4VTPCDetectorComponent( fFirstName, parent, nclones,
                                               nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4TPCCentralMembrane::~J4TPCCentralMembrane()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4TPCCentralMembrane::Assemble() 
{   
  if(!GetLV()){
     J4TPCParameterList *list = OpenParameterList();
     
     G4double rmin = list->GetCentralMembraneInnerR();
     G4double rmax = list->GetCentralMembraneOuterR();
     G4double len  = list->GetCentralMembraneHalfThick() / 2;
     G4double dphi = list->GetCentralMembraneDeltaPhi();
  	
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi);
    
    // MakeLogicalVolume --//
    G4String material = list->GetCentralMembraneMaterial();  
    MakeLVWith(OpenMaterialStore()->Order(material));
        
    // SetVisAttribute ----//
    PaintLV(list->GetCentralMembraneVisAtt(), list->GetCentralMembraneColor());
  }
  	
    // Install daughter PV //
  		  
      
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4TPCCentralMembrane::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4TPCCentralMembrane::InstallIn(J4VComponent         *,
                                     G4RotationMatrix     *,
                                     const G4ThreeVector  &)
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  G4double z = OpenParameterList()->GetTPCHalfZ() / 2 -
               OpenParameterList()->GetCentralMembraneHalfThick() / 2;
  
  G4ThreeVector tlate(0., 0., -z) ;
  SetPVPlacement(0, tlate); 
  
}

//* Draw  --------------------------------------------------------
void J4TPCCentralMembrane::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4TPCCentralMembrane::Print() const
{
}

