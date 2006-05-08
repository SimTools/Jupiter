// $Id$
//*************************************************************************
//* --------------------
//* J4CLXEndcapEM
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2005/05/01  H.Ono       Derived from J4CALBlock
//*************************************************************************
#include "J4VCLXBlock.hh"
#include "J4VCLXLayer.hh"
#include "J4CLXEMLayer.hh"
#include "J4CLXEndcapEM.hh"
#include "J4CLXParameterList.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXEndcapEM::fgFirstName = "EndcapEM";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXEndcapEM::J4CLXEndcapEM( J4VDetectorComponent *parent,
			      G4int  nclones,
			      G4int  nbrothers,
			      G4int  me,
			      G4int  copyno )
  : J4VCLXBlock( fgFirstName, parent, nclones, nbrothers, me, copyno  )  
{
}

//=====================================================================
//* Copy constructor --------------------------------------------------
J4CLXEndcapEM::J4CLXEndcapEM( const J4CLXEndcapEM& orig, G4int  copyno )
  : J4VCLXBlock( orig, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXEndcapEM::~J4CLXEndcapEM()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXLayer *J4CLXEndcapEM::Create( J4VDetectorComponent *parent,
				    G4int nclones,
				    G4int nbrothers,
				    G4int me,
				    G4int copyno ) 
{
  return new J4CLXEMLayer( IsBarrel(), parent, nclones, nbrothers, me, copyno );
}
