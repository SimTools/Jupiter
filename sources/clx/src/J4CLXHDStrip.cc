// $Id$
//*************************************************************************
//* --------------------
//* J4CLXHDStrip
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "G4Trap.hh"
#include "J4VCLXSubLayer.hh"
#include "J4CLXHDStrip.hh"
#include "J4VCLXCell.hh"
#include "J4CLXHDCell.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXHDStrip::fgFirstName= "HDStrip" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXHDStrip::J4CLXHDStrip( G4bool isBarrel,
                            J4VDetectorComponent *parent,
                            G4int  nclones,
                            G4int  nbrothers,
                            G4int  me,
                            G4int  copyno )
  : J4VCLXStrip( isBarrel, fgFirstName, parent, nclones, nbrothers, me, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CLXHDStrip::~J4CLXHDStrip()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXCell *J4CLXHDStrip::Create( J4VDetectorComponent *parent,
                                  G4int nclones,
                                  G4int nbrothers,
                                  G4int me,
                                  G4int copyno )
{
  return new J4CLXHDCell( IsBarrel(), parent, nclones, nbrothers, me, copyno );
}
