// $Id$
//*************************************************************************
//* --------------------
//* J4CLX
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2006/05/01  H.Ono       Derived from J4CAL
//*************************************************************************
#include "J4CLX.hh"
#include "J4CLXSD.hh"
#include "J4Timer.hh"

#include "J4CLXBarrelEM.hh"
#include "J4CLXBarrelHD.hh"
#include "J4CLXEndcapEM.hh"
#include "J4CLXEndcapHD.hh"
#include "J4ParameterTable.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLX::fFirstName= "CLX" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLX::J4CLX( J4VDetectorComponent *parent,
                             G4int  nclones,
                             G4int  nbrothers,
                             G4int  me,
                             G4int  copyno )
  : J4VCLXDetectorComponent( fFirstName, parent, nclones, nbrothers, me, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CLX::~J4CLX()
{
  G4int nTraps = OpenParameterList()->GetNTraps();

  //* Barrel
  for ( G4int i = 0; i < nTraps; i++ ) {
    if ( fBarrelEM[i] ) delete fBarrelEM[i];
    if ( fBarrelHD[i] ) delete fBarrelHD[i];
  }
  
  //* Endcap exist +/-Z position
  for ( G4int i = 0 ; i < 2*nTraps; i++ ) {
    if ( fEndcapEM[i] ) delete fEndcapEM[i];
    if ( fEndcapHD[i] ) delete fEndcapHD[i];
  }
  
  if ( fBarrelEM ) delete [] fBarrelEM;
  if ( fBarrelHD ) delete [] fBarrelHD;
  if ( fEndcapEM ) delete [] fEndcapEM;
  if ( fEndcapHD ) delete [] fEndcapHD;

}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CLX::Assemble()
{   
  if ( !GetLV() ) {

    J4CLXParameterList *ptrList = OpenParameterList(); 

    G4double rmin        = ptrList->GetCLXInnerR();
    G4double rmax        = ptrList->GetCLXOuterR();
    G4double len         = ptrList->GetCLXOuterHalfZ();
    G4double dphi        = ptrList->GetCLXDeltaPhi();
    G4double endcaprmin  = ptrList->GetEndcapInnerR();
    G4double endcaphalfz = 0.5 * ( len - ptrList->GetCLXInnerHalfZ() );

    // MakeSolid ----------//
    OrderNewTubs( rmin, rmax, len, dphi, endcaphalfz, endcaprmin );
    
    // MakeLogicalVolume --//  
    MakeLVWith( OpenMaterialStore()->Order( ptrList->GetCLXMaterial() ) );
    
    // SetVisAttribute ----//
    PaintLV( ptrList->GetCLXVisAtt(), ptrList->GetCLXColor() );
    
    // Install daughter PV //
    const G4int nTraps = ptrList->GetNTraps();

    //* Placement case
    //*Barrel-------------------------------------------------
    fBarrelEM = new J4CLXBarrelEM* [nTraps];
    fBarrelHD = new J4CLXBarrelHD* [nTraps];

    for ( G4int i = 0; i < nTraps; i++ ) {
      fBarrelEM[i] = new J4CLXBarrelEM( this, 1, nTraps, i );
      fBarrelHD[i] = new J4CLXBarrelHD( this, 1, nTraps, i );
      Register( fBarrelEM[i] );
      Register( fBarrelHD[i] );
      fBarrelEM[i]->InstallIn( this );
      fBarrelHD[i]->InstallIn( this );
      SetDaughter( fBarrelEM[i] );
      SetDaughter( fBarrelHD[i] );      
    }

    //*Endcap install +/-Z position ------------------------
    fEndcapEM = new J4CLXEndcapEM* [2*nTraps];
    fEndcapHD = new J4CLXEndcapHD* [2*nTraps];
    Register( fEndcapEM );
    Register( fEndcapHD );    

    for ( G4int i = 0; i < 2*nTraps; i++ ) {

      //* -Z position created by copy of +Z objcet
      if ( i < nTraps ) {
	//* Create Endcap +Z part first
	fEndcapEM[i] = new J4CLXEndcapEM( this, 1, nTraps, i );
	fEndcapHD[i] = new J4CLXEndcapHD( this, 1, nTraps, i );
      } else {
	//* Endcap -Z part created by copy of +Z object
	fEndcapEM[i] = new J4CLXEndcapEM( *fEndcapEM[i-nTraps], i );
	fEndcapHD[i] = new J4CLXEndcapHD( *fEndcapHD[i-nTraps], i );
      }
      //      fEndcapEM[i] = new J4CLXEndcapEM( this, 1, 2*nTraps, i );
      //      fEndcapHD[i] = new J4CLXEndcapHD( this, 1, 2*nTraps, i );

      Register( fEndcapEM[i] );
      Register( fEndcapHD[i] );
      fEndcapEM[i]->InstallIn( this );
      fEndcapHD[i]->InstallIn( this );
      SetDaughter( fEndcapEM[i] );
      SetDaughter( fEndcapHD[i] );      
    }
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CLX::Cabling()
{
  if ( !GetSD() ) {
    J4CLXSD* sd = new J4CLXSD( this );
    Register( sd );
    SetSD( sd );
  }
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CLX::InstallIn( J4VComponent*         /* mother */,
                       G4RotationMatrix*     /* prot   */, 
                       const G4ThreeVector&  /* tlate  */  )
{ 
  static G4int timerID = -1;
  J4Timer timer( timerID, "J4CLX", "InstallIn()" );
  timer.Start(); 

  Assemble();			// You MUST call Assemble(); at first.

  //* User defined limits for time cut, step cut
  G4UserLimits *myLimits = new G4UserLimits();
  G4double umaxtime = J4ParameterTable::GetValue("J4CLX.UserMaxTime",1000.0)*nanosecond;
  myLimits->SetUserMaxTime( umaxtime );
  GetLV()->SetUserLimits( myLimits );
  
  // Placement function into mother object...
  SetPVPlacement();
  
  // Cabling function to install SD
  Cabling();

  timer.Stop();
}

//* Draw  --------------------------------------------------------
void J4CLX::Draw() { }
	
//* Print  --------------------------------------------------------
void J4CLX::Print() const { }
