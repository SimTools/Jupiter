//*************************************************************************
//* -----------------------
//* J4VTPCDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4VTPCDetectorComponent.hh"


J4TPCMaterialStore* J4VTPCDetectorComponent::fMaterialStore = 0;

G4String J4VTPCDetectorComponent::fSubGroup("TPC");

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------

J4VTPCDetectorComponent::J4VTPCDetectorComponent(
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

J4VTPCDetectorComponent::J4VTPCDetectorComponent(
                                const J4VTPCDetectorComponent &orig,
                                                        G4int  copyno)
                       : J4VDetectorComponent(orig, copyno)
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTPCDetectorComponent::~J4VTPCDetectorComponent()
{	
   if (Deregister(fMaterialStore)) delete fMaterialStore;
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VTPCDetectorComponent::OpenMaterialStore()
{
   if (!fMaterialStore) {
      fMaterialStore = new J4TPCMaterialStore();
      Register(fMaterialStore); 
      G4cerr << "*** Opend J4TPCMaterialStore ***" << G4endl;
   }
    
   return fMaterialStore;
}


