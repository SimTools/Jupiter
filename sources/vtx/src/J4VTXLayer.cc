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
#ifdef __HOSHINA__
           fLadders(0)
#else
           fLadder(0)
#endif
{   

  // Define Layer parameters ----------------//    

    fRmin = RINNER_LAYER[me];
    fRmax = ROUTER_LAYER[me];
    fLen  = VTXMASTER_Z/2.;
    fTotalPhi = ((G4Tubs *)parent->GetLV()->GetSolid())->GetDeltaPhiAngle();
    
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXLayer::~J4VTXLayer()
{
#ifdef __HOSHINA__
  if (fLadders) {   
    G4int i;  
    for (i = 0; i < NLADDER[GetMyID()] ; i++) {
     if(Deregister(fLadders[i])) delete fLadders [i];
    } 
    if (Deregister(fLadders)) delete [] fLadders;
  }
#else
  if (Deregister(fLadder)) delete fLadder;
#endif
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTXLayer::Assemble() 
{   
  if (!GetLV())
  {	  
    // define geometry
    // MakeSolid ----------//
    OrderNewTubs (fRmin, fRmax, fLen, fTotalPhi );
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()-> Order(_LAYERMATERIAL_));
    // SetVisAttribute ----//
    PaintLV( _VTXLAYERVISATT_ , G4Color(1,0,0));    
        
    // Install daughter PV //
    // Install Ladder      //
    G4int layer = GetMyID();
    G4int numOfLadders = NLADDER[layer];
 
#ifdef __HOSHINA__

    // make pointer array for Ladder...
    fLadders = new J4VTXLadder* [numOfLadders]; 
    Register(fLadders);
    
    // make first ladder object (MUST define copyNo as 0)
    fLadders[0] = new J4VTXLadder(this,numOfLadders, 1, 0, 0);
    Register(fLadders[0]);
    fLadders[0]->InstallIn(this);  
    
    // copy ladder objects (copyNo must start from 1)
    G4int copyNo;
    for (copyNo = 1; copyNo < numOfLadders; copyNo++) {
    	fLadders[copyNo] = new J4VTXLadder(*fLadders[0], copyNo);
        Register(fLadders[copyNo]);
    }
    
    // install ladder objects...    
    for (copyNo = 1 ; copyNo < numOfLadders; copyNo++) {
       fLadders[copyNo]->InstallIn(this);  
       SetDaughter(fLadders[copyNo]);
    }
    
#else

    fLadder  = new J4VTXLadder(this,numOfLadders);
    Register(fLadders);
    fLadder->InstallIn(this);  
    SetDaughter(fLadder);

#endif
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
  G4cout << "-J4VTXLayer(mm)-  " <<G4endl;
  G4cout << "Rmin " << fRmin/mm 
       << " Rmax "<< fRmax/mm 
       <<" Z "<< fLen/mm 
       << G4endl;
  G4cout << "----------------" << G4endl;
}

	
	
