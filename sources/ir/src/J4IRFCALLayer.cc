// $Id$
//*************************************************************************
//* --------------------
//* J4IRFCALLayer
//* --------------------
//* (Description)
//* 	Beam Calorimeter just infront of QC1
//*     
//* (Update Record)
//*	2006/01/29   A.Miyamoto Original version.
//*************************************************************************

#include "J4IRFCALLayer.hh"
#include "J4IRFCAL.hh"
#include "J4ParameterTable.hh"

#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4VSolid.hh"

#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRFCALLayer::fName("IRFCALLayer");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRFCALLayer::J4IRFCALLayer(J4VAcceleratorComponent *parent,
                                          G4int  nbrothers, 
			                  G4int  me) :
            J4VIRAcceleratorComponent( fName, parent, 1,
                                    nbrothers, me, -1, false  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRFCALLayer::~J4IRFCALLayer()
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

void J4IRFCALLayer::Assemble() 
{   
  if(!GetLV()){

    J4IRFCAL *parent=(J4IRFCAL*)GetMother();
    G4Cons *solid=(G4Cons*)parent->GetSolid(); 

    G4double rmin1p=solid->GetInnerRadiusMinusZ();
    G4double rmax1p=solid->GetOuterRadiusMinusZ();
    G4double rmin2p=solid->GetInnerRadiusPlusZ();
    G4double rmax2p=solid->GetOuterRadiusPlusZ();
    G4double hzp   =solid->GetZHalfLength();

    G4double nb   =(G4double)GetNbrothers();
    G4double rmin1=rmin1p + (rmin2p-rmin1p)/nb*(G4double)GetMyID();
    G4double rmax1=rmax1p + (rmax2p-rmax1p)/nb*(G4double)GetMyID();
    G4double rmin2=rmin1p + (rmin2p-rmin1p)/nb*(G4double)(GetMyID()+1);
    G4double rmax2=rmax1p + (rmax2p-rmax1p)/nb*(G4double)(GetMyID()+1);

    // MakeSolid ---------------
    std::ostringstream sname;
    sname.str(GetName());
    sname << GetMyID() << std::ends;

    G4double hzl=hzp/nb;
    G4double margin = 0.00001*mm;
	 hzl -= margin;
    G4VSolid *fcal = new G4Cons(sname.str(), rmin1, rmax1, rmin2, rmax2,
				hzl, 0, 2*M_PI);
    Register(fcal);
    SetSolid(fcal);	// Don't forgat call it!
                                       
    // MakeLogicalVolume -------------
    G4String material= "vacuum";
    MakeLVWith(OpenMaterialStore()->Order(material));
    
    // SetVisAttribute ---------------
    G4bool visatt = J4ParameterTable::GetValue("J4IR.VisAtt.FCAL.Layer",true);

    std::vector<double> col=J4ParameterTable::GetDValue("J4IR.Color.FCAL.Layer","1.0 0.0 0.5 1.0",4);
    G4Color *icol=new G4Color(col[0], col[1], col[2], col[3]); 

    PaintLV(visatt, *icol);
  	
    // Install daughter PV -----------

    G4int nsublayer=2;  // FCALSubLayer is fixed to 2, 0=Absorber,1=Gap
    fSubLayers = new J4IRFCALSubLayer*[nsublayer];
    Register(fSubLayers);
    for( G4int i=0;i<nsublayer;i++) {
      fSubLayers[i] = new J4IRFCALSubLayer(this, i);
      Register( fSubLayers[i] );
      fSubLayers[i] -> InstallIn(this);
      SetDaughter( fSubLayers[i] );
    }  
    fSensor = new J4IRFCALSensor(this);
    Register( fSensor );
    fSensor -> InstallIn(this);
    SetDaughter( fSensor );
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRFCALLayer::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRFCALLayer::GetRotation()
{
  G4RotationMatrix* rotM = new G4RotationMatrix;

  // No rotation, because solid is rotated by the mother volume

  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRFCALLayer::GetTranslation()
{
  J4VComponent *parent=GetMother();
  G4Cons *solid=(G4Cons*)parent->GetSolid(); 

  G4double hzp=solid->GetZHalfLength();
  G4double nb=(G4double)GetNbrothers();
  G4double hzstep=hzp/nb;

  G4double zcnt  = -hzp+((G4double)GetMyID()+0.5)*2*hzstep;

  G4ThreeVector* position = new G4ThreeVector();
  position->setZ(zcnt);
  return *position;
}

//* Draw  --------------------------------------------------------
void J4IRFCALLayer::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRFCALLayer::Print() const
{
}

	
	

