// $Id$
//*************************************************************************
//* --------------------
//* J4CLXHDBoundStrip
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "G4Box.hh"
#include "J4VCLXCell.hh"
#include "J4CLXHDCell.hh"
#include "J4CLXHDBoundStrip.hh"
#include "J4CLXEMActiveSD.hh"
#include "J4ParameterTable.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXHDBoundStrip::fgFirstName= "HDBoundStrip" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXHDBoundStrip::J4CLXHDBoundStrip( G4bool isBarrel,
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
J4CLXHDBoundStrip::~J4CLXHDBoundStrip()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXCell *J4CLXHDBoundStrip::Create( J4VDetectorComponent *parent,
				       G4int nclones,
				       G4int nbrothers,
				       G4int me,
				       G4int copyno )
{
  return new J4CLXHDCell( IsBarrel(), IsBoundary(), parent, nclones, nbrothers, me, copyno );
}
