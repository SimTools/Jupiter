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
//*	2002/11/19  T.Aso       Modify to use ParameterList
//*************************************************************************

#include "J4VTXLadder.hh"
#include "G4Box.hh"
#include "J4VTXMaterialStore.hh"
#include "J4VTXLadderSD.hh"

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
J4VTXLadder::J4VTXLadder(J4VDetectorComponent *parent, 
                         G4int                 numOfLadders,
                         G4int                 nbrothers,
                         G4int                 me,
                         G4int                 copyno):
  	     J4VVTXDetectorComponent(fFirstName, parent, numOfLadders, 
                                     nbrothers, me, copyno)
{
}

J4VTXLadder::J4VTXLadder(const J4VTXLadder &orig, G4int copyno):
             J4VVTXDetectorComponent(orig, copyno)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXLadder::~J4VTXLadder()
{
  if (fSensors) {   
    G4int layer = GetMother()->GetMyID();
    for (G4int i = 0; i < OpenParameterList()->GetNSensors(layer) ; i++) {
      if(Deregister(fSensors[i])) delete fSensors [i];
    } 
    if (Deregister(fSensors)) delete [] fSensors;
  }

}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTXLadder::Assemble() 
{   
  if(!GetLV())
  {	  

    J4VTXParameterList* list = OpenParameterList();

    G4int layer        = GetMother()->GetMyID();
    G4ThreeVector* dxyzLadder  = list->GetLadderSize(layer);

    // define geometry
    // MakeSolid ----------//
    G4VSolid *solid = new G4Box(GetName(), dxyzLadder->x()/2.,
			           dxyzLadder->y()/2.,
			           dxyzLadder->z()/2. );
    Register(solid);
    SetSolid(solid);

    MakeLVWith(OpenMaterialStore()-> Order(list->GetLadderMaterial()));

    // SetVisAttribute ----//
    PaintLV(list->GetLadderVisAtt(), list->GetLadderColor());    
        
    // Install daughter PV //
    // Install Sensor      //

#if 1 
  if ( !(OpenParameterList()->IsLadderSD()) ){
    G4int numOfSensors = list->GetNSensors(layer);
    // make pointer array for Sensor...
    fSensors = new J4VTXSensor* [numOfSensors]; 
    Register(fSensors);
    
    // make first sensor object (MUST define copyNo as 0)
    fSensors[0] = new J4VTXSensor(this, numOfSensors, 1, 0, 0);
    Register(fSensors[0]);
    fSensors[0]->InstallIn(this);  
    SetDaughter(fSensors[0]);

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
  }
#endif
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VTXLadder::Cabling()
{
  if(!GetLV()) Assemble();

  if (OpenParameterList()->IsLadderSD()){
    J4VTXLadderSD* sd = new J4VTXLadderSD(this);
    Register(sd);
    SetSD(sd);
  }
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VTXLadder::InstallIn(J4VComponent         *mother,
                            G4RotationMatrix     *prot, 
                            const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 

  G4int layerID        = mother->GetMyID();
  G4int ladderID       = GetCopyNo();
  
  G4ThreeVector xyzLadder  = 
    OpenParameterList()->GetLadderPosition(layerID,ladderID);
  G4double angle      = 
    OpenParameterList()->GetLadderAngle(layerID,ladderID);
  
  // Placement into mother object ------//
  G4RotationMatrix* rot = new G4RotationMatrix;
  rot->rotateZ(angle);
  SetPVPlacement(rot,xyzLadder);
  
  if (!GetSD()) Cabling(); 
}


//* Draw  --------------------------------------------------------
void J4VTXLadder::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4VTXLadder::Print() const
{
}

	
	
