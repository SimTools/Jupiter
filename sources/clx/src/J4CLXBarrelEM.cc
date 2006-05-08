// $Id$
//*************************************************************************
//* --------------------
//* J4CLXBarrelEM
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2006/05/01 H.Ono Original version.
//*************************************************************************
#include "J4VCLXBlock.hh"
#include "J4VCLXLayer.hh"
#include "J4CLXEMLayer.hh"
#include "J4CLXBarrelEM.hh"
#include "J4CLXParameterList.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXBarrelEM::fgFirstName = "BarrelEM";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXBarrelEM::J4CLXBarrelEM( J4VDetectorComponent *parent,
			      G4int  nclones,
			      G4int  nbrothers,
			      G4int  me,
			      G4int  myID )
  : J4VCLXBlock( fgFirstName, parent, nclones, nbrothers, me, myID  )  
{
}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXBarrelEM::~J4CLXBarrelEM()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXLayer *J4CLXBarrelEM::Create( J4VDetectorComponent *parent,
				    G4int nclones,
				    G4int nbrothers,
				    G4int me,
				    G4int copyno )
{
  return new J4CLXEMLayer( IsBarrel(), parent, nclones, nbrothers, me, copyno );  
}
