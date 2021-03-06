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
    G4double motherHalfX  = mother->GetXHalfLength1();
    G4double cellSize = OpenParameterList()->GetCellSize();

    //* Number of cells can be fill in motherHalfX length
    G4int  nCellsHalf = (G4int)( motherHalfX / cellSize );
    G4int  nCells     = 2*nCellsHalf;  // nCells always even number

    //* HalfX length fixed as n * cellSize (Not motherHalfX)
    G4double halfX  = ( IsBoundary() ) ? 0.5*(motherHalfX - cellSize*nCellsHalf)
                                       : cellSize*nCellsHalf;
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
    //* Cell created by replica at center part, boundary is placement
    if ( IsBoundary() ) {
      fCell = Create( this );
    } else { // If is not boundary : Replicated
      fCell = Create( this, nCells );
    }
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

  G4double motherHalfX = ((G4Trap*)GetMother()->GetSolid())->GetXHalfLength1();
  G4double cellSize     = OpenParameterList()->GetCellSize();
  G4int    nXCellsHalf  = (G4int)( motherHalfX/cellSize );
  G4double halfX        = nXCellsHalf*cellSize + 0.5*(motherHalfX-nXCellsHalf*cellSize);
    
  G4double px = ( IsBoundary() ) ?  halfX : 0.;
  G4double py = 0.;
  G4double pz = 0.;

  //* if ID == 0 x position set to minus
  if ( GetMyID() == 0 ) px *= -1.;
  
  G4ThreeVector position( px, py, pz );
  
  SetPVPlacement( 0, position );

  //Cabling();
}

//====================================================================
// * Draw ------------------------------------------------------------
void J4VCLXStrip::Draw() { }

//====================================================================
// * Print -----------------------------------------------------------
void J4VCLXStrip::Print() const { }
