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
#include "J4MUDBlock.hh"
#include "J4MUDParameterList.hh"
#include "J4UnionSolid.hh"
#include "G4Tubs.hh"

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
: J4VMUDDetectorComponent( fFirstName, parent, nclones, nbrothers, me, copyno )
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4MUD::~J4MUD()
{
#ifdef __MUDREPLICA__
  if ( Deregister( fBlocks ) ) delete fBlocks; 
#else
  J4MUDParameterList* ptrList = OpenParameterList();
  for ( G4int i = 0; i < ptrList->GetNTraps(); i++ ) {
    if ( Deregister( fBlocks[i] ) ) delete fBlocks[i]; 
  }
  if ( Deregister( fBlocks ) )  delete [] fBlocks;
#endif
}

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4MUD::Assemble() 
{   
  if ( !GetLV() ) {

    J4MUDParameterList* ptrList = OpenParameterList(); 
    G4double rmin             = ptrList->GetMUDInnerR();
    G4double rmax             = ptrList->GetMUDOuterR();
    G4double dphi             = ptrList->GetMUDDeltaPhi();
    G4double endcap           = 0.5*( ptrList->GetEndcapThick() );
    G4double endcaprmin       = ptrList->GetEndcapInnerR();
 
#ifdef __FRONTENDCAP__
    G4double len              = ptrList->GetMUDHalfL() - ptrList->GetEndcapThick();
    G4double endcapfront      = ptrList->GetEndcapFrontZ();
    G4double frontEndcap      = 0.5*(ptrList->GetFrontEndcapThick());
    G4double frontEndcaprmin  = ptrList->GetEndcapInnerR();
    G4double frontEndcaprmax  = ptrList->GetFrontEndcapOuterR();
    G4double frontEndcapFront = ptrList->GetFrontEndcapFrontZ();
    
    G4String barrelName( GetName() ); barrelName += ".Barrel";
    G4VSolid* ptrBarrel = new G4Tubs( barrelName, rmin, rmax, len, 0, dphi );
    G4String letfEndcapName( GetName() ); letfEndcapName += ".EndcapLeft";
    G4VSolid* ptrLeftEndcap = new G4Tubs( letfEndcapName, endcaprmin, rmax, endcap, 0, dphi );
    G4String rightEndcapName( GetName() ); rightEndcapName += ".EndcapRight";
    G4VSolid* ptrRightEndcap = new G4Tubs( rightEndcapName, endcaprmin, rmax, endcap, 0, dphi );
    G4String leftFrontEndcapName( GetName() ); leftFrontEndcapName += ".FrontEndcapLeft";
    G4VSolid* ptrLeftFrontEndcap = new G4Tubs( leftFrontEndcapName, frontEndcaprmin, frontEndcaprmax, frontEndcap, 0, dphi );
    G4String rightFrontEndcapName( GetName() ); rightFrontEndcapName += ".FrontEndcapRight"; 
    G4VSolid* ptrRightFrontEndcap = new G4Tubs( rightFrontEndcapName, frontEndcaprmin, frontEndcaprmax, frontEndcap, 0, dphi );

    G4String solid1name( GetName() ); solid1name += ".solid1";
    G4ThreeVector tlate1( 0, 0, endcapfront+endcap );
    G4VSolid* solid1 = new J4UnionSolid( solid1name, ptrBarrel, ptrLeftEndcap, 0, tlate1 );
    G4String solid2name( GetName() ); solid2name += ".solid2";
    G4ThreeVector tlate2( 0, 0, -1*(endcapfront+endcap) );
    G4VSolid* solid2 = new J4UnionSolid( solid2name, solid1, ptrRightEndcap, 0, tlate2 );    
    G4String solid3name( GetName() ); solid3name += ".solid3";
    G4ThreeVector tlate3( 0, 0, frontEndcapFront+frontEndcap );
    G4VSolid* solid3 = new J4UnionSolid( solid3name, solid2, ptrLeftFrontEndcap, 0, tlate3 );
    G4ThreeVector tlate4( 0, 0, -1*(frontEndcapFront+frontEndcap) );
    G4VSolid* ptrMUDSolid = new J4UnionSolid( GetName(), solid3, ptrRightFrontEndcap, 0, tlate4 );
    Register(ptrMUDSolid);
    SetSolid(ptrMUDSolid);
#else
    G4double len              = ptrList->GetMUDHalfL();
    OrderNewTubs( rmin, rmax, len, dphi, endcap, endcaprmin );
#endif

    // MakeLogicalVolume --//  
    MakeLVWith( OpenMaterialStore()->Order( ptrList->GetMUDMaterial() ) );
    
    // SetVisAttribute ----//
    PaintLV( ptrList->GetMUDVisAtt(), ptrList->GetMUDColor() );

#ifdef __MUDREPLICA__
    const G4int nTraps = ptrList->GetNTraps();
    fBlocks = new J4MUDBlock( this, nTraps );
    Register( fBlocks ); 
    fBlocks -> InstallIn( this );
    SetDaughter( fBlocks ); 
#else
    const G4int nTraps = ptrList->GetNTraps();
    fBlocks = new J4MUDBlock*  [nTraps];
    for ( G4int i = 0; i < nTraps; i++ ) {
      fBlocks[i] = new J4MUDBlock( this, 1, nTraps, i );
      Register( fBlocks[i] );
      fBlocks[i] -> InstallIn( this );
      SetDaughter( fBlocks[i] );
    }
#endif

  }
}

void J4MUD::Cabling() { }

///=====================================================================
//* InstallIn  --------------------------------------------------------
void J4MUD::InstallIn( J4VComponent*        /* mother */,
                       G4RotationMatrix*    /* prot   */, 
                       const G4ThreeVector& /* tlate  */ ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  
  SetPVPlacement();
  
  Cabling();
}
