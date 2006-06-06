// $Id$
//*************************************************************************
//* --------------------
//* J4CLXEMBoundStrip
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXCell.hh"
#include "J4CLXEMCell.hh"
#include "J4CLXEMBoundStrip.hh"
#include "J4CLXEMActiveSD.hh"
#include "J4ParameterTable.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXEMBoundStrip::fgFirstName= "EMBoundStrip" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXEMBoundStrip::J4CLXEMBoundStrip( G4bool isBarrel,
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
J4CLXEMBoundStrip::~J4CLXEMBoundStrip()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXCell *J4CLXEMBoundStrip::Create( J4VDetectorComponent *parent,
				       G4int nclones,
				       G4int nbrothers,
				       G4int me,
				       G4int copyno )
{
  return new J4CLXEMCell( IsBarrel(), IsBoundary(), parent, nclones, nbrothers, me, copyno );
}
