// $Id$
//*************************************************************************
//* --------------------
//* J4CLXEMLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2006/05/01  H.Ono       Deriverd from J4CALLayer
//*************************************************************************

#include "J4VCLXLayer.hh"
#include "J4CLXEMLayer.hh"
#include "J4VCLXSubLayer.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXEMLayer::fgFirstName= "EMLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXEMLayer::J4CLXEMLayer( G4bool isBarrel,
                            J4VDetectorComponent *parent,
			    G4int  nclones,
			    G4int  nbrothers,
			    G4int  me,
			    G4int  copyno )
  : J4VCLXLayer( isBarrel, fgFirstName, parent, nclones, nbrothers, me, copyno )
{ 
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CLXEMLayer::~J4CLXEMLayer()
{
}

//===================================================================
//* Create ----------------------------------------------------------
J4VCLXSubLayer *J4CLXEMLayer::CreateAbs( J4VDetectorComponent *parent,
                                                        G4int  nclones,
                                                        G4int  nbrothers,
                                                        G4int  me,
                                                        G4int  copyno )
{
  return new J4CLXEMAbsLayer( IsBarrel(), parent, nclones, nbrothers, me, copyno );
}

J4VCLXSubLayer *J4CLXEMLayer::CreateActive( J4VDetectorComponent *parent,
                                                           G4int  nclones,
                                                           G4int  nbrothers,
                                                           G4int  me,
                                                           G4int  copyno )
{
  return new J4CLXEMActiveLayer( IsBarrel(), parent, nclones, nbrothers, me, copyno );
}

J4VCLXSubLayer *J4CLXEMLayer::CreateFlex( J4VDetectorComponent *parent,
                                                           G4int  nclones,
                                                           G4int  nbrothers,
                                                           G4int  me,
                                                           G4int  copyno )
{
  return new J4CLXEMFlexLayer( IsBarrel(), parent, nclones, nbrothers, me, copyno );
}
