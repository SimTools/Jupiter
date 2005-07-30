// $Id$
//*************************************************************************
//* --------------------
//* J4IRBPIP
//* --------------------
//* (Description)
//* 	For central part of beam pipe
//*     
//* (Update Record)
//*	2005/07/25  A.Miyamoto  Created from T.Aso's original
//*************************************************************************

#include "J4IRBPIP.hh"
#include "J4ParameterTable.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBPIP::fName("IRBPIP");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBPIP::J4IRBPIP(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno ) :
            J4VIRAcceleratorComponent( fName, parent, nclones,
                                    nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRBPIP::~J4IRBPIP()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBPIP::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    G4double rout = J4ParameterTable::GetValue("J4IR.BeamPipeIP.OuterRadius", 1.525)*cm;
    G4double rin  = rout - J4ParameterTable::GetValue("J4IR.BeamPipeIP.Thickness", 0.025)*cm; 
    G4double zlen = J4ParameterTable::GetValue("J4IR.BeamPipeIP.HalfZLength",7.0)*cm;
  	
    // MakeSolid ---------------
    G4String iptubename( GetName() );
    iptubename += ".BePipeTube";
    G4VSolid *iptube = new G4Tubs( iptubename, rin,rout,zlen, 0, 2*M_PI);  

    Register(iptube);
    SetSolid(iptube);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    G4String material = J4ParameterTable::GetValue("J4IR.BeamPipeIP.Material","Beryllium");
    MakeLVWith(OpenMaterialStore()->Order(material));
    
    // SetVisAttribute ---------------
    G4bool visatt = J4ParameterTable::GetValue("J4IR.VisAtt.BeamPipeIP",true);
    std::vector<double> col=J4ParameterTable::GetDValue("J4IR.Color.BeamPipeIP","0.0 0.5 0.5 1.0",4);
    G4Color icolor(col[0], col[1], col[2], col[3]);  // cyan

    PaintLV(visatt, icolor);
  	
    // Install daughter PV -----------
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRBPIP::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4IRBPIP::InstallIn(J4VComponent         *, // mother
                             G4RotationMatrix     *, // prot
                             const G4ThreeVector  &) // tlate
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}


//* Draw  --------------------------------------------------------
void J4IRBPIP::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRBPIP::Print() const
{
}

	
	

