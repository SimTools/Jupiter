// $Id$
//*************************************************************************
//* --------------------
//* J4MUDEndcapActive
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
//#include "J4VMUDActiveSD.hh"
#include "J4MUDEndcapActive.hh"
#include "J4MUDEndcapActiveSD.hh"

G4String J4MUDEndcapActive::fFirstName( "EndcapActive" );

//=====================================================================
//* constructor -------------------------------------------------------
J4MUDEndcapActive::J4MUDEndcapActive( J4VDetectorComponent *parent,
                                                     G4int  nclones,
                                                     G4int  nbrothers, 
                                                     G4int  me,
                                                     G4int  copyno )
: J4VMUDEndcapTrap( fFirstName, parent, nclones, nbrothers, me, copyno  ) 
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4MUDEndcapActive::~J4MUDEndcapActive() { }

//=====================================================================
//* Cabling --------------------------------------------------------
void J4MUDEndcapActive::Cabling() 
{ 
  if ( !GetSD() ) {
    J4MUDEndcapActiveSD* sd = new J4MUDEndcapActiveSD( this );
    Register( sd );
    SetSD( sd );
  }
}
