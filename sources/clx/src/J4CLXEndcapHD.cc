// $Id$
//*************************************************************************
//* --------------------
//* J4CLXEMEndcapHD
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
#include "J4CLXHDLayer.hh"
#include "J4CLXEndcapHD.hh"
#include "J4CLXParameterList.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXEndcapHD::fgFirstName = "EndcapHD";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXEndcapHD::J4CLXEndcapHD( J4VDetectorComponent *parent,
			      G4int  nclones,
			      G4int  nbrothers,
			      G4int  me,
			      G4int  copyno )
  : J4VCLXBlock( fgFirstName, parent, nclones, nbrothers, me, copyno  )
{
}

//=====================================================================
//* Copy constructor --------------------------------------------------
J4CLXEndcapHD::J4CLXEndcapHD( const J4CLXEndcapHD& orig, G4int copyno )
  : J4VCLXBlock( orig, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXEndcapHD::~J4CLXEndcapHD()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXLayer *J4CLXEndcapHD::Create( J4VDetectorComponent *parent,
				    G4int nclones,
				    G4int nbrothers,
				    G4int me,
				    G4int copyno )
{
  return new J4CLXHDLayer( IsBarrel(), parent, nclones, nbrothers, me, copyno );  
}
