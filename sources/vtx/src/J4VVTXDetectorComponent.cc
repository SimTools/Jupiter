// $Id$
//*************************************************************************
//* -----------------------
//* J4VVTXDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VVTXDetectorComponent.hh"

J4VTXMaterialStore* J4VVTXDetectorComponent::fMaterialStore = 0;
J4VTXParameterList* J4VVTXDetectorComponent::fParameterList = 0;

G4String J4VVTXDetectorComponent::fSubGroup("VTX");

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------

J4VVTXDetectorComponent::J4VVTXDetectorComponent(
			   	const G4String       &name, 
  			   	J4VDetectorComponent *parent,
                                G4int                 nclones,
                                G4int                 nbrothers, 
                                G4int                 me,
                                G4int                 copyno ) :
                         J4VDetectorComponent(fSubGroup, name, 
                         		      parent, nclones,	 
                         		      nbrothers, me, copyno  ),
                         fUserLimits(0)   
{ 
}

J4VVTXDetectorComponent::J4VVTXDetectorComponent(
                               const J4VVTXDetectorComponent &orig, 
                                     G4int                    copyno)
                        :J4VDetectorComponent(orig, copyno), 
                         fUserLimits(orig.fUserLimits)   
{ 
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VVTXDetectorComponent::~J4VVTXDetectorComponent()
{	
   if(Deregister(fMaterialStore)) delete fMaterialStore;
   if(Deregister(fParameterList)) delete fParameterList;
   if(Deregister(fUserLimits))    delete fUserLimits;
}

//=====================================================================
//* SetMaxAllowedStep

void J4VVTXDetectorComponent::SetMaxAllowedStep(G4double maxStep){

    if (fUserLimits) {
       TBookKeeper::GetBookKeeper()->Deregister(fUserLimits);
       delete fUserLimits;  
    }

    fUserLimits = new G4UserLimits;
    Register(fUserLimits); 
    fUserLimits->SetMaxAllowedStep(maxStep);
    GetLV()->SetUserLimits(fUserLimits);

} 
//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VVTXDetectorComponent::OpenMaterialStore()
{
   if(!fMaterialStore) {
   	fMaterialStore = new J4VTXMaterialStore();
        Register(fMaterialStore);
  	std::cerr << "*** Opend J4VTXMaterialStore ***" << std::endl;
  }
    
   return fMaterialStore;
}

//=====================================================================
//* OpenParameterList -------------------------------------------------

J4VTXParameterList* J4VVTXDetectorComponent::OpenParameterList()
{
  if(!fParameterList) {
    fParameterList = new J4VTXParameterList();
    Register(fParameterList);
    std::cerr << "*** Opend J4VTXParameterList ***" << std::endl;
  }

  return fParameterList;
}



