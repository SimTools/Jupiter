// $Id$
//*************************************************************************
//* --------------------
//* J4IRCons
//* --------------------
//* (Description)
//* 	General purpose tube solid
//*     
//* (Update Record)
//*	2005/07/22  A.Miyamoto 	Original version.
//*************************************************************************

#include "J4IRCons.hh"

#include "G4Cons.hh"
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

J4IRCons::J4IRCons(G4String name, G4double rmin1, G4double rmax1,
	   G4double rmin2, G4double rmax2,  
	   G4double hzlen, G4double zcnt, 
			 J4VAcceleratorComponent *parent,
                           G4int  nclones   ,
                           G4int  nbrothers , 
                           G4int  me        ,
 	                   G4int  copyno    ,
	                   G4bool reflect ):
         J4VIRAcceleratorComponent( name, parent, nclones,
                                    nbrothers, me, copyno,reflect  ),
	fName(name), fRmin1(rmin1), fRmax1(rmax1), fRmin2(rmin2), fRmax2(rmax2), 
        fHZlen(hzlen), fZcnt(zcnt)
{   
	fMaterial="Vaccum";
	fVisAtt=FALSE;
        fColor=G4Color(0.0, 0.0, 0.0, 1.0);
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRCons::~J4IRCons()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRCons::Assemble() 
{   
  if(!GetLV()){
  	
    // MakeSolid ---------------
    G4VSolid *solid = new G4Cons( fName, fRmin1, fRmax1, fRmin2, fRmax2,  
				 fHZlen, 0, 2*M_PI);  

    Register(solid);
    SetSolid(solid);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(fMaterial));
    
    // PaintLV -----------------------
    PaintLV(fVisAtt, fColor);
  	
    // Install daughter PV -----------
  		  
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRCons::Cabling()
{
}

//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRCons::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix();
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRCons::GetTranslation()
{
  G4ThreeVector *position=new G4ThreeVector(0, 0, fZcnt);
  return *position;
}
                                                                                
                                                                               

//* Draw  --------------------------------------------------------
void J4IRCons::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRCons::Print() const
{
}

	
	

