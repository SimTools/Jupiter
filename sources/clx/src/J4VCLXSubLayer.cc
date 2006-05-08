// $Id$
//*************************************************************************
//* --------------------
//* J4VCLXSubLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*     2005/05/01  H.Ono      Original version
//*************************************************************************
#include "J4Timer.hh"
#include "G4Trap.hh"
#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXStrip.hh"
#include "J4VCLXTrapStrip.hh"
#include "J4VCLXSubLayer.hh"
#include "J4CLXParameterList.hh"
#include "J4ParameterTable.hh"

//====================================================================
//---------------------
// Class Description
//---------------------

//====================================================================
//* constructor ------------------------------------------------------
J4VCLXSubLayer::J4VCLXSubLayer( G4bool isBarrel, 
				const G4String &name,
				J4VDetectorComponent *parent,
				G4int nclones,
				G4int nbrothers,
				G4int me,
				G4int copyno )
  : J4VCLXDetectorComponent( name, parent, nclones, nbrothers, me, copyno )
  ,fIsBarrel( isBarrel )
{
}

//====================================================================
//* destructor -------------------------------------------------------
J4VCLXSubLayer::~J4VCLXSubLayer()
{
  G4int nTrapStrips = fTrapStrips.size();
  for ( G4int i = 0; i < nTrapStrips; i++ ) {
    if ( fTrapStrips[i] ) delete fTrapStrips[i];
  }
}

//====================================================================
//* Assemble ---------------------------------------------------------
void J4VCLXSubLayer::Assemble()
{
  if ( !GetLV() ) {

    //* tolerance for each layer
    G4double layertol = OpenParameterList()->GetLayerTolerance();

    G4int    myID = GetMyID();
    G4double px   = GetHalfX( myID ) -0.5*layertol;
    G4double plx  = GetHalfXL( myID ) -0.5*layertol;
    //G4double py   = 0.5*( GetYmax( myID ) - GetYmin( myID ) );
    //G4double pz   = GetHalfZ( myID );
    G4double py   = 0.5*( GetYmax( myID ) - GetYmin( myID ) -layertol );
    G4double pz   = GetHalfZ( myID ) - 0.5*layertol;
    G4double phi  = GetSphi( myID );
    
    G4Trap* ptrTrap = new G4Trap( GetName(), pz, 0., phi, py, px, plx, 0., py, px, plx, 0. );
    Register( ptrTrap );
    SetSolid( ptrTrap );
    
    // MakeLogicalVolume --//
    MakeLVWith( OpenMaterialStore()->Order( GetMaterial() ) );
    
    // SetVisAttribute ----//
    PaintLV( GetVisAtt(), GetColor() );

    //* Install Daughter volume

    G4double cellSize  = OpenParameterList()->GetCellSize();
    G4int    nTrapStrips   = ( IsBarrel() )
                          ? 2*(G4int)( pz / cellSize )
                          : 2*(G4int)( py / cellSize );

    J4VCLXTrapStrip* trap = 0;
    
    if ( IsActive() ) {
      if ( IsBarrel() ) { // Barrel part
	trap = Create( this, nTrapStrips );
	fTrapStrips.push_back( trap );
	Register( trap );
	trap->InstallIn( this );
	SetDaughter( trap );
      } else {                 // Endcap part
	for ( G4int i = 0; i < nTrapStrips; i++ ) {
	  trap = Create( this, 1, nTrapStrips, i );
	  fTrapStrips.push_back( trap );
	  Register( trap );
	  trap->InstallIn( this );
	  SetDaughter( trap );
	}
      }     
    }

  }
}

//====================================================================
//* Cabling ----------------------------------------------------------
void J4VCLXSubLayer::Cabling()
{
}

//====================================================================
// * InstallIn -------------------------------------------------------
void J4VCLXSubLayer::InstallIn( J4VComponent*        /*mother*/,
                                G4RotationMatrix*    /*prot*/  ,
                                const G4ThreeVector& /*tlate*/   )
{
  //* First call Assemble
  Assemble();

  //* User defined limits for time cut, step cut
  G4UserLimits *myLimits = new G4UserLimits();
  G4double umaxtime = J4ParameterTable::GetValue("J4CLX.UserMaxTime",1000.0)*nanosecond;
  myLimits->SetUserMaxTime( umaxtime );
  GetLV()->SetUserLimits( myLimits );
  
  J4CLXParameterList* ptrList = OpenParameterList();

  const G4int nSubLayers = ( IsEM() ) ? ptrList->GetEMNSubLayers()
                                      : ptrList->GetHDNSubLayers();

  G4double* layerThick = new G4double [nSubLayers];
  layerThick[0] = ( IsEM() ) ? ptrList->GetEMAbsLayerThickness()       
                             : ptrList->GetHDAbsLayerThickness();
  layerThick[1] = ( IsEM() ) ? ptrList->GetEMActiveLayerThickness()       
                             : ptrList->GetHDActiveLayerThickness();
  layerThick[2] = ( IsEM() ) ? ptrList->GetEMFlexLayerThickness()       
                             : ptrList->GetHDFlexLayerThickness();

  G4double motherThick = ( IsEM() ) ? ptrList->GetEMLayerThickness()       
                                    : ptrList->GetHDLayerThickness();

/*
  G4double activeThick = ( IsEM() ) ? ptrList->GetEMActiveLayerThickness() 
                                    : ptrList->GetHDActiveLayerThickness();
  G4double absThick    = ( IsEM() ) ? ptrList->GetEMAbsLayerThickness()    
                                    : ptrList->GetHDAbsLayerThickness();
  G4double flexThick   = ( IsEM() ) ? ptrList->GetEMFlexLayerThickness()
                                    : ptrList->GetHDFlexLayerThickness();
*/
  
  
  G4int    myID = GetMyID();
  G4double px   = 0.;
  G4double py   = -0.5*motherThick;
  G4double pz   = -0.5*motherThick;

  for ( G4int i = 0; i <= myID; i++ ) {
    if ( i == myID ) {
      py += 0.5*layerThick[i];
      pz += 0.5*layerThick[i];
    } else {
      py += layerThick[i];
      pz += layerThick[i];
    }
  }

#if 0
  G4double py = ( IsActive() ) ? 0.5*activeThick + absThick - 0.5*motherThick
                               : 0.5*absThick -0.5*motherThick;
  G4double pz = ( IsActive() ) ? 0.5*activeThick + absThick - 0.5*motherThick
                               : 0.5*absThick -0.5*motherThick;
#endif

  py *= ( IsBarrel() ) ? 1 : 0; // Endcap py = 0
  pz *= ( IsBarrel() ) ? 0 : 1; // Barrel pz = 0

  G4ThreeVector position( px, py, pz ) ;
  SetPVPlacement( 0, position );

  Cabling();
}

//====================================================================
// * Draw ------------------------------------------------------------
void J4VCLXSubLayer::Draw() { }

//====================================================================
// * Print -----------------------------------------------------------
void J4VCLXSubLayer::Print() const { }
