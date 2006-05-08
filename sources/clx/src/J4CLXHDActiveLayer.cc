// $Id$
//*************************************************************************
//* --------------------
//* J4CLXHDActiveLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2006/05/01  H.Ono       Deriverd from J4CALHDActiveLayer
//*************************************************************************

#include "J4CLXHDActiveLayer.hh"
#include "J4VCLXTrapStrip.hh"
#include "J4CLXHDTrapStrip.hh"
#include "J4VCLXStrip.hh"
#include "J4CLXHDStrip.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXHDActiveLayer::fgFirstName= "HDActiveLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXHDActiveLayer::J4CLXHDActiveLayer( G4bool isBarrel, 
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

J4CLXHDActiveLayer::~J4CLXHDActiveLayer()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXTrapStrip *J4CLXHDActiveLayer::Create( J4VDetectorComponent *parent,
                                             G4int nclones,
                                             G4int nbrothers,
                                             G4int me,
                                             G4int copyno )
{
  return new J4CLXHDTrapStrip( IsBarrel(), parent, nclones, nbrothers, me, copyno);
}
