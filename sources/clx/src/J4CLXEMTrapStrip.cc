// $Id$
//*************************************************************************
//* --------------------
//* J4CLXEMTrapStrip
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2005/05/01  H.Ono       Derived from J4CALEMLayer
//*************************************************************************

#include "J4CLXEMTrapStrip.hh"
#include "J4CLXEMStrip.hh"
#include "J4CLXEMBoundStrip.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXEMTrapStrip::fgFirstName= "EMTrapStrip" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXEMTrapStrip::J4CLXEMTrapStrip( G4bool isBarrel,
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

J4CLXEMTrapStrip::~J4CLXEMTrapStrip()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXStrip *J4CLXEMTrapStrip::Create( J4VDetectorComponent *parent,
                                       G4int nclones,
                                       G4int nbrothers,
                                       G4int me,
                                       G4int copyno )
{
  return new J4CLXEMStrip( IsBarrel(), parent, nclones, nbrothers, me, copyno );
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXStrip *J4CLXEMTrapStrip::CreateBound( J4VDetectorComponent *parent,
					    G4int nclones,
					    G4int nbrothers,
					    G4int me,
					    G4int copyno )
{
  return new J4CLXEMBoundStrip( IsBarrel(), parent, nclones, nbrothers, me, copyno );
}
