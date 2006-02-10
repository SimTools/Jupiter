// $Id$
//*************************************************************************
//* --------------------
//* J4IRFCALSensor
//* --------------------
//* (Description)
//* 	Class of FCAL aborber, sensor, and gap
//*     
//* (Update Record)
//*	2006/01/29   A.Miyamoto Original version.
//*************************************************************************

#include "J4IRFCALSensor.hh"
#include "J4IRFCAL.hh"
#include "J4ParameterTable.hh"
#include "J4IRFCALSD.hh"

#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4VSolid.hh"

#include <cmath>
#include <vector>

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRFCALSensor::fName("FCALSensor");
J4IRSensorMaterialStore  *J4IRFCALSensor::fMaterialStore=0;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

// J4IRFCALSensor::J4IRFCALSensor(J4VAcceleratorComponent *parent,
J4IRFCALSensor::J4IRFCALSensor(J4VComponent *parent) :
            J4VDetectorComponent( G4String("FCAL"), fName, parent, 1,
                                    1, 0, -1 ) 
{   
  //  std::cerr << "J4IRFCALSensor constructed. " ;
  //  std::cerr << " ID=" << GetMyID() ;
  //  std::cerr << " name=" << GetName() << std::endl;

}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRFCALSensor::~J4IRFCALSensor()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRFCALSensor::Assemble() 
{   
  if(!GetLV()){

    J4IRFCALLayer *parent=(J4IRFCALLayer*)GetMother();
    G4Cons *solid=(G4Cons*)parent->GetSolid(); 

    G4double rmin1p=solid->GetInnerRadiusMinusZ();
    G4double rmax1p=solid->GetOuterRadiusMinusZ();
    G4double rmin2p=solid->GetInnerRadiusPlusZ();
    G4double rmax2p=solid->GetOuterRadiusPlusZ();
    G4double hzp   =solid->GetZHalfLength();

    fZpos[0]=0;
    fZpos[1]=J4ParameterTable::GetValue("J4IR.FCAL.AbsorberThickness",0.3)*cm;
    fZpos[2]=fZpos[1]+
      J4ParameterTable::GetValue("J4IR.FCAL.SensorThickness",0.03)*cm;
    fZpos[3]=2*hzp;
    
    G4double rmin1=rmin1p+(rmin2p-rmin1p)*fZpos[1]/fZpos[3];
    G4double rmax1=rmax1p+(rmax2p-rmax1p)*fZpos[1]/fZpos[3];
    G4double rmin2=rmin1p+(rmin2p-rmin1p)*fZpos[2]/fZpos[3];
    G4double rmax2=rmax1p+(rmax2p-rmax1p)*fZpos[2]/fZpos[3];
    G4double hz=(fZpos[2]-fZpos[1])*0.5;

    // MakeSolid ---------------
    std::ostringstream sname;
    sname.str(GetName());
    sname << GetMyID() << std::ends;

    G4VSolid *fcal = new G4Cons(sname.str(), rmin1, rmax1, rmin2, rmax2,
				hz, 0, 2*M_PI);
    Register(fcal);
    SetSolid(fcal);	// Don't forgat call it!
                                       
    // MakeLogicalVolume -------------

    G4int fid=(parent->GetMother()->GetMyID())%2;
    std::vector<G4String> ft;
    ft.push_back(G4String("Tail"));  // MyID=2, 4 (Tail)
    ft.push_back(G4String("Front")); // MyID=1, 3 (Front)


    std::vector<GeoInfo> geoinfo;
    geoinfo.push_back(GeoInfo(G4String("Sensor"),G4String("Silicon"),
			      true,G4String("1.0, 0.0, 0.7, 1.0")));

    G4int id=0;
    G4String key=G4String("J4IR.FCAL.")+ft[fid]
      +G4String(".")+geoinfo[id].name+G4String(".Material");
    G4String material=
      J4ParameterTable::GetValue(key.data(),geoinfo[id].material.data());
    MakeLVWith(OpenMaterialStore()->Order(material));
    
    // SetVisAttribute ---------------
    key=string("J4IR.VisAtt.FCAL.")+ft[fid]+G4String(".")+geoinfo[id].name;
    G4bool visatt=J4ParameterTable::GetValue(key,geoinfo[id].visatt);
    key=string("J4IR.Color.FCAL.")+ft[fid]+G4String(".")+geoinfo[id].name;
    std::vector<double> col=
      J4ParameterTable::GetDValue(key.data(),geoinfo[id].color.data(),4);    

    PaintLV(visatt, G4Color(col[0], col[1], col[2], col[3])); 
  	
    /*
    // Install daughter PV -----------
    fLayers = new J4IRFCALLayerLayer*[nlayer];
    Register(fLayers);
    for( G4int i=0;i<nlayer;i++) {
      fLayers[i] = new J4IRFCALLayerLayer(this, nlayer, i);
      Register( fLayers[i] );
      fLayers[i] -> InstallIn(this);
      SetDaughter( fLayers[i] );
    }  
    */
  		  
  }     
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4IRFCALSensor::OpenMaterialStore()
{
   if(!fMaterialStore) {
   	fMaterialStore = new J4IRSensorMaterialStore();
	Register(fMaterialStore);
  	std::cerr << "*** Opened J4IRSensorMaterialStore ***" << std::endl;
   }
    
   return fMaterialStore;
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRFCALSensor::Cabling()
{
    J4IRFCALSD* sd = new J4IRFCALSD(this);
    Register(sd);
    SetSD(sd);
}

//=====================================================================
void J4IRFCALSensor::InstallIn(J4VComponent      *, // mother
                                          G4RotationMatrix  *,
                                    const G4ThreeVector     &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  //  G4UserLimits* myLimits = new G4UserLimits;
  //  GetLV()->SetUserLimits(myLimits);

  // Placement function into mother object...
  G4RotationMatrix* rotation = new G4RotationMatrix;
  G4ThreeVector position;
  position.setZ(GetZCenter());

  SetPVPlacement(rotation,position);

  if (!GetSD()) Cabling(); 

}

//* Draw  --------------------------------------------------------
void J4IRFCALSensor::Draw()
{
  // set visualization attributes
 
}
	
//* Print  --------------------------------------------------------
void J4IRFCALSensor::Print() const
{
}

	
	

