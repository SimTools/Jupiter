// $Id$
//*************************************************************************
//* -----------------------
//* J4VITDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VITDetectorComponent.hh"


J4ITMaterialStore* J4VITDetectorComponent::fMaterialStore = 0;

G4String J4VITDetectorComponent::fSubGroup("IT");

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------

J4VITDetectorComponent::J4VITDetectorComponent(
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

J4VITDetectorComponent::~J4VITDetectorComponent()
{	
   if (Deregister(fMaterialStore)) delete fMaterialStore;
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VITDetectorComponent::OpenMaterialStore()
{
   if (!fMaterialStore) {
      fMaterialStore = new J4ITMaterialStore();
      Register(fMaterialStore); 
      std::cerr << "*** Opend J4ITMaterialStore ***" << std::endl;
   }
    
   return fMaterialStore;
}


