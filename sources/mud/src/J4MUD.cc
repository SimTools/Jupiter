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
//*	2005/05/26  H.Ono       Install magnetic field
//*************************************************************************
#include "J4MUD.hh"
#include "J4MUDSD.hh"
#include "J4MUDBlock.hh"
#include "J4MUDParameterList.hh"
#include "J4UnionSolid.hh"
#include "G4Tubs.hh"
#include "G4FieldManager.hh"
#include "J4MFieldMapStore.hh"
#include "G4TransportationManager.hh"
#include "G4ChordFinder.hh"
#include "J4MUDMField.hh"

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
    J4AttMFieldMap()
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4MUD::~J4MUD()
{
  J4MUDParameterList* ptrList = OpenParameterList();
  for ( G4int i = 0; i < ptrList->GetNTraps(); i++ ) {
    if ( Deregister( fBlocks[i] ) ) delete fBlocks[i]; 
  }
  if ( Deregister( fBlocks ) )  delete [] fBlocks;
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
    G4double endcapHalf       = 0.5*( ptrList->GetMUDEndcapThick() );
    G4double endcaprmin       = ptrList->GetMUDEndcapInnerR();

#ifdef __GLD_V1__
    G4double sphi             = -0.5*dphi; //0.0;
    G4double halfLength       = ptrList->GetMUDHalfL() - ptrList->GetMUDEndcapThick();
    G4double endcapfront      = ptrList->GetMUDEndcapFrontZ();
    G4double frontEndcapHalf  = 0.5*(ptrList->GetMUDFrontEndcapThick());
    G4double frontEndcaprmin  = ptrList->GetMUDEndcapInnerR();
    G4double frontEndcaprmax  = ptrList->GetMUDFrontEndcapOuterR();
    G4double frontEndcapFront = ptrList->GetMUDFrontEndcapFrontZ();

    G4String barrelName( GetName() ); barrelName += ".Barrel";
    G4VSolid* ptrBarrel = new G4Tubs( barrelName, rmin, rmax, halfLength, sphi, dphi );
    G4String EndcapName( GetName() ); EndcapName += ".Endcap";
    G4VSolid* ptrEndcap = new G4Tubs( EndcapName, endcaprmin, rmax, endcapHalf, sphi, dphi );
    G4String FrontEndcapName( GetName() ); FrontEndcapName += ".FrontEndcap"; 
    G4VSolid* ptrFrontEndcap = new G4Tubs( FrontEndcapName, frontEndcaprmin, frontEndcaprmax, frontEndcapHalf, sphi, dphi );

    G4String solid1name( GetName() ); solid1name += ".solid1";
    G4ThreeVector tlate1( 0, 0, frontEndcapFront+frontEndcapHalf );
    G4VSolid* solid1 = new J4UnionSolid( solid1name, ptrBarrel, ptrFrontEndcap, 0, tlate1 );
    G4String solid2name( GetName() ); solid2name += ".solid2";
    G4ThreeVector tlate2( 0, 0, -1*(frontEndcapFront+frontEndcapHalf) );
    G4VSolid* solid2 = new J4UnionSolid( solid2name, solid1, ptrFrontEndcap, 0, tlate2 );    
    G4String solid3name( GetName() ); solid3name += ".solid3";
    G4ThreeVector tlate3( 0, 0, endcapfront+endcapHalf );
    G4VSolid* solid3 = new J4UnionSolid( solid3name, solid2, ptrEndcap, 0, tlate3 );
    G4ThreeVector tlate4( 0, 0, -1*(endcapfront+endcapHalf) );
    G4VSolid* ptrMUDSolid = new J4UnionSolid( GetName(), solid3, ptrEndcap, 0, tlate4 );
    Register(ptrMUDSolid);
    SetSolid(ptrMUDSolid);
    
#else
    G4double len              = ptrList->GetMUDHalfL();
    OrderNewTubs( rmin, rmax, len, dphi, endcapHalf, endcaprmin );
#endif

    // MakeLogicalVolume --//  
    MakeLVWith( OpenMaterialStore()->Order( ptrList->GetMUDMaterial() ) );
    
    // SetVisAttribute ----//
    PaintLV( ptrList->GetMUDVisAtt(), ptrList->GetMUDColor() );

    const G4int nTraps = ptrList->GetNTraps();
    fBlocks = new J4MUDBlock*  [nTraps];
    for ( G4int i = 0; i < nTraps; i++ ) {
      fBlocks[i] = new J4MUDBlock( this, 1, nTraps, i );
      Register( fBlocks[i] );
      fBlocks[i] -> InstallIn( this );
      SetDaughter( fBlocks[i] );
    }

  }
}

//======================================================================
//* Cabling ------------------------------------------------------------
void J4MUD::Cabling() 
{
  if ( !GetSD() ) {
    J4MUDSD* sd = new J4MUDSD( this ); 
    Register( sd );
    SetSD( sd );
  }
}

///=====================================================================
//* InstallIn  ---------------------------------------------------------
void J4MUD::InstallIn( J4VComponent*        /* mother */,
                       G4RotationMatrix*    /* prot   */, 
                       const G4ThreeVector& /* tlate  */ ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  
  SetPVPlacement();
  
  Cabling();

  // Set magnetic field
  SetMagField();
}

//====================================================================
//* SetMagField ------------------------------------------------------
void J4MUD::SetMagField()
{
  std::cerr << "-----------------------------------------------" << std::endl;
  std::cerr << "-----------------------------------------------" << std::endl;
  std::cerr << "J4DetectorConstruction:: new J4MagneticField!!!" << std::endl;
  std::cerr << "-----------------------------------------------" << std::endl;
  std::cerr << "-----------------------------------------------" << std::endl;

  J4MUDParameterList *list = OpenParameterList();
  J4MUDMField* mfield = new J4MUDMField( list );

  if ( list->GetBField() != 0 ) {

    SetMField( mfield ); 

    G4FieldManager* fieldManager= G4TransportationManager::GetTransportationManager()->GetFieldManager();
    J4MFieldMapStore* mfManager = J4MFieldMapStore::GetInstance();
    mfManager->NameList();
    Register( mfManager );
    fieldManager->SetDetectorField( mfManager );
    fieldManager->CreateChordFinder( mfManager );
    fieldManager->GetChordFinder()-> SetDeltaChord( 3.*mm ); // if you need
    fieldManager->SetDeltaOneStep( 0.0025*mm );
    fieldManager->SetDeltaIntersection( 0.001*mm );
    InstallMField( this );
   }
}
