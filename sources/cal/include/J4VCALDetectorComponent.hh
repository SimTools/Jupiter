// $Id$
#ifndef __J4VCALDETECTORCOMPONENT__
#define __J4VCALDETECTORCOMPONENT__
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

#include "J4CALMaterialStore.hh"
#include "J4VDetectorComponent.hh"
#include "J4CALParameter.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCALDetectorComponent : public J4VDetectorComponent
{	// abstruct class

public:
  //default constructor...
  J4VCALDetectorComponent( const G4String       &name, 
  			   J4VDetectorComponent *parent    = 0,
                           G4int                 nclones   = 1,
                           G4int                 nbrothers = 1, 
                           G4int                 me        = 0,
                           G4int                 copyno    = -1 );
  virtual ~J4VCALDetectorComponent();
#if 0 		          
  J4VCALDetectorComponent(J4VCALDetectorComponent& right);
  virtual const J4VCALDetectorComponent& 
  		operator=(const J4VCALDetectorComponent& right);    
#endif
      
protected:    
  J4VMaterialStore* 	 OpenMaterialStore();
  
private:
  static J4CALMaterialStore* fMaterialStore;
  static G4String fSubGroup;
       
};

#if 0
//=====================================================================
//---------------------
// inline function
//---------------------


inline J4VCALDetectorComponent::J4VCALDetectorComponent(J4VCALDetectorComponent& right)
{

  fMaterialStore = right.fMaterialStore;
  fSubGroup      = right.fSubGroup;
          
}

inline const J4VCALDetectorComponent& 
J4VCALDetectorComponent::operator=(const J4VCALDetectorComponent& right)
{

  fMaterialStore = right.fMaterialStore;
  fSubGroup      = right.fSubGroup;
  
  return *this;
            
}

#endif



#endif


