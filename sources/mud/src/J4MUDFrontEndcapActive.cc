// $Id$
//*************************************************************************
//* --------------------
//* J4MUDFrontEndcapActive
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
//#include "J4VMUDActiveSD.hh"
#include "J4MUDFrontEndcapActive.hh"
#include "J4MUDFrontEndcapActiveSD.hh"

G4String J4MUDFrontEndcapActive::fFirstName( "FrontEndcapActive" );

//=====================================================================
//* constructor -------------------------------------------------------
J4MUDFrontEndcapActive::J4MUDFrontEndcapActive( J4VDetectorComponent *parent,
                                                     G4int  nclones,
                                                     G4int  nbrothers, 
                                                     G4int  me,
                                                     G4int  copyno )
: J4VMUDEndcapTrap( fFirstName, parent, nclones, nbrothers, me, copyno  ) 
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4MUDFrontEndcapActive::~J4MUDFrontEndcapActive() { }

//=====================================================================
//* Cabling --------------------------------------------------------
void J4MUDFrontEndcapActive::Cabling() 
{ 
  if ( !GetSD() ) {
    J4MUDFrontEndcapActiveSD* sd = new J4MUDFrontEndcapActiveSD( this );
    Register( sd );
    SetSD( sd );
  }
}
