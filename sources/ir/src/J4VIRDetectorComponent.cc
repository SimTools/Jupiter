// $Id$
//*************************************************************************
//* -----------------------
//* J4VIRDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VIRDetectorComponent.hh"

J4IRMaterialStore* J4VIRDetectorComponent::fMaterialStore = 0;

G4String J4VIRDetectorComponent::fSubGroup("IR");

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------
J4VIRDetectorComponent::J4VIRDetectorComponent(
			   	const G4String       &name, 
  			   	J4VComponent *parent,
                                G4int                 nclones,
                                G4int                 nbrothers, 
                                G4int                 me,
                                G4int                 copyno ) :
                         J4VDetectorComponent(fSubGroup, name, 
                         		      parent, nclones,	 
                         		      nbrothers, me, copyno  )
{ 
}

J4VIRDetectorComponent::J4VIRDetectorComponent(
                               const J4VIRDetectorComponent &orig, 
                                     G4int                    copyno)
                        :J4VDetectorComponent(orig, copyno)
{ 
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VIRDetectorComponent::~J4VIRDetectorComponent()
{	
   if(Deregister(fMaterialStore)) delete fMaterialStore;
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VIRDetectorComponent::OpenMaterialStore()
{
   if(!fMaterialStore) {
   	fMaterialStore = new J4IRMaterialStore();
        Register(fMaterialStore);
  	std::cerr << "*** Opend J4IRMaterialStore ***" << std::endl;
  }
    
   return fMaterialStore;
}


