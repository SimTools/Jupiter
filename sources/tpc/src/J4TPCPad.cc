//*************************************************************************
//* --------------------
//* J4TPCPad
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4TPCPad.hh"
#include "J4TPCParameterList.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4TPCPad::fFirstName("Pad");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4TPCPad::J4TPCPad(J4VDetectorComponent *parent,
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

J4TPCPad::~J4TPCPad()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4TPCPad::Assemble() 
{   
  if(!GetLV())
  {	  
    // Define Geometry ----//
    J4TPCParameterList * list = OpenParameterList();
      
    G4double rmin = list->GetPadInnerR(GetMother()->GetMyID());
    G4double rmax = list->GetPadOuterR(GetMother()->GetMyID());
    G4double len  = list->GetPadHalfZ();
    G4double dphi = list->GetPadDeltaPhi();

    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()-> Order(list->GetPadMaterial()));
    
    // SetVisAttribute ----//
    PaintLV(list->GetPadVisAtt() , list->GetPadColor());    
        
    // Install daughter PV //
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4TPCPad::Cabling()
{
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4TPCPad::InstallIn(J4VComponent        *parent,
                         G4RotationMatrix    *,
                         const G4ThreeVector &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ... 
  J4TPCParameterList *list = OpenParameterList();

  SetPVReplica(kPhi, list->GetPadDeltaPhi() /
                     list->GetNpads(parent->GetMyID()));
}


//* Draw  --------------------------------------------------------
void J4TPCPad::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4TPCPad::Print() const
{
}

