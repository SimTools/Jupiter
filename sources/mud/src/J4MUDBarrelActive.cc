// $Id$
//*************************************************************************
//* --------------------
//* J4MUDBarrelActive
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
//#include "J4VMUDActiveSD.hh"
#include "J4MUDBarrelActive.hh"
#include "J4MUDBarrelActiveSD.hh"
#include "J4MUDParameterList.hh"

G4String J4MUDBarrelActive::fFirstName( "BarrelActive" );

//=====================================================================
//* constructor -------------------------------------------------------
J4MUDBarrelActive::J4MUDBarrelActive( J4VDetectorComponent* parent,
                                                     G4int  nclones,
                                                     G4int  nbrothers, 
                                                     G4int  me,
                                                     G4int  copyno )
 : J4VMUDBarrelTrap( fFirstName, parent, nclones, nbrothers, me, copyno )
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4MUDBarrelActive::~J4MUDBarrelActive() { }

//=====================================================================
//* Cabling --------------------------------------------------------
void J4MUDBarrelActive::Cabling() 
{ 
  if ( !GetSD() ) {
    J4MUDBarrelActiveSD* sd = new J4MUDBarrelActiveSD( this );
    Register( sd );
    SetSD( sd );
  }
}
