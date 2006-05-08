// $Id$
//*************************************************************************
//* --------------------
//* J4VCLXStrip
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*     2005/05/01  H.Ono       Original Version
//*************************************************************************
#include "J4Timer.hh"
#include "G4Trap.hh"
#include "G4Box.hh"
#include "J4VCLXStrip.hh"
#include "J4VCLXSubLayer.hh"
#include "J4VCLXDetectorComponent.hh"
#include "J4CLXParameterList.hh"
#include "J4ParameterTable.hh"

//====================================================================
//---------------------
// Class Description
//---------------------

//====================================================================
//* constructor ------------------------------------------------------
J4VCLXStrip::J4VCLXStrip( G4bool isBarrel,
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
J4VCLXStrip::~J4VCLXStrip()
{
  if ( fCell ) delete fCell;
}

//====================================================================
//* Assemble ---------------------------------------------------------
void J4VCLXStrip::Assemble()
{
  if ( !GetLV() ) {

    G4Trap*  mother = (G4Trap*)( GetMother()->GetSolid() );
    G4double halfX  = mother->GetXHalfLength1();
    G4double halfY  = mother->GetYHalfLength1();
    G4double halfZ  = mother->GetZHalfLength();

    //* Create box
    G4Box* ptrBox  = new G4Box( GetName(), halfX, halfY, halfZ );
    Register( ptrBox );
    SetSolid( ptrBox );    

    // MakeLogicalVolume --//
    MakeLVWith( OpenMaterialStore()->Order( GetMaterial() ) );
    
    // SetVisAttribute ----//
    PaintLV( GetVisAtt(), GetColor() );

    //* Install daughter volume-----//
    G4double cellSize = OpenParameterList()->GetCellSize();
    G4int    nCells   = 2*(G4int)( halfX / cellSize );
    
    //* Cell created by replica
    fCell = Create( this, nCells );
    Register( fCell );
    fCell->InstallIn( this );
    SetDaughter( fCell );
  }
}

//====================================================================
//* Cabling ----------------------------------------------------------
void J4VCLXStrip::Cabling()
{
}

//====================================================================
// * InstallIn -------------------------------------------------------
void J4VCLXStrip::InstallIn( J4VComponent*        /*mother*/,
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
  
  SetPVPlacement();

  //Cabling();
}

//====================================================================
// * Draw ------------------------------------------------------------
void J4VCLXStrip::Draw() { }

//====================================================================
// * Print -----------------------------------------------------------
void J4VCLXStrip::Print() const { }
