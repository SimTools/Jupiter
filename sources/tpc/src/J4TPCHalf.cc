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

G4String J4TPCHalf::fFirstName("Half");

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

J4TPCHalf::J4TPCHalf(const J4TPCHalf &orig, G4int copyno)
         : J4VTPCDetectorComponent(orig, copyno)
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4TPCHalf::~J4TPCHalf()
{
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
    // Install T0 detector       //
#if 1
    fLayer = new J4TPCLayer(this, 1, list->GetNlayers(), 0);
    Register(fLayer);
    G4ThreeVector tlate(0., 0., list->GetCentralMembraneHalfThick() / 2
                              - list->GetEndcapHalfThick()
                              - list->GetPadPlaneHalfThick());

    fLayer->InstallIn(this, 0, tlate);
    SetDaughter(fLayer);
#endif
    // Install DriftRegion       //

    fDriftRegion = new J4TPCDriftRegion(this);
    Register(fDriftRegion);
    fDriftRegion->InstallIn(this);
    SetDaughter(fDriftRegion);
    
    // Install SupportTub       //
                                                                                
    G4double otubInnerR  = list->GetOuterSupportTubInnerR();
    G4double otubOuterR  = list->GetOuterSupportTubOuterR();
    G4double itubInnerR  = list->GetInnerSupportTubInnerR();
    G4double itubOuterR  = list->GetInnerSupportTubOuterR();
    G4double tublen      = list->GetSupportTubHalfZ();
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

#if 0
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
#else
void J4TPCHalf::InstallIn(J4VComponent        *,
                          G4RotationMatrix    *rotp,
                          const G4ThreeVector &tlate) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  
  // Placement function into mother object...

  SetPVPlacement(rotp, tlate);
}
#endif



//* Draw  --------------------------------------------------------
void J4TPCHalf::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4TPCHalf::Print() const
{
}

