// $Id$
//*************************************************************************
//* --------------------
//* J4MUDBarrelAbs
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "J4MUDBarrelAbs.hh"
#include "J4MUDParameterList.hh"

G4String J4MUDBarrelAbs::fFirstName( "BarrelAbs" );

//=====================================================================
//* constructor -------------------------------------------------------
J4MUDBarrelAbs::J4MUDBarrelAbs( J4VDetectorComponent* parent,
                                               G4int  nclones,
                                               G4int  nbrothers, 
                                               G4int  me,
                                               G4int  copyno )
 : J4VMUDBarrelTrap( fFirstName, parent, nclones, nbrothers, me, copyno )
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4MUDBarrelAbs::~J4MUDBarrelAbs() { }

void J4MUDBarrelAbs::Cabling() { }
