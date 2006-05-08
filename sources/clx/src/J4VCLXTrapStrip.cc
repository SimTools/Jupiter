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
  if ( fStrip ) delete fStrip;  
}

//====================================================================
//* Assemble ---------------------------------------------------------
void J4VCLXTrapStrip::Assemble()
{
  if ( !GetLV() ) {

    J4CLXParameterList* ptrList = OpenParameterList();
    G4int    myID     = GetMyID();
    G4Trap*  mother   = (G4Trap*)( GetMother()->GetSolid() );
    G4double cellSize = ptrList->GetCellSize();

    G4double px   = mother->GetXHalfLength1();
    G4double plx  = mother->GetXHalfLength2();
    G4double py   = ( IsBarrel() ) ? mother->GetYHalfLength1() : 0.5*cellSize;
    G4double pz   = ( IsBarrel() ) ? 0.5*cellSize : mother->GetZHalfLength();
    G4double phi  = 0;

    //* Endcap part
    if ( !IsBarrel() ) {
      px  += myID*cellSize*std::tan( 0.5*((J4VCLXSubLayer*)GetMother())->GetDphi() );
      plx  = px + cellSize*std::tan( 0.5*((J4VCLXSubLayer*)GetMother())->GetDphi() );
    } 

    G4Trap* ptrTrap = new G4Trap( GetName(), pz, 0., phi, py, px, plx, 0., py, px, plx, 0. );
    Register( ptrTrap );
    SetSolid( ptrTrap );
    
    // MakeLogicalVolume --//
    MakeLVWith( OpenMaterialStore()->Order( GetMaterial() ) );
    
    // SetVisAttribute ----//
    PaintLV( GetVisAtt(), GetColor() );
    
    //* Install daughter volume
    fStrip = Create( this );
    Register( fStrip );
    fStrip->InstallIn( this );
    SetDaughter( fStrip );
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
  G4double width        = OpenParameterList()->GetCellSize();

  G4double px = 0;
  G4double py = -motherHalfY + (myID+0.5)*width;
  G4double pz = 0;

  G4ThreeVector position( px, py, pz );

  if ( IsBarrel() )
    SetPVReplica( kZAxis, width );
  else
    SetPVPlacement( 0, position );
}

//====================================================================
// * Draw ------------------------------------------------------------
void J4VCLXTrapStrip::Draw() { }

//====================================================================
// * Print -----------------------------------------------------------
void J4VCLXTrapStrip::Print() const { }
