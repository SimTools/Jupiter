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
//*     2006/05/01  H.Ono       Derived from J4CALHDLayer
//*************************************************************************

#include "J4VCLXLayer.hh"
#include "J4CLXHDLayer.hh"
#include "J4VCLXSubLayer.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXHDLayer::fgFirstName = "HDLayer";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXHDLayer::J4CLXHDLayer( G4bool isBarrel,
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
  return new J4CLXHDAbsLayer( IsBarrel(), parent, nclones, nbrothers, me, copyno );
}

J4VCLXSubLayer *J4CLXHDLayer::CreateActive( J4VDetectorComponent *parent,
                                                           G4int  nclones,
                                                           G4int  nbrothers,
                                                           G4int  me,
                                                           G4int  copyno )
{
  return new J4CLXHDActiveLayer( IsBarrel(), parent, nclones, nbrothers, me, copyno );
}

J4VCLXSubLayer *J4CLXHDLayer::CreateFlex( J4VDetectorComponent *parent,
                                                           G4int  nclones,
                                                           G4int  nbrothers,
                                                           G4int  me,
                                                           G4int  copyno )
{
  return new J4CLXHDFlexLayer( IsBarrel(), parent, nclones, nbrothers, me, copyno );
}
