// $Id$
//*************************************************************************
//* -----------------------
//* J4VCTDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCTDetectorComponent.hh"


J4CTMaterialStore* J4VCTDetectorComponent::fMaterialStore = 0;

G4String J4VCTDetectorComponent::fSubGroup("CT");

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------

J4VCTDetectorComponent::J4VCTDetectorComponent(
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

J4VCTDetectorComponent::~J4VCTDetectorComponent()
{	
   if (Deregister(fMaterialStore)) delete fMaterialStore;
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VCTDetectorComponent::OpenMaterialStore()
{
   if (!fMaterialStore) {
      fMaterialStore = new J4CTMaterialStore();
      Register(fMaterialStore); 
      G4cerr << "*** Opend J4CTMaterialStore ***" << G4endl;
   }
    
   return fMaterialStore;
}


