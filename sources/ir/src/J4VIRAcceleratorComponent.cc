// $Id$
//*************************************************************************
//* -----------------------
//* J4VIRAcceleratorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"


J4IRMaterialStore* J4VIRAcceleratorComponent::fMaterialStore = 0;

G4String J4VIRAcceleratorComponent::fSubGroup("IR");

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------

J4VIRAcceleratorComponent::J4VIRAcceleratorComponent(
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

J4VIRAcceleratorComponent::~J4VIRAcceleratorComponent()
{	
   if (Deregister(fMaterialStore)) delete fMaterialStore;
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VIRAcceleratorComponent::OpenMaterialStore()
{
   if (!fMaterialStore) {
       fMaterialStore = new J4IRMaterialStore();
       Register(fMaterialStore); 
       G4cerr << "*** Opend J4IRMaterialStore ***" << G4endl;
   }
    
   return fMaterialStore;
}


