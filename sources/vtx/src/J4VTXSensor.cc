// $Id$
//*************************************************************************
//* --------------------
//* J4VTXSensor
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2002/11/19  T.Aso       ParameterList.
//*************************************************************************

#include "J4VTXSensor.hh"
#include "J4VTXSensorSD.hh"
#include "G4Box.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4VTXSensor::fFirstName("Sensor");

//=====================================================================
//---------------------
// Class Description
//---------------------
//=====================================================================
//* constructor -------------------------------------------------------

J4VTXSensor::J4VTXSensor(J4VDetectorComponent *parent,
                         G4int                 numOfSensors,
                         G4int                 nbrothers,
                         G4int                 me,
                         G4int                 copyno):
             J4VVTXDetectorComponent(fFirstName, parent, numOfSensors, 
                                     nbrothers, me, copyno)
{  
  // Define Sensor parameters ----------------//    
}

J4VTXSensor::J4VTXSensor(const J4VTXSensor &orig, G4int copyno):
  	     J4VVTXDetectorComponent(orig, copyno)
{   
  // Define Sensor parameters ----------------//    
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXSensor::~J4VTXSensor()
{
   if (Deregister(fSubstrate))  delete fSubstrate;
   if (Deregister(fEpitaxial))  delete fEpitaxial;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTXSensor::Assemble() 
{   
  if (!GetLV())
  {	  
    // define geometry
    J4VTXParameterList* list = OpenParameterList();
    G4ThreeVector dxyzSensor = list->GetSensorSize();
     
    // MakeSolid ----------//
    G4VSolid *solid = new G4Box(GetName(),dxyzSensor.x()/2.,
		                 dxyzSensor.y()/2.,
		                 dxyzSensor.z()/2.);
    Register(solid);
    SetSolid(solid);

    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()-> Order(list->GetSensorMaterial()));

    // SetVisAttribute ----//
    PaintLV(list->GetSensorVisAtt() , list->GetSensorColor());    

    SetMaxAllowedStep(list->GetMaxAllowedStep());
        
    // Install daughter PV //
    // Install Sensor      //
#if 1   
  if ( !(OpenParameterList()->IsSensorSD()) ){
    fSubstrate  = new J4VTXSubstrate(this);
    Register(fSubstrate);
    fSubstrate->InstallIn(this);  
    SetDaughter(fSubstrate);

    fEpitaxial  = new J4VTXEpitaxial(this);
    Register(fEpitaxial);
    fEpitaxial->InstallIn(this);  
    SetDaughter(fEpitaxial);
  }
#endif
  } 
}

//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4VTXSensor::Cabling()
{
  if(!GetLV()) Assemble();

  if (OpenParameterList()->IsSensorSD()){
    J4VTXSensorSD* sd = new J4VTXSensorSD(this);
    Register(sd);
    SetSD(sd);
  }

}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VTXSensor::InstallIn(J4VComponent         * /* mother */,
                            G4RotationMatrix     *prot, 
                            const G4ThreeVector  & /* tlate  */) 
{ 
   Assemble();			// You MUST call Assemble(); at first.
   G4int layerID        = GetMother()->GetMother()->GetMyID();
   G4int sensorID       = GetCopyNo();

   G4ThreeVector xyzSensor  = 
   OpenParameterList()->GetSensorPosition(layerID,sensorID);  
  // Placement into mother object ------//
  SetPVPlacement(prot,xyzSensor);

  if (!GetSD()) Cabling(); 
}


//* Draw  --------------------------------------------------------
void J4VTXSensor::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4VTXSensor::Print() const
{
}
