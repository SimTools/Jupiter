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
//*     2004/10/07  H.Ono       Parametrized
//*************************************************************************

#include "J4CLXEMLayer.hh"
#include "J4VCLXSubLayer.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXEMLayer::fFirstName= "EMLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXEMLayer::J4CLXEMLayer( J4VDetectorComponent *parent,
                                           G4int  nclones,
                                           G4int  nbrothers,
                                           G4int  me,
                                           G4int  copyno )
: J4VCLXLayer( fFirstName, parent, nclones, nbrothers, me, copyno )
{ }

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
  return new J4CLXEMAbsLayer( parent, nclones, nbrothers, me, copyno );
}

J4VCLXSubLayer *J4CLXEMLayer::CreateActive( J4VDetectorComponent *parent,
                                                           G4int  nclones,
                                                           G4int  nbrothers,
                                                           G4int  me,
                                                           G4int  copyno )
{
  return new J4CLXEMActiveLayer( parent, nclones, nbrothers, me, copyno );
}

