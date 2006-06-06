// $Id$
//*************************************************************************
//* --------------------
//* J4CLXEMStrip
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2006/05/01  H.Ono       Derived from J4CALEMActiveLayer
//*************************************************************************

#include "G4Trap.hh"
#include "J4CLXEMStrip.hh"
#include "J4VCLXTrapStrip.hh"
#include "J4VCLXCell.hh"
#include "J4CLXEMCell.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXEMStrip::fgFirstName= "EMStrip" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXEMStrip::J4CLXEMStrip( G4bool isBarrel,
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

J4CLXEMStrip::~J4CLXEMStrip()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXCell *J4CLXEMStrip::Create( J4VDetectorComponent *parent,
				  G4int nclones,
				  G4int nbrothers,
				  G4int me,
				  G4int copyno )
{
  return new J4CLXEMCell( IsBarrel(), IsBoundary(), parent, nclones, nbrothers, me, copyno );
}
