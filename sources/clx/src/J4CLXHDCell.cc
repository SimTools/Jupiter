// $Id$
//*************************************************************************
//* --------------------
//* J4CLXHDCell
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2006/05/01  H.Ono       Derived from J4CALSubLayer
//*************************************************************************

#include "G4Box.hh"
#include "J4VCLXCell.hh"
#include "J4CLXHDCell.hh"
#include "J4CLXHDActiveSD.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXHDCell::fgFirstName= "HDCell" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXHDCell::J4CLXHDCell( G4bool isBarrel,
                          J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers,
                          G4int  me,
                          G4int  copyno )
  : J4VCLXCell( isBarrel, fgFirstName, parent, nclones, nbrothers, me, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXHDCell::~J4CLXHDCell()
{
}

//=====================================================================
//* Cabling -----------------------------------------------------------
void J4CLXHDCell::Cabling()
{
 if ( !GetSD() ) {
    J4CLXHDActiveSD* sd = new J4CLXHDActiveSD( this );
    Register( sd );
    SetSD( sd );
 }
}
