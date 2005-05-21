//*************************************************************************
//* --------------------
//* J4TPCDriftRegion
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4TPCDriftRegion.hh"
#include "J4TPCDriftRegionSD.hh"
#include "J4TPCParameterList.hh"
#include "J4TPCEndcap.hh"
#include "J4TPCSupportTub.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4TPCDriftRegion::fFirstName("DriftRegion");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4TPCDriftRegion::J4TPCDriftRegion(J4VDetectorComponent *parent,
                                    G4int  nclones,
                                    G4int  nbrothers, 
                                    G4int  me,
                                    G4int  copyno ) :
           J4VTPCDetectorComponent( fFirstName, parent, nclones,
                                    nbrothers, me, copyno ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4TPCDriftRegion::~J4TPCDriftRegion()
{
  J4TPCParameterList *list = OpenParameterList(); 
  if (fLayers){	
    for (G4int i = 0; i < list->GetNlayers(); i++) {
      if(Deregister(fLayers[i])) delete fLayers [i];
    } 
    if (Deregister(fLayers)) delete [] fLayers;
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4TPCDriftRegion::Assemble() 
{   
  if(!GetLV()){
  	
    J4TPCParameterList *list = OpenParameterList(); 
    G4double rmin = list->GetInnerSupportTubOuterR(); 
    G4double rmax = list->GetOuterSupportTubInnerR();
    G4double len  = list->GetDriftRegionHalfZ();
    G4double dphi = list->GetDriftRegionDeltaPhi();
  	
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(list->GetDriftRegionMaterial()));
    
    // SetVisAttribute ----//
    PaintLV(list->GetDriftRegionVisAtt(), list->GetDriftRegionColor());
  	
    // Install daughter PV //
    // Install Layer       //
  		  
    G4int  nlayers = list->GetNlayers();
    fLayers = new J4TPCLayer* [nlayers];
    Register(fLayers);
    for (G4int i = 0; i < nlayers; i++) { 
      fLayers [i] = new J4TPCLayer(this, 1, nlayers, i);
      G4ThreeVector tlate(0., 0., 0.);
      Register(fLayers [i]);
      fLayers [i]->InstallIn(this, 0, tlate);  
      
      SetDaughter(fLayers[i]);
    }  

  }
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4TPCDriftRegion::Cabling()
{
  J4TPCDriftRegionSD *sd = new J4TPCDriftRegionSD(this);
  Register(sd);
  SetSD(sd);
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4TPCDriftRegion::InstallIn(J4VComponent        *,
                                 G4RotationMatrix    *,
                                 const G4ThreeVector &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  J4TPCParameterList *list = OpenParameterList();
  G4double z = list->GetCentralMembraneHalfThick() / 2
             - list->GetEndcapHalfThick()
             - list->GetPadPlaneHalfThick();
              
  G4ThreeVector tlate(0., 0., z);
  SetPVPlacement(0, tlate);

  if (!GetSD()) Cabling();
}


//* Draw  --------------------------------------------------------
void J4TPCDriftRegion::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4TPCDriftRegion::Print() const
{
}

