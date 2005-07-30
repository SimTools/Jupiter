// $Id$
//*************************************************************************
//* --------------------
//* J4IRWMask3
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2005/07/09  A.Miyamoto 	Original version.
//*************************************************************************

#include "J4IRWMask3.hh"
#include "J4ParameterTable.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRWMask3::fName("IRWMask3");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRWMask3::J4IRWMask3(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno,G4bool reflect ) :
            J4VIRAcceleratorComponent( fName, parent, nclones,
                                    nbrothers, me, copyno,reflect  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRWMask3::~J4IRWMask3()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRWMask3::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    G4double rmin = J4ParameterTable::GetValue("J4IR.WMask3.InnerRadius",20.0)*cm;
    G4double rmax = J4ParameterTable::GetValue("J4IR.WMask3.OuterRadius",35.0)*cm;
    G4double zlen =J4ParameterTable::GetValue("J4IR.WMask3.Length",160.0)*cm;

    // MakeSolid ---------------
    G4String name( GetName() );
    name += "/WMask3";
    G4VSolid *tube = new G4Tubs( name,rmin,rmax,zlen/2., 0, 2*M_PI);  

    Register(tube);
    SetSolid(tube);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    G4String material= J4ParameterTable::GetValue("J4IR.WMask3.Material","Tungsten");
    MakeLVWith(OpenMaterialStore()->Order(material));
    
    // SetVisAttribute ---------------
    G4bool visatt = J4ParameterTable::GetValue("J4IR.VisAtt.WMask3",true);

    std::vector<double> col=J4ParameterTable::GetDValue("J4IR.Color.WMask3","1.0 0.0 1.0 1.0",4);
    G4Color *icol=new G4Color(col[0], col[1], col[2], col[3]); 

    PaintLV(visatt, *icol);
  	
    // Install daughter PV -----------
  		  
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRWMask3::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRWMask3::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRWMask3::GetTranslation()
{
  G4double zpos = J4ParameterTable::GetValue("J4IR.WMask3.ZPosition",290.0)*cm;
  G4double zlen = J4ParameterTable::GetValue("J4IR.WMask3.Length",160.0)*cm;
  G4double zcnt = zpos + 0.5*zlen;

  G4ThreeVector* position = new G4ThreeVector(0,0,zcnt);

  return *position;
}




//* Draw  --------------------------------------------------------
void J4IRWMask3::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRWMask3::Print() const
{
}

	
	

