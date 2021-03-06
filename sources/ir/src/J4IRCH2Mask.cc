// $Id$
//*************************************************************************
//* --------------------
//* J4IRCH2Mask
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/12  T.Aso	Original version.
//*************************************************************************

#include "J4IRCH2Mask.hh"
#include "J4ParameterTable.hh"
#include "J4SubtractionSolid.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRCH2Mask::fName("IRCH2Mask");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRCH2Mask::J4IRCH2Mask(J4VAcceleratorComponent *parent,
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

J4IRCH2Mask::~J4IRCH2Mask()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRCH2Mask::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    G4double rmin = J4ParameterTable::GetValue("J4IR.CH2Mask.InnerRadius",3.75)*cm;
    G4double rmax = J4ParameterTable::GetValue("J4IR.CH2Mask.OuterRadius",20.0)*cm;
    G4double zlen = J4ParameterTable::GetValue("J4IR.CH2Mask.ZLength",20.0)*cm;
    G4double zpos = J4ParameterTable::GetValue("J4IR.CH2Mask.ZPosition",410.0)*cm;
    G4double zcnt = zpos + zlen*0.5;


    // MakeSolid ---------------
    G4double qcangle=J4ParameterTable::GetValue("J4IR.Q.Angle",0.00)*rad;

    if( std::abs(qcangle) < 0.001 ) { 
       G4String name( GetName() );
       name += "/CH2";
       G4VSolid *tube = new G4Tubs( name, rmin,rmax,zlen/2.,0.,2*M_PI);  
                                       
       Register(tube);
       SetSolid(tube);	// Don't forgat call it!
    }
    else {
//    Make holes for input/out beam in cylindrical CH2 Mask
      G4String tubname=fName+".tubs";
      G4VSolid *tube = new G4Tubs( tubname, rmin, rmax, zlen*0.5, 0, 2*M_PI);  

      G4double holeR1=J4ParameterTable::GetValue(
		"J4IR.CH2Mask.HoleRadius.Upstream",2.0)*cm;
      G4String holename1=fName+".hole1";
      G4VSolid *hole1 = new G4Tubs( holename1, 0.0, holeR1, zlen, 0, 2*M_PI);

      G4RotationMatrix *rotm=new G4RotationMatrix();
      rotm->rotateY(-qcangle);
      G4ThreeVector trans(-zcnt*std::sin(-qcangle),0,
		zcnt*(std::cos(-qcangle)-1) );

      G4String tmpname1=fName+".tmp1";
      G4VSolid *tmp1=new J4SubtractionSolid(tmpname1, tube, hole1, rotm, trans);

      G4double holeR2=J4ParameterTable::GetValue(
		"J4IR.CH2Mask.HoleRadius.Downstream",4.0)*cm;
      G4String holename2=fName+".hole2";
      G4VSolid *hole2 = new G4Tubs( holename2, 0.0, holeR2, zlen, 0, 2*M_PI);

      G4RotationMatrix *rotp=new G4RotationMatrix();
      rotp->rotateY(qcangle);
      G4ThreeVector transp(-zcnt*std::sin(qcangle),0,
		zcnt*(std::cos(qcangle)-1) );

      G4VSolid *solid=new J4SubtractionSolid(fName, tmp1, hole2, rotp, transp);


      Register(solid);
      SetSolid(solid);	// Don't forgat call it!

    }


    // MakeLogicalVolume -------------
    G4String material= J4ParameterTable::GetValue("J4IR.CH2Mask.Material","Polyethylene");
    MakeLVWith(OpenMaterialStore()->Order(material));
    
    // SetVisAttribute ---------------
    G4bool visatt = J4ParameterTable::GetValue("J4IR.VisAtt.CH2Mask",true);

    std::vector<double> col=J4ParameterTable::GetDValue("J4IR.Color.CH2Mask","1.0 0.0 1.0 1.0",4);
    G4Color icol(col[0], col[1], col[2], col[3]); 

    PaintLV(visatt, icol);

    // Install daughter PV -----------
  		  
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRCH2Mask::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRCH2Mask::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRCH2Mask::GetTranslation()
{
  G4double zlen = J4ParameterTable::GetValue("J4IR.CH2Mask.ZLength",20.0)*cm;
  G4double zpos = J4ParameterTable::GetValue("J4IR.CH2Mask.ZPosition",410.0)*cm;
  G4double zcnt = zpos + 0.5*zlen;
  	
  G4ThreeVector* position = new G4ThreeVector;
  position->setZ(zcnt);

  return *position;
}




//* Draw  --------------------------------------------------------
void J4IRCH2Mask::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRCH2Mask::Print() const
{
}

	
	

