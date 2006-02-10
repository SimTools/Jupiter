// $Id$
//*************************************************************************
//* --------------------
//* J4IRBCALSensor
//* --------------------
//* (Description)
//* 	Class of BCAL aborber, sensor, and gap
//*     
//* (Update Record)
//*	2006/01/29   A.Miyamoto Original version.
//*************************************************************************

#include "J4IRBCALSensor.hh"
#include "J4IRBCAL.hh"
#include "J4ParameterTable.hh"
#include "J4IRBCALSD.hh"

#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4VSolid.hh"

#include <cmath>
#include <vector>

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBCALSensor::fName("BCALSensor");
J4IRSensorMaterialStore  *J4IRBCALSensor::fMaterialStore=0;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

// J4IRBCALSensor::J4IRBCALSensor(J4VAcceleratorComponent *parent,
J4IRBCALSensor::J4IRBCALSensor(J4VComponent *parent) :
            J4VDetectorComponent( G4String("BCAL"), fName, parent, 1,
                                    1, 0, -1 ) 
{   
  //  std::cerr << "J4IRBCALSensor constructed. " ;
  //  std::cerr << " ID=" << GetMyID() ;
  //  std::cerr << " name=" << GetName() << std::endl;

}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRBCALSensor::~J4IRBCALSensor()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBCALSensor::Assemble() 
{   
  if(!GetLV()){

    J4IRBCALLayer *parent=(J4IRBCALLayer*)GetMother();
    G4Tubs *solid=(G4Tubs*)parent->GetSolid(); 

    G4double rmin=solid->GetInnerRadius();
    G4double rmax=solid->GetOuterRadius();
    G4double hzp   =solid->GetZHalfLength();

    fZpos[0]=0;
    fZpos[1]=J4ParameterTable::GetValue("J4IR.BCAL.AbsorberThickness",0.3)*cm;
    fZpos[2]=fZpos[1]+
      J4ParameterTable::GetValue("J4IR.BCAL.SensorThickness",0.03)*cm;
    fZpos[3]=2*hzp;
    
    G4double hz=(fZpos[2]-fZpos[1])*0.5;

    // MakeSolid ---------------
    std::ostringstream sname;
    sname.str(GetName());
    sname << GetMyID() << std::ends;

    G4VSolid *bcal = new G4Tubs(sname.str(), rmin, rmax, hz, 0, 2*M_PI);
    Register(bcal);
    SetSolid(bcal);	// Don't forgat call it!
                                       
    // MakeLogicalVolume -------------

    G4String material=
      J4ParameterTable::GetValue("J4IR.BCAL.Sensor.Material","Silicon");
    MakeLVWith(OpenMaterialStore()->Order(material));
    
    // SetVisAttribute ---------------
    G4bool visatt=J4ParameterTable::GetValue("J4IR.VisAtt.BCAL.Sensor",true);
    std::vector<double> col=J4ParameterTable::GetDValue(
	"J4IR.Color.BCAL.Sensor","1.0 0.0 0.7 1.0",4);

    PaintLV(visatt, G4Color(col[0], col[1], col[2], col[3])); 
  	
    // Install daughter PV -----------
  		  
  }     
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------
 
J4VMaterialStore* J4IRBCALSensor::OpenMaterialStore()
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

void J4IRBCALSensor::Cabling()
{
    J4IRBCALSD* sd = new J4IRBCALSD(this);
    Register(sd);
    SetSD(sd);
}

//=====================================================================
void J4IRBCALSensor::InstallIn(J4VComponent      *, // mother
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
void J4IRBCALSensor::Draw()
{
  // set visualization attributes
 
}
	
//* Print  --------------------------------------------------------
void J4IRBCALSensor::Print() const
{
}

	
	

