// $Id$
//*************************************************************************
//* --------------------
//* J4MUDFrontEndcapAbs
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "J4MUDFrontEndcapAbs.hh"
G4String J4MUDFrontEndcapAbs::fFirstName( "FrontEndcapAbs" );

//=====================================================================
//* constructor -------------------------------------------------------
J4MUDFrontEndcapAbs::J4MUDFrontEndcapAbs( J4VDetectorComponent *parent,
                                               G4int  nclones,
                                               G4int  nbrothers, 
                                               G4int  me,
                                               G4int  copyno )
: J4VMUDEndcapTrap( fFirstName, parent, nclones, nbrothers, me, copyno  ) 
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4MUDFrontEndcapAbs::~J4MUDFrontEndcapAbs() { }

void J4MUDFrontEndcapAbs::Cabling() {}
