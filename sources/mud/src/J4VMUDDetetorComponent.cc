// $Id$
//*************************************************************************
//* -----------------------
//* J4VMUDDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VMUDDetectorComponent.hh"


J4MUDMaterialStore* J4VMUDDetectorComponent::fMaterialStore = 0;

G4String J4VMUDDetectorComponent::fSubGroup("MUD");

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------

J4VMUDDetectorComponent::J4VMUDDetectorComponent(
			   	const G4String       &name, 
  			   	J4VDetectorComponent *parent,
                                G4int                 nclones,
                                G4int                 nbrothers, 
                                G4int                 me,
                                G4int                 copyno ) :
                         J4VDetectorComponent(fSubGroup, name, 
                         		      parent, nclones,	 
                         		      nbrothers, me, copyno)   
{ 
}


//=====================================================================
//* destructor --------------------------------------------------------

J4VMUDDetectorComponent::~J4VMUDDetectorComponent()
{	
   if (Deregister(fMaterialStore)) delete fMaterialStore;
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VMUDDetectorComponent::OpenMaterialStore()
{
   if (!fMaterialStore) {
      fMaterialStore = new J4MUDMaterialStore();
      Register(fMaterialStore); 
      G4cerr << "*** Opend J4MUDMaterialStore ***" << G4endl;
   }
    
   return fMaterialStore;
}


