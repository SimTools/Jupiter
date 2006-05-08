// $Id$
//*************************************************************************
//* --------------------
//* J4CLXBarrelHD
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2006/05/01 H.Ono Original version
//*************************************************************************
#include "J4VCLXBlock.hh"
#include "J4VCLXLayer.hh"
#include "J4CLXHDLayer.hh"
#include "J4CLXBarrelHD.hh"
#include "J4CLXParameterList.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXBarrelHD::fgFirstName = "BarrelHD";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXBarrelHD::J4CLXBarrelHD( J4VDetectorComponent *parent,
			      G4int  nclones,
			      G4int  nbrothers,
			      G4int  me,
			      G4int  copyno )
  : J4VCLXBlock( fgFirstName, parent, nclones, nbrothers, me, copyno  )
{
}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXBarrelHD::~J4CLXBarrelHD()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXLayer *J4CLXBarrelHD::Create( J4VDetectorComponent *parent,
				    G4int nclones,
				    G4int nbrothers,
				    G4int me,
				    G4int copyno )
{
  return new J4CLXHDLayer( IsBarrel(), parent, nclones, nbrothers, me, copyno );
}
