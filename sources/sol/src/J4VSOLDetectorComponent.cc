// $Id$
//*************************************************************************
//* -----------------------
//* J4VSOLDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/10/28  R.Kuboshima  Original version.
//*************************************************************************

#include "J4VSOLDetectorComponent.hh"


J4SOLMaterialStore* J4VSOLDetectorComponent::fMaterialStore = 0;

G4String J4VSOLDetectorComponent::fSubGroup("SOL");

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------

J4VSOLDetectorComponent::J4VSOLDetectorComponent(
			   	const G4String       &name, 
  			   	J4VDetectorComponent *parent,
                                G4int                 nclones,
                                G4int                 nbrothers, 
                                G4int                 me,
                                G4int                 copyno ) :
                         J4VDetectorComponent(fSubGroup, name, 
                         		      parent, nclones,	 
                         		      nbrothers, me, copyno  )   
{ 
}


//=====================================================================
//* destructor --------------------------------------------------------

J4VSOLDetectorComponent::~J4VSOLDetectorComponent()
{	
   if(Deregister(fMaterialStore)) delete fMaterialStore;
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VSOLDetectorComponent::OpenMaterialStore()
{
   if(!fMaterialStore) {
   	fMaterialStore = new J4SOLMaterialStore();
        Register(fMaterialStore);
  	G4cerr << "*** Opend J4SOLMaterialStore ***" << G4endl;
  }
    
   return fMaterialStore;
}

