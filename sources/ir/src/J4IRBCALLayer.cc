// $Id$
//*************************************************************************
//* --------------------
//* J4IRBCALLayer
//* --------------------
//* (Description)
//* 	Beam Calorimeter just infront of QC1
//*     
//* (Update Record)
//*	2006/01/29   A.Miyamoto Original version.
//*************************************************************************

#include "J4IRBCALLayer.hh"
#include "J4IRBCAL.hh"
#include "J4ParameterTable.hh"

#include "G4Tubs.hh"
#include "G4VSolid.hh"

#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBCALLayer::fName("IRBCALLayer");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBCALLayer::J4IRBCALLayer(J4VAcceleratorComponent *parent,
                                          G4int  nbrothers, 
			                  G4int  me) :
            J4VIRAcceleratorComponent( fName, parent, 1,
                                    nbrothers, me, -1, false  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRBCALLayer::~J4IRBCALLayer()
{
  if ( fSubLayers ) {
    G4int nsublayer = 2;
    for( G4int i=0; i<nsublayer; i++ ) {
      if (Deregister(fSubLayers[i])) delete fSubLayers[i];
    }
    if( Deregister(fSubLayers) ) delete fSubLayers;
  }

  if( fSensor ) { delete fSensor; }

}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBCALLayer::Assemble() 
{   
  if(!GetLV()){

    //    J4IRBCAL *parent=(J4IRBCAL*)GetMother();
    //    if( parent->GetShape() != 0 ) {
    //      std::cerr << "Fatal error i J4IRBCALLayer ....." << std::endl;
    //      std::cerr << "Bcal shape for large crossing angle is not supported" ;
    //      std::cerr << std::endl ;
    //      exit(0);
    //    }
    //    G4Tubs *solid=(G4Tubs*)parent->GetSolid(); 
    G4double rmin = J4ParameterTable::GetValue("J4IR.BCAL.InnerRadius",3.75)*cm;
    G4double rmax = J4ParameterTable::GetValue("J4IR.BCAL.OuterRadius",20.0)*cm;
    G4double zlen = J4ParameterTable::GetValue("J4IR.BCAL.ZLength",20.0)*cm;

    G4double tolerance=1.E-5*mm;
    rmin += tolerance;
    rmax -= tolerance;
    G4double hzp   = zlen*0.5;
    G4double nb   =(G4double)GetNbrothers();

    // MakeSolid ---------------
    std::ostringstream sname;
    sname.str(GetName());
    sname << GetMyID() << std::ends;

    G4double hzl=hzp/nb-tolerance;
    G4VSolid *bcal = new G4Tubs(sname.str(), rmin, rmax, hzl, 0, 2*M_PI);
    Register(bcal);
    SetSolid(bcal);	// Don't forgat call it!
                                       
    // MakeLogicalVolume -------------
    G4String material= "Air";
    MakeLVWith(OpenMaterialStore()->Order(material));
    
    // SetVisAttribute ---------------
    G4bool visatt = J4ParameterTable::GetValue("J4IR.VisAtt.BCAL.Layer",true);

    std::vector<double> col=J4ParameterTable::GetDValue("J4IR.Color.BCAL.Layer","1.0 0.0 0.5 1.0",4);
    G4Color *icol=new G4Color(col[0], col[1], col[2], col[3]); 

    PaintLV(visatt, *icol);
  	
    // Install daughter PV -----------
    G4int nsublayer=2;  // BCALSubLayer is fixed to 2, 0=Absorber,1=Gap
    fSubLayers = new J4IRBCALSubLayer*[nsublayer];
    Register(fSubLayers);
    for( G4int i=0;i<nsublayer;i++) {
      fSubLayers[i] = new J4IRBCALSubLayer(this, i);
      Register( fSubLayers[i] );
      fSubLayers[i] -> InstallIn(this);
      SetDaughter( fSubLayers[i] );
    }  
    fSensor = new J4IRBCALSensor(this);
    Register( fSensor );
    fSensor -> InstallIn(this);
    SetDaughter( fSensor );
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRBCALLayer::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRBCALLayer::GetRotation()
{
  G4RotationMatrix* rotM = new G4RotationMatrix;

  // No rotation, because solid is rotated by the mother volume

  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRBCALLayer::GetTranslation()
{
  //  J4VComponent *parent=GetMother();
  //  G4Tubs *solid=(G4Tubs*)parent->GetSolid(); 

  //  G4double hzp=solid->GetZHalfLength();
  G4double hzp = J4ParameterTable::GetValue("J4IR.BCAL.ZLength",20.0)*cm*0.5;
  G4double nb=(G4double)GetNbrothers();
  G4double hzstep=hzp/nb;

  G4double zcnt  = -hzp+((G4double)GetMyID()+0.5)*2*hzstep;

  G4ThreeVector* position = new G4ThreeVector();
  position->setZ(zcnt);
  return *position;
}

//* Draw  --------------------------------------------------------
void J4IRBCALLayer::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRBCALLayer::Print() const
{
}

	
	

