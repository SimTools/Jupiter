// $Id$
//*************************************************************************
//* --------------------
//* J4VCLXTrapStrip
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
#include "J4VCLXSubLayer.hh"
#include "J4VCLXTrapStrip.hh"
#include "J4VCLXStrip.hh"
#include "J4VCLXCell.hh"
#include "J4CLXParameterList.hh"
#include "J4ParameterTable.hh"

//====================================================================
//---------------------
// Class Description
//---------------------

//====================================================================
//* constructor ------------------------------------------------------
J4VCLXTrapStrip::J4VCLXTrapStrip( G4bool isBarrel,
                                  const G4String &name,
                                  J4VDetectorComponent *parent,
                                  G4int nclones,
                                  G4int nbrothers,
                                  G4int me,
                                  G4int copyno )
  : J4VCLXDetectorComponent( name, parent, nclones, nbrothers, me, copyno )
  ,fIsBarrel( isBarrel)
{
}

//====================================================================
//* destructor -------------------------------------------------------
J4VCLXTrapStrip::~J4VCLXTrapStrip()
{
  //  if ( fStrip ) delete fStrip;  
  for ( G4int i = 0; i < (G4int)fStrips.size(); i++ ) {
    if ( fStrips[i] ) delete fStrips[i]; 
  }
}

//====================================================================
//* Assemble ---------------------------------------------------------
void J4VCLXTrapStrip::Assemble()
{
  if ( !GetLV() ) {

    J4CLXParameterList* ptrList = OpenParameterList();
    G4int    myID      = GetMyID();
    G4Trap*  mother    = (G4Trap*)( GetMother()->GetSolid() );
    G4double cellSize  = ptrList->GetCellSize();
    G4double tolerance = ptrList->GetLayerTolerance();

    G4double motherHalfY = mother->GetYHalfLength1();
    G4double motherHalfZ = mother->GetZHalfLength();

    G4double px   = ( IsBarrel() ) ? mother->GetXHalfLength1()
                                   : mother->GetXHalfLength1()+myID*cellSize*std::tan( 0.5*ptrList->GetTrapDeltaPhi() );
    G4double plx  = ( IsBarrel() ) ? mother->GetXHalfLength2()
                                   : px + cellSize*std::tan( 0.5*ptrList->GetTrapDeltaPhi() );
    G4double py   = ( IsBarrel() ) ? motherHalfY  : 0.5*cellSize -tolerance;
    G4double pz   = ( IsBarrel() ) ? 0.5*cellSize : motherHalfZ;
    G4double phi    = 0;
    
    G4Trap* ptrTrap = new G4Trap( GetName(), pz, 0., phi, py, px, plx, 0., py, px, plx, 0. );
    Register( ptrTrap );
    SetSolid( ptrTrap );
    
    // MakeLogicalVolume --//
    MakeLVWith( OpenMaterialStore()->Order( GetMaterial() ) );
    
    // SetVisAttribute ----//
    PaintLV( GetVisAtt(), GetColor() );
    
    //* Install daughter volume of strips
    J4VCLXStrip* stripPtr = 0;
    G4int nStrips = 3;

    for ( G4int i = 0; i < nStrips; i++ ) {
      if ( i == 1 ) { // center strip
	stripPtr = Create( this, 1, nStrips, i );
      } else {        // boundary strip
	stripPtr = CreateBound( this, 1, nStrips, i );
      }
      fStrips.push_back( stripPtr );
      Register( stripPtr );
      stripPtr->InstallIn( this );
      SetDaughter( stripPtr );
    }
  }
}

//====================================================================
//* Cabling ----------------------------------------------------------
void J4VCLXTrapStrip::Cabling()
{
}

//====================================================================
// * InstallIn -------------------------------------------------------
void J4VCLXTrapStrip::InstallIn( J4VComponent*        /*mother*/,
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

  G4int    myID         = GetMyID();
  G4double motherHalfY  = ((G4Trap*)GetMother()->GetSolid())->GetYHalfLength1();
  G4double cellSize     = OpenParameterList()->GetCellSize();

  G4double px = 0;
  G4double py = -motherHalfY + (myID+0.5)*cellSize;
  G4double pz = 0;

  G4ThreeVector position( px, py, pz );

  if ( IsBarrel() ) {
    SetPVReplica( kZAxis, cellSize );
  } else {
    SetPVPlacement( 0, position );
  }
}

//====================================================================
// * Draw ------------------------------------------------------------
void J4VCLXTrapStrip::Draw() { }

//====================================================================
// * Print -----------------------------------------------------------
void J4VCLXTrapStrip::Print() const { }
