// $Id$
//*************************************************************************
//* --------------------
//* J4CALEMLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2004/10/07  H.Ono       Parametrized
//*************************************************************************

#include "J4CALEMLayer.hh"
#include "J4VCALSubLayer.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALEMLayer::fFirstName= "EMLayer" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALEMLayer::J4CALEMLayer( J4VDetectorComponent *parent,
                                           G4int  nclones,
                                           G4int  nbrothers, 
                                           G4int  me,
                                           G4int  copyno )
: J4VCALLayer( fFirstName, parent, nclones, nbrothers, me, copyno ) 
{ }

//=====================================================================
//* destructor --------------------------------------------------------

J4CALEMLayer::~J4CALEMLayer()
{
}

//===================================================================
//* Create ----------------------------------------------------------

J4VCALSubLayer *J4CALEMLayer::CreateAbs( J4VDetectorComponent *parent,
                                                        G4int  nclones,
                                                        G4int  nbrothers,
                                                        G4int  me,
                                                        G4int  copyno )
{
  return new J4CALEMAbsLayer( parent, nclones, nbrothers, me, copyno ); 
}

J4VCALSubLayer *J4CALEMLayer::CreateActive( J4VDetectorComponent *parent,
                                                           G4int  nclones,
                                                           G4int  nbrothers,
                                                           G4int  me,
                                                           G4int  copyno )
{
  return new J4CALEMActiveLayer( parent, nclones, nbrothers, me, copyno ); 
}

