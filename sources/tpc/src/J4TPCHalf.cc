//*************************************************************************
//* --------------------
//* J4TPCHalf
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4TPCHalf.hh"
#include "J4TPCParameterList.hh"
#include "J4TPCEndcap.hh"
#include "J4TPCSupportTub.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4TPCHalf::fFirstName("TPCHalf");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4TPCHalf::J4TPCHalf(J4VDetectorComponent *parent,
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

J4TPCHalf::~J4TPCHalf()
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

void J4TPCHalf::Assemble() 
{   
  if(!GetLV()){
  	
    J4TPCParameterList *list = OpenParameterList(); 
    G4double rmin = list->GetTPCInnerR(); 
    G4double rmax = list->GetTPCOuterR();
    G4double len  = list->GetTPCHalfZ() / 2;
    G4double dphi = list->GetTPCDeltaPhi();
  	
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(list->GetTPCMaterial()));
    
    // SetVisAttribute ----//
    PaintLV(list->GetTPCVisAtt(), list->GetTPCColor());
  	
    // Install daughter PV //
    // Install Layer       //
  		  
    G4int  nlayers = list->GetNlayers();
    fLayers = new J4TPCLayer* [nlayers];
    Register(fLayers);
    for (G4int i = 0; i < nlayers + 1; i++) {     // "+ 1" <- t0 detector
      fLayers [i] = new J4TPCLayer(this, 1, nlayers, i);
      Register(fLayers [i]);
      fLayers [i]->InstallIn(this);  
      
      SetDaughter(fLayers[i]);
    }  
    
    // Install SupportTub       //
                                                                                
    G4double otubInnerR  = list->GetOuterSupportTubInnerR();
    G4double otubOuterR  = list->GetOuterSupportTubOuterR();
    G4double itubInnerR  = list->GetInnerSupportTubInnerR();
    G4double itubOuterR  = list->GetInnerSupportTubOuterR();
    G4double tublen      = list->GetSupportTubHalfZ() / 2;
    G4double tubdphi     = list->GetSupportTubDeltaPhi();
                                                                                
    fOuterSupportTub = new J4TPCSupportTub(otubInnerR, otubOuterR, tublen,
                                                   tubdphi, this);
    Register(fOuterSupportTub);
    fOuterSupportTub->InstallIn(this);
    SetDaughter(fOuterSupportTub);
                                                                                
    fInnerSupportTub = new J4TPCSupportTub(itubInnerR, itubOuterR, tublen,
                                                   tubdphi, this);
    Register(fInnerSupportTub);
    fInnerSupportTub->InstallIn(this);
    SetDaughter(fInnerSupportTub);

    // Install Endcap
                                                                               
    fEndcaps = new J4TPCEndcap(this);
    Register(fEndcaps);
    fEndcaps->InstallIn(this);
    SetDaughter(fEndcaps);

    // Install CentralMembrane
                                                                                
    fCentralMembrane = new J4TPCCentralMembrane(this);
    Register(fCentralMembrane);
    fCentralMembrane->InstallIn(this);
    SetDaughter(fCentralMembrane);

    // Install PadPlane
                                                                                
    fPadPlanes = new J4TPCPadPlane(this);
    Register(fPadPlanes);
    fPadPlanes->InstallIn(this);
    SetDaughter(fPadPlanes);

  }
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4TPCHalf::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4TPCHalf::InstallIn(J4VComponent        *,
                          G4RotationMatrix    *,
                          const G4ThreeVector &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  G4double z = OpenParameterList()->GetTPCHalfZ() / 2;

  if (GetMyID()) {
    G4ThreeVector tlate(0., 0., z);
    SetPVPlacement(0, tlate);
  }
  else {
    G4ThreeVector xv(1., 0., 0);
    G4ThreeVector yv(0.,-1., 0);
    G4ThreeVector zv(0., 0.,-1);
    G4RotationMatrix *rotMat = new G4RotationMatrix();
    rotMat->rotateAxes(xv, yv, zv);
    G4ThreeVector tlate(0., 0., -z);  

    SetPVPlacement(rotMat, tlate);
  }
}



//* Draw  --------------------------------------------------------
void J4TPCHalf::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4TPCHalf::Print() const
{
}

