//*************************************************************************
//* --------------------
//* J4TPCEndcap
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4TPCEndcap.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4TPCEndcap::fFirstName("Endcap");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4TPCEndcap::J4TPCEndcap(J4VDetectorComponent *parent,
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

J4TPCEndcap::~J4TPCEndcap()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4TPCEndcap::Assemble() 
{   
  if(!GetLV()){
    J4TPCParameterList *list = OpenParameterList();
     
    G4double rmin = list->GetEndcapInnerR();
    G4double rmax = list->GetEndcapOuterR();
    G4double len  = list->GetEndcapHalfThick();
    G4double dphi = list->GetEndcapDeltaPhi();
  	
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi);
    
    // MakeLogicalVolume --//
    G4String material = list->GetEndcapMaterial();  
    MakeLVWith(OpenMaterialStore()->Order(material));
        
    // SetVisAttribute ----//
    PaintLV(list->GetEndcapVisAtt(), list->GetEndcapColor());
  }
  	
    // Install daughter PV //
  		  
      
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4TPCEndcap::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4TPCEndcap::InstallIn(J4VComponent         *,
                            G4RotationMatrix     *,
                            const G4ThreeVector  &)
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  G4double z = OpenParameterList()->GetTPCHalfZ() / 2 -
               OpenParameterList()->GetEndcapHalfThick();  
               
  G4ThreeVector tlate(0., 0., z ) ;
  SetPVPlacement(0, tlate); 
  
}

//* Draw  --------------------------------------------------------
void J4TPCEndcap::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4TPCEndcap::Print() const
{
}

