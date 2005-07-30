// $Id$
//*************************************************************************
//* --------------------
//* J4IRTubs
//* --------------------
//* (Description)
//* 	General purpose tube solid
//*     
//* (Update Record)
//*	2005/07/16  A.Miyamoto 	Original version.
//*************************************************************************

#include "J4IRTubs.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRTubs::J4IRTubs(G4String name, G4double rmin, G4double rmax, G4double hzlen, G4double zcnt, 
	   G4String material, G4bool visatt, G4Color icol, 
			 J4VAcceleratorComponent *parent,
                           G4int  nclones   ,
                           G4int  nbrothers , 
                           G4int  me        ,
 	                   G4int  copyno    ,
	                   G4bool reflect ):
         J4VIRAcceleratorComponent( name, parent, nclones,
                                    nbrothers, me, copyno,reflect  ),
	fName(name), fRmin(rmin), fRmax(rmax), fHZlen(hzlen), fZcnt(zcnt),
	fMaterial(material), fVisAtt(visatt), fColor(icol), fRotation(0.0),
	fXcnt(0.0), fYcnt(0.0)     
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRTubs::~J4IRTubs()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRTubs::Assemble() 
{   
  if(!GetLV()){
  	
    // MakeSolid ---------------
    G4VSolid *tube = new G4Tubs( fName,fRmin, fRmax, fHZlen, 0, 2*M_PI);  

    Register(tube);
    SetSolid(tube);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(fMaterial));
    
    // PaintLV -----------------------
    PaintLV(fVisAtt, fColor);
  	
    // Install daughter PV -----------
  		  
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRTubs::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRTubs::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix();
  rotM->rotateY(fRotation);
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRTubs::GetTranslation()
{
  G4ThreeVector* position = new G4ThreeVector(fXcnt,fYcnt,fZcnt);
  return *position;
}


//* Draw  --------------------------------------------------------
void J4IRTubs::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRTubs::Print() const
{
}

	
	

