// $Id$
//*************************************************************************
//* --------------------
//* J4MUDBlock
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "J4MUDParameterList.hh"
#include "J4MUDBlock.hh"
#include "J4MUDEndcapAbs.hh"
#include "J4MUDEndcapActive.hh"
#include "J4MUDEndcapActiveSD.hh"
#include "J4MUDBarrelAbs.hh"
#include "J4MUDBarrelActive.hh"
#include "J4MUDBarrelActiveSD.hh"
#include "J4UnionSolid.hh"
#include "G4Tubs.hh"

#ifdef __FRONTENDCAP__
 #include "J4MUDFrontEndcapAbs.hh"
 #include "J4MUDFrontEndcapActive.hh"
 #include "J4MUDFrontEndcapActiveSD.hh"
#endif

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------
G4String J4MUDBlock::fFirstName( "Block" );

//=====================================================================
//* constructor -------------------------------------------------------
J4MUDBlock::J4MUDBlock( J4VDetectorComponent* parent,
                                       G4int  nclones,
                                       G4int  nbrothers, 
                                       G4int  me,
                                       G4int  copyno )
: J4VMUDDetectorComponent( fFirstName, parent, nclones, nbrothers, me, copyno )
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4MUDBlock::~J4MUDBlock()
{
  J4MUDParameterList* ptrList = OpenParameterList();

  for ( G4int i = 0; i < 2*ptrList->GetEndcapNAbsLayers(); i++ ) {
     if ( Deregister( fEndcapAbs[i] ) ) delete fEndcapAbs [i];
   }
   if ( Deregister( fEndcapAbs ) ) delete [] fEndcapAbs;

  for ( G4int i = 0; i < 2*ptrList->GetEndcapNActiveLayers(); i++ ) {
    if ( Deregister( fEndcapActive[i] ) ) delete fEndcapActive [i];
  }
  if ( Deregister( fEndcapActive ) ) delete [] fEndcapActive;


  for ( G4int i = 0; i < ptrList->GetBarrelNAbsLayers(); i++ ) {
    if ( Deregister( fBarrelAbs[i] ) ) delete fBarrelAbs [i];
  }
  if ( Deregister( fBarrelAbs ) ) delete [] fBarrelAbs;

  for ( G4int i = 0; i < ptrList->GetBarrelNActiveLayers(); i++ ) {
    if ( Deregister( fBarrelActive[i] ) ) delete fBarrelActive [i];
  }
  if ( Deregister( fBarrelActive ) ) delete [] fBarrelActive;
  
#ifdef __FRONTENDCAP__
  for ( G4int i = 0; i < 2*ptrList->GetFrontEndcapNAbsLayers(); i++ ) {
     if ( Deregister( fFrontEndcapAbs[i] ) ) delete fFrontEndcapAbs [i];
   }
   if ( Deregister( fFrontEndcapAbs ) ) delete [] fFrontEndcapAbs;

  for ( G4int i = 0; i < 2*ptrList->GetFrontEndcapNActiveLayers(); i++ ) {
    if ( Deregister( fFrontEndcapActive[i] ) ) delete fFrontEndcapActive [i];
  }
  if ( Deregister( fFrontEndcapActive ) ) delete [] fFrontEndcapActive;
#endif
  
}

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4MUDBlock::Assemble() 
{   
  if ( !GetLV() ) {
  	
    J4MUDParameterList* ptrList = OpenParameterList(); 
    G4double rmin             = ptrList->GetMUDInnerR(); 
    G4double rmax             = ptrList->GetMUDOuterR();
    G4double endcap           = 0.5*( ptrList->GetEndcapThick() );
    G4double endcaprmin       = ptrList->GetEndcapInnerR();

#ifdef __FRONTENDCAP__

 #ifdef __MUDREPLICA__
    G4double dphi             = ptrList->GetMUDDeltaPhi();
    G4double sphi             = 0.0;
 #else
    G4int    myID             = GetMyID();
    G4double dphi             = ptrList->GetTrapDeltaPhi();
    G4double sphi             = dphi*myID - 0.5*dphi;
 #endif
 
    G4double len              = ptrList->GetMUDHalfL() - ptrList->GetEndcapThick();
    G4double endcapfront      = ptrList -> GetEndcapFrontZ();
    G4double frontEndcap      = 0.5*( ptrList->GetFrontEndcapThick() );
    G4double frontEndcaprmin  = ptrList->GetEndcapInnerR();
    G4double frontEndcaprmax  = ptrList->GetFrontEndcapOuterR();
    G4double frontEndcapFront = ptrList->GetFrontEndcapFrontZ();

    G4String  barrelName( GetName() ); barrelName += ".Barrel";
    G4VSolid* ptrBarrel = new G4Tubs( barrelName, rmin, rmax, len, sphi, dphi );
    G4String  endcapName( GetName() ); endcapName += ".Endcap";
    G4VSolid* ptrEndcap = new G4Tubs( endcapName, endcaprmin, rmax, endcap, sphi, dphi );
    G4String  frontEndcapName( GetName() ); frontEndcapName += ".FrontEndcap";
    G4VSolid* ptrFrontEndcap = new G4Tubs( frontEndcapName, frontEndcaprmin, frontEndcaprmax, frontEndcap, sphi, dphi );

    G4String solid1name( GetName() ); solid1name += ".solid1";
    G4ThreeVector tlate1( 0, 0, frontEndcapFront+frontEndcap );
    G4VSolid* solid1 = new J4UnionSolid( solid1name, ptrBarrel, ptrFrontEndcap, 0, tlate1 );
    
    G4String solid2name( GetName() ); solid2name += ".solid2";
    G4ThreeVector tlate2( 0, 0, -1*(frontEndcapFront+frontEndcap) );
    G4VSolid* solid2 = new J4UnionSolid( solid2name, solid1, ptrFrontEndcap, 0, tlate2 );
    
    G4String solid3name( GetName() ); solid3name += ".solid3";
    G4ThreeVector tlate3( 0, 0, endcapfront+endcap );
    G4VSolid* solid3 = new J4UnionSolid( solid3name, solid2, ptrEndcap, 0, tlate3 );
    G4ThreeVector tlate4( 0, 0, -1*(endcapfront+endcap) );
    G4VSolid* ptrBlockSolid = new J4UnionSolid( GetName(), solid3, ptrEndcap, 0, tlate4 );
    Register(ptrBlockSolid);
    SetSolid(ptrBlockSolid);
#else

    G4double len     = ptrList->GetMUDHalfL();

 #ifdef __MUDREPLICA__
    G4double dphi             = ptrList->GetMUDDeltaPhi();
    G4double sphi             = -0.5*45*deg;
 #else
    G4int    myID             = GetMyID();
    G4double dphi             = ptrList->GetTrapDeltaPhi();
    G4double sphi             = dphi*myID - 0.5*dphi;
 #endif
 
    // MakeSolid ----------//
    OrderNewTubs( rmin, rmax, len, dphi, endcap, endcaprmin, sphi );
#endif

    // MakeLogicalVolume --//  
    MakeLVWith( OpenMaterialStore()->Order( ptrList->GetBlockMaterial() ) );
    
    // SetVisAttribute ----//
    PaintLV( ptrList->GetBlockVisAtt(), ptrList->GetBlockColor() );

    const G4int nEndcapAbs         = ptrList->GetEndcapNAbsLayers();
    const G4int nEndcapActive      = ptrList->GetEndcapNActiveLayers();
    const G4int nBarrelAbs         = ptrList->GetBarrelNAbsLayers();
    const G4int nBarrelActive      = ptrList->GetBarrelNActiveLayers();

    fEndcapAbs         = new J4MUDEndcapAbs*         [2*nEndcapAbs];
    fEndcapActive      = new J4MUDEndcapActive*      [2*nEndcapActive];
    fBarrelAbs         = new J4MUDBarrelAbs*         [nBarrelAbs];
    fBarrelActive      = new J4MUDBarrelActive*      [nBarrelActive];

    Register( fEndcapAbs );
    Register( fEndcapActive );
    Register( fBarrelAbs );
    Register( fBarrelActive );

    for ( G4int i = 0; i < 2*nEndcapAbs; i++ ) {
      fEndcapAbs[i] = new J4MUDEndcapAbs( this, 1, 2*nEndcapAbs, i );
      Register( fEndcapAbs[i] );
      fEndcapAbs[i] -> InstallIn( this );
      SetDaughter( fEndcapAbs[i] );
    }
    
    for ( G4int i = 0; i < 2*nEndcapActive; i++ ) {
      fEndcapActive[i] = new J4MUDEndcapActive( this, 1, 2*nEndcapActive, i );
      Register( fEndcapActive[i] );
      fEndcapActive[i] -> InstallIn( this );
      SetDaughter( fEndcapActive[i] );
    }

    for ( G4int i = 0; i < nBarrelAbs; i++ ) {
      fBarrelAbs[i] = new J4MUDBarrelAbs( this, 1, nBarrelAbs, i );
      Register( fBarrelAbs[i] );
      fBarrelAbs[i] -> InstallIn( this );
      SetDaughter( fBarrelAbs[i] );
    }
    
    for ( G4int i = 0; i < nBarrelActive; i++ ) {
      fBarrelActive[i] = new J4MUDBarrelActive( this, 1, nBarrelActive, i );
      Register( fBarrelActive[i] );
      fBarrelActive[i] -> InstallIn( this );
      SetDaughter( fBarrelActive[i] );
    }

#ifdef __FRONTENDCAP__
    const G4int nFrontEndcapAbs    = ptrList->GetFrontEndcapNAbsLayers();
    const G4int nFrontEndcapActive = ptrList->GetFrontEndcapNActiveLayers();
    fFrontEndcapAbs    = new J4MUDFrontEndcapAbs*    [2*nFrontEndcapAbs];
    fFrontEndcapActive = new J4MUDFrontEndcapActive* [2*nFrontEndcapActive];
    Register( fFrontEndcapAbs );
    Register( fFrontEndcapActive );
    
    for ( G4int i = 0; i < 2*nFrontEndcapAbs; i++ ) {
      fFrontEndcapAbs[i] = new J4MUDFrontEndcapAbs( this, 1, 2*nFrontEndcapAbs, i );
      Register( fFrontEndcapAbs[i] );
      fFrontEndcapAbs[i] -> InstallIn( this );
      SetDaughter( fFrontEndcapAbs[i] );
    }
    
    for ( G4int i = 0; i < 2*nFrontEndcapActive; i++ ) {
      fFrontEndcapActive[i] = new J4MUDFrontEndcapActive( this, 1, 2*nFrontEndcapActive, i );
      Register( fFrontEndcapActive[i] );
      fFrontEndcapActive[i] -> InstallIn( this );
      SetDaughter( fFrontEndcapActive[i] );
    }
#endif
    
  }
}

//=====================================================================
//* Cabling -----------------------------------------------------------
void J4MUDBlock::Cabling() { }

///=====================================================================
//* InstallIn  --------------------------------------------------------
void J4MUDBlock::InstallIn( J4VComponent*        /* mother */,
                            G4RotationMatrix*    /* prot   */, 
                            const G4ThreeVector& /* tlate  */ ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.

#ifdef __MUDREPLICA__
  G4double dphi = OpenParameterList()->GetTrapDeltaPhi();
  SetPVReplica( kPhi, dphi );
#else
  SetPVPlacement();
#endif

 Cabling();
}
