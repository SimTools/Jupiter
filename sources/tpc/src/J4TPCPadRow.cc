//*************************************************************************
//* --------------------
//* J4TPCPadRow
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4TPCPadRow.hh"
#include "J4TPCParameterList.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4TPCPadRow::fFirstName("PadRow");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4TPCPadRow::J4TPCPadRow(J4VDetectorComponent* parent,
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

J4TPCPadRow::~J4TPCPadRow()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4TPCPadRow::Assemble() 
{   
  if(!GetLV())
  {	  
    // Define Geometry ----//
    J4TPCParameterList *list = OpenParameterList();

    G4double rmin = list->GetPadRowInnerR(GetMyID());
    G4double rmax = list->GetPadRowOuterR(GetMyID());
    G4double len  = list->GetPadRowHalfZ();
    G4double dphi = list->GetPadRowDeltaPhi();
      
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()-> Order(list->GetPadRowMaterial()));
    
    // SetVisAttribute ----//
    PaintLV(list->GetPadRowVisAtt() , list->GetPadRowColor());    
        
    // Install daughter PV //
    // Install Pad         //
    G4int  npads = list->GetNpads(GetMyID());

    fPad = new J4TPCPad(this, npads);
    Register(fPad);
    fPad->InstallIn(this);
    SetDaughter(fPad);
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4TPCPadRow::Cabling()
{
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4TPCPadRow::InstallIn(J4VComponent        *,
                            G4RotationMatrix    *,
                            const G4ThreeVector &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ... 
  SetPVPlacement();
  
}


//* Draw  --------------------------------------------------------
void J4TPCPadRow::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4TPCPadRow::Print() const
{
}

