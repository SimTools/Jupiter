// $Id$
//*************************************************************************
//* --------------------
//* J4CLXEMCell
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "G4Box.hh"
#include "J4VCLXCell.hh"
#include "J4CLXEMCell.hh"
#include "J4CLXEMActiveSD.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXEMCell::fgFirstName= "EMCell" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXEMCell::J4CLXEMCell( G4bool isBarrel,
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
J4CLXEMCell::~J4CLXEMCell()
{
}

//=====================================================================
//* cabling -----------------------------------------------------------
void J4CLXEMCell::Cabling()
{
  if ( !GetSD() ) {
    J4CLXEMActiveSD* sd = new J4CLXEMActiveSD( this );
    Register( sd );
    SetSD( sd );
  }
}
