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
J4IRParameterList* J4VIRDetectorComponent::fParameterList = 0;

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
                                G4int                 copyno ,
				G4bool                reflection):
                       J4VDetectorComponent(fSubGroup, name, 
                         		      parent, nclones,	 
                         		      nbrothers, me, copyno  ),
			fReflection(reflection)
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
   if(Deregister(fParameterList)) delete fParameterList;
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

//=====================================================================
//*   --------------------------------------------------------
G4RotationMatrix* J4VIRDetectorComponent::GetRotation(){
  G4RotationMatrix* rot = new G4RotationMatrix;
  return rot;
}
G4ThreeVector&  J4VIRDetectorComponent::GetTranslation(){
  G4ThreeVector* p = new G4ThreeVector;
  return *p;
}
//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VIRDetectorComponent::InstallIn(J4VComponent *mother,
                             G4RotationMatrix     *prot, 
                             const G4ThreeVector  &tlate )
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  G4UserLimits* myLimits = new G4UserLimits;
  GetLV()->SetUserLimits(myLimits);

  // Placement function into mother object...
  G4ThreeVector position = tlate;
  G4RotationMatrix* rotation = prot;
  if ( prot == 0 && tlate==0 ) {
    rotation = GetRotation();
    position = GetTranslation();
    if ( fReflection ){
      position.setZ(-position.z());
      G4double angle = (rotation->getAxis()).y()*rotation->getDelta();
      angle = 180.*degree - angle*2.;
      rotation->rotateY(angle);
    } 
  }

    SetPVPlacement(rotation,position);
    
    if ( !GetSD()) Cabling();
}




