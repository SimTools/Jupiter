// $Id$
//*************************************************************************
//* --------------------
//* J4MUD
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "J4MUD.hh"
#include "J4MUDParameterList.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------
G4String J4MUD::fFirstName( "MUD" );

//=====================================================================
//* constructor -------------------------------------------------------
J4MUD::J4MUD( J4VDetectorComponent* parent,
                             G4int  nclones,
                             G4int  nbrothers, 
                             G4int  me,
                             G4int  copyno )
: J4VMUDDetectorComponent( fFirstName, parent, nclones, nbrothers, me, copyno ),
  fEndcaps(0), fLayers(0)
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4MUD::~J4MUD()
{
  J4MUDParameterList *ptrList = OpenParameterList(); 
  if ( fEndcaps ) {
    for ( G4int i = 0; i < 2*ptrList->GetNEndcapLayers(); i++ ) {
      if ( Deregister( fEndcaps[i] ) ) delete fEndcaps [i];
    }
    if ( Deregister( fEndcaps ) ) delete [] fEndcaps;
  }

  if ( fLayers ) {	
    for ( G4int i = 0; i < ptrList->GetNBarrelLayers(); i++ ) {
      if ( Deregister( fLayers[i] ) ) delete fLayers [i];
    } 
    if ( Deregister( fLayers ) ) delete [] fLayers;
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4MUD::Assemble() 
{   
  if ( !GetLV() ) {
  	
    J4MUDParameterList* ptrList = OpenParameterList(); 
    G4double rmin = ptrList->GetMUDInnerR(); 
    G4double rmax = ptrList->GetMUDOuterR();
    G4double len  = ptrList->GetMUDHalfZ();
    G4double dphi = ptrList->GetMUDDeltaPhi();
    G4double endcap = 0.5*( ptrList->GetEndcapThickness() );
    G4double endcaprin = ptrList->GetEndcapInnerR();
  	
    // MakeSolid ----------//
    OrderNewTubs( rmin, rmax, len, dphi,endcap, endcaprin );
    
    // MakeLogicalVolume --//  
    MakeLVWith( OpenMaterialStore()->Order( ptrList->GetMUDMaterial() ) );
    
    // SetVisAttribute ----//
    PaintLV( ptrList->GetMUDVisAtt(), ptrList->GetMUDColor() );

    // Here, we should install doughter volumes
    // J4MUDLayer, J4MUDEndcap, J4MUD
    const G4int  nEndcapLayers = ptrList->GetNEndcapLayers();
    const G4int  nBarrelLayers = ptrList->GetNBarrelLayers();
    
    // Install Endcap layers ---//
    fEndcaps = new J4MUDEndcap* [2*nEndcapLayers];
    Register( fEndcaps );
    for ( G4int i = 0; i < 2*nEndcapLayers; i++ ) {
      fEndcaps[i] = new J4MUDEndcap( this, 1, 2*nEndcapLayers, i );
      Register( fEndcaps[i] );
      fEndcaps[i] -> InstallIn( this );
      SetDaughter( fEndcaps[i] );
    }

    // Install Barrrel layers ---//
    fLayers = new J4MUDBarrel* [nBarrelLayers];
    Register( fLayers );
    for ( G4int i = 0; i < nBarrelLayers ; i++ ) {
      fLayers [i] = new J4MUDBarrel( this, 1 , nBarrelLayers , i );
      Register( fLayers[i] );
      fLayers [i]->InstallIn( this );
      SetDaughter( fLayers[i] );
    } 
  }
}

///=====================================================================
//* InstallIn  --------------------------------------------------------
void J4MUD::InstallIn( J4VComponent*        /* mother */,
                       G4RotationMatrix*    /* prot   */, 
                       const G4ThreeVector& /* tlate  */ ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  
  SetPVPlacement();
}
