// $Id$
//*************************************************************************
//* --------------------
//* J4CDCEndcap
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CDCEndcap.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CDCEndcap::fFirstName("Endcap");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CDCEndcap::J4CDCEndcap(J4VDetectorComponent *parent,
                                        G4int  nclones,
                                        G4int  nbrothers, 
                                        G4int  me,
                                        G4int  copyno ) :
             J4VCDCDetectorComponent( fFirstName, parent, nclones,
                                      nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CDCEndcap::~J4CDCEndcap()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CDCEndcap::Assemble() 
{   
  if(!GetLV()){
     J4CDCParameterList *list = OpenParameterList();
     
     G4double rmin = list->GetEndcapInnerR();
     G4double rmax = list->GetEndcapOuterR();
     G4double len  = list->GetEndcapHalfZ();
     G4double dphi = list->GetCDCDeltaPhi();
  	
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

void J4CDCEndcap::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CDCEndcap::InstallIn(J4VComponent         *mother,
                            G4RotationMatrix     *prot, 
                            const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  G4double z = OpenParameterList()->GetCDCHalfZ() -
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
void J4CDCEndcap::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CDCEndcap::Print() const
{
}

	
	



