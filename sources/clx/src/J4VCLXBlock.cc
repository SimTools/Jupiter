// $Id$
//*************************************************************************
//* --------------------
//* J4VCALBlock
//* --------------------
//* (Description)
//*    Base class for CAL blocks like EM or HD.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2004/11/14  K.Fujii	Derived from J4CALEM by S.Ono.
//*	2006/05/01  H.Ono       Deriverd from J4VCALBlock
//*************************************************************************
#include "G4Trap.hh"
#include "J4VCLXBlock.hh"
#include "J4CLXParameterList.hh"
#include "J4ParameterTable.hh"
#include "G4ThreeVector.hh"

//=====================================================================
//* constructor -------------------------------------------------------
J4VCLXBlock::J4VCLXBlock( const G4String& name,
			  J4VDetectorComponent* parent,
			  G4int  nclones,
			  G4int  nbrothers,
			  G4int  me, G4int  copyno ) 
  : J4VCLXDetectorComponent( name, parent, nclones, nbrothers, me, copyno  )
{ }

//=====================================================================
//* Copy constructor --------------------------------------------------
J4VCLXBlock::J4VCLXBlock( const J4VCLXBlock& orig, G4int  copyno )
  : J4VCLXDetectorComponent( orig, copyno )
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4VCLXBlock::~J4VCLXBlock()
{
  G4int nLayers = (G4int)fLayers.size();
  for ( G4int i = 0; i < nLayers; ++i ) {
    if ( fLayers[i] ) delete fLayers[i];    
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4VCLXBlock::Assemble()
{
  if ( !GetLV() ) {

    //* tolerance for each layer
    G4double tol    = OpenParameterList()->GetLayerTolerance();

    G4int    myID = GetMyID();
    G4double px   = GetHalfX( myID ) -0.5*tol;
    G4double plx  = GetHalfXL( myID ) -0.5*tol;
    G4double py   = 0.5*( GetYmax( myID ) - GetYmin( myID ) );
    G4double pz   = GetHalfZ( myID );
    G4double phi  = GetSphi( myID );
    
    G4Trap* ptrTrap = new G4Trap( GetName(), pz, 0., phi, py, px, plx, 0., py, px, plx, 0. );
    Register( ptrTrap );
    SetSolid( ptrTrap );
    
    // MakeLogicalVolume --//
    MakeLVWith( OpenMaterialStore()->Order( GetMaterial() ) );
    
    // SetVisAttribute ----//
    PaintLV( GetVisAtt(), GetColor() );

    // SetDaughterVolume --//
    G4int nLayers = GetNLayers();
    J4VCLXLayer* layer = 0;

    if ( IsBarrel() ) {  // Barrel part created by placement
      for ( G4int i = 0; i < nLayers; i++ ) {
	layer = Create( this, 1, nLayers, i ) ;
	fLayers.push_back( layer );
	Register( layer );
	layer->InstallIn( this );
	SetDaughter( layer );
      }
    } else { // Endcap part created by replica
      layer = Create( this, nLayers ) ;
      fLayers.push_back( layer );
      Register( layer );
      layer->InstallIn( this );
      SetDaughter( layer );
    }
  }
}

//=====================================================================
//* Cabling -----------------------------------------------------------
void J4VCLXBlock::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------
void J4VCLXBlock::InstallIn( J4VComponent*        /* mother */,
                             G4RotationMatrix*    /* prot   */,
                             const G4ThreeVector& /* tlate  */  )
{
  // You MUST call Assemble(); at first.
  Assemble();			

  //* User defined limits for time cut, step cut
  G4UserLimits *myLimits = new G4UserLimits();
  G4double umaxtime = J4ParameterTable::GetValue("J4CLX.UserMaxTime",1000.0)*nanosecond;
  myLimits->SetUserMaxTime( umaxtime );
  GetLV()->SetUserLimits( myLimits );
  
  //* Placement function into mother object
  J4CLXParameterList* ptrList = OpenParameterList();

  G4int    myID = GetMyID();  
  G4double dphi = ptrList->GetTrapDeltaPhi();
  G4double pr = GetYmin() + 0.5*( GetYmax() - GetYmin() );
  G4double px = 0.;
  G4double py = pr;
  G4double pz   = (IsEM()) ? ptrList->GetEMEndcapFrontZ() + GetHalfZ()
                           : ptrList->GetHDEndcapFrontZ() + GetHalfZ();

  //* IsEndcap() = Barrel = 0, Endcap+Z = 1, Endcap-Z = -1
  pz *= (G4double)IsEndcap();

  G4ThreeVector position( px, py, pz );
  position.rotateZ( -dphi*(G4double)myID );
  G4RotationMatrix* rotation = new G4RotationMatrix();
  rotation->rotateZ( dphi * (G4double)myID );

  if ( IsEndcap() == -1 ) {
    G4ThreeVector xv(-1., 0., 0.);
    G4ThreeVector yv( 0., 1., 0.);
    G4ThreeVector zv( 0., 0.,-1.);
    rotation->rotateAxes(xv, yv, zv); 
  }

  SetPVPlacement( rotation, position );
  
  //Cabling();
}

//=====================================================================
//* Draw --------------------------------------------------------------
void J4VCLXBlock::Draw() { }

//=====================================================================
//* Print --------------------------------------------------------------
void J4VCLXBlock::Print() const { }
