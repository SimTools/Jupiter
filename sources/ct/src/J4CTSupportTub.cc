// $Id$
//*************************************************************************
//* --------------------
//* J4CTSupportTub
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CTSupportTub.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CTSupportTub::fFirstName("SupportTub");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CTSupportTub::J4CTSupportTub(G4double rmin,
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

J4CTSupportTub::~J4CTSupportTub()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CTSupportTub::Assemble() 
{   
   if(!GetLV()){
      J4CTParameterList *list = OpenParameterList();
      // MakeSolid ----------//
      OrderNewTubs (fRmin, fRmax, fLen, fTotalPhi);
    
      // MakeLogicalVolume --//
      G4String material = list->GetSupportTubMaterial();
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

void J4CTSupportTub::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CTSupportTub::InstallIn(J4VComponent         *mother,
                                G4RotationMatrix     *prot, 
                                const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}

//* Draw  --------------------------------------------------------
void J4CTSupportTub::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CTSupportTub::Print() const
{
}

	
	

