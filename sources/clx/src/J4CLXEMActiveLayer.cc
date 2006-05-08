// $Id$
//*************************************************************************
//* --------------------
//* J4CLXEMActiveLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXSubLayer.hh"
#include "J4CLXEMActiveLayer.hh"
#include "J4VCLXTrapStrip.hh"
#include "J4CLXEMTrapStrip.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXEMActiveLayer::fgFirstName= "EMActiveLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXEMActiveLayer::J4CLXEMActiveLayer( G4bool isBarrel,
                                        J4VDetectorComponent *parent,
					G4int  nclones,
					G4int  nbrothers,
					G4int  me,
					G4int  copyno )
: J4VCLXSubLayer( isBarrel, fgFirstName, parent, nclones, nbrothers, me, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CLXEMActiveLayer::~J4CLXEMActiveLayer()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXTrapStrip *J4CLXEMActiveLayer::Create( J4VDetectorComponent *parent,
                                             G4int nclones,
                                             G4int nbrothers,
                                             G4int me,
                                             G4int copyno )
{
  return new J4CLXEMTrapStrip( IsBarrel(), parent, nclones, nbrothers, me, copyno );
}
