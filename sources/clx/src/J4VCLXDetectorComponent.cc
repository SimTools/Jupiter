// $Id$
//*************************************************************************
//* -----------------------
//* J4VCLXDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXDetectorComponent.hh"


J4CLXMaterialStore* J4VCLXDetectorComponent::fMaterialStore = 0;

G4String J4VCLXDetectorComponent::fSubGroup("CLX");

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------

J4VCLXDetectorComponent::J4VCLXDetectorComponent(
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

J4VCLXDetectorComponent::~J4VCLXDetectorComponent()
{	
   if(Deregister(fMaterialStore)) delete fMaterialStore;
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VCLXDetectorComponent::OpenMaterialStore()
{
   if(!fMaterialStore) {
   	fMaterialStore = new J4CLXMaterialStore();
        Register(fMaterialStore);
  	std::cerr << "*** Opend J4CLXMaterialStore ***" << std::endl;
  }
    
   return fMaterialStore;
}
