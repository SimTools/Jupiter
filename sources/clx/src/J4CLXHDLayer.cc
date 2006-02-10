// $Id$
//*************************************************************************
//* --------------------
//* J4CLXHDLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2004/10/07  H.Ono       Parametrized
//*************************************************************************

#include "J4CLXHDLayer.hh"
#include "J4VCLXSubLayer.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXHDLayer::fFirstName= "HDLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXHDLayer::J4CLXHDLayer( J4VDetectorComponent *parent,
                                           G4int  nclones,
                                           G4int  nbrothers,
                                           G4int  me,
                                           G4int  copyno )
: J4VCLXLayer( fFirstName, parent, nclones, nbrothers, me, copyno )
{ }

//=====================================================================
//* destructor --------------------------------------------------------

J4CLXHDLayer::~J4CLXHDLayer()
{
}

//===================================================================
//* Create ----------------------------------------------------------

J4VCLXSubLayer *J4CLXHDLayer::CreateAbs( J4VDetectorComponent *parent,
                                                        G4int  nclones,
                                                        G4int  nbrothers,
                                                        G4int  me,
                                                        G4int  copyno )
{
  return new J4CLXHDAbsLayer( parent, nclones, nbrothers, me, copyno );
}

J4VCLXSubLayer *J4CLXHDLayer::CreateActive( J4VDetectorComponent *parent,
                                                           G4int  nclones,
                                                           G4int  nbrothers,
                                                           G4int  me,
                                                           G4int  copyno )
{
  return new J4CLXHDActiveLayer( parent, nclones, nbrothers, me, copyno );
}

