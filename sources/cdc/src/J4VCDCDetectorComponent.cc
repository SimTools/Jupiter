// $Id$
//*************************************************************************
//* -----------------------
//* J4VCDCDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCDCDetectorComponent.hh"


J4CDCMaterialStore* J4VCDCDetectorComponent::fMaterialStore = 0;
J4CDCParameterList* J4VCDCDetectorComponent::fParameterList = 0;

G4String J4VCDCDetectorComponent::fSubGroup("CDC");

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* constructor -----------------------------------------------

J4VCDCDetectorComponent::J4VCDCDetectorComponent(
                                const G4String       &name, 
                                J4VDetectorComponent *parent,
                                G4int                 nclones,
                                G4int                 nbrothers, 
                                G4int                 me,
                                G4int                 copyno ) :
                         J4VDetectorComponent(fSubGroup, name,
                                              parent, nclones,	 
                                              nbrothers, me, copyno )   
{ 
}

J4VCDCDetectorComponent::J4VCDCDetectorComponent( 
                             const J4VCDCDetectorComponent &orig,
                                   G4int                    copyno)
                        :J4VDetectorComponent(orig, copyno)
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VCDCDetectorComponent::~J4VCDCDetectorComponent()
{	
   if(Deregister(fMaterialStore)) delete fMaterialStore;
   if(Deregister(fParameterList)) delete fParameterList;
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VCDCDetectorComponent::OpenMaterialStore()
{
   if(!fMaterialStore) {
   	fMaterialStore = new J4CDCMaterialStore();
        Register(fMaterialStore);
  	G4cerr << "*** Opend J4CDCMaterialStore ***" << G4endl;
   }
    
   return fMaterialStore;
}

//=====================================================================
//* OpenParameterList -------------------------------------------------

J4CDCParameterList* J4VCDCDetectorComponent::OpenParameterList()
{
   if(!fParameterList) {
      fParameterList = new J4CDCParameterList();
      Register(fParameterList);
      G4cerr << "*** Opend J4CDCParameterList ***" << G4endl;
   }

   return fParameterList;
}

