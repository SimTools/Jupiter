// $id: J4VTXLadder.cc,v 1.1.1.2 2001/05/31 06:35:26 hoshina Exp $
//*************************************************************************
//* --------------------
//* J4VTXLadder
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VTXLadder.hh"
#include "G4Box.hh"
#include "J4VTXParameter.hh"
#include "J4VTXMaterialStore.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4VTXLadder::fFirstName("Ladder");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

#ifdef __HOSHINA__

J4VTXLadder::J4VTXLadder(J4VDetectorComponent *parent, 
                         G4int                 numOfLadders,
                         G4int                 nbrothers,
                         G4int                 me,
                         G4int                 copyno):
  	     J4VVTXDetectorComponent(fFirstName, parent, numOfLadders, 
                                     nbrothers, me, copyno),
             fDxyzLadder(0), fxyzLadder(0), fRot(0), fSensors(0) 
{   
  // Define Ladder parameters ----------------//    
  G4int layer        = parent->GetMyID();
  fDxyzLadder        = DXYZ_LADDER[layer];

}

J4VTXLadder::J4VTXLadder(const J4VTXLadder &orig, G4int copyno):
             J4VVTXDetectorComponent(orig, copyno),
             fDxyzLadder(orig.fDxyzLadder), fxyzLadder(orig.fxyzLadder), 
             fSensors(orig.fSensors) 
{   
  // Define Ladder parameters ----------------//    
  G4int layer        = orig.GetMother()->GetMyID();
  fDxyzLadder        = DXYZ_LADDER[layer];
}

#else 

J4VTXLadder::J4VTXLadder(J4VDetectorComponent *parent, G4int numOfLadders):
             J4VVTXDetectorComponent(fFirstName, parent, numOfLadders,1, 0, -1),
             fDxyzLadder(0), fxyzLadder(0), fRot(0), fSensor(0) 
{   
  // Define Ladder parameters ----------------//    
  G4int layer = parent->GetMyID();
  fDxyzLadder = DXYZ_LADDER[layer];
}

#endif
//=====================================================================
//* destructor --------------------------------------------------------

J4VTXLadder::~J4VTXLadder()
{
  if (Deregister(fDxyzLadder)) delete fDxyzLadder; 
  if (Deregister(fxyzLadder))  delete fxyzLadder; 
  if (Deregister(fRot))        delete fRot; 

#ifdef __HOSHINA__

  if (fSensors) {   
    G4int layer = GetMother()->GetMyID();
    G4int i;  
    for (i = 0; i < NSENSOR[layer] ; i++) {
      if(Deregister(fSensors[i])) delete fSensors [i];
    } 
    if (Deregister(fSensors)) delete [] fSensors;
  }

#else

  if (Deregister(fSensor))     delete fSensor; 

#endif
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTXLadder::Assemble() 
{   
  if(!GetLV())
  {	  

    // define geometry
    // MakeSolid ----------//
    G4VSolid *solid = new G4Box(GetName(), fDxyzLadder->x()/2.,
			           fDxyzLadder->y()/2.,
			           fDxyzLadder->z()/2. );
    Register(solid);
    SetSolid(solid);

    MakeLVWith(OpenMaterialStore()-> Order(_LADDERMATERIAL_));

    // SetVisAttribute ----//
    PaintLV( _VTXLADDERVISATT_ , G4Color(0.,1.,1.));    
        
    // Install daughter PV //
    // Install Sensor      //
    G4int layer = GetMother()->GetMyID();
    G4int numOfSensors = NSENSOR[layer];

#ifdef __HOSHINA__

    // make pointer array for Sensor...
    fSensors = new J4VTXSensor* [numOfSensors]; 
    Register(fSensors);
    
    // make first sensor object (MUST define copyNo as 0)
    fSensors[0] = new J4VTXSensor(this, numOfSensors, 1, 0, 0);
    Register(fSensors[0]);
    fSensors[0]->InstallIn(this);  
    
    // copy sensor objects (copyNo must start from 1)
    G4int copyNo;
    for (copyNo = 1; copyNo < numOfSensors; copyNo++) {
        fSensors[copyNo] = new J4VTXSensor(*fSensors[0], copyNo);
        Register(fSensors[copyNo]);
    }
    
    // install sensor objects...    
    for (copyNo = 1 ; copyNo < numOfSensors; copyNo++) {
       fSensors[copyNo]->InstallIn(this);  
       SetDaughter(fSensors[copyNo]);
    }

#else

    fSensor  = new J4VTXSensor(this,numOfSensors);
    Register(fSensors);
    fSensor->InstallIn(this);  
    SetDaughter(fSensor);

#endif
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VTXLadder::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VTXLadder::InstallIn(J4VComponent         *mother,
                            G4RotationMatrix     *prot, 
                            const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 

  G4int layer        = mother->GetMyID();
  G4int copyNo       = GetCopyNo();
  
#ifdef __HOSHINA__

  fxyzLadder  = new G4ThreeVector(XYZ_LADDER[layer][copyNo]);
  Register(fxyzLadder);
  fAngle      = ANGLE_LADDER[layer][copyNo];
  
  // Placement into mother object ------//
  fRot = new G4RotationMatrix;
  Register(fRot);
  fRot->rotateZ(fAngle);
  SetPVPlacement(fRot,*fxyzLadder);
  
#else 

  G4int numOfLadders = GetNclones();
  for ( copyNo = 0 ; copyNo < numOfLadders; copyNo++ ){
    fxyzLadder  = new G4ThreeVector(XYZ_LADDER[layer][copyNo]);
    Register(fxyzLadder);
    fAngle =  ANGLE_LADDER[layer][copyNo];
    // Placement function into mother object ------//
    fRot = new G4RotationMatrix;
    Register(fRot);
    fRot->rotateZ(fAngle);
    SetPVPlacement(fRot,*fxyzLadder,copyNo);
  }

#endif

}


//* Draw  --------------------------------------------------------
void J4VTXLadder::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4VTXLadder::Print() const
{
  G4cout << "-J4VTXLadder(mm)-  " <<G4endl;
  G4cout << "dx " << fDxyzLadder->x()/mm 
       << " dy "<< fDxyzLadder->y()/mm 
       << " dz "<< fDxyzLadder->z()/mm 
       << G4endl;
  G4cout << "x " << fxyzLadder->x()/mm 
       << " y "<< fxyzLadder->y()/mm 
       << " z "<< fxyzLadder->z()/mm 
       << G4endl;
  G4cout << "----------------" << G4endl;
}

	
	
