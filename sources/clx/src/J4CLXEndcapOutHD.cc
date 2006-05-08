// $Id$

#include "J4VCLXBlock.hh"
#include "J4VCLXLayer.hh"
#include "J4CLXHDLayer.hh"
#include "J4CLXEndcapOutHD.hh"
#include "J4CLXParameterList.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXEndcapOutHD::fgFirstName = "EndcapOutHD";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXEndcapOutHD::J4CLXEndcapOutHD( J4VDetectorComponent *parent,
				    G4int  nclones,
				    G4int  nbrothers,
				    G4int  me,
				    G4int  copyno )
  : J4VCLXBlock( fgFirstName, parent, nclones, nbrothers, me, copyno  )
{
}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXEndcapOutHD::~J4CLXEndcapOutHD()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXLayer *J4CLXEndcapOutHD::Create( J4VDetectorComponent* /* parent    */,
				                      G4int  /* nclones   */,
				                      G4int  /* nbrothers */,
                                                      G4int  /* me        */, 
                                                      G4int  /* copyno    */ )
{
  //return new J4CLXHDLayer( IsEndcap(), parent, nclones, nbrothers, me, copyno );  
  return 0;  
}
