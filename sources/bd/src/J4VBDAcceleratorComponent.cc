// $Id$
//*************************************************************************
//* -----------------------
//* J4VBDAcceleratorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VBDAcceleratorComponent.hh"


J4BDMaterialStore* J4VBDAcceleratorComponent::fMaterialStore = 0;

G4String J4VBDAcceleratorComponent::fSubGroup("BD");

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------

J4VBDAcceleratorComponent::J4VBDAcceleratorComponent(
                                const G4String       &name, 
  			   	J4VAcceleratorComponent *parent,
                                G4int                 nclones,
                                G4int                 nbrothers, 
                                G4int                 me,
                                G4int                 copyno ) :
                        J4VAcceleratorComponent(fSubGroup, name, 
                         		      parent, nclones,	 
                         		      nbrothers, me, copyno )   
{ 
}


//=====================================================================
//* destructor --------------------------------------------------------

J4VBDAcceleratorComponent::~J4VBDAcceleratorComponent()
{	
   if (Deregister(fMaterialStore)) delete fMaterialStore;
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VBDAcceleratorComponent::OpenMaterialStore()
{
   if (!fMaterialStore) {
      fMaterialStore = new J4BDMaterialStore();
      Register(fMaterialStore);
      std::cerr << "*** Opend J4BDMaterialStore ***" << std::endl;
   }
    
   return fMaterialStore;
}


