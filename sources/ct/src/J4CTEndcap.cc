// $Id$
//*************************************************************************
//* --------------------
//* J4CTEndcap
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CTEndcap.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CTEndcap::fFirstName("Endcap");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CTEndcap::J4CTEndcap(J4VDetectorComponent *parent,
                                        G4int  nclones,
                                        G4int  nbrothers, 
                                        G4int  me,
                                        G4int  copyno ) :
             J4VCTDetectorComponent( fFirstName, parent, nclones,
                                      nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CTEndcap::~J4CTEndcap()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CTEndcap::Assemble() 
{   
  if(!GetLV()){
     J4CTParameterList *list = OpenParameterList();
     
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
    PaintLV(list->GetSupportTubVisAtt(), list->GetSupportTubColor());
  }
  	
    // Install daughter PV //
  		  
      
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CTEndcap::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CTEndcap::InstallIn(J4VComponent         *mother,
                            G4RotationMatrix     *prot, 
                            const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  G4double z = OpenParameterList()->GetCTHalfZ() -
               OpenParameterList()->GetEndcapHalfThick();  
               
  if (GetMyID() == 0) 
  {
  	G4ThreeVector tlate(0., 0., z ) ;
  	SetPVPlacement(0, tlate); 
  }
  else if (GetMyID() == 1)
  {
  	G4ThreeVector tlate(0., 0., -1 * z) ;
  	SetPVPlacement(0, tlate);
  }	  	
  
}

//* Draw  --------------------------------------------------------
void J4CTEndcap::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CTEndcap::Print() const
{
}

	
	



