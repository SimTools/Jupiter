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
//*************************************************************************

#include "J4VTXSensor.hh"
#include "G4Box.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4VTXSensor::fFirstName("Sensor");
#ifdef __HOSHINA__
#else
G4LogicalVolume* J4VTXSensor::fStaticLV=NULL;
#endif

//=====================================================================
//---------------------
// Class Description
//---------------------
//=====================================================================
//* constructor -------------------------------------------------------

#ifdef __HOSHINA__

J4VTXSensor::J4VTXSensor(J4VDetectorComponent *parent,
                         G4int                 numOfSensors,
                         G4int                 nbrothers,
                         G4int                 me,
                         G4int                 copyno):
             J4VVTXDetectorComponent(fFirstName, parent, numOfSensors, 
                                     nbrothers, me, copyno),
             fSubstrate(0), fEpitaxial(0), fDxyzSensor(0), fxyzSensor(0)
{  
  // Define Sensor parameters ----------------//    
  fDxyzSensor = new G4ThreeVector(DXYZ_SENSOR);
  Register(fDxyzSensor);
}

J4VTXSensor::J4VTXSensor(const J4VTXSensor &orig, G4int copyno):
  	     J4VVTXDetectorComponent(orig, copyno)
{   
  // Define Sensor parameters ----------------//    
  fDxyzSensor = new G4ThreeVector(DXYZ_SENSOR);
  Register(fDxyzSensor);
}

#else

J4VTXSensor::J4VTXSensor(J4VDetectorComponent* parent,G4int numOfSensors):
  	   J4VVTXDetectorComponent(fFirstName, parent, numOfSensors,1, 0, -1)
{   
  // Define Sensor parameters ----------------//    
  fDxyzSensor = new G4ThreeVector(DXYZ_SENSOR);
  Register(fDxyzSensor);
}

#endif

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXSensor::~J4VTXSensor()
{
  if (Deregister(fDxyzSensor)) delete fDxyzSensor;
  if (Deregister(fxyzSensor))  delete fxyzSensor;
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
      
    // MakeSolid ----------//
    G4VSolid *solid = new G4Box(GetName(),fDxyzSensor->x()/2.,
		                 fDxyzSensor->y()/2.,
		                 fDxyzSensor->z()/2.);
    Register(solid);
    SetSolid(solid);

    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()-> Order(_SENSORMATERIAL_));

#ifdef __HOSHINA__
    // nothing to do here
#else 
    LoadLV( );
#endif

    // SetVisAttribute ----//
    PaintLV( _VTXSENSORVISATT_ , G4Color(0.,0.,1.));    

    SetMaxAllowedStep(0.001*mm);
        
    // Install daughter PV //
    // Install Sensor      //
    fSubstrate  = new J4VTXSubstrate(this);
    Register(fSubstrate);
    fEpitaxial  = new J4VTXEpitaxial(this);
    Register(fEpitaxial);
    fSubstrate->InstallIn(this);  
    SetDaughter(fSubstrate);
    fEpitaxial->InstallIn(this);  
    SetDaughter(fEpitaxial);
  } 
}

//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4VTXSensor::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VTXSensor::InstallIn(J4VComponent         *mother,
                            G4RotationMatrix     *prot, 
                            const G4ThreeVector  &tlate ) 
{ 

  Assemble();			// You MUST call Assemble(); at first.

  G4int layer        = GetMother()->GetMother()->GetMyID();
  G4int copyNo       = GetCopyNo();

#ifdef __HOSHINA__

  fxyzSensor  = new G4ThreeVector(XYZ_SENSOR[layer][copyNo]);  
  Register(fxyzSensor);
  // Placement into mother object ------//
  SetPVPlacement(prot,*fxyzSensor);

#else

  G4int numOfSensors = NSENSOR[layer];
  for (copyNo = 0; copyNo < numOfSensors ; copyNo++){
    fxyzSensor  = new G4ThreeVector(XYZ_SENSOR[layer][copyNo]);  
    Register(fxyzSensor);
  // Placement into mother object ------//
    // Placement function into mother object ------//
    SetPVPlacement(0,*fxyzSensor,copyNo);
  }

#endif

}


//* Draw  --------------------------------------------------------
void J4VTXSensor::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4VTXSensor::Print() const
{
  G4cout << "-J4VTXSensor(mm)-  " <<G4endl;
  G4cout << "dx " << fDxyzSensor->x()/mm 
       << " dy "<< fDxyzSensor->y()/mm 
       << " dz "<< fDxyzSensor->z()/mm 
       << G4endl;
  G4cout << "x " << fxyzSensor->x()/mm 
       << " y "<< fxyzSensor->y()/mm 
       << " z "<< fxyzSensor->z()/mm 
       << G4endl;
  G4cout << "----------------" << G4endl;
  
}
