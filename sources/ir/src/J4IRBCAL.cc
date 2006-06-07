// $Id$
//*************************************************************************
//* --------------------
//* J4IRBCAL
//* --------------------
//* (Description)
//* 	Beam Calorimeter just infront of QC1
//*     
//* (Update Record)
//*	2005/07/08   A.Miyamoto Original version.
//*************************************************************************

#include "J4IRBCAL.hh"
#include "J4IRBCALLayer.hh"
#include "J4IRBCALPreHitSD.hh"

#include "J4ParameterTable.hh"
#include "J4SubtractionSolid.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBCAL::fName("IRBCAL");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBCAL::J4IRBCAL(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno,G4bool reflect ) :
            J4VIRAcceleratorComponent( fName, parent, nclones,
                                    nbrothers, me, copyno,reflect  ) 
{   
  fShape=0;
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRBCAL::~J4IRBCAL()
{
  if ( fLayers ) {
    G4int nlayer=J4ParameterTable::GetValue("J4IR.BCAL.NLayer",30);
    for( G4int i=0; i<nlayer; i++ ) {
      if (Deregister(fLayers[i])) delete fLayers[i];
    }
    if( Deregister(fLayers) ) delete fLayers;
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBCAL::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    G4double rmin = J4ParameterTable::GetValue("J4IR.BCAL.InnerRadius",3.75)*cm;
    G4double rmax = J4ParameterTable::GetValue("J4IR.BCAL.OuterRadius",20.0)*cm;
    G4double zlen = J4ParameterTable::GetValue("J4IR.BCAL.ZLength",20.0)*cm;
    G4double zpos = J4ParameterTable::GetValue("J4IR.BCAL.ZPosition",430.0)*cm;
    fZpos=zpos;
    G4double zcnt = zpos + zlen*0.5;
  	
    // MakeSolid ---------------
    G4double qcangle=J4ParameterTable::GetValue("J4IR.Q.Angle",0.00)*rad;

    if( std::abs(qcangle) < 0.001 ) { 
      OrderNewTubs( rmin, rmax, zlen*0.5, 2*M_PI);
    }
// Case with a crossing angle.
    else {
      fShape=1;
      G4String tubname=fName+".tubs";
      G4VSolid *tube = new G4Tubs( tubname, rmin, rmax, zlen*0.5, 0, 2*M_PI);  

      G4double holeR1=J4ParameterTable::GetValue(
		"J4IR.BCAL.HoleRadius.Upstream",2.0)*cm;
      G4String holename1=fName+".hole1";
      G4VSolid *hole1 = new G4Tubs( holename1, 0.0, holeR1, zlen, 0, 2*M_PI);

      G4RotationMatrix *rotm=new G4RotationMatrix();
      rotm->rotateY(-qcangle);
      G4ThreeVector trans(-zcnt*std::sin(-qcangle),0,
		zcnt*(std::cos(-qcangle)-1) );
      G4String tmpname1=fName+".tmp1";
      G4VSolid *tmp1=new J4SubtractionSolid(tmpname1, tube, hole1, rotm, trans);

      G4double holeR2=J4ParameterTable::GetValue(
		"J4IR.BCAL.HoleRadius.Downstream",5.0)*cm;
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
    G4String material= J4ParameterTable::GetValue("J4IR.BCAL.Material","Tungsten");
    MakeLVWith(OpenMaterialStore()->Order(material));
    
    // SetVisAttribute ---------------
    G4bool visatt = J4ParameterTable::GetValue("J4IR.VisAtt.BCAL",true);

    std::vector<double> col=J4ParameterTable::GetDValue("J4IR.Color.BCAL","0.0 0.0 1.0 1.0",4);
    G4Color *icol=new G4Color(col[0], col[1], col[2], col[3]); 

    PaintLV(visatt, *icol);
  	
    // Install daughter PV -----------

    fLayers = 0 ;
    if( fShape == 0 ) {
      G4int nlayer=J4ParameterTable::GetValue("J4IR.BCAL.NLayer",30);
      fLayers = new J4IRBCALLayer*[nlayer];
      Register(fLayers);
      for( G4int i=0;i<nlayer;i++) {
	fLayers[i] = new J4IRBCALLayer(this, nlayer, i);
	Register( fLayers[i] );
	fLayers[i] -> InstallIn(this);
	SetDaughter( fLayers[i] );
      } 
    }  		  
  }     

  if( !GetSD() ) { Cabling(); }

}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRBCAL::Cabling()
{
  if( !GetSD() ) {
    J4IRBCALPreHitSD *sd=new J4IRBCALPreHitSD(this);
    Register( sd );
    SetSD( sd );
  }
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRBCAL::GetRotation()
{
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRBCAL::GetTranslation()
{
  G4double zpos = J4ParameterTable::GetValue("J4IR.BCAL.ZPosition",430.0)*cm;
  G4double zlen = J4ParameterTable::GetValue("J4IR.BCAL.ZLength",20.0)*cm;
  G4double zcnt = zpos+zlen*0.5; 
  G4ThreeVector* position = new G4ThreeVector();
  position->setZ(zcnt);

  return *position;
}

//* Draw  --------------------------------------------------------
void J4IRBCAL::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRBCAL::Print() const
{
}

	
	

