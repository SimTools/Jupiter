// $Id$
//*************************************************************************
//* --------------------
//* J4MUDEndcapAbs
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "J4MUDEndcapAbs.hh"
G4String J4MUDEndcapAbs::fFirstName( "EndcapAbs" );

//=====================================================================
//* constructor -------------------------------------------------------
J4MUDEndcapAbs::J4MUDEndcapAbs( J4VDetectorComponent *parent,
                                               G4int  nclones,
                                               G4int  nbrothers, 
                                               G4int  me,
                                               G4int  copyno )
: J4VMUDEndcapTrap( fFirstName, parent, nclones, nbrothers, me, copyno  ) 
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4MUDEndcapAbs::~J4MUDEndcapAbs() { }

void J4MUDEndcapAbs::Cabling() { }
