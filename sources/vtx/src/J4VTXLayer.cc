// $Id$
//*************************************************************************
//* --------------------
//* J4VTXLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2002/11/19  T.Aso       Modify to use ParameterList.
//*************************************************************************

#include "J4VTXLayer.hh"
#include "G4Tubs.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4VTXLayer::fFirstName("Layer");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4VTXLayer::J4VTXLayer(J4VDetectorComponent* parent,
  		  	              G4int  nbrothers, 
  		  	              G4int  me) :
  	   J4VVTXDetectorComponent(fFirstName, parent, 1,nbrothers, me),
           fLadders(0)
{   

  // Define Layer parameters ----------------//    

}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXLayer::~J4VTXLayer()
{

  G4int layerID = GetMyID();
  if (fLadders) {   
    for (G4int i = 0; i < OpenParameterList()->GetNLadders(layerID) ; i++) {
     if(Deregister(fLadders[i])) delete fLadders [i];
    } 
    if (Deregister(fLadders)) delete [] fLadders;
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTXLayer::Assemble() 
{   

    J4VTXParameterList* list = OpenParameterList();
    G4int layerID = GetMyID();

    G4double   rmin = list->GetLayerInnerRadius(layerID);
    G4double   rmax = list->GetLayerOuterRadius(layerID);
    G4double   len  = 
      ((G4Tubs *)GetMother()->GetLV()->GetSolid())->GetZHalfLength();
    G4double   totalPhi=
      ((G4Tubs *)GetMother()->GetLV()->GetSolid())->GetDeltaPhiAngle();


  if (!GetLV())
  {	  
    // define geometry
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, totalPhi );
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(list->GetLayerMaterial()));
    // SetVisAttribute ----//
    PaintLV(list->GetLayerVisAtt() , list->GetLayerColor());    
        
    // Install daughter PV //
    // Install Ladder      //
    G4int numOfLadders = list->GetNLadders(layerID);
 
    // make pointer array for Ladder...
    fLadders = new J4VTXLadder* [numOfLadders]; 
    Register(fLadders);
    
    // make first ladder object (MUST define copyNo as 0)
    fLadders[0] = new J4VTXLadder(this,numOfLadders, 1, 0, 0);
    Register(fLadders[0]);

    // copy ladder objects (copyNo must start from 1)
    G4int copyNo;
    for (copyNo = 1; copyNo < numOfLadders; copyNo++) {
    	fLadders[copyNo] = new J4VTXLadder(*fLadders[0], copyNo);
        Register(fLadders[copyNo]);
    }
    
    // install ladder objects...    
    for (copyNo = 0 ; copyNo < numOfLadders; copyNo++) {
       fLadders[copyNo]->InstallIn(this);  
       SetDaughter(fLadders[copyNo]);
    }
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VTXLayer::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VTXLayer::InstallIn(J4VComponent         *mother,
                           G4RotationMatrix     *prot, 
                           const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//
  
  SetPVPlacement();
  
}


//* Draw  --------------------------------------------------------
void J4VTXLayer::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4VTXLayer::Print() const
{
}

	
	
