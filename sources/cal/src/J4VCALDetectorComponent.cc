// $Id$
//*************************************************************************
//* -----------------------
//* J4VCALDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"


J4CALMaterialStore* J4VCALDetectorComponent::fMaterialStore = 0;

G4String J4VCALDetectorComponent::fSubGroup("CAL");

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------

J4VCALDetectorComponent::J4VCALDetectorComponent(
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

J4VCALDetectorComponent::~J4VCALDetectorComponent()
{	
   if(Deregister(fMaterialStore)) delete fMaterialStore;
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VCALDetectorComponent::OpenMaterialStore()
{
   if(!fMaterialStore) {
   	fMaterialStore = new J4CALMaterialStore();
        Register(fMaterialStore);
  	G4cerr << "*** Opend J4CALMaterialStore ***" << G4endl;
  }
    
   return fMaterialStore;
}


