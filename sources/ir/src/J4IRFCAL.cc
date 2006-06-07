// $Id$
//*************************************************************************
//* --------------------
//* J4IRFCAL
//* --------------------
//* (Description)
//* 	Beam Calorimeter just infront of QC1
//*     
//* (Update Record)
//*	2005/07/08   A.Miyamoto Original version.
//*************************************************************************

#include "J4IRFCAL.hh"
#include "J4ParameterTable.hh"
#include "J4IRFCALPreHitSD.hh"

#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "J4UnionSolid.hh"
#include "G4VSolid.hh"

#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRFCAL::fName("IRFCAL");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRFCAL::J4IRFCAL(J4VAcceleratorComponent *parent,
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

J4IRFCAL::~J4IRFCAL()
{
  if ( fLayers ) {
    G4int nlayer = 0;
    if( GetMyID() == 0 || GetMyID() == 2 ) {
      nlayer=J4ParameterTable::GetValue("J4IR.FCAL.Front.NLayer",30);
    }
    else {
      nlayer=J4ParameterTable::GetValue("J4IR.FCAL.Tail.NLayer",30);
    }
    for( G4int i=0; i<nlayer; i++ ) {
      if (Deregister(fLayers[i])) delete fLayers[i];
    }
    if( Deregister(fLayers) ) delete fLayers;
  }

}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRFCAL::Assemble() 
{   

  if(!GetLV()){

    G4int nlayer=0;
    G4bool isFront=true;
    // Calcurate parameters ----------
    std::vector<double> geom;
    if ( GetMyID() == 0 || GetMyID() == 2 ) {
      geom = J4ParameterTable::GetDValue("J4IR.FCAL.FrontGeom",
            "8.0 13.0 9.043478 17.69565   230.0 30.0", 6); 
      nlayer=J4ParameterTable::GetValue("J4IR.FCAL.Front.NLayer",30);
      isFront=true;
    }
    else {
      geom = J4ParameterTable::GetDValue("J4IR.FCAL.TailGeom",
          "9.043478 36.0  12.52174 36.0 260.0 25.0", 6); 
      nlayer=J4ParameterTable::GetValue("J4IR.FCAL.Tail.NLayer",30);
      isFront=false;
    } 
    for(int i=0;i<6;i++) {
	geom[i] *= cm; 
	fGeom[i] = geom[i];
    }

    // MakeSolid ---------------
    std::ostringstream sname;
    sname.str(GetName());
    sname << GetMyID() << std::ends;

    G4VSolid *fcal = new G4Cons(sname.str(), geom[0], geom[1], geom[2], 
	geom[3], geom[5]*0.5, 0, 2*M_PI);
                                       
    Register(fcal);
    SetSolid(fcal);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    G4String material= J4ParameterTable::GetValue("J4IR.FCAL.Material","Tungsten");
    MakeLVWith(OpenMaterialStore()->Order(material));
    
    // SetVisAttribute ---------------
    G4bool visatt = J4ParameterTable::GetValue("J4IR.VisAtt.FCAL",true);

    std::vector<double> col=J4ParameterTable::GetDValue("J4IR.Color.FCAL","1.0 0.0 1.0 1.0",4);

    PaintLV(visatt, G4Color(col[0], col[1], col[2], col[3])); 
  	
    // Install daughter PV -----------

    fLayers = 0 ;
    fLayers = new J4IRFCALLayer*[nlayer];
    Register(fLayers);
    for( G4int i=0;i<nlayer;i++) {
      fLayers[i] = new J4IRFCALLayer(this, nlayer, i);
      Register( fLayers[i] );
      fLayers[i] -> InstallIn(this);
      SetDaughter( fLayers[i] );
    } 

  }     

  if( !GetSD() ) { Cabling(); }

}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRFCAL::Cabling()
{
  if( !GetSD() ) {
    J4IRFCALPreHitSD *sd=new J4IRFCALPreHitSD(this);
    Register( sd );
    SetSD( sd );
  }

}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRFCAL::GetRotation()
{
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRFCAL::GetTranslation()
{

   G4double zcnt = (fGeom[4]+fGeom[5]*0.5); 
   G4ThreeVector* position = new G4ThreeVector();
   position->setZ(zcnt);
   return *position;
}

//* Draw  --------------------------------------------------------
void J4IRFCAL::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRFCAL::Print() const
{
}

	
	

