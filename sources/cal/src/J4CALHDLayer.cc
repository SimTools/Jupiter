// $Id$
//*************************************************************************
//* --------------------
//* J4CALHDLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2004/10/07  H.Ono       Parametrized
//*************************************************************************

#include "J4CALHDLayer.hh"
#include "J4VCALSubLayer.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALHDLayer::fFirstName= "HDLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALHDLayer::J4CALHDLayer( J4VDetectorComponent *parent,
                                           G4int  nclones,
                                           G4int  nbrothers, 
                                           G4int  me,
                                           G4int  copyno )
: J4VCALLayer( fFirstName, parent, nclones, nbrothers, me, copyno ) 
{ }

//=====================================================================
//* destructor --------------------------------------------------------

J4CALHDLayer::~J4CALHDLayer()
{
}

//===================================================================
//* Create ----------------------------------------------------------

J4VCALSubLayer *J4CALHDLayer::CreateAbs( J4VDetectorComponent *parent,
                                                        G4int  nclones,
                                                        G4int  nbrothers,
                                                        G4int  me,
                                                        G4int  copyno )
{
  return new J4CALHDAbsLayer( parent, nclones, nbrothers, me, copyno ); 
}

J4VCALSubLayer *J4CALHDLayer::CreateActive( J4VDetectorComponent *parent,
                                                           G4int  nclones,
                                                           G4int  nbrothers,
                                                           G4int  me,
                                                           G4int  copyno )
{
  return new J4CALHDActiveLayer( parent, nclones, nbrothers, me, copyno ); 
}
