//*************************************************************************
//* --------------------
//* J4TPCSupportTub
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4TPCSupportTub.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4TPCSupportTub::fFirstName("SupportTub");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4TPCSupportTub::J4TPCSupportTub(G4double rmin,
				 G4double rmax,
				 G4double len,
				 G4double totalphi,
				 J4VDetectorComponent *parent,
                                 G4int  nclones,
                                 G4int  nbrothers, 
                                 G4int  me,
                                 G4int  copyno ) :
                 J4VTPCDetectorComponent( fFirstName, parent, nclones,
  					  nbrothers, me, copyno  ),
                 fRmin(rmin), fRmax(rmax), fLen(len), fTotalPhi(totalphi)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4TPCSupportTub::~J4TPCSupportTub()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4TPCSupportTub::Assemble() 
{   
   if(!GetLV()){
      J4TPCParameterList *list = OpenParameterList();
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

void J4TPCSupportTub::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4TPCSupportTub::InstallIn(J4VComponent        *,
                                G4RotationMatrix    *, 
                                const G4ThreeVector &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}

//* Draw  --------------------------------------------------------
void J4TPCSupportTub::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4TPCSupportTub::Print() const
{
}

