// $Id$
//*************************************************************************
//* --------------------
//* J4CDCSupportTub
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CDCSupportTub.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CDCSupportTub::fFirstName("SupportTub");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CDCSupportTub::J4CDCSupportTub(G4double rmin,
				 G4double rmax,
				 G4double len,
				 G4double totalphi,
				 J4VDetectorComponent *parent,
                                 G4int  nclones,
                                 G4int  nbrothers, 
                                 G4int  me,
                                 G4int  copyno ) :
                 J4VCDCDetectorComponent( fFirstName, parent, nclones,
  					  nbrothers, me, copyno  ),
                 fRmin(rmin), fRmax(rmax), fLen(len), fTotalPhi(totalphi)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CDCSupportTub::~J4CDCSupportTub()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CDCSupportTub::Assemble() 
{   
   if(!GetLV()){
      J4CDCParameterList *list = OpenParameterList();
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

void J4CDCSupportTub::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CDCSupportTub::InstallIn(J4VComponent        *,
                                G4RotationMatrix    *,
                                const G4ThreeVector &)
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}

//* Draw  --------------------------------------------------------
void J4CDCSupportTub::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CDCSupportTub::Print() const
{
}

	
	

