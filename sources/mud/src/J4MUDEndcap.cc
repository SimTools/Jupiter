// $Id$
//*************************************************************************
//* --------------------
//* J4MUDEndcap
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "J4MUDEndcap.hh"
#include "J4MUDEndcapSD.hh"
G4String J4MUDEndcap::fFirstName( "Endcap" );

//=====================================================================
//* constructor -------------------------------------------------------
J4MUDEndcap::J4MUDEndcap( J4VDetectorComponent *parent,
                                         G4int  nclones,
                                         G4int  nbrothers, 
                                         G4int  me,
                                         G4int  copyno )
: J4VMUDDetectorComponent( fFirstName, parent, nclones, nbrothers, me, copyno  ) 
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4MUDEndcap::~J4MUDEndcap() { }

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4MUDEndcap::Assemble() 
{   
  if ( !GetLV() ) {
     J4MUDParameterList* ptrList = OpenParameterList();

     //     G4int myid  = GetMyID();
     G4double rmin = ptrList->GetEndcapInnerR();
     G4double rmax = ptrList->GetEndcapOuterR();
     //    G4double len  = (ptrList->GetEndcapThickness())*0.5;
     G4double len  = (ptrList->GetEndcapLayer())*0.5;
     G4double dphi = ptrList->GetEndcapDeltaPhi();
  	
    // MakeSolid ----------//
    OrderNewTubs( rmin, rmax, len, dphi );
    
    // MakeLogicalVolume --//
    G4String material = ptrList->GetEndcapMaterial();
    MakeLVWith( OpenMaterialStore()->Order( material ) );
        
    // SetVisAttribute ----//
    PaintLV( ptrList->GetEndcapVisAtt(), ptrList->GetEndcapColor() );
  }
}


void J4MUDEndcap::Cabling() {
 J4MUDEndcapSD* sd = new J4MUDEndcapSD( this );
  Register( sd );
  SetSD( sd ); 
}

//=====================================================================
//* InstallIn  --------------------------------------------------------
void J4MUDEndcap::InstallIn( J4VComponent*        /* mother */,
                             G4RotationMatrix*    /* prot   */, 
                             const G4ThreeVector& /* tlate  */ ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.

  // Placement function into mother object...
  J4MUDParameterList* ptrList = OpenParameterList();

  G4int myid = GetMyID();
  G4double z = ptrList->GetEndcapZ(myid);
  
  if ( myid < ptrList->GetNEndcapLayers() ) {
    G4ThreeVector tlate( 0., 0., z );
    SetPVPlacement( 0, tlate ); 
  } else {
    G4ThreeVector tlate( 0., 0., -1 * z );
    SetPVPlacement( 0, tlate );
  }
  
 if ( !GetSD() ) Cabling();
}
