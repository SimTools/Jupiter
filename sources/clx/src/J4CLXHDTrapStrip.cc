// $Id$
//*************************************************************************
//* --------------------
//* J4CLXHDTrapStrip
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CLXHDTrapStrip.hh"
#include "J4VCLXStrip.hh"
#include "J4CLXHDStrip.hh"
#include "J4CLXHDBoundStrip.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXHDTrapStrip::fgFirstName= "HDTrapStrip" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXHDTrapStrip::J4CLXHDTrapStrip( G4bool isBarrel,
                                    J4VDetectorComponent *parent,
                                    G4int  nclones,
                                    G4int  nbrothers,
                                    G4int  me,
                                    G4int  copyno )
  : J4VCLXTrapStrip( isBarrel, fgFirstName, parent, nclones, nbrothers, me, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CLXHDTrapStrip::~J4CLXHDTrapStrip()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXStrip *J4CLXHDTrapStrip::Create( J4VDetectorComponent *parent,
                                       G4int nclones,
                                       G4int nbrothers,
                                       G4int me,
                                       G4int copyno )
{
  return new J4CLXHDStrip( IsBarrel(), parent, nclones, nbrothers, me, copyno );
}

//=====================================================================
//* CreateBound -------------------------------------------------------
J4VCLXStrip *J4CLXHDTrapStrip::CreateBound( J4VDetectorComponent *parent,
					    G4int nclones,
					    G4int nbrothers,
					    G4int me,
					    G4int copyno )
{
  return new J4CLXHDBoundStrip( IsBarrel(), parent, nclones, nbrothers, me, copyno );
}
