// $Id$
//*************************************************************************
//* --------------------
//* J4VAcceleratorComponent
//* --------------------
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VAcceleratorComponent.hh"
#include "J4SubtractionSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"


//=====================================================================
//* constructor -----------------------------------------------

J4VAcceleratorComponent::J4VAcceleratorComponent(
                                  const G4String          &groupname,
                                  const G4String          &name,
                                  J4VComponent            *parent,
                                  G4int                    nclones,
                                  G4int                    nbrothers,
                                  G4int                    me,
                                  G4int                    copyno)
                        :J4VComponent(groupname, name, parent,
                                      nclones, nbrothers, me, copyno)
{
} 

J4VAcceleratorComponent::J4VAcceleratorComponent(
                                  const G4String          &groupname,
                                  const G4String          &name,
                                  J4VAcceleratorComponent *parent,
                                  G4int                    nclones,
                                  G4int                    nbrothers,
                                  G4int                    me,
                                  G4int                    copyno)
                        :J4VComponent(groupname, name, parent,
                                      nclones, nbrothers, me, copyno)
{
} 

//=====================================================================
//* destructor --------------------------------------------------------

J4VAcceleratorComponent::~J4VAcceleratorComponent()
{
}

       
    
