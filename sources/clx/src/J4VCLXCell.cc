// $Id$
//*************************************************************************
//* --------------------
//* J4VCLXCell
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*     2005/05/01  H.Ono       Original Version
//*************************************************************************
#include "J4Timer.hh"
#include "G4Box.hh"
#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXCell.hh"
#include "J4CLXParameterList.hh"
#include "J4ParameterTable.hh"
#include "J4VCLXActiveSD.hh"

//====================================================================
//---------------------
// Class Description
//---------------------

//====================================================================
//* constructor ------------------------------------------------------
J4VCLXCell::J4VCLXCell( G4bool isBarrel, 
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
J4VCLXCell::~J4VCLXCell()
{
}

//====================================================================
//* Assemble ---------------------------------------------------------
void J4VCLXCell::Assemble()
{
  if ( !GetLV() ) {

    G4double halfX = ((G4Box*)GetMother()->GetSolid())->GetXHalfLength();
    G4double halfY = ((G4Box*)GetMother()->GetSolid())->GetYHalfLength();
    G4double halfZ = ((G4Box*)GetMother()->GetSolid())->GetZHalfLength();
    halfX /= GetNclones();
    
    G4Box* ptrBox = new G4Box( GetName(), halfX, halfY, halfZ );
    Register( ptrBox );
    SetSolid( ptrBox );
    
    // MakeLogicalVolume --//
    MakeLVWith( OpenMaterialStore()->Order( GetMaterial() ) );
    
    // SetVisAttribute ----//
    PaintLV( GetVisAtt(), GetColor() );

  }
}

//====================================================================
//* Cabling ----------------------------------------------------------
//void J4VCLXCell::Cabling()
//{
////  if ( !GetSD() ) {
//    J4VCLXActiveSD* sd = new J4VCLXActiveSD( this );
//    Register( sd );
//    SetSD( sd );
//  }
//}

//====================================================================
// * InstallIn -------------------------------------------------------
void J4VCLXCell::InstallIn( J4VComponent*        /*mother*/,
			    G4RotationMatrix*    /*prot*/  ,
			    const G4ThreeVector& /*tlate*/   )
{
  //* First call Assemble
  Assemble();

  //* User defined limits for time cut, step cut
  G4double ullen = J4ParameterTable::GetValue( "J4CLX.UserLimits", 0.01)*cm;
  G4UserLimits *myLimits = new G4UserLimits( ullen );
  G4double umaxtime = J4ParameterTable::GetValue("J4CLX.UserMaxTime",1000.0)*nanosecond;
  myLimits->SetUserMaxTime( umaxtime );
  GetLV()->SetUserLimits( myLimits );
  
  G4double halfX    = ((G4Box*)GetMother()->GetSolid())->GetXHalfLength();
  G4double cellSize = 2*halfX / GetNclones();
  //G4double cellSize = OpenParameterList()->GetCellSize();
  //G4double offset = 0.5*(1-GetNclones())*cellSize ;

  SetPVReplica( kXAxis, cellSize );

  Cabling();
}

//====================================================================
// * Draw ------------------------------------------------------------
void J4VCLXCell::Draw() { }

//====================================================================
// * Print -----------------------------------------------------------
void J4VCLXCell::Print() const { }
