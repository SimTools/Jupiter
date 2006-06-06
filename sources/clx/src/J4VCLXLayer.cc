// $Id$
//*************************************************************************
//* --------------------
//* J4VCLXLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*     2005/05/01  H.Ono   Original Version  
//*************************************************************************
#include "G4Trap.hh"
#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXLayer.hh"
#include "J4CLXParameterList.hh"
#include "J4ParameterTable.hh"

//====================================================================
//---------------------
// Class Description
//---------------------

//====================================================================
//* constructor ------------------------------------------------------
J4VCLXLayer::J4VCLXLayer( G4bool isBarrel,
			  const G4String &name,
			  J4VDetectorComponent *parent,
			  G4int nclones,
			  G4int nbrothers,
			  G4int me,
			  G4int copyno )
  : J4VCLXDetectorComponent( name, parent, nclones, nbrothers, me, copyno )
  , fIsBarrel( isBarrel )
{}

//====================================================================
//* destructor -------------------------------------------------------
J4VCLXLayer::~J4VCLXLayer()
{
  G4int nSubLayers = (G4int)fSubLayers.size();
  for ( G4int i = 0; i < nSubLayers; i++ ) {
    if ( fSubLayers[i] ) delete fSubLayers[i];
  }
  
//  if ( Deregister( fAbsLayer )    ) delete fAbsLayer;
//  if ( Deregister( fActiveLayer ) ) delete fActiveLayer;
//  if ( Deregister( fFlexLayer )   ) delete fFlexLayer;
}

//====================================================================
//* Assemble ---------------------------------------------------------
void J4VCLXLayer::Assemble()
{
  if ( !GetLV() ) {

    //* tolerance for each layer
    G4double layertol = OpenParameterList()->GetLayerTolerance();

    J4CLXParameterList* ptrList = OpenParameterList();
    
    G4Trap* mother = (G4Trap*)(GetMother()->GetSolid());

    G4int    myID = GetMyID();

    G4double layerThick = ( IsEM() ) ? ptrList->GetEMLayerThickness()
                                     : ptrList->GetHDLayerThickness();
    G4double px   = GetHalfX( myID ) -0.5*layertol;
    G4double plx  = GetHalfXL( myID ) -0.5*layertol;
    G4double py   = ( IsBarrel() ) ? 0.5*layerThick - layertol
                                   : mother->GetYHalfLength1();
    G4double pz   = ( IsBarrel() ) ? mother->GetZHalfLength()
                                   : 0.5*layerThick - layertol;
    G4double phi  = GetSphi( myID );
    
    G4Trap* ptrTrap = new G4Trap( GetName(), pz, 0., phi, py, px, plx, 0., py, px, plx, 0. );
    Register( ptrTrap );
    SetSolid( ptrTrap );
    
    // MakeLogicalVolume --//
    MakeLVWith( OpenMaterialStore()->Order( GetMaterial() ) );
    
    // SetVisAttribute ----//
    PaintLV( GetVisAtt(), GetColor() );

    // SetDaughterVolume --//
    // Make AbsLayer and ActiveLayer objects ---//
    J4VCLXSubLayer* subLayer = 0;
    G4int nSubLayers = ( IsEM() ) ? OpenParameterList()->GetEMNSubLayers()
                                  : OpenParameterList()->GetHDNSubLayers();

    for ( G4int i = 0; i < nSubLayers; i++ ) {

      if ( i == 0 ) subLayer = CreateAbs( this, 1, nSubLayers, i );
      if ( i == 1 ) subLayer = CreateActive( this, 1, nSubLayers, i );
      if ( i == 2 ) subLayer = CreateFlex( this, 1, nSubLayers, i );
      
      fSubLayers.push_back( subLayer );
      Register( subLayer );
      subLayer->InstallIn( this );
      SetDaughter( subLayer );
    }

  }
}

//====================================================================
//* Cabling ----------------------------------------------------------
void J4VCLXLayer::Cabling()
{
}

//====================================================================
// * InstallIn -------------------------------------------------------
void J4VCLXLayer::InstallIn( J4VComponent*        /* mother*/ ,
			     G4RotationMatrix*    /* prot */ ,
			     const G4ThreeVector& /* tlate */ )
{
  //* First call Assemble
  Assemble();

  //* User defined limits for time cut, step cut
  G4UserLimits *myLimits = new G4UserLimits();
  G4double umaxtime = J4ParameterTable::GetValue("J4CLX.UserMaxTime",1000.0)*nanosecond;
  myLimits->SetUserMaxTime( umaxtime );
  GetLV()->SetUserLimits( myLimits );
  
  J4CLXParameterList* ptrList = OpenParameterList();
  G4int    myID        = GetMyID();  

  G4double layerThick  = ( IsEM() ) ? ptrList->GetEMLayerThickness() 
                                    : ptrList->GetHDLayerThickness();

  G4double motherHalfThick = ((G4Trap*)(GetMother()->GetSolid()))->GetYHalfLength1();
  
  G4double px = 0.;
  G4double py = ((G4double)myID+0.5)*layerThick -motherHalfThick;
  G4double pz = 0.;
  
  //* If motherID > nTraps, Set position to -Z
  py *= ( IsBarrel() ) ? 1. : 0.; // Endcap py = 0
  
  G4ThreeVector position( px, py, pz ) ;

  if ( IsBarrel() ) { // Barrel placed by placement
    SetPVPlacement( 0, position );
  } else { // Endcap placed by replica
    SetPVReplica( kZAxis, layerThick );
  }

  //Cabling();
}

//====================================================================
// * Draw ------------------------------------------------------------
void J4VCLXLayer::Draw() { }

//====================================================================
// * Print -----------------------------------------------------------
void J4VCLXLayer::Print() const { }
