// $Id$

#include "J4VCLXBlock.hh"
#include "J4VCLXLayer.hh"
#include "J4CLXHDLayer.hh"
#include "J4CLXEndcapInHD.hh"
#include "J4CLXParameterList.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXEndcapInHD::fgFirstName = "EndcapInHD";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXEndcapInHD::J4CLXEndcapInHD( J4VDetectorComponent *parent,
				  G4int  nclones,
				  G4int  nbrothers,
				  G4int  me,
				  G4int  copyno )
  : J4VCLXBlock( fgFirstName, parent, nclones, nbrothers, me, copyno  )
{
}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXEndcapInHD::~J4CLXEndcapInHD()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXLayer *J4CLXEndcapInHD::Create( J4VDetectorComponent* /* parent    */,
				                     G4int  /* nclones   */, 
 				                     G4int  /* nbrothers */, 
				                     G4int  /* me	 */, 
				                     G4int  /* copyno     */ )
{
  //return new J4CLXHDLayer( IsEndcap(), parent, nclones, nbrothers, me, copyno );  
  return 0;  
}
